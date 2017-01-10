#version 330

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D texOne;
uniform sampler2D texTwo;

void main()
{
    vec4 texColor = mix(texture(texOne, Texcoord),
                        texture(texTwo, Texcoord), 0.5);
    outColor = vec4(Color, 1.0) * texColor;
}
