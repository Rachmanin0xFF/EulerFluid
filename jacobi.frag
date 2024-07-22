
#version 330

out vec4 frag_color;
in vec2 texture_coord;

uniform sampler2D TEX;

uniform vec2 RES;
uniform float dt;

// Encode

void main() {
    vec2 uv = gl_FragCoord.xy;
    vec2 step_size = 2.0/RES.xy;

    // solve for pressure (assuming navier-stokes incompressible) with Jacobi iterative method
    // todo: fix this up
    vec4 current_cell = texture2D(TEX, texture_coord);
    frag_color.xyz = current_cell.xyz;
    frag_color.w = 0.25*(current_cell.z +
          texture2D(TEX, texture_coord + vec2(step_size.x, 0.0)).w
        + texture2D(TEX, texture_coord + vec2(-step_size.x, 0.0)).w
        + texture2D(TEX, texture_coord + vec2(0.0, step_size.y)).w
        + texture2D(TEX, texture_coord + vec2(0.0, -step_size.y)).w
    );
}