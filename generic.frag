
#version 330

out vec4 frag_color;
in vec2 texture_coord;

uniform sampler2D TEX;


void main() {
    vec2 uv = gl_FragCoord.xy;
    frag_color = texture2D(TEX, texture_coord.xy);
    frag_color = sin(frag_color*10.0);
}