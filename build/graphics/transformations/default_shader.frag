#version 460

layout (location = 0) out vec4 out_color;

layout (binding = 1, std140) uniform u_material
{
    vec3 diffuse;
}
material;

void main()
{
    out_color = vec4(material.diffuse, 1.0);
}