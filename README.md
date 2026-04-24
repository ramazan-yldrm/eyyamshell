*This project has been created as part of the 42 curriculum by ryildiri, asari.*

---

# 🐚 minishell

A minimal Unix shell implementation written in C — because understanding how bash works is better than just using it.

---

## Description

**minishell** is a project from the 42 school curriculum that challenges students to build a functional Unix shell from scratch in C. The goal is to deeply understand how shells work under the hood: how they parse and interpret command-line input, manage processes, handle file descriptors, and implement built-in commands.

The shell supports interactive use with a prompt, reads from a history, and handles a significant subset of bash behavior — including pipes, redirections, environment variables, and signals — all while managing memory correctly and robustly handling edge cases.

### Features

- **Interactive prompt** — displays a prompt and waits for user input
- **Command history** — navigable with arrow keys via `readline`
- **Command execution** — runs executables found via `PATH` or via absolute/relative paths
- **Built-in commands** — `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Redirections** — `<` (input), `>` (output), `>>` (append), `<<` (heredoc)
- **Pipes** — `|` chains commands by connecting `stdout` to `stdin`
- **Environment variables** — expansion of `$VAR` and `$?` (last exit status)
- **Quotes** — single quotes (`'`) prevent all expansion; double quotes (`"`) allow `$` expansion
- **Signals** — `Ctrl+C`, `Ctrl+D`, `Ctrl+\` handled as in bash

---

## Instructions

### Requirements

- A Unix-based system (Linux or macOS)
- `gcc` or `cc`
- `make`
- `readline` library installed

> On macOS, readline can be installed via Homebrew:
> ```bash
> brew install readline
> ```
> On Debian/Ubuntu:
> ```bash
> sudo apt-get install libreadline-dev
> ```

### Compilation

Clone the repository and build the project with `make`:

```bash
git clone https://github.com/your_login/minishell.git
cd minishell
make
```

This will produce an executable named `minishell` in the project root.

Other Makefile rules:

| Rule | Effect |
|---|---|
| `make` | Compiles the project |
| `make clean` | Removes object files |
| `make fclean` | Removes object files and the executable |
| `make re` | Full recompilation from scratch |

### Execution

```bash
./minishell
```

The shell will launch and display a prompt. You can then enter commands as you would in a standard terminal.

```
minishell$ echo "Hello, World!"
Hello, World!
minishell$ ls -la | grep .c
minishell$ export MY_VAR=42
minishell$ echo $MY_VAR
42
minishell$ exit
```

### Running without a TTY (non-interactive mode)

```bash
echo "ls -la" | ./minishell
```

---

## Usage Examples

```bash
# Pipes
minishell$ ls | grep main | wc -l

# Redirections
minishell$ cat < infile.txt > outfile.txt
minishell$ echo "append this" >> log.txt

# Heredoc
minishell$ cat << EOF
> line one
> line two
> EOF

# Environment variables
minishell$ export GREETING="hello"
minishell$ echo "$GREETING world"
hello world

# Exit status
minishell$ ls nonexistent
ls: cannot access 'nonexistent': No such file or directory
minishell$ echo $?
2
```

---

## Project Structure

```
minishell/
├── Makefile
├── README.md
├── includes/
│   └── minishell.h         # Main header — structs, enums, prototypes
├── src/
│   ├── core/               # Entry point, main loop
│   ├── lexer/              # Tokenization of raw input
│   ├── expander/			# $VAR and $? expansion
│   ├── parser/             # AST or command list construction
│   ├── executor/           # Fork, exec, pipe, redirection logic
│   ├── builtins/           # echo, cd, pwd, export, unset, env, exit
│   └── utils/              # Utility programs like Envarionmet, Signal, and garbage collection.
└── lib/                    # Your standard C library (if included as submodule)
```

---

## Resources

### Official Documentation

- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — the reference for expected shell behavior
- [POSIX Shell Specification](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) — formal standard for shell behavior
- [readline Documentation](https://tiswww.case.edu/php/chet/readline/readline.html) — GNU readline library API reference

### Key System Calls & Man Pages

- `man 2 fork` — process creation
- `man 3 execve` — executing a program
- `man 2 pipe` — inter-process communication
- `man 2 dup2` — file descriptor duplication
- `man 2 waitpid` — waiting for child processes
- `man 2 sigaction` — signal handling

### Articles & Tutorials

- [Writing a Shell in C — Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/) — excellent step-by-step tutorial on building a basic shell
- [Linux Process API — fork, exec, wait](https://man7.org/linux/man-pages/man2/fork.2.html)
- [The TTY demystified](https://www.linusakesson.net/programming/tty/) — deep dive into terminals, TTYs, and signals
- [Understanding File Descriptors](https://bottomupcs.com/ch01s03.html) — essential background for redirections and pipes

### Testing

- [minishell_tester by LucasKuhn](https://github.com/LucasKuhn/minishell_tester) — community test suite for minishell
- [42 minishell tester by zstenger](https://github.com/zstenger93/42_minishell_tester)

### AI Usage

AI assistance (Claude by Anthropic) was used in this project for the following purposes:

- **Debugging** — analyzing cryptic segfaults and memory issues, particularly in the parser and pipe chain logic
- **Understanding concepts** — getting clear explanations of how `dup2`, heredocs, and signal handling work in combination
- **Code review** — asking for feedback on structure and edge case coverage in the lexer and expander
- **README writing** — drafting and structuring this documentation file

AI was **not** used to generate core logic or to write implementations directly. All code was written and understood by the team members. AI served as an interactive reference tool, similar to using Stack Overflow or man pages.

---

## Authors

- **your_login** — [GitHub](https://github.com/your_login) | [42 Intra](https://profile.intra.42.fr/users/your_login)
- **partner_login** — [GitHub](https://github.com/partner_login) | [42 Intra](https://profile.intra.42.fr/users/partner_login)
