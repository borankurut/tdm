# 3D Math Library (tdm)

A lightweight C++ mathematics library for 2D/3D graphics, physics, and game development.

![C++](https://img.shields.io/badge/C++-17-blue?logo=cplusplus)
![License](https://img.shields.io/badge/License-MIT-green)
![Tests](https://img.shields.io/badge/Tests-100%25%20coverage-success)

## Features

### Core Components
- **Vectors**: `Vec2`, `Vec3`, `Vec4` with arithmetic operations, dot/cross products, normalization
- **Matrices**: `Mat2`, `Mat3`, `Mat4` with inversion, determinants, and matrix-matrix/vector multiplication
- **Coordinate Systems**:
  - Polar coordinates (`Polar2`, `Polar3`) with canonicalization
  - Euler angles with gimbal lock handling
- **Angles**: `Radian`/`Degree` conversions and arithmetic
- **Quaternions (only rotation)**: Arithmetic operations
- **Orientation matrices**: Matrices for object -> upright conversions and fast inverse using transpose

### Features
- Robust canonicalization for angles and polar coordinates
- Efficient matrix inversion via adjugate/cofactors
- Edge-case handling (zero vectors, singular matrices)
- Orientations and conversions (Euler, Quaternion, Matrix)

### Testing
- Test coverage with Catch2
- Validation of:
  - Vector operations
  - Matrix operations (determinants, inverses)
  - Vector transformations
  - Angle wrapping and conversions
  - Polar ↔  Cartesian coordinate conversions
  - Euler angles operations
  - Quaternion operations
  - Orientation matrix operations

## Getting Started

### Installation

1. **Install Dependencies**  
   Make sure Python and pip are installed. Then install Meson and Ninja:

   ```sh
   pip install meson ninja
   ```

2. **Configure the Build Directory**  
   If you're building the library only:

   ```sh
   meson setup build -Dbuild_examples=true
   ```

   If you want to enable tests:

   ```sh
   meson wrap install catch2
   meson setup build -Dbuild_tests=true
   ```

3. **Build the Library**

   ```sh
   meson compile -C build
   ```

4. **Run Tests (Optional)**

   ```sh
   meson test -C build
   ```

### Usage
```cpp
#include "tdm/vec3.h"
#include "tdm/polar3.h"
#include "tdm/mat3.h"

std::cout << " Determinant Example \n";
Mat3 B(342.0f, -42.0f, 53.0f, 11.9f, -31.57f, 0.05f, 99.0f, 21.0f, -3.0f);
std::cout << "Determinant of " << B << " is:" << B.determinant();

// Polar coordinates
tdm::Polar3 polar(5.0f, tdm::Radian(PI/4), tdm::Radian(PI/6));
tdm::Vec3 cartesian = polar.toCartesian();
```

## Integrating with Another Meson Project

To use `tdm` as a subproject in your own Meson project:

1. Create a `.wrap` file in your `subprojects/` folder named `tdm.wrap`:

   ```ini
   [wrap-git]
   url = https://github.com/borankurut/tdm.git
   revision = main

   [provide]
   tdm = tdm_dep
   ```

2. In your project's `meson.build` file, add:

   ```meson
   tdm_dep = dependency(
     'tdm',
     default_options: ['build_tests=false', 'build_examples=false'],
   )
   ```

3. Link the library in your targets:

   ```meson
   executable('my_app', 'main.cpp', dependencies: tdm_dep)
   ```

## Roadmap

### Planned Features
- **Geometric primitives**: Axis-Aligned Bounding Box (AABB), Ray, Plane
- **Camera matrices**: `lookAt` view matrices and perspective projection matrices
- **Calculus**

