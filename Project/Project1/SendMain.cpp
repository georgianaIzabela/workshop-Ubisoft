#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "Shader.h"
#include "Sprite.h"
#include "Texture.h"
#include "Window.h"

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif  // _DEBUG
#include<vector>




int main () {

	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	Window m_window(800, 600, "Joc");
	
	Vertex verts[] = {
		Vertex(glm::vec3(0.2, 0.2, 0), glm::vec2(0, 1)),
		Vertex(glm::vec3(0.2, -0.2, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(-0.2, -0.2, 0), glm::vec2(1, 0)),
		Vertex(glm::vec3(-0.2, 0.2, 0), glm::vec2(1, 1))
	};
	
	
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	Shader sh("../data/Shader");
	Sprite square(verts, sizeof(verts) / sizeof(verts[0]));
	Texture tex("../textures/spaceship2.png");
	Transform trans;

	float counter = 0.0f;

	while (m_window.IsRunning()) {
		
		m_window.Clear();
		trans.GetPos().x = sin(counter);
		
		
		sh.Bind();
		tex.Bind();
		sh.Update(trans);
		square.Draw();

		counter += 0.01f;

		m_window.Update();
	}
  
	_CrtDumpMemoryLeaks();

	return 0;
}