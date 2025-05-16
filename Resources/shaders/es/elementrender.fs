#version 300 es
#ifdef GL_ES
precision mediump float;
#else
precision highp float;
#endif

out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D image;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = texture(image, TexCoord);
}