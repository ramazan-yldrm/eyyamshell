# 🐚 Eyyamshell (Minishell)

A beautiful, minimal bash-like shell built from scratch in C for the Ecole 42 curriculum. This project delves deep into Unix processes, file descriptors, signals, and abstract syntax tree parsing.

![C](https://img.shields.io/badge/Language-C-blue.svg)
![Norminette](https://img.shields.io/badge/Norminette-Passing-success.svg)
![Memory](https://img.shields.io/badge/Memory-Zero%20Leaks-success)

---

## 📜 About The Project

"As beautiful as a shell." 
The objective of this project is to create a simple, yet robust Unix shell. It replicates fundamental functionalities of `bash`, giving deep insights into how a command interpreter operates under the hood.

## ✨ Features (Subject Requirements)

Eyyamshell strictly adheres to the 42 Minishell subject requirements:

- **Interactive Prompt:** Displays a prompt and waits for user input.
- **History:** Maintains a working command history using the `readline` library.
- **Execution:** Searches and launches executables via the `PATH` environment variable, or via absolute/relative paths.
- **Quote Handling:**
  - `'` (Single quotes) prevent interpretation of meta-characters.
  - `"` (Double quotes) prevent interpretation of meta-characters except for `$`.
- **Redirections:**
  - `<` : Redirects input.
  - `>` : Redirects output.
  - `<<` : Heredoc (reads input until a delimiter is found).
  - `>>` : Redirects output in append mode.
- **Pipes (`|`):** Connects the output of one command to the input of the next.
- **Environment Variables:** Expands `$VAR` to its corresponding value.
- **Exit Status:** Expands `$?` to the exit status of the most recently executed foreground pipeline.
- **Signal Handling:**
  - `ctrl-C` : Displays a new prompt on a new line.
  - `ctrl-D` : Exits the shell safely.
  - `ctrl-\` : Does nothing in interactive mode.
- **Built-in Commands:**
  - `echo` (with `-n` flag)
  - `cd` (relative or absolute path only)
  - `pwd` (without options)
  - `export` (without options)
  - `unset` (without options)
  - `env` (without options/arguments)
  - `exit` (without options)

## 🛠️ Architecture & Under the Hood

- **Lexer & Parser:** Reads the raw string, breaks it into meaningful tokens (words, pipes, redirections), and constructs a command execution table.
- **Expander:** Handles environment variable substitutions and quote removals seamlessly.
- **Executor:** Manages child processes (`fork`), replaces process images (`execve`), and carefully wires file descriptors using `pipe` and `dup2`.
- **Garbage Collector (GC):** A custom built memory management system (`t_gc`) ensuring that allocations (both permanent and temporary) are tracked and properly freed, guaranteeing a leak-free shell.

## 🚀 Getting Started

### Prerequisites
- `gcc` or `clang`
- `make`
- `readline` library

### Installation
Clone the repository and compile using the provided Makefile:
```bash
git clone <your_repository_url> eyyamshell
cd eyyamshell
make
```

### Usage
Start the interactive shell:
```bash
./minishell
```

## 🧹 Cleaning Up
To remove object files:
```bash
make clean
```
To remove object files and the executable:
```bash
make fclean
```
To recompile from scratch:
```bash
make re
```

---
*Created for the 42 Network Curriculum.*
