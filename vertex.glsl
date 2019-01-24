#version 410 core

layout(location=0) in vec3 vertex;
layout(location=1) in vec3 input_color;
out vec3 vertex_color;

uniform float x;
uniform float y;

vec3 rotate_y(vec3 v, float rot)
{
    vec3 vo;
    vo.x = cos(rot) * v.x - sin(rot) + v.z;
    vo.y = v.y;
    vo.z = sin(rot) * v.x + cos(rot) + v.z;
    return vo;
}

float linear_convert(float value, float old_min, float old_max, float new_min)
{
    float gradient = (value - old_min) / (old_max - old_min);
    return new_min + gradient * (new_max - new_min);
}

void main()
{
    // gl_Position = vec4(0, 0, 0, 1);

    // if (gl_VertexID == 0)
    // {
    //     gl_Position = vec4(0, 0, 0, 1);
    //     vertex_color = vec3(1, 1, 0);
    // }
    // if (gl_VertexID == 1)
    // {
    //     gl_Position = vec4(0.5, 0, 0, 1);
    //     vertex_color = vec3(0, 0, 1);
    // }
    // if (gl_VertexID == 2)
    // {
    //     gl_Position = vec4(0.5, -0.5, 0, 1);
    //     vertex_color = vec3(0, 1, 0);
    // }

    // vertex_color = gl_Position.xyz;

    gl_Position = vec4(vertex.x + x, vertex.y + y, vertex.z, 1);
    vertex_color = input_color;
}