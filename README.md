# Project Overview

This is a SQLite clone written in C that is largely based on the tutorial found [here](https://cstack.github.io/db_tutorial/).

# Modifications
- Part 1 ([75df135](github.com/bryanbritten/sqliter/commit/75df135f907aabdb7c4948acbc1cd7f8b16c7a19)):
  - Refactored the code to utilize function prototypes and move `main` closer to the top of the file.
  - Explicitly used `void` in functions where no parameters were required.
  - Added a Message of the Day to more closely replicate SQLite's REPL.
- Part 2 ([49aa674](github.com/bryanbritten/sqliter/commit/0cee866b155589b794b610ba43b5385f4633e1a2)):
  - Centralized program termination inside of `main` instead of in `handle_meta_command`.
  - Added additional `MetaCommandResult` enum members.