#version 450

in vec4 fragColor;
in vec2 fragPosition;
in vec2 fragUV;

out vec4 color;

uniform sampler2D texSampler;

void main() {
    vec4 texColor = texture(texSampler, fragUV);

    color = texColor;
}
