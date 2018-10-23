#version 130

in vec3 position;
in vec3 colour;

uniform int vertexMode;

out vec3 interpolatedColour;

void main() {
    if (vertexMode == 1) {
        gl_Position = vec4(position * 0.5, 1);
    }
    else {
        gl_Position = vec4(position, 1);
    }
    interpolatedColour = colour;
}