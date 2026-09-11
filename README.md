# pipex

A reimplementation of the shell pipeline in C. `./pipex infile cmd1 cmd2
outfile` does what `< infile cmd1 | cmd2 > outfile` does, built from `pipe`,
`fork`, `dup2` and `execve`: one child per command, each with its standard
input and output rewired onto the pipe before the executable replaces it.
Commands are resolved against `PATH` the way a shell resolves them, so the
arguments are plain command strings rather than absolute paths. The bonus
binary generalises the same structure to any number of commands and adds
`here_doc`, which feeds the pipeline from standard input up to a delimiter
instead of from a file.

## Build and run

Requirements on the host: a C compiler and `make`. Nothing else, no external
libraries. The bundled `libft` is built first by the project's Makefile.

```bash
make          # pipex, two commands
make bonus    # pipex_bonus, N commands and here_doc
make fclean   # removes the binaries, the library and the objects
```

```bash
# < in.txt grep pere | wc -l > out.txt
./pipex in.txt "grep pere" "wc -l" out.txt

# any number of commands
./pipex_bonus in.txt cat "grep e" sort "uniq -c" out.txt

# here_doc: reads standard input until the delimiter, then pipes it,
# and appends to the outfile instead of truncating it
./pipex_bonus here_doc EOF cat "wc -l" out.txt
```

Failures are reported on standard error and stop the pipeline: an unreadable
infile, an outfile that cannot be created, a command that is not in `PATH`.

Compiled without warnings with clang on macOS (arm64) and with gcc 12 on Debian
(x86_64 and aarch64). Checked under valgrind on Linux, including the error
paths: no leaks, no invalid reads.

## Repository layout

```
.
├── pipex.c             # entry point, two commands
├── pipex.h
├── forking.c           # fork, the first and last child, execve
├── utils1.c            # PATH lookup, pipe and struct setup
├── utils2.c            # error exit and file descriptor cleanup
├── bonus/
│   ├── pipex_bonus.c   # entry point, N commands
│   ├── pipex_bonus.h
│   ├── forking_bonus.c # the middle children of the pipeline
│   ├── here_doc.c      # reads stdin up to the delimiter
│   └── utils_bonus.c   # closes the pipes a given child does not use
└── libft/              # the library, as published in redei-ma/libft
```
