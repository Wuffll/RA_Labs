#shader VERT
#version 450 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vColor;
out vec2 vTexCoord;

mat4 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    
    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

void main()
{
	vec3 fromTexToPlayer = aPosition - view[4].xyz; // view[4] == cameraPosition
	vec3 normalVec = aPosition + aNormal;
	
	float angleBetween = dot(normalize(fromTexToPlayer), normalize(normalVec));
	
	gl_Position = projection * view * model * vec4(aPosition, 1.0f);
	vColor = aColor;
	vTexCoord = aTexCoord;
}

#shader FRAG
#version 450 core

in vec3 vColor;
in vec2 vTexCoord;

out vec4 color;

uniform sampler2D aTexture;

void main()
{
	color = texture(aTexture, vTexCoord);
}