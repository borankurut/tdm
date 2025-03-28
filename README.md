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
- **Quaternions (only rotation)**: Basic type definition (WIP)

### Features
- Robust canonicalization for angles and polar coordinates
- Efficient matrix inversion via adjugate/cofactors
- Edge-case handling (zero vectors, singular matrices)

### Testing
- Test coverage with Catch2
- Validation of:
  - Vector operations
  - Matrix operations (determinants, inverses)
  - Vector transformations
  - Angle wrapping and conversions
  - Polar ↔  Cartesian coordinate conversions
  - Euler angles operations

## Getting Started

### Installation
Build it as a static library and use it in your project.
A better cmake file will be added later

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

## Roadmap

### Planned Features
- **Quaternion operations**: SLERP, conjugation, and conversion to/from matrices
- **Geometric primitives**: Axis-Aligned Bounding Box (AABB), Ray, Plane
- **Camera matrices**: `lookAt` view matrices and perspective projection matrices
- **Calculus**

