

out vec4 PixelColor;
uniform sampler2D gotten_texture;
in vec2 TexCoord;
void main()
{
    PixelColor = texture(gotten_texture,TexCoord);
 
}


