#pragma once
#include <string>
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <iostream>

class Window
{
public:
	Window(int width, int height, const std::string& title);

	void Clear();
	void Update();
	bool IsRunning();

	virtual ~Window();
	
	GLFWwindow* m_window;
};

