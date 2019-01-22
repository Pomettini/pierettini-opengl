#version 410 core

layout(location=0) in vec3 vertex;
layout(location=1) in vec3 input_color;
out vec3 vertex_color;

uniform float x;
uniform float y;

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