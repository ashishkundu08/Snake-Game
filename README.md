# 🐍 Snake Game (C++ Console)

This is a simple **Snake Game** implemented in **C++**, using the **linked list** data structure to represent the snake’s body.

---

## 📌 Features
- Snake represented as a **singly linked list**:
  - Head = snake’s **tail** in game
  - Tail = snake’s **head** in game
- Snake grows whenever it eats food (`F`)
- Game ends if the snake hits:
  - The **boundary walls**
  - **Itself**
- Score increases with each food eaten
- Arrow keys control the snake’s movement
- Console-based graphics with line (`-`, `|`) boundaries

---

## 🛠️ Requirements
- C++ Compiler (e.g., **g++**, MinGW, or MSVC)
- Windows Console  
  *(for `_kbhit()` / `GetAsyncKeyState()`. On Linux, replace with `ncurses`.)*

---

## ▶️ How to Run
1. Clone this repository:
   ```bash
   git clone https://github.com/your-username/snake-game.git
   cd snake-game
