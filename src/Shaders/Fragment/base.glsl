#version 400

in vec3 Colour;
out vec4 FragmentColour;

void main() {
    FragmentColour = vec4(Colour, 1.0);
}
