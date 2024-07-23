# EulerFluid

A GPU Eulerian (no particles) fluid simulation. Written for a daily challenge. Planning to implement in CUDA + OpenGL, starting with OpenGL for now.

Color transport is obviously unphysical, but the underlying velocity grid is solved via semi-Lagrangian advection and pressure-corrected with an ~80-iteration Jacobi solver.

Work-in-progress!



https://github.com/user-attachments/assets/eecc7453-63a0-4bc8-a31f-ee786a4b8d20



TODO:
* CUDA version
* Vorticity confinement
* Conjugate gradient solver
