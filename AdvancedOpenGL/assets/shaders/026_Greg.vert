
#version 450 core

in vec4 position;

out DATA_OUT
{
    vec2 uv;
} data_out;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform float timeT2;

void main(void)
{
    gl_Position = proj_matrix * mv_matrix * position;

    data_out.uv = (position.xy);
}
