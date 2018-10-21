#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>

void draw(GLsizei count);

void init(char* title);

void setupBuffer(GLuint index, GLfloat* bufferData, GLint size);

GLuint setupShaders(char* vertexShader, char* fragmentShader) ;