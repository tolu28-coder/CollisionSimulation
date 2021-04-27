#include "Ball.h"
#include <iostream>

Ball::Ball(glm::vec3 position, glm::vec3 velocity, float radius)
:m_Position(position),m_Velocity(velocity),m_Radius(radius){

  m_ScaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(m_Radius, m_Radius, 0));

}

Ball::~Ball()
{
}

void Ball::Update(float duration) {

  m_Position = m_Position + (duration * m_Velocity);

}

const glm::mat4 Ball::GetMatrix() {
  //glm::mat4 matrix = m_ScaleMatrix * glm::translate(glm::mat4(1.0f), m_Position);
  //return matrix;
  return m_ScaleMatrix * glm::translate(glm::mat4(1.0f), m_Position);
}