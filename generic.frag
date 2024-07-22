
// generic shader for pasting textures to screen

#version 330

out vec4 frag_color;
in vec2 texture_coord;

uniform sampler2D TEX;


void main() {
    vec2 uv = gl_FragCoord.xy;
    frag_color = texture2D(TEX, texture_coord.xy)*0.1;
    //frag_color.x = frag_color.z;
    //frag_color.y = frag_color.z;
    frag_color = abs(sin(frag_color*20.0));
}