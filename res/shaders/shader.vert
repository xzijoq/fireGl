#version 440 core
layout( location = 0 ) in vec2 aPos;
//layout( location = 1 )in vec4 coloP;
out vec4 colorP;
void main() 
{
//	colorP = coloP;

	gl_Position = vec4( aPos.x , aPos.y , 0.0 , 1.0 );
}