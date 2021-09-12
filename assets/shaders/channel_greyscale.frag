#version 150

uniform int			channelIndex;
uniform sampler2D	uTex0;

in vec2             vertTexCoord0;

out vec4            fragColor;

void main()
{	
	float value = texture(uTex0, vertTexCoord0)[channelIndex];
	fragColor = vec4(value, value, value, 1.0);
}