#version 130

in vec3 interpolatedColour;

uniform int fragmentMode;

out vec3 colour;

void main() {
    switch (fragmentMode) {
        case 1:
            colour = vec3(1, 0, 0);
            break;
        case 2:
            colour = vec3(0, 1, 0);
            break;
        case 3:
            colour = vec3(0, 0, 1);
            break;
        default:
            colour = interpolatedColour;
    }
}