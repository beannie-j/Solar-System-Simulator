#shader vertex
#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

layout(location = 0) out vec3 v_WorldNormal;

void main()
{
	v_WorldNormal = mat3(u_Transform) * normal;
	//v_WorldNormal = normal;
	gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0);
};

#shader fragment
#version 450 core

layout(location = 0) out vec4 color;
layout(location = 0) in vec3 v_WorldNormal;

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

	//color.rgb = vec3(intensity);
	//color.rgb = normal * 0.5 + 0.5; // -1 -> 1 == 0 -> 1, 0 == 0.5
};