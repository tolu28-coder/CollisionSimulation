#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Ball
{
public:
	Ball( glm::vec3 position, glm::vec3 velocity, float radius);
	~Ball();

	glm::mat4 GetTranslationMatrix();
	void Update(float duration);

	

protected:
	glm::vec3 m_Position;
	glm::vec3 m_Velocity;
	float m_Radius;
	float m_Mass = 5;
	friend class Container;

};

