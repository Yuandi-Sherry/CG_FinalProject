#version 330 core
out vec4 color;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

uniform sampler2D myTexture;
uniform vec3 viewPos;

void main()
{
    vec4 texColor = texture(myTexture, TexCoord);
	if(texColor.a < 0.5)
		discard;
    color = texColor;
}