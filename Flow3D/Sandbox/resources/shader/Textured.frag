#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
	vec4 texColor = texture(texture1, TexCoord);
	if (texColor.a < 0.5) // should not be 0.5, but it helps with the grass texture to not have white fragments
		discard;
	FragColor = texture(texture1, TexCoord);
}