#version 460

layout (location = 0) in vec3 in_position;

layout (location = 0) uniform mat4    u_model;
layout (binding  = 0, std140) uniform u_camera
{
    mat4 view;
    mat4 proj;
}
camera;

void main()
{
    gl_Position = camera.proj * camera.view * u_model * vec4(in_position, 1.0);
}