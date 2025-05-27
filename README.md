<h1 align="center">🖥️ minishell</h1>

<p align="center">
  <i>A minimalist Unix shell implementation with essential features.</i>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue.svg" />
  <img src="https://img.shields.io/badge/Project-minishell-yellowgreen.svg" />
  <img src="https://img.shields.io/badge/Status-In%20Progress-orange.svg" />
</p>

---

## 📌 Project Overview

**minishell** is a Unix shell built from scratch as part of the 42 curriculum. It supports parsing and executing commands, handling built-in commands, managing environment variables, input/output redirections, pipes, and basic job control. The project emphasizes Unix system programming and process control.

---

## 🧠 Key Features

- Supports command parsing with quotes, escapes, and variable expansions  
- Implements essential built-in commands (`cd`, `echo`, `pwd`, `export`, etc.)  
- Handles environment variables, input/output redirections, and pipes  
- Includes heredoc support and basic signal handling (`CTRL+C`, `CTRL+D`)  
- Provides error reporting, exit status management, and custom prompt  

---

## 🚀 Getting Started

### 🔨 Build

```bash
git clone https://github.com/KGalstyan/minishell
cd minishell
make
