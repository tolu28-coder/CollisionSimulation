#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Ball.h"
#include <vector>
#include "Shader.h"
#include <iostream>
#include "Utilities.h"

class Container
{
public:
	Container(float xRange,float yRange, float frameRate,int circleDivision = 180);
	~Container();
	
	void AddBall(Ball &ballObject);

	void AddBalls(std::vector<Ball>& ballObject);

	void CheckOutOfBounds();

	void CheckCollisions();
	void Draw();
	void Update();
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	VertexBuffer m_SharedVertexBuffer;
	IndexBuffer m_SharedIndexBuffer;
	VertexArray m_SharedVertexArray;
	Renderer m_Renderer;
	Shader m_Shader;
	glm::mat4 m_Projection;
	float m_Left;
	float m_Right;
	float m_Top;
	float m_Bottom;
	float m_Duration;
	std::vector<Ball> m_BallObjects;
};

