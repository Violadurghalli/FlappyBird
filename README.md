# 🐦 Flappy Bird (C++ / SFML)

A simple clone of the classic **Flappy Bird** game built using **C++** and the **SFML (Simple and Fast Multimedia Library)**.
Navigate the bird through pipes, avoid collisions, and aim for the highest score!

---

## 🎮 Features

* Classic Flappy Bird gameplay
* Smooth 2D graphics using SFML
* Real-time input handling
* Collision detection
* Score tracking system
* Lightweight and fast

---

## 🛠️ Tech Stack

* **C++**
* **SFML (Simple and Fast Multimedia Library)**

---

## 📦 Installation

### 1. Clone the Repository

```bash
git clone https://github.com/Violadurghalli/FlappyBird.git
cd FlappyBird
```

---

### 2. Install SFML

#### On macOS (using Homebrew)

```bash
brew install sfml
```

#### On Ubuntu

```bash
sudo apt-get install libsfml-dev
```

#### On Windows

* Download SFML from: https://www.sfml-dev.org/download.php
* Set up include and library paths in your compiler/IDE

---

### 3. Build the Project

#### Using g++

```bash
g++ main.cpp -o flappybird -lsfml-graphics -lsfml-window -lsfml-system
```

*(Adjust file names if needed)*

---

## ▶️ Run the Game

```bash
./flappybird
```

---

## 🎯 Controls

| Key   | Action    |
| ----- | --------- |
| Space | Flap bird |
| Esc   | Quit game |

---

## 🧠 Game Mechanics

* Gravity constantly pulls the bird downward
* Pressing **Space** applies an upward force
* Pipes spawn at intervals with randomized gaps
* The player earns points by passing through pipes
* Collision with pipes or the ground ends the game

---

## 📁 Project Structure

```
FlappyBird/
│── src/
│   ├── main.cpp
│   ├── Bird.cpp / Bird.h
│   ├── Pipe.cpp / Pipe.h
│── assets/
│   ├── textures/
│   ├── sounds/
│── include/
│── CMakeLists.txt (optional)
```

*(Update this section to match your repo exactly)*

---

## 🚀 Future Improvements

* Add sound effects and music 🎵
* Start menu and game-over screen
* Difficulty scaling
* High score saving
* Better animations

---

## 🤝 Contributing

Contributions are welcome!

1. Fork the repository
2. Create your feature branch (`git checkout -b feature-name`)
3. Commit your changes
4. Push to the branch
5. Open a Pull Request

---

## 📄 License

This project is licensed under the MIT License.

---

## 🙌 Acknowledgements

* Inspired by the original Flappy Bird game
* Built using SFML for graphics and input handling

---

## ⭐ Support

If you like this project, consider giving it a ⭐ on GitHub!
 
