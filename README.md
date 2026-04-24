*This project has been created as part of the 42 curriculum by ryildiri, asari.*

---

# minishell

## Description

**minishell** is a project from the 42 school curriculum that challenges students to build a functional Unix shell from scratch in C. The goal is to deeply understand how shells work under the hood: how they parse and interpret command-line input, manage processes, handle file descriptors, and implement built-in commands.

The shell supports interactive use with a prompt, command history, and handles a significant subset of bash behavior — including pipes, redirections, environment variables, and signals — while managing memory correctly and handling edge cases robustly.

**Implemented features:**

- Interactive prompt with command history (via `readline`)
- Command execution through `PATH` or absolute/relative paths
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Redirections: `<`, `>`, `>>`, and `<<` (heredoc)
- Pipes `|` to chain commands
- Environment variable expansion (`$VAR`, `$?`)
- Single and double quote handling
- Signal handling: `Ctrl+C`, `Ctrl+D`, `Ctrl+\`

---

## Instructions

### Requirements

- A Unix-based system (Linux or macOS)
- `readline` library
- `make`

Install readline if needed:

```bash
# macOS
brew install readline

# Debian/Ubuntu
sudo apt-get install libreadline-dev
```

### Compilation

```bash
git clone https://github.com/ryildiri/minishell.git
cd minishell
make
```

| Rule | Effect |
|---|---|
| `make` | Compiles the project |
| `make clean` | Removes object files |
| `make fclean` | Removes object files and the executable |
| `make re` | Full recompilation |

### Execution

```bash
./minishell
```

---

## Resources

### Documentation

- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [POSIX Shell Specification](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- [readline Documentation](https://tiswww.case.edu/php/chet/readline/readline.html)

### Key Man Pages

- `man 2 fork`, `man 3 execve`, `man 2 pipe`, `man 2 dup2`, `man 2 waitpid`, `man 2 sigaction`

### Articles

- [Writing a Shell in C — Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [The TTY demystified](https://www.linusakesson.net/programming/tty/)

### Testers

- [minishell_tester by LucasKuhn](https://github.com/LucasKuhn/minishell_tester)
- [42 minishell tester by zstenger](https://github.com/zstenger93/42_minishell_tester)

### AI Usage

- **Testing** — Creating challenging tests for the program
- **Concept Explanations** — Explaining how `dup2`, heredocs, and signal processing interact
- **Architectural Evaluation** — "The good and bad aspects of the project architecture are listed, and recommendations are received, such as the classification structure, appropriate file and function naming conventions"

Artificial intelligence was not used in the creation or writing of any core application. All code was written and understood by the project authors.