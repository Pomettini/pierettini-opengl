#version 410 core

out vec4 color;

in vec3 light_vertex;
in vec3 light_normal;

void main()
{
    float lambert = clamp(dot(light_vertex, light_normal), 0, 1);
    color = vec4(vec3(1, 1, 1) * lambert, 1);
}