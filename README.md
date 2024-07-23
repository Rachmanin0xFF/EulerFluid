# EulerFluid

A GPU Eulerian (no particles) fluid simulation. Written for a daily challenge. Planning to implement in CUDA + OpenGL, starting with OpenGL for now.

Color transport is obviously unphysical, but the underlying velocity grid is solved via semi-Lagrangian advection and pressure-corrected with an ~80-iteration Jacobi solver.

Work-in-progress!

https://github.com/user-attachments/assets/ca54ad1d-5e3a-4eb9-b494-1a4738ce5574

TODO:
* CUDA version
* Vorticity confinement
* Conjugate gradient solver
