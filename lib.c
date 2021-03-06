#include <SDL2/SDL.h>
#include "lib.h"

static SDL_GLContext context;
static SDL_Window *window;
static unsigned usedBuffers = 0;
static GLuint vertexArray, vertexBuffers[2];

void draw(const GLsizei count) {
    glDrawArrays(GL_TRIANGLES, 0, count);
    SDL_GL_SwapWindow(window);
    SDL_Event event;
    while (SDL_WaitEvent(&event) && event.type != SDL_QUIT);
    glDeleteBuffers(usedBuffers, vertexBuffers);
    glDeleteVertexArrays(1, &vertexArray);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
}

void init(char *title) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(window);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
}

static char *readFile(char *file) {
    FILE *f = fopen(file, "rb");
    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buffer = malloc(length + 1);
    fread(buffer, 1, length, f);
    buffer[length] = '\0';
    fclose(f);
    return buffer;
}

void setupBuffer(GLfloat *bufferData, GLint size) {
    glGenBuffers(1, &vertexBuffers[usedBuffers]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[usedBuffers]);
    glBufferData(GL_ARRAY_BUFFER, size, bufferData, GL_STATIC_DRAW);
    glEnableVertexAttribArray(usedBuffers);
    glVertexAttribPointer(usedBuffers++, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

static GLuint setupShader(GLint type, char *file) {
    GLuint shader = glCreateShader(type);
    const GLchar *shaderSource = readFile(file);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    free((void *) shaderSource);
    return shader;
}

GLuint setupShaders(char *vertexShader, char *fragmentShader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, setupShader(GL_VERTEX_SHADER, vertexShader));
    glAttachShader(program, setupShader(GL_FRAGMENT_SHADER, fragmentShader));
    glLinkProgram(program);
    glUseProgram(program);
    return program;
}