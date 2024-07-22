
#version 330

out vec4 frag_color;
in vec2 texture_coord;

uniform sampler2D TEX;

uniform vec2 RES;
uniform float dt;
uniform float rho;

// Encode

void main() {
    vec2 uv = gl_FragCoord.xy;
    vec2 step_size = 1.0/RES.xy;

    vec4 current_cell = texture2D(TEX, texture_coord);
    frag_color.xy = current_cell.xy;
    vec2 advected_vel = current_cell.xy;

    float divergence = -2.0 * step_size.x * rho / dt * (
          texture2D(TEX, texture_coord + vec2(step_size.x, 0.0)).x
        - texture2D(TEX, texture_coord + vec2(-step_size.x, 0.0)).x
        + texture2D(TEX, texture_coord + vec2(0.0, step_size.y)).y
        - texture2D(TEX, texture_coord + vec2(0.0, -step_size.y)).y
    );

    frag_color.z = divergence;

    frag_color.w = 0.0;
}