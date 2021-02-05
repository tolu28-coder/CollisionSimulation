#pragma once
#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak()
#define GLCall(x) GLClearError();\
        x;\
        ASSERT(GLLogError(#x,__FILE__,__LINE__))

void GLClearError();

bool GLLogError(const char* function, const char* file, unsigned int line);


class Renderer {

private:

public:
  void Draw(VertexArray& va,IndexBuffer& ib, Shader& shader);

  void Clear();
};