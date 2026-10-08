# Syntax Directed Translation (SDT) Schemes

[![Language](https://img.shields.io/badge/Language-C99%20%2F%20Lex%20%26%20Yacc-00599C.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Compiler](https://img.shields.io/badge/Translation-Synthesized%20Attributes%20%2F%20SDT-green.svg)](https://gcc.gnu.org/)
[![Course](https://img.shields.io/badge/Course-BCSE306L%20Compiler%20Design-red.svg)](https://vit.ac.in)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Author Information
- **Author:** Shrri Dharshan D R
- **GitHub:** [@shrridharshan27](https://github.com/shrridharshan27)
- **Registration Number:** `23BPS1090`
- **Course:** Compiler Design Laboratory (`BCSE306L`)
- **Lab Slot:** `L23+L24`

---

## Overview
This repository implements three fundamental **Syntax Directed Translation (SDT)** schemes:
1. **Expression Evaluation Scheme**: Synthesized attributes evaluating arithmetic calculations on parse tree reduction.
2. **Semantic Type Checking Scheme**: Decorates parse tree nodes with type attributes (`int`, `float`), verifying type safety in assignment statements via a Symbol Table.
3. **Infix to Postfix Translation Scheme**: Translates standard infix expressions into postfix notation suitable for execution on stack-based virtual machines.

---

## Compilation & Execution
```bash
# Compile and run SDT suite with GCC
gcc -std=c99 -Wall -Wextra src/sdt_suite.c -o build/sdt_suite
./build/sdt_suite
```

---

## License
MIT License - see [LICENSE](LICENSE) for details.
