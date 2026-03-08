# TrEngine

Personal game engine (will be oriented towards both 2D and 3D), developed in my spare time for future use. The project is currently under development (WIP).

## Tech Stack
* **Language:** C++17
* **Graphics API:** OpenGL 4.5+
* **Windowing & Input:** GLFW
* **UI:** Dear ImGui
* **Build System:** Premake5
* **Logging:** spdlog

## Supported Platforms
* **Windows:** Tested on Windows 10/11 with GitHub Actions.
* **Linux:** Tested on Ubuntu 24.04 LTS with GCC/Make and GitHub Actions.

## Quick Start

### 0. Prerequisites
* **Windows:** C++ workload, generator (Visual Studio or similar).
* **Linux (Ubuntu/Debian):** Build essentials and required windowing packages:
  ```bash
  sudo apt update
  sudo apt install build-essential xorg-dev libglu1-mesa-dev

### 1. Clone the repository
Clone with submodules to fetch all required dependencies (GLFW, ImGui, Glad, spdlog, etc.):

```bash
git clone --recursive [https://github.com/tuonome/TrEngine.git](https://github.com/tuonome/TrEngine.git)