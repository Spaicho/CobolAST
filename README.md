# Cripple Cobol Compiler

CCC is prototye for an Incremental Compiler front-end of a subset (for the moment) of IBM Enterprise COBOL language.
It's written in C language, Cross platform (i.e : support compiling on IBMC, GNUC and MSC), and is a work in progess.

The compiler produces an Abstract sytax tree that can be manipulated.
The inital requirement was to be able to refactor poorly written code and translate chunks of code in order to enhance performance and reduce MIPS/costs on mainframes (e.g : replacing INITIALZE statements by MOVE statements).

The compiler integrate with the mainframe Developer Environment i.e "z/OS ISPF Text Editor" using a REXX script and Edit Macro. 
Integration with Other text editor (Notepad++, Eclipse) is intended.

Below is a printing of the AST built for a MOVE statement :

-> Put here a screen shot of a complex move statement and its generated AST <-

## Architecture Overview

The complier is written from scratch and make no use of Lexer/Parser generator (e.g Flex/Bison).

### Lexical Analysis

Lexical analysis is done using Regular expression.
It generates tokens ready to conusme by the parser.
Cobol have a context-sensitive lexing, so a context si shared between Lexer and parser.

### Grammar Analysis

Cobol has context-sensitive grammar, 
The parsing is done by implementing a Recursive Descent Parser.
It generates an AST.

See link beside for EBNF Cobol grammar : http://www.cs.vu.nl/grammarware/vs-cobol-ii/
See file grammar.h, for the supported subset of Cobol Grammar.


### Abstract Syntax Tree 

The Abstract Syntax tree is implemented using simple Linked lists.
Advanced Semantic inspection is done on the generated AST for further analysis and elimination.


### AST refactoring 

*Not implemented yet.*

### AST Translation 

*Not implemented yet.*

