#version 400

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexColour;

out vec3 Colour;

uniform mat4 Matrix;

void main() {
    Colour = VertexColour;
    gl_Position = Matrix * vec4(VertexPosition, 1.0);
}
