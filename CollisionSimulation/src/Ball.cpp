#include "Ball.h"
#include <iostream>

Ball::Ball(glm::vec3 position, glm::vec3 velocity, float radius)
:m_Position(position),m_Velocity(velocity),m_Radius(radius){

}

Ball::~Ball()
{
}

void Ball::Update(float duration) {

  m_Position = m_Position + (duration * m_Velocity);

}

glm::mat4 Ball::GetTranslationMatrix() {

  return glm::translate(glm::mat4(1.0f), m_Position);
}