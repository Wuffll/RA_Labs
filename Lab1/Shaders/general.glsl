#shader VERT
#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform vec4 uColor;

out vec3 vColor;

void main()
{
	gl_Position = vec4(position, 1.0f);
	vColor = uColor;
}

#shader FRAG
#version 450 core

in vec3 vColor;

out vec4 color;

void main()
{
	color = vec4(vColor, 1.0f);
}