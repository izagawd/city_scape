uniform mat4 projection;
uniform mat4 view;
uniform mat4 world;
in vec4 a_position;
in vec2 a_tex_coord;
out vec2 TexCoord;
uniform vec2 texture_multiplier;
void main()
{
    gl_Position = projection * view * world * a_position;

    TexCoord = a_tex_coord  * texture_multiplier;
}
