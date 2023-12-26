# Nearly CC: compiler skeleton for the "Nearly C" C subset

This project is a compiler framework for the [Nearly C](https://github.com/daveho/nearly_c)
C subset front end. It contains the following components (in addition to the code provided
by `nearly_c`):

* A representation for C data types
* Symbol tables
* Linear intermediate representations for both "high-level" code
  (RISC-like, unlimited virtual registers) and low-level x86-64 code
* Control-flow graphs
* Generic dataflow analysis framework, with provided implementations
  for live values on both high-level and low-level IR
* Driver program with command line option handling

It omits implementation of the following components:

* Semantic analysis (type checking, insertion of implicit conversions)
* Code generation
* Optimization

This project was developed for the 601.428 Compilers and Interpreters
course at [Johns Hopkins University](http://www.jhu.edu/). The
[Fall 2023 course web page](https://jhucompilers.github.com/fall2023)
has the assignments in which students implement the missing parts.
(Note that the code in this repository has been refactored quite a bit,
so some minor details have changed.)  The Fall 2023 course also has
a [test repository](https://github.com/jhucompilers.github.com/fall2023-tests)
which is useful for testing code generation. (The `assign04` and
`assign05` subdirectories have the code generation tests.)

This repository is intended to be the official "public" release of
Nearly CC. It is in a somewhat preliminary form currently, but is
definitely at a point where it is useful. I will be adding documentation
and making improvements in the future.

Please send comments to <mailto:daveho@cs.jhu.edu>.
