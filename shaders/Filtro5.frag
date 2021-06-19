#version 450 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

// Texture sampler
uniform sampler2D ourTexture1;

void main()
{
    color = texture(ourTexture1, TexCoord);

	float media = (color.r + color.g + color.b) / 3;
	
	if (media < 0.55) {
		color.r = 0.0;
		color.g = 0.0;
		color.b = 0.0;
	}
	else {
		color.r = 1.0;
		color.g = 1.0;
		color.b = 1.0;
	}
}