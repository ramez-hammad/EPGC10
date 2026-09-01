# Interpreter Documentation

## Purpose
This file documents the three-stage interpreter in
[../src/core/interpreter](../src/core/interpreter): how an expression string becomes a
number, what the grammar accepts, how errors and angle modes are handled, and which
design decisions are worth knowing before changing it. The lexer has its own file,
[lexer.md](lexer.md).

## The pipeline
```
"2(3+4)"  --lexer-->  TOKEN[]  --parser-->  NODE tree  --evaluator-->  14.0
            lexer.c              parser.c                evaluator.c
```

The single entry point is `interpret()` in `interpreter.c`:

```c
double interpret(const char *expr)
{
    double ans = evaluate(parse_expression_str(expr));

    if (num_paren != 0) {   // mismatched parentheses
        error(0);
        num_paren = 0;
    }

    return ans;
}
```

Nothing else in the codebase needs to call the stages individually; the UI calls
`interpret()` for the input line, for variable assignment, and once per pixel column
while graphing.

## Stage 1 — lexer
`tokenize()` turns the string into a `TOKEN[]`. See [lexer.md](lexer.md). Two properties
of the token stream matter to the rest of the pipeline:

*   A function token stores its argument as an **unparsed string** (`token.arg`), not as a
    sub-tree. `sin(1+2)` is one token whose `arg` is `"1+2"`.
*   Each function token owns its own copy of that string.

## Stage 2 — parser
`parser.c` is a hand-written recursive-descent parser producing a binary tree of `NODE`.
The grammar, in decreasing precedence:

```
expression -> term       (('+' | '-') term)*
term       -> exponent   (('*' | '/') exponent)*
exponent   -> factor     ('^' factor)*
factor     -> ('+' | '-') factor        unary
            | number ['!']
            | '(' expression ')'
            | variable ['!']
            | function                 the argument is kept as a string
```

Each level is a function — `parse_expression()`, `parse_term()`, `parse_exponent()`,
`parse_factor()` — and `parse_expression_str()` is the variant that lexes first.
`next_token(look_ahead)` walks the token array with `0` to consume, `1` to peek forward and
`-1` to peek back after the first token.

Three things happen here rather than in the evaluator:

*   **Implicit multiplication.** `parse_factor()` inserts a `TOKEN_MUL` into the token array
    (`insert_token()`) and carries on when a number or a function is followed by `(`, a
    variable or a function, and when a variable is followed by `(` or another variable. So
    `2(3+4)`, `2x` and `2sin(30)` all become explicit multiplications.
*   **Unary plus/minus.** The lexer only ever emits binary `TOKEN_PLUS`/`TOKEN_MINUS`;
    `parse_factor()` is what turns a leading sign into `TOKEN_UNARY_PLUS`/`TOKEN_UNARY_MINUS`.
*   **Factorial.** Computed at parse time by a loop, and folded into a literal node. A
    non-integer operand is a syntax error.

Syntax errors do not abort the parse. `parse_factor()` calls `error(0)` and then *repairs*
the token stream — usually by inserting a `0` literal, or a matching `)` — so parsing can
continue and produce a tree. The result is meaningless, but the caller has already been
told via `error_present`, and the UI discards the value and shows a popup.

The parser keeps its state in file-scope globals (`arr_tok`, `num_tokens`, `next_index`,
`num_paren`), so it handles exactly one expression at a time. Function arguments are parsed
during evaluation, once the outer parse has finished, which is why they can reuse the same
globals (see below).

## Stage 3 — evaluator
`evaluate(NODE *)` walks the tree recursively and returns a `double`. Operators evaluate
their children; literals return their value; variables are looked up.

Function nodes are the special case: since the argument is still a string, the evaluator
calls `evaluate(parse_expression_str(root->arg))`, i.e. the lexer and parser run *again*,
nested inside evaluation. Two consequences worth knowing:

*   Cost. A function argument is re-lexed and re-parsed every time the node is evaluated,
    and nested functions multiply that. It is invisible on a single expression, and it is
    the reason plotting is comparatively slow — graphing evaluates the whole tree once per
    pixel column.
*   Those nested parses reset the parser globals, but evaluation happens after the outer
    parse has completed, so no outer parser state needs to be restored.

### Angle modes
`deg_rad` (0 degrees, 1 radians, 2 gradians) is read directly by the trig cases:
forward functions convert the argument into radians (`deg_to_rad`, `grad_to_rad`) before
calling libm, and inverse functions convert the result back out (`rad_to_deg`,
`rad_to_grad`). `ln`, `log`, `sqrt` and `abs` are mode-independent.

Because degrees are converted through `π/180` in a double, degree-mode trig at the
quadrant boundaries is not exact: `cos(90)` yields `6.123234e-17`, not `0`. Results are not
rounded to a display precision anywhere.

### Variables
| Name | Meaning |
|------|---------|
| `A`–`Z` | user variables, defined in `evaluator.c`, set from the variable popup |
| `Ans` | the previous result — lexed as a variable named `'n'`, read from `prev_ans` |
| `x` | the graphing variable, read from `x_value`, which `screen_graph.c` sweeps |
| `p` | π |
| `e` | Euler's number |

`I` is `I_VAL` in the source because `I` is a macro in `<complex.h>`.

## Errors
`error.c` holds two globals and one function:

```c
extern char error_present;      // sticky flag, cleared by the caller
extern char error_message[17];  // "Division by zero" is 16 chars + NUL
void error(char code);          // 0 syntax, 1 division by zero, 2 argument
```

Any stage can call `error()`. The flag is what the UI checks after `interpret()` returns:
if it is set the returned value is discarded and `error_message` goes into the popup, and
the UI clears the flag. Nothing inside the interpreter clears it, so a host test must
reset `error_present` itself between cases.

## Memory
Every stage allocates and nothing frees: the token array, each function-argument string,
and every AST node are `malloc`'d per evaluation and leak. On a PC that is bounded by how
long you keep the process open; on the device it accumulates for as long as the calculator
is powered, and graphing allocates once per pixel column. Cleaning this up means either
freeing the tree after `evaluate()` or arena-allocating per `interpret()` call.

## Tests
Host-only Unity tests, built by the simulator CMake and run in CI:

*   `test/test_lexer.c` — token count, token types, numeric values, function arguments.
*   `test/test_evaluator.c` — division by zero sets the error and returns 0; normal
    division still works.

`test_lexer` links `lexer.c`; `test_evaluator` links the interpreter sources directly.
Neither links UI or display sources. `test_evaluator` defines `prev_ans` and `deg_rad`
because those live in the UI layer, which is also the one dependency pointing the wrong
way: `evaluator.c` includes `app.h` and `status_bar.h` to reach them.
