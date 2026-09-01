# Architecture Overview

## Purpose
This file describes how EPGC10 is put together: the layers the code is split into,
what each of the two build variants does, and where the platform-specific code lives.
For the interpreter internals see [interpreter.md](interpreter.md) and [lexer.md](lexer.md);
for wiring and assembly see [hardware.md](hardware.md).

## Layers
The source tree has three layers. The intended dependency direction is downward, with one
existing dependency from the evaluator to UI headers for shared globals:

```
src/port/esp32   src/port/sdl      platform: entry point, display, window size
        \             /
         src/ui                    screens, keypad handling, formatting, graphing
            |
         src/core/interpreter      lexer, parser, evaluator, error state
```

*   **`src/core/interpreter/`** — interpreter computation. Given a string it returns a
    `double`. Most of it has no display or platform code, but `evaluator.c` includes
    `app.h` and `status_bar.h` for the UI-owned `prev_ans` and `deg_rad`; the unit tests
    and the `repl` target still link without UI or LVGL sources.
*   **`src/ui/`** — everything the user sees, written against LVGL only. Screens, the
    on-screen text buffers, the status bar, the graphing canvas, the popups. It contains
    no `#ifdef`s for either platform.
*   **`src/port/<platform>/`** — the thin platform layer: the entry point, the display
    driver, and the window geometry.

`src/ui` and `src/core` are compiled from the same files by both builds, so a fix to
either one reaches the firmware and the simulator at once. That is the whole point of
the layout: before it existed the two lived on separate branches and drifted.

## The port contract
A platform has to supply an entry point plus the two hooks declared in
[../src/port/port.h](../src/port/port.h):

| Hook | ESP32 | SDL |
|------|-------|-----|
| `port_create_input()` | empty — the keys are physical (see gaps below) | builds the 54-button on-screen keypad |
| `port_create_graph_draw_buf()` | heap `lv_draw_buf_create()`, RGB565 | static `LV_DRAW_BUF_DEFINE_STATIC`, ARGB8888 |

The graph buffer is split because a static ARGB8888 buffer of that size does not fit in
ESP32 DRAM. Each port also owns its entry point and display setup. The port-specific
window geometry is defined in its own `port_config.h` (240x320 on the device, 370x770 in
the simulator, where the window also has to hold the on-screen keypad).

`components/lv_conf.h` is shared. Its three SDL-only options (`LV_USE_SDL`,
`LV_USE_LINUX_FBDEV`, `LV_USE_EVDEV`) are gated on the `EPGC10_SDL` define, which only the
simulator build sets. Both builds use the single LVGL submodule at `components/lvgl`;
LVGL locates its config as `<lvgl dir>/../lv_conf.h`, which is why that file sits in
`components/` rather than next to the sources.

## Startup and the main loop
Both entry points do the same three things in the same order — initialise LVGL and a tick
source, create a display, then hand over to the shared code:

```
esp32/main.c app_main()          sdl/main.c main()
  lv_init()                        lv_init()
  lv_tick_set_cb(esp_timer)        lv_tick_set_cb(SDL_GetTicks)
  ili9341_init() + lv_display      lv_sdl_window_create() + lv_sdl_mouse_create()
        \                              /
              app_create_ui()      creates every screen and popup up front,
                                   calls port_create_input(), sets SCREEN_INPUT
              app_run()            lv_timer_handler() / usleep(1000) forever
```

`app_create_ui()` builds *all* screens at startup and then shows and hides them;
there is no lazy construction and no teardown, so `current_screen` is what decides
where a keypress goes.

## What happens on a keypress
```
button (LVGL event, or the physical key once scanning exists)
  -> button_matrix_*_callback.c   dispatch on current_screen + shift/alpha
  -> text.c buffers               the expression is stored as an array of glyph strings
  -> "=" pressed: interpret(expr) core, returns a double
  -> error_present ? error_popup with error_message
                   : create_ans_label(ans) formats it and prev_ans is updated
```

Formatting lives in `create_ans_label()` in [../src/ui/input_area.c](../src/ui/input_area.c):
`NORMAL` is `%.10g`, `SCI` is `%e`, `ENG` is a mantissa/exponent pair, any result whose
string reaches 14 characters is re-printed as `%e`, and `inf`/`nan` become `∞`/`Error`.

## Shared state
The UI keeps its state in a handful of globals, each declared in the header of the module
that defines it:

| State | Defined in | Meaning |
|-------|-----------|---------|
| `current_screen` | `app.c` | which screen has focus; every keypad callback branches on it |
| `shift`, `alpha` | `app.c` | keypad modifier latches |
| `prev_ans` | `app.c` | the `Ans` variable, read by the evaluator |
| `deg_rad` | `status_bar.c` | angle mode: 0 degrees, 1 radians, 2 gradians |
| `display_format` | `status_bar.c` | `NORMAL` / `SCI` / `ENG` |
| `A`–`Z`, `x_value` | `evaluator.c` | user variables and the graphing x |

Because these are globals rather than a context struct, the interpreter is not reentrant
and one evaluation at a time is assumed. That is also why graphing has to save and restore
the angle mode around itself, as described next.

## Graphing
`draw_graph_func_canvas()` in [../src/ui/screen_graph.c](../src/ui/screen_graph.c) plots by
sweeping `x_value` across the visible range and calling `interpret()` once per pixel column,
so a plotted function goes through the full lex/parse/evaluate pipeline on every sample.
It forces `deg_rad = 1` for the sweep — graphs are drawn in radians regardless of the
calculator's angle mode — and restores the previous mode afterwards from a local snapshot.

## Building
Firmware (ESP-IDF v5.5.1). `main/CMakeLists.txt` is a thin component that registers
`../src/ui`, `../src/core/interpreter`, `../src/port/esp32` and `../fonts`, so the build
stays idiomatic ESP-IDF while the sources live outside `main/`:

```
idf.py build
idf.py -p <port> flash monitor
```

Simulator (CMake ≥ 3.20, SDL2):

```
cmake -S sim -B build-sim && cmake --build build-sim
./build-sim/ui              # the calculator, with the on-screen keypad
./build-sim/repl            # terminal REPL over interpret(), no display needed
./build-sim/test_lexer      # Unity tests
./build-sim/test_evaluator
```

## Tests and CI
Tests are host-only Unity tests under [../test](../test) and cover the interpreter, which is
the layer worth testing without hardware — `test_lexer.c` for tokenising and
`test_evaluator.c` for evaluation. `.github/workflows/ci.yml` runs on every push to `main`
and every pull request, and does two jobs: build the simulator and run both test binaries,
and build the firmware inside the `espressif/idf:v5.5.1` container.

## Known gaps
Documented deliberately, so nobody rediscovers them the hard way:

*   **No keypad scanning on the ESP32.** The hardware has a 9x6 matrix and
    [hardware.md](hardware.md) tells you how to wire it, but no firmware code reads those
    GPIOs, so `port_create_input()` is empty and the device takes no input yet. This is the
    piece standing between the firmware compiling and the calculator being usable; it
    belongs inside the ESP32 `port_create_input()`, feeding an LVGL input device, and the
    shared UI needs no changes for it.
*   **The firmware is only verified to compile.** CI builds a flashable image; nothing in
    this repository proves it runs on a device.
*   **Degree-mode trig carries conversion error.** `cos(90)` is computed as
    `cos(90 × π/180)`, and π/2 is not representable in a double, so the result is
    `6.123234e-17` rather than `0`. Same for `sin(180)`, `tan(180)`. Results are not
    snapped to a display precision.
*   **The interpreter leaks.** Tokens, AST nodes and function-argument strings are
    `malloc`'d per evaluation and never freed. Bounded on a PC; on the device it accumulates
    for as long as the calculator is on.
*   **Warnings are suppressed rather than fixed.** `main/CMakeLists.txt` passes
    `-Wno-parentheses -Wno-char-subscripts -Wno-switch`, and neither build sets `-Wall`.
    Compiling `src/` with `-Wall -Wextra` reports ~115 warnings, most stylistic but some
    genuine missing-return paths.
