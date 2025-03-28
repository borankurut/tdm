# Changelog

All notable changes to this project will be documented in this file.

---

## [v0.1.0] - Initial Release (Current)
### Core Implementation
**Added**  
- **Vector Types**  
  - `Vec2`, `Vec3`, `Vec4` with arithmetic operations, normalization, dot/cross products  
  - Static constants (e.g., `Vec3::Forward`, `Vec4::Zero`)  

- **Matrix Types**  
  - `Mat2`, `Mat3`, `Mat4` with:  
    - Matrix-matrix/matrix-vector multiplication  
    - Determinant calculations  
    - Inversion via adjugate method  
    - Identity/Zero static constants  

- **Coordinate Systems**  
  - `Polar2` and `Polar3` with canonicalization logic  
  - `Euler` angles with gimbal lock handling and angle wrapping  

- **Angles**  
  - `Radian` and `Degree` types with conversions and arithmetic  

- **Testing Infrastructure**  
  - Catch2 test suite covering:  
    - Vector/matrix operations  
    - Polar ↔  Cartesian conversions  
    - Euler angle canonicalization  
    - Edge cases (zero vectors, singular matrices)  

### Partial Implementation
- **Quaternions**  
  - Placeholder `Quaternion` class with `Identity` constant  

---

