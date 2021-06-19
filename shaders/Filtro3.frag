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
    
    color.r = media;
    color.g = media;
    color.b = media;
}