
#version 330

out vec4 frag_color;
in vec2 texture_coord;

uniform sampler2D TEX0;

uniform vec2 mouse;
uniform vec2 dmouse;
uniform vec2 RES;
uniform float dt;
uniform float rho;
uniform float time;


void main() {
    vec2 uv = gl_FragCoord.xy;
    vec2 step_size = 1.0/RES.xy;

    vec4 current_cell = texture2D(TEX0, texture_coord);

    vec2 advected_vel = current_cell.xy;
    float pressure = current_cell.w;

    // calculate pressure differentials
    float dpdx = texture2D(TEX0, texture_coord + vec2(step_size.x, 0.0)).w 
                -texture2D(TEX0, texture_coord + vec2(-step_size.x, 0.0)).w;
    
    float dpdy = texture2D(TEX0, texture_coord + vec2(0.0, step_size.y)).w 
                -texture2D(TEX0, texture_coord + vec2(0.0, -step_size.y)).w;

    // accelerate using pressure information
    float euler_update_vel_x = advected_vel.x - 1.0*dt/(2*rho*step_size.x)*dpdx;
    float euler_update_vel_y = advected_vel.y - 1.0*dt/(2*rho*step_size.y)*dpdy;

    frag_color = vec4(euler_update_vel_x, euler_update_vel_y, 0.0, 1.0);

    // Mouse input!!!
    float R = length(gl_FragCoord.xy - mouse.xy);
    if(R < 40) {
        frag_color.x += 500.0*dt*(40.0-R)*dmouse.x/40.0;
        frag_color.y += 500.0*dt*(40.0-R)*dmouse.y/40.0;
    }

    frag_color.wz = current_cell.wz;
}