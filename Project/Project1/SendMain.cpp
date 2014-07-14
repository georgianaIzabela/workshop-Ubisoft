#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "Shader.h"
#include "Sprite.h"
#include "Texture.h"
#include "Window.h"
#include "Player.h"
#include "Enemy.h"

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
	
	Vertex verts2[] = {
		Vertex(glm::vec3(-0.5, 0.5, 0), glm::vec2(1, 1)),
		Vertex(glm::vec3(-0.5, 0.5, 0), glm::vec2(1, 0)),
		Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(0.5, 0.5, 0), glm::vec2(0, 1))
	};
	
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	Shader* sh = new Shader("../data/Shader");
	Player* player = new Player(sh, 0.2f, "../textures/spaceship2.png");
	Enemy* e1 = new Enemy(sh, 0.1f, 1, "../textures/");
	Enemy* e2 = new Enemy(sh, 0.1f, 2, "../textures/");

	while (m_window.IsRunning()) {
		
		m_window.Clear();
		
		sh->Bind();
		
		player->move(m_window.m_window);
		player->draw();

		e1->move();
		e1->draw();

		e2->move();
		e2->draw();

		m_window.Update();
	}
  
	delete sh;
	delete player;
	delete e1;
	delete e2;

	_CrtDumpMemoryLeaks();

	return 0;
}