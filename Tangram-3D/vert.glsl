#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords; // Add texture coordinates input

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords; // Pass texture coordinates to fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    FragPos = vec3(model * vec4(position, 1.0f));
    Normal = mat3(transpose(inverse(model))) * normal; // Generate normal matrix (3x3) from model matrix (4x4)
    TexCoords = texCoords; // Pass through texture coordinates
}