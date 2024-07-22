
#version 430

out vec4 frag_color;
in vec2 texture_coord;

layout(binding=0) uniform sampler2D TEX0;
layout(binding=1) uniform sampler2D TEX1;

uniform vec2 RES;
uniform float dt;
uniform vec2 mouse;
uniform float time;


float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
    vec2 uv = gl_FragCoord.xy;
    vec2 step_size = 1.0/RES.xy;

    vec4 A = texture2D(TEX0, texture_coord);
    vec4 B = texture2D(TEX1, texture_coord);

    vec2 velocity = A.xy;
    vec4 advect_B = texture2D(TEX1, texture_coord - velocity*dt);

    frag_color = advect_B;

    float R = length(gl_FragCoord.xy - mouse.xy);
    if(R < 50) {
        float w = time*3.0;
        vec3 color_wheel = vec3(sin(w), sin(w+2.0), sin(w+4.0))*0.5+0.5;
        frag_color.xyz += length(velocity)*0.02*color_wheel;
    }

    frag_color.xyz += frag_color.xyz * A.w * 0.00004;

    frag_color.xyz *= 0.995;

}