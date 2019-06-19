#include "Model.h"
#include "Shader.h"

#include "Math/vec.h"
#include "Math/mat.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


int g_windowWidth = 800;
int g_windowHeight = 600;


void windowsize_callback(GLFWwindow* window, int width, int height){
  g_windowWidth = width;
  g_windowHeight = height;
}
  

int main(){

  
  if(!glfwInit()) glfwInit();
  glfwWindowHint(GLFW_SAMPLES, 8);
  GLFWwindow* window = glfwCreateWindow(g_windowWidth, g_windowHeight, "Graphics", 0, 0);
  glfwMakeContextCurrent(window);
  glfwSetWindowSizeCallback(window, windowsize_callback);
  glfwSwapInterval(1);

  if(!glewInit()) glewInit();
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glEnable(GL_DEPTH_TEST);

  Shader shader;
  shader.InitShader("Shaders/model.vert", "Shaders/model.frag");
  Model icecream;
  icecream.LoadModel("Model/bowling.obj");

  bool wireframe = false;
  float angle = 0.0f;
  vec3 position = vec3(-2.0f, -5.0f, -17.0f);
  while(!glfwWindowShouldClose(window)){

    double startTime = glfwGetTime();
    glViewport(0, 0, g_windowWidth, g_windowHeight);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();

	mat4 projection = mat4::perspective(45.0f, g_windowHeight / float(g_windowHeight), 0.1f, 1000.0f);
	mat4 model = mat4::translate(position) * mat4::rotateY(angle) * mat4::scale(vec3(5.0f, 7.0f, 5.0f));
	
	shader.Use();
	shader.LoadMat("projection", projection);
	shader.LoadMat("model", model);
	icecream.Draw(shader);
	shader.Unuse();

    if(glfwGetKey(window, GLFW_KEY_F2))
      wireframe = !wireframe;

	if (glfwGetKey(window, GLFW_KEY_UP))
		position.z += 0.1f;
	else if (glfwGetKey(window, GLFW_KEY_DOWN))
		position.z -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_LEFT))
		position.x += 0.1f;
	else if (glfwGetKey(window, GLFW_KEY_RIGHT))
		position.x -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_W))
		position.y -= 0.1f;
	else if (glfwGetKey(window, GLFW_KEY_S))
		position.y += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_Q))
		angle++;
	else if(glfwGetKey(window, GLFW_KEY_E))
		angle--;
	std::cout << position.x << " " << position.y << " " << position.z << std::endl;
    if(wireframe)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  
  return 0;
}
