#shader VERT
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vColor;

void main()
{
	gl_Position = vec4(position, 1.0f);
	vColor = color;
}

#shader FRAG
#version 330 core

in vec3 vColor;

out vec4 color;

void main()
{
	color = vec4(vColor, 1.0f);
}