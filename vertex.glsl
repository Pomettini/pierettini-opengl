#version 410 core

layout(location=0) in vec3 vertex;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 model_uv;

out vec3 light_vertex;
out vec3 light_normal;
out vec2 uv;

uniform float rot;

vec3 rotate_y(vec3 v, float rot)
{
    vec3 vo;
    vo.x = cos(rot) * v.x - sin(rot) * v.z;
    vo.y = v.y;
    vo.z = sin(rot) * v.x + cos(rot) * v.z;
    return vo;
}

float linear_convert(float value, float old_min, float old_max, float new_min, float new_max)
{
    float gradient = (value - old_min) / (old_max - old_min);
    return new_min + gradient * (new_max - new_min);
}

void main()
{
    vec3 light = vec3(10, 0, 0);

    vec3 world_position = rotate_y(vec3(vertex.y, vertex.z, vertex.x), rot);

    float new_x = linear_convert(world_position.x, -200, 200, -1, 1);
    float new_y = linear_convert(world_position.y, -200, 200, -1, 1);
    float new_z = linear_convert(world_position.z, -200, 200, -1, 1);

    light_vertex = normalize(normal);
    light_normal = normalize(light - world_position);

    uv = normalize(model_uv);

    gl_Position = vec4(new_x, new_y, new_z, 1);
}