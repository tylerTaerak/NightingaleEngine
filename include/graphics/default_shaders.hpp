#pragma once

#define DEFAULT_VERTEX_SHADER "#version 450 \n\
    in vec2 vertexPosition;\n\
    in vec2 vertexUV;\n\
    \n\
    out vec2 fragPos;\n\
    out vec2 fragUV;\n\
    \n\
    uniform mat4 projectionMatrix;\n\
    \n\
    void main() {\n\
        gl_Position = projectionMatrix * vec4(vertexPosition.x, vertexPosition.y, 0.0, 1.0); \n\
        \n\
        fragUV = vec2(vertexUV.x, -1.0 - vertexUV.y);\n\
    }"

#define DEFAULT_FRAGMENT_SHADER "#version 450 \n\
    in vec2 fragUV;\n\
    \n\
    out vec4 color;\n\
    \n\
    uniform sampler2D texSampler;\n\
    \n\
    void main() {\n\
        vec4 texColor = texture(texSampler, fragUV);\n\
        \n\
        color = texColor;\n\
    }"

#define DEFAULT_FONT_VERTEX_SHADER "#version 450 \n\
    in vec4 vertex;\n\
    out vec2 TexCoords;\n\
    \n\
    uniform mat4 projectionMatrix;\n\
    \n\
    void main() {\n\
        gl_Position = projectionMatrix * vec4(vertex.xy, 0.0, 1.0);\n\
        TexCoords = vertex.zw;\n\
    }"

#define DEFAULT_FONT_FRAGMENT_SHADER "#version 450 \n\
    in vec2 TexCoords;\n\
    out vec4 color;\n\
    \n\
    uniform sampler2D text;\n\
    uniform vec3 textColor;\n\
    \n\
    void main() {\n\
        vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n\
        color = vec4(textColor, 1.0) * sampled;\n\
    }"
