
// generic shader for pasting textures to screen

#version 330

layout(location = 0)in vec4 v_in;

out vec2 texture_coord;


void main() {
    gl_Position = v_in;
    texture_coord = v_in.xy*0.5 + vec2(0.5, 0.5);
}