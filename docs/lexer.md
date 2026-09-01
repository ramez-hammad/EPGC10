# Lexer Documentation

## Purpose
This file documents [../src/core/interpreter/lexer.c](../src/core/interpreter/lexer.c) —
the first of the three interpreter stages, which turns an expression string into an array
of tokens. For the pipeline it feeds, see [interpreter.md](interpreter.md).

## Interface
```c
TOKEN *tokenize(const char *expr, int *array_size);
```

It returns a heap array of `array_size` tokens. The caller (the parser) owns it, and today
never frees it — see the memory note in [interpreter.md](interpreter.md).

## The token
```c
typedef struct TOKEN {
    TOKEN_TYPE type;
    char name;    // variables only
    double val;   // numbers only
    char *arg;    // functions only: the argument, still unparsed
} TOKEN;
```

The union-like layout is deliberate for its size: only one of `name`, `val`, `arg` is
meaningful, and which one is determined by `type`.

`TOKEN_TYPE` covers the operators (`+ - * / ^ ( ) = !`), `TOKEN_NUM`, `TOKEN_VAR`, one
constant per supported function, and `TOKEN_NULL` as the end/no-token marker.
`TOKEN_UNARY_PLUS` and `TOKEN_UNARY_MINUS` exist in the enum but are never produced here —
the parser derives them.

## How scanning works
One `while` loop over the string with a cursor `x`, and a `switch` on the current
character. Numbers are handled before the switch; everything else is a case.

There is no keyword table and no identifier scanning. **A function is recognised by testing
a single character at a fixed offset from its first letter**, which is possible because the
keypad inserts whole function names at once, so keypad-generated input is well-formed:

| First char | Test | Function | Argument starts at |
|-----------|------|----------|--------------------|
| `a` | `expr[x+2] == 's'` | `abs(` | `x+4` |
| `a` | `expr[x+3] == 's'`, `expr[x+6] == '('` | `arcsin(` | `x+7` |
| `a` | `expr[x+3] == 's'`, otherwise | `arcsinh(` | `x+8` |
| `a` | `expr[x+3] == 'c'` / `'t'` | `arccos`/`arctan`, same two shapes | `x+7` / `x+8` |
| `s` | `expr[x+3] == '('` | `sin(` | `x+4` |
| `s` | `expr[x+3] == 'h'` | `sinh(` | `x+5` |
| `s` | otherwise | `sqrt(` | `x+5` |
| `c` | `expr[x+3] == '('` / otherwise | `cos(` / `cosh(` | `x+4` / `x+5` |
| `t` | `expr[x+3] == '('` / otherwise | `tan(` / `tanh(` | `x+4` / `x+5` |
| `l` | `expr[x+1] == 'n'` / otherwise | `ln(` / `log(` | `x+3` / `x+4` |

Single characters are variables: `p` is π, `e` is Euler's number, `x` is the graphing
variable, `An` is `Ans` (emitted as a variable named `'n'`), and after the switch any
remaining `A`–`Z` becomes a variable of that name.

After a function token the cursor jumps past the whole call:
`x = x + <name length> + arg_width + 1`, plus the `x++` at the end of the loop, which lands
it on the character after the closing `)`.

## Numbers
Digits are accumulated into a scratch buffer and converted with `atof()`:

*   A digit starts the scan; further digits and at most one `.` are appended. A second `.`,
    or a `.` not followed by a digit, is a syntax error (`error(0)`).
*   A leading `.` is a case of its own: it synthesises the `0`, so `.5` becomes `"0.5"`.
    That is why the buffer is `strlen(expr) + 2` bytes and not `+ 1` — the synthesised `0`
    is one character the input did not contain.
*   The buffer is NUL-terminated at `num[num_width + 1]` before `atof()` reads it. It has to
    be: it is reused across tokens, so without the terminator `atof()` would keep reading
    into the digits of a previous number.

## Function arguments
```c
char *get_arg(const char *expr, size_t index, int *width);
```

`get_arg()` copies from `index` up to the `)` that closes the call, counting nested
parentheses so inner ones are kept and only the unbalanced `)` stops the scan. It reports
the length through `width` — the cursor arithmetic above depends on it — and returns a
freshly `malloc`'d, NUL-terminated string.

**Each function token gets its own allocation.** This is not incidental: the argument is
not evaluated until the evaluator reaches that node (see
[interpreter.md](interpreter.md)), so a buffer shared between tokens would have been
overwritten by then and every function in an expression would end up evaluating the last
argument parsed. `sin(30)+cos(0)` returned `1` instead of `1.5` for exactly that reason
before each token owned its string.

## Sizing
The token array starts at `malloc(strlen(expr) * sizeof(TOKEN))` — an upper bound, since no
token is shorter than one character — and is `realloc`'d down to `num_tokens` at the end.

## Caveats
*   The fixed-offset recognition assumes complete function names. A truncated identifier
    (`"s"`, `"co"`) makes the lexer read a few characters past the terminator, and an
    unrecognised character falls through the switch and produces no token at all rather than
    an error. Input from the keypad is always complete names, so this is reachable mainly
    from the `repl` target and from tests.
*   `=` has a token but no grammar rule; assignment is handled by the variable popup in the
    UI, not by the interpreter.
*   Whitespace is not skipped — nothing in the UI produces it.

## Tests
[../test/test_lexer.c](../test/test_lexer.c) covers the token count, the token types, the
numeric values (including `.5` and multi-digit decimals) and the extracted function
argument. It builds as `test_evaluator`'s sibling target in the simulator CMake and runs in
CI on every push and pull request.
