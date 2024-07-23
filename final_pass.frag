
#version 430

out vec4 frag_color;
in vec2 texture_coord;

layout(binding=0) uniform sampler2D TEX0;
layout(binding=1) uniform sampler2D TEX1;

uniform vec2 RES;
uniform float dt;
uniform vec2 mouse;
uniform float time;

uniform float rho;

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

float density_at(vec2 tc) {
    return texture2D(TEX1, tc).w*2.0 +
           texture2D(TEX0, tc).w*0.02;
}

float lum(vec3 color) {
  return dot(color, vec3(0.299, 0.587, 0.114));
}

void main() {
    vec2 uv = gl_FragCoord.xy;
    vec2 step_size = 2.0/RES.xy;

    vec4 A = texture2D(TEX0, texture_coord);
    vec4 B = texture2D(TEX1, texture_coord);
    float WL = density_at(texture_coord + vec2(-step_size.x, 0.0));
    float WR = density_at(texture_coord + vec2(step_size.x, 0.0));
    float WD = density_at(texture_coord + vec2(0.0, -step_size.x));
    float WU = density_at(texture_coord + vec2(0.0, step_size.x));

    float dWdx = (WR-WL)/step_size.x;
    float dWdy = (WU-WD)/step_size.y;

    vec3 dW = normalize(vec3(dWdx, dWdy, 1000.0));

    vec3 to_mouse = normalize(vec3(gl_FragCoord.xy - mouse.xy, 100));

    float luma = 0.6*dot(dW, to_mouse) / length(0.01*vec3(gl_FragCoord.xy - mouse.xy, 100));
    luma = max(luma, 0.0) + 0.1;

    vec3 eye_to_point = normalize(vec3(texture_coord*2.0 - 1.0, 4.0));
    vec3 refl = reflect(-to_mouse, dW);
    float spec = 2.0*pow(min(1.0, max(0.0, dot(eye_to_point, refl))), 40.0) / length(0.01*vec3(gl_FragCoord.xy - mouse.xy, 100));

    float luma2 = 0.6*dot(dW, normalize(vec3(-1.0, -1.0, 0.1)));
    luma2 = max(luma2, 0.0) + 0.1;
    //luma
    
    vec3 light = (spec + max(0.0, luma))*vec3(1.0);// + max(0.0, luma2)*vec3(1.0, 0.3, 0.1);
    //light = light*1.6 - vec3(0.5);

    frag_color.xyz = 1.8*(normalize(B.xyz));
    frag_color.xyz += 1.1*(1.0-dW.z)*normalize(texture2D(TEX1, texture_coord - dW.xy*0.05).xyz);

    frag_color.xyz *= pow(light, vec3(1.0/2.0));


    
    //frag_color.xyz = vec3(spec);
}