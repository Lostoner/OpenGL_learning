#shader
#version 330 core

in vec2 v_texCoord;

out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
	FragColor = texture(u_Texture, v_texCoord) * 0.5;
};
#end


#shader
#version 330 core

in vec2 v_texCoord;
in vec3 fragPosition;
in vec3 Normal;

layout(location = 0) out vec4 color;

uniform sampler2D u_Texture;
uniform sampler2D h_Texture;
uniform vec3 lightPosition;
uniform vec3 viewPosition;
uniform vec3 lightColor;
uniform float lightPower;

void main()
{
	vec4 texColor = texture(u_Texture, v_texCoord);
	vec4 hTexColor = texture(h_Texture, v_texCoord);

	float ambient = 0.1;

	vec3 lightDir = normalize(lightPosition - fragPosition);
	float diff = max(dot(Normal, lightDir), 0.0);

	float specularStrength = 1.0;
	vec3 viewDir = normalize(viewPosition - fragPosition);
	vec3 reflectDir = reflect(-lightDir, Normal);
	float specular = specularStrength * pow(max(dot(viewDir, reflectDir), 0.0), 100);

	vec3 ambientV = ambient * vec3(texColor);
	vec3 diffV = diff * vec3(texColor);
	vec3 specularV = specular * vec3(hTexColor);

	//color = lightPower * vec4(lightColor * (ambient + diff + specular) * vec3(texColor), 1.0);
	color = lightPower * vec4(lightColor * (ambientV + diffV + specularV), 1.0);
};
#end



#shader
#version 330 core

out vec4 fragColor;

uniform vec4 lightColor;
uniform vec4 objectColor;

void main()
{
	fragColor = lightColor * objectColor;
};
#end