# Recursive Descent Parser

## Description
This project is a simple implementation of a recursive descent parser. It is designed to parse and interpret mathematical expressions.

## Features
- Mathematical expressions
- Variables     [ with chaining assignment ]  
- Configuration [ hex, dec & bin ]
- Supports addition, subtraction, multiplication, and division
- Handles parentheses to manage precedence

## Grammar

```
S: Statement
E: Rule (Expression)
T: Non-Terminal Symbols "Grammar Symbols" (Term)
F: (Factor)
+-*/()=: Terminal Symbols
```

```
S     -> ID [ ID | E ]+
S     -> ID = [ E | ID ]
E     -> T [ + | - T ]+
T     -> F [ * | / T ]+
F     -> ID | INT | FLOAT | (E) | -F
ID    -> ^[a-zA-Z][a-zA-Z0-9_]*$
INT   -> ^[-+]?[0-9]+$
```
