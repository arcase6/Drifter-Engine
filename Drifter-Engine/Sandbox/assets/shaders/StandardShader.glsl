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

uniform float u_Time;	
uniform sampler2D u_MainTex;		

void main(){
	float sinAmp = 3.;
	float sinFreq = .25;
	float sinFac = sinAmp * (sin(u_Time * sinFreq) / 2. + .5);
	vec4 col = texture(u_MainTex, v_UV * sinFac / sinFac);
	fragColor = col;
}
