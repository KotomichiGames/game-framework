#version 460

layout (location = 0) in vec3 in_position;

layout (binding = 0, std140) uniform u_camera
{
    mat4 view;
    mat4 proj;
}
camera;

void main()
{
    gl_Position = camera.proj * camera.view * mat4(1.0) * vec4(in_position, 1.0);
}