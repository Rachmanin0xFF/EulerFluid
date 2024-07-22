
#version 330

out vec4 frag_color;
in vec2 texture_coord;

uniform sampler2D TEX;

uniform vec2 RES;
uniform float dt;

// Encode

void main() {
    float dt = 0.01;
    float rho = 1.0;


    vec2 uv = gl_FragCoord.xy;
    vec2 step_size = 1.0/RES.xy;
    vec4 current_cell = texture2D(TEX, texture_coord);
    vec2 velocity = current_cell.xy;

    vec2 advected_vel = texture2D(TEX, texture_coord - velocity*dt).xy;
    frag_color = vec4(advected_vel, current_cell.z, current_cell.w);
}