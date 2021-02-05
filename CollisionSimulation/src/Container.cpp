#include "Container.h"

Container::Container(float xRange, float yRange, VertexBuffer* vb, VertexArray* va,
                      IndexBuffer* ib, Renderer* renderer,Shader* shader, VertexBufferLayout &layout,float frameRate) 
                      : m_SharedVertexBuffer(vb),m_SharedIndexBuffer(ib), m_Left(xRange/2),
                      m_Right(-xRange / 2), m_Top(yRange / 2), m_Bottom(-yRange / 2), m_Renderer(renderer), 
                      m_Shader(shader),m_SharedVertexArray(va) , m_Duration(1/frameRate)
{
  m_Projection = glm::ortho(m_Left, m_Right, m_Bottom, m_Top);
  m_Shader->Bind();
  m_SharedVertexBuffer->Bind();
  m_SharedIndexBuffer->Bind();
  m_SharedVertexArray->Bind();
  m_SharedVertexArray->AddBuffer(*m_SharedVertexBuffer, layout);

}

Container::~Container()
{
}

void Container::AddBall(Ball &ballObject) {

  m_BallObjects.push_back(ballObject);

}

void Container::CheckOutOfBounds() {

  for (Ball &ball : m_BallObjects) {
    glm::vec3& ballPos = ball.m_Position;
    glm::vec3& ballVel = ball.m_Velocity;
    if (ballPos.x > m_Left) {
      ballPos.x = m_Left - (ballPos.x - m_Left);
      ballVel.x *= -1;
    }

    if (ballPos.x < m_Right) {
      ballPos.x = m_Right - (ballPos.x - m_Right);
      ballVel.x *= -1;
    }

    if (ballPos.y > m_Top) {
      ballPos.y = m_Top - (ballPos.y - m_Top);
      ballVel.y *= -1;
    }

    if (ballPos.y < m_Bottom) {
      ballPos.y = m_Bottom - (ballPos.y - m_Bottom);
      ballVel.y *= -1;
    }
  }
}

void Container::CheckCollisions() {
  int i{ 1 };
  for (size_t k = 0; k < m_BallObjects.size(); k++) {

    for (size_t  j = i; j < m_BallObjects.size(); j++) {

      Ball& ball1 = m_BallObjects[k];
      Ball& ball2 = m_BallObjects[j];

      float distance = glm::distance(ball1.m_Position, ball2.m_Position);
      
      if (distance < (ball1.m_Radius + ball2.m_Radius)) {

        glm::vec3 normalised_displacement = glm::normalize(ball1.m_Position - ball2.m_Position);
        glm::vec3 vel1x = normalised_displacement * glm::dot(ball1.m_Velocity, normalised_displacement);
        glm::vec3 vel1y = ball1.m_Velocity - vel1x;

        normalised_displacement *= -1;
        glm::vec3 vel2x = normalised_displacement * glm::dot(ball2.m_Velocity,normalised_displacement  );
        glm::vec3 vel2y = ball2.m_Velocity - vel2x;

        ball1.m_Velocity = (vel1x * ((ball1.m_Mass - ball2.m_Mass) / (ball1.m_Mass + ball2.m_Mass))) + (vel2x * ((2.0f * ball2.m_Mass) / (ball1.m_Mass + ball2.m_Mass))) + vel1y;
        ball2.m_Velocity = (vel1x * ((2.0f * ball2.m_Mass) / (ball1.m_Mass + ball2.m_Mass))) + (vel2x * ((ball1.m_Mass - ball2.m_Mass) / (ball1.m_Mass + ball2.m_Mass))) + vel2y;
        
      }
    }
    i++;
  }
}

void Container::Draw() {
  this->Update();
  this->CheckCollisions();
  this->CheckOutOfBounds();
  glm::mat4 mvp;
  m_Renderer->Clear();
  for (const Ball& ball : m_BallObjects) {
    mvp = m_Projection * glm::translate(glm::mat4(1.0f), ball.m_Position);
    m_Shader->SetUniformMat4f("u_MVP",mvp);
    m_Renderer->Draw(*m_SharedVertexArray, *m_SharedIndexBuffer, *m_Shader);
  }
 
}

void Container::Update() {
  for (auto& ball : m_BallObjects) {
    ball.Update(m_Duration);
  }
}

void Container::AddBalls(std::vector<Ball>& ballObjects) {

  for (auto& ball : ballObjects) {

    m_BallObjects.push_back(ball);
  }

}