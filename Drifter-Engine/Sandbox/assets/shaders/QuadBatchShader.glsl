#type vertex
#version 330 core

layout(location=0) in vec4 a_Position;
layout(location=1) in vec2 a_UV;
layout(location=2) in vec4 a_Tint;
layout(location=3) in float a_Tex;

out vec2 v_UV;			
out vec4 v_Tint;			
out float v_Tex;			

uniform mat4 u_ViewProjection;

void main(){
	gl_Position = u_ViewProjection * a_Position;
	v_UV = a_UV;
	v_Tint = a_Tint;
	v_Tex = a_Tex;
}

#type fragment
#version 330 core

layout(location=0) out vec4 fragColor;

in vec2 v_UV;	
in vec4 v_Tint;			
in float v_Tex;	

uniform sampler2D[32] u_Textures;

void main(){
	highp int texIndex = int(v_Tex);
	vec4 col = texture(u_Textures[texIndex], v_UV) * v_Tint;
	//vec4 col = vec4(mod(v_UV, vec2(1.0, 1.0)), 0.0, 1.0);
	fragColor = col;
}
