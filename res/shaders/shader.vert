#version 440 core
layout( location = 0 ) in vec3 aPos;
layout( location = 1 )in vec4 coloP;
out vec4 colorP;
void main() 
{	mat4x4 m=mat4 (1.0);
	m[3][0]=0.5;
	vec4 disgusting=vec4(aPos.x,aPos.y,aPos.z,1.0);
	disgusting=disgusting*m;
	colorP = coloP;
	gl_Position=disgusting;
	//gl_Position = vec4( aPos.x , aPos.y , aPos.z , 1.0 );
}