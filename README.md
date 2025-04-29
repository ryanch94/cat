# cat
A scrappy reimplementation of the `cat` *nix utility in C. For education purposes only, not intended for production use.

## Building
Simple run `make` from the project directory, run `make debug` for a gdb debug build

## Current status
- [x] Print a single file passed to the program
- [x] Print the help info
- [x] Print the version info
- [x] Print line numbers when `-n` or `--number` param passed
- [x] `-A` / `--show-all` params implemented
- [x] `-b` / `--number-nonblank` params implemented
- [x] `-e` param implemented
- [x] `-E` / `--show-ends` params implemented
- [x] `-s` `--squeeze-blank` params implemented
- [x] `-t` param implemented
- [x] `-T` / `--show-tabs` params implemented
- [x] `-v` / `--show-nonprinting` params implemented
- [ ] Ability to concatenate multiple files passed to program
- [ ] Ability to pass stdin `-` to the program
