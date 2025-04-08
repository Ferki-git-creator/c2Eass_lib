

---

# eass.h – Easy Syntax Library for C 🚀

<div align="center">
  <h2>Transforming C into a Python-like Experience!</h2>
  <p>
    Say goodbye to the pain of <code>printf("%d")</code> and welcome the simplicity of <strong>eass.h</strong> – a single-header library that makes C programming fun and intuitive! 😎
  </p>
  <img src="https://via.placeholder.com/600x150?text=Easy+Syntax+Library+for+C" alt="eass.h Banner">
</div>

---

## Overview 📚

**eass.h** is a header-only library designed for:
- **Newbies and seasoned programmers alike:** Enjoy a cleaner, Python-inspired syntax in your C projects.
- **Cross-platform development:** Fully supported on **Windows**, **Linux**, **macOS**, and **Android** (via Cxxdroid).
- **Embedded systems:** Minimal overhead and a straightforward API for resource-constrained environments.

The library is built to reduce boilerplate, making common tasks—like printing to the console and reading user input—a breeze.

---

## Key Features ✨

- **Simplified I/O:**  
  - `print()`: Automatically detects data types and prints without the hassle of format specifiers.
  - `input()`: Reads console input and auto-converts to the appropriate type (integer, float, or string).
- **Dynamic Arrays:**  
  Python-like dynamic arrays that automatically expand as needed.
- **Context Managers:**  
  Macros for automatic resource management that ensure your resources are properly released.
- **Hex/Binary Output:**  
  `printhd()` prints numbers in both hexadecimal and binary, perfect for debugging.
- **Single-file simplicity:**  
  Everything you need is in one file – no extra dependencies or complex build systems.
- **Cross-Platform Compatibility:**  
  Works seamlessly on **Windows**, **Linux**, **macOS**, and **Android** (use with Cxxdroid).

---

## How to Use 🛠️

### Installation

Simply download the single header file `eass.h` from [GitHub](https://github.com/you/eass) and place it in your project's include directory. For Android users, copy it into:

/storage/emulated/0/Android/data/com.cxxdroid/files/

### Usage Example

Simply compile your project with your favorite C compiler. No CMake configuration or extra build steps are required – just include the header and start coding!


---

Supported Platforms 🌐

Windows

Linux

macOS

Android (via Cxxdroid)


This versatility means you can write code on your desktop, laptop, or even on your mobile device. Perfect for learning on the go! 📱


---

Why eass.h? 💡

Ease-of-Use: Perfect for beginners and those transitioning from high-level languages like Python.

Simplicity: One file does it all – no clutter, no unnecessary files. Your GitHub repository will only contain:

eass.h

README.md

LICENSE


Performance & Portability: Designed to work across platforms, including embedded systems, without sacrificing performance.

Community-Driven: Contributions, bug reports, and feature requests are welcome! Let's build a better C ecosystem together.



---

For questions or contributions, please reach out via email: denisdola278@gmail.com.


---

<div align="center">
  <h3>Get Started Today!</h3>
  <p>Embrace the ease of Python-like syntax in C and boost your productivity! 🎉</p>
  <a href="https://github.com/you/eass" target="_blank">
    <img src="https://img.shields.io/badge/GitHub-eass.h-blue?style=for-the-badge" alt="GitHub eass.h">
  </a>
</div>
---

Additional Tips & Improvements 🔧

Modular Extensions: As you grow with eass.h, consider extending its functionality with additional modules while keeping the core minimal.

Community Engagement: Join the conversation on GitHub. Share your projects, provide feedback, and help others learn.

Best Practices: Although the library is designed for simplicity, always keep an eye on best practices in memory management and error handling when integrating into larger projects.


Happy coding and enjoy the new, simplified C experience! 🚀😊


### Example
```c
#include <eass.h>

int main(void) {
    // Print a greeting without the need for format specifiers
    print("Hello, world!"); // Simple output 🎉

    // Read an input into the variable 'age'
    int age;
    input(age); // Auto type detection in action!

    // Using dynamic arrays (if available)
    // array_create, array_push, etc. make managing collections easy!

    return 0;
}

---
