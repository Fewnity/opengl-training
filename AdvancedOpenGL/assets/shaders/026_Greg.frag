#version 450 core

out vec4 color;
uniform float timeSin;
uniform float timeCos;

layout (binding = 0) uniform sampler2D tex0;
layout (binding = 1) uniform sampler2D tex1;
layout (binding = 2) uniform sampler2D tex2;
layout (binding = 3) uniform sampler2D tex3;

in DATA_OUT
{
    vec2 uv;
} data_in;

void main()
{
    vec4 colorTex0 = texture(tex0, data_in.uv);
    vec4 colorTex1 = texture(tex1, data_in.uv);
    vec4 colorTex2 = texture(tex2, data_in.uv);
    vec4 colorTex3 = texture(tex3, data_in.uv);

    color = colorTex0 * (1 - timeSin) +  colorTex1 * (timeSin) - colorTex2 * (timeCos) - colorTex3 * (1-timeCos) + vec4(0.5, 0.5, 0.5 ,0);
} 
