# ShapeMixer

## Description
ShapeMixer is an interactive OpenGL application built with wxWidgets that demonstrates the integration of modern UI controls with real-time 2D graphics rendering. The application implements a **factory design pattern** for shape management, providing a scalable foundation for adding new shapes without modifying existing code. This design choice allows for easy application extension with new geometric primitives while maintaining a clean separation of concerns.

---

## Key Features
- A `wxGLCanvas`-based OpenGL rendering system that displays four distinct shapes: **Triangle, Square, Circle, and Julia Fractal**
- A transparent **overlay button** rendered directly in the OpenGL context, providing seamless integration with the 2D scene
- A dynamic control panel with intuitive UI elements:
  - Shape toggles using `wxCheckBox` controls
  - Precise position control through horizontal and vertical `wxSliders`
  - Scale adjustment via a dedicated `wxSlider`
  - A **Clear All** button for quick scene reset
- Robust event handling system that manages:
  - Mouse interactions with the overlay button
  - Window resizing events
  - Control panel visibility toggling
  - Real-time shape transformations

---

## Technical Implementation
- Factory pattern implementation for shape creation and management
- Proper OpenGL context handling throughout the application lifecycle
- Efficient resource management with **RAII** principles
- Clean separation between UI controls and rendering logic
- Responsive event handling system for smooth user interaction

---

## Demonstrated Concepts
- Modern C++ design patterns in graphics applications
- Integration of **wxWidgets** with **OpenGL**
- Real-time 2D graphics rendering and event-driven programming
- UI/UX design principles for desktop apps

---

## 🖥️ Windows Release

You can download the Windows executable from the GitHub release:  
👉 [ShapeMixer v1.0.0](https://github.com/abizyane/ShapeMixer/releases/tag/v1.0.0)

The ZIP archive includes:
- `ShapeMixer.exe`
- Required DLLs
- Icon and resources

No installation needed — just extract and run `ShapeMixer.exe`.

---

## ⚙️ Build Instructions

### Requirements
- **wxWidgets 3.2.x**
- **Visual Studio 2022** or CMake with MSVC
- **OpenGL and GDI+** (included in Windows SDK)

___