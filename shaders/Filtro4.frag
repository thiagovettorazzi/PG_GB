#version 450 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

// Texture sampler
uniform sampler2D ourTexture1;

void main()
{
    color = texture(ourTexture1, TexCoord);
    
    color.r += 0.90196078431;
    color.g += 0.49411764705;
    color.b += 0.13333333333;
}