#pragma once
#include "Renderer.h"
#include <iostream>

void GLClearError() {

  while (glGetError() != GL_NO_ERROR);

}

bool GLLogError(const char* function, const char* file, unsigned int line) {
  GLenum error = glGetError();
  while (error != GL_NO_ERROR) {

    std::cout << "[OpenGL Error] (" << error << ")" << "::" << function << "::" << file << "::line " << line << std::endl;
    return false;
  }
  return true;
}

void Renderer::Draw(VertexArray& va, IndexBuffer& ib, Shader& shader) {


  shader.Bind();
  va.Bind();
  ib.Bind();
  

  GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

}
void Renderer::Clear() {
  GLCall(glClear(GL_COLOR_BUFFER_BIT));
}