#version 150

uniform vec4		colorMul;
uniform sampler2D	uTex0;
uniform vec2		uWindowOrigin;
uniform vec2		uWindowSize;

in vec2             vertTexCoord0;

out vec4            fragColor;

void main()
{	
	// find the actual screen coordinate of this fragment
	float y = uWindowSize.y - gl_FragCoord.y + uWindowOrigin.y;

	fragColor = texture(uTex0, vertTexCoord0) * colorMul;
}