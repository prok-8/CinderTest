#version 150

uniform vec4		colorMul;
uniform sampler2D	uTex0;

in vec2             vertTexCoord0;

out vec4            fragColor;

void main()
{	
	fragColor = texture(uTex0, vertTexCoord0) * colorMul;
}