#version 420

uniform sampler2D Texture0;
in vec4 ExColor;
in vec2 ExTexCoords0;
out vec4 OutColor;

void main()
{
	OutColor = ExColor * texture( Texture0, ExTexCoords0 );
}
