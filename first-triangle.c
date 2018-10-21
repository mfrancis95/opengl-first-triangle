#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

static void setupBuffers(void) {
    GLfloat positionData[9] = {
        0, 1, 0,
        -1, -1, 0,
        1, -1, 0
    };
    setupBuffer(0, positionData, sizeof(positionData));
    GLfloat colourData[9] = {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };
    setupBuffer(1, colourData, sizeof(colourData));
}

static void setupUniforms(int vertexMode, int fragmentMode) {
    GLuint program = setupShaders("shader.vert", "shader.frag");
    glUniform1i(glGetUniformLocation(program, "vertexMode"), vertexMode);
    glUniform1i(glGetUniformLocation(program, "fragmentMode"), fragmentMode);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: first-triangle vertexMode fragmentMode\n");
        return 1;
    }
    init("Intro to OpenGL - Your First Triangle");
    setupBuffers();
    setupUniforms(atoi(argv[1]), atoi(argv[2]));
    draw(3);
    return 0;
}