#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_WorldNormal;

void main()
{
	v_WorldNormal = mat3(u_Transform) * normal;
	//v_WorldNormal = normal;
	gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_WorldNormal;

uniform vec4 u_Color;

void main()
{
	vec4 u_Color = u_Color;
	vec3 normal = normalize(v_WorldNormal);
	vec3 lightDir = vec3(-0.5, 0.5, 0.5);

	float intensity = dot(lightDir, normal);
	vec3 staticColor = vec3(0.8, 0.2, 0.2);
	vec3 finalColor = staticColor * intensity;
	color = vec4(finalColor, 1.0);
};