#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoords;
out vec4 ParticleColor;

uniform mat4 projection;
uniform mat4 view
uniform vec4 color;

void main()
{
    float scale = 10.0f;
    TexCoords = vertex.zw;
    ParticleColor = color;
    gl_Position = projection * view * vec4((aPos * scale), 0.0, 1.0);
}