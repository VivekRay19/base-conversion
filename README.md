# 🔢 Base Conversion Utility

A command-line tool written in **C** that converts numbers between any two bases (from **Base 2** up to **Base 36**). It handles validation, digit mapping (0-9, A-Z), and error reporting.

## 🚀 Features
- **Flexible Inputs:** Supports any base between 2 (Binary) and 36 (Hexatrigesimal).
- **Command Line Arguments:** Uses flags to specify input/output configurations.
- **Error Handling:** Detects invalid digits for a specific base (e.g., 'G' in Hexadecimal).

## 🛠️ Compilation
Compile the program using GCC:
```bash
gcc -o base-convert base-convert.c
