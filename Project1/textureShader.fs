#version 330 core
out vec4 color;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

uniform sampler2D solarTexture;
uniform vec3 viewPos;

void main()
{
    vec3 result = vec3(1.0f);
    color = texture(solarTexture, TexCoord) * vec4(result, 1.0f);
}