#version 410 core

out vec4 color;

in vec3 light_vertex;
in vec3 light_normal;
in vec2 uv;

uniform sampler2D tex_base_color;

void main()
{
    vec3 base_color = texture(tex_base_color, vec2(uv.x, 1 - uv.y)).xyz;
    
    float lambert = clamp(dot(light_vertex, light_normal), 0, 1);
    color = vec4(vertex_color * lambert, 1);
}