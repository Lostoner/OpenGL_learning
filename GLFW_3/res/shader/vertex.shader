#shader
#version 330 core

layout(location = 0) in vec3 Pos;
layout(location = 1) in vec2 texCoord;

uniform mat4 mM;
uniform mat4 mV;
uniform mat4 mP;

out vec2 v_texCoord;

void main()
{
	gl_Position = mP * mV * mM * vec4(Pos, 1.0);
	v_texCoord = texCoord;
};
#end


#shader
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 inNormal;

uniform mat4 mM;
uniform mat4 mV;
uniform mat4 mP;

out vec2 v_texCoord;
out vec3 fragPosition;
out vec3 Normal;

void main()
{
	gl_Position = mP * mV * mM * vec4(position, 1.0);
	v_texCoord = texCoord;
	fragPosition = vec3(mM * vec4(position, 1.0));
	Normal = normalize(vec3(mM * vec4(inNormal, 0.0)));
	//Normal = normalize(inNormal);
	//Normal = mat3(transpose(inverse(mM))) * inNormal;
};
#end


#shader
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 mM;
uniform mat4 mV;
uniform mat4 mP;

void main()
{
	gl_Position = mP * mV * mM * position;
}
#end