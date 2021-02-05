#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"


struct ShaderProgramSource {
  std::string VertexSource;
  std::string FragmentSource;
};

class Shader {
private:
  std::string m_filepath;
  unsigned int m_RendererID;
  std::unordered_map<std::string, int > m_UniformLocationCache;
public:
  Shader(const std::string& filepath);
  ~Shader();
  void Bind() const;
  void Unbind() const;

  //Set Uniforms

  void SetUniform4f(const std::string& name , float v0, float v1, float v2, float v3);
  void SetUniformMat4f(const std::string& name, glm::mat4& matrix);
  void SetUniform1f(const std::string& name, float value);
  void SetUniform1i(const std::string& name, int value);

private:
  ShaderProgramSource ParseShader(std::string filepath);
  unsigned int CompileShader(unsigned int type, std::string& source);
  unsigned int CreateShader(std::string& vertexShader, std::string& fragmentShader);
  int GetUniformLocation(const std::string& name);
};
