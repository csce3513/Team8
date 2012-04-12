#version 420

layout( location = 0 ) in vec2 InVertex;
layout( location = 1 ) in vec4 InColor;
layout( location = 2 ) in vec2 InTexCoords0;
out vec4 ExColor;
out vec2 ExTexCoords0;

void main()
{
	gl_Position = vec4( InVertex, 0.0, 1.0 );
	ExColor = InColor;
	ExTexCoords0 = InTexCoords0;
}
