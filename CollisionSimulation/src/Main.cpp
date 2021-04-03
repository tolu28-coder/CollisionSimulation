#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
//#include <math.h>
#include "Container.h"
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"




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

    Container simulation = Container(1800, 1000, 60);

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

      Ball ball = Ball(ballPos, ballVel, 20 -i);

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
      simulation.SetUniform4f("u_Color", colour.x, colour.y, colour.z, 1.0);
      

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