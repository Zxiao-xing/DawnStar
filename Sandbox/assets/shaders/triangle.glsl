#type vertex
#version 430 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;

out vec2 TexCoord;

void main()
{
	gl_Position = vec4(a_Position, 1.0);
	TexCoord = vec2(a_TexCoord.x, a_TexCoord.y);
}

#type fragment
#version 430 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, TexCoord);
}