#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include "Container.h"
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"


float pi = atan(1) * 4;

struct Circle {
  float* Position;
  unsigned int* Index;
};

Circle CreateCircle(float radius, int division) {
  float* position = new float[(division + 1) * 2];
  unsigned int* index = new unsigned int[division * 3];

  float divisionAngle = ((2 * pi) / division);

  position[0] = 0.0f;
  position[1] = 0.0f;

  float x = 0.0f;
  float y = radius;


  for (int i = 0; i < division; i++) {

    position[(2 * i) + 2] = x;
    position[(2 * i) + 3] = y;

    float xnew = (x * cos(divisionAngle)) - (y * sin(divisionAngle));
    float ynew = (x * sin(divisionAngle)) + (y * cos(divisionAngle));

    x = xnew;
    y = ynew;
  }

  for (int i = 0; i < division; i++) {
    if (i != (division - 1)) {
      index[3 * i] = 0;
      index[(3 * i) + 1] = i + 1;
      index[(3 * i) + 2] = i + 2;
    }
    else {
      index[3 * i] = 0;
      index[(3 * i) + 1] = i + 1;
      index[(3 * i) + 2] = 1;
    }
  }


  return { position,index };

}

int main(void)
{
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(1800, 1000, "Hello World", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  if (glewInit() != GLEW_OK) {
    std::cout << "GLEW not initialised" << std::endl;
  };

  std::cout << glGetString(GL_VERSION) << std::endl;


  {
    float division = 180;
    Circle circle = CreateCircle(20, division);
    float* positions = circle.Position;
    unsigned int* indices = circle.Index;
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    VertexArray va;
    VertexBuffer vb = VertexBuffer(positions, (division+1) * 2 * sizeof(float));
    IndexBuffer ib = IndexBuffer(indices, 3*division);
    VertexBufferLayout layout;


    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    Shader shader = Shader("res/shaders/Basic.shader");
    Renderer renderer;

    Container simulation = Container(1800, 1000, &vb, &va, &ib, &renderer, &shader, layout, 60);

    for (int i = 0; i < 12; i++) {

      glm::vec3 ballPos = glm::vec3( (i*100)-600,
                                     (i%2)*200,
                                      0       );
      int sign = 1;
      if (i % 3 == 1) {

        sign = -1;
      }
      glm::vec3 ballVel = glm::vec3(sign*((i * 5) +200),
                                    25 -(((i+1) % 2) * 50),
                                     0        );

      Ball ball = Ball(ballPos, ballVel, 20);

      simulation.AddBall(ball);

    }
    

    //initialization (after renderer )
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init((char*)glGetString(330));

    //set up values

    glm::vec3 colour = glm::vec3(1.0f, 1.0f, 1.0f);

    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose(window))
    {
      /* Render here */
      //our game loop (while) (after clear color)

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      simulation.Draw();
      shader.SetUniform4f("u_Color", colour.x, colour.y, colour.z, 1.0);
      

      static float f = 0.0f;
      static int counter = 0;




      //GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

      

      {

        ImGui::Begin("Collisions");                          // Create a window called "Collisions" and append into it.

       

        ImGui::SliderFloat3("Colour(RGB)", &colour.x, 0.0f, 1.0f);           


        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
      }
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      /* Swap front and back buffers */
      glfwSwapBuffers(window);

      /* Poll for and process events */
      glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }


  glfwTerminate();
  return 0;
}