#type vertex
#version 330 core

layout(location=0) in vec3 a_Position;
layout(location=1) in vec2 a_UV;

out vec2 v_UV;			


uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main(){
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
	v_UV = a_UV;
}

#type fragment
#version 330 core

layout(location=0) out vec4 fragColor;
in vec2 v_UV;			

uniform sampler2D u_MainTex;
uniform vec4 u_Tint;

void main(){
	vec4 col = texture(u_MainTex, v_UV) * u_Tint;
	fragColor = col;
}
