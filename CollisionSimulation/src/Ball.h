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
	Ball( glm::vec3 position, glm::vec3 velocity, float radius, float mass);
	~Ball();

	const glm::mat4 GetMatrix();
	void Update(float duration);

	

protected:
	glm::mat4 m_ScaleMatrix;
	glm::vec3 m_Position;
	glm::vec3 m_Velocity;
	float m_Radius;
	float m_Mass;
	friend class Container;

};

