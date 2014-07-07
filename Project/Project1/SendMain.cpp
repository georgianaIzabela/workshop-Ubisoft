#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "Shader.h"
#include "Sprite.h"
#include"Texture.h"

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


	
	Vertex verts[] = {
		Vertex(glm::vec3(0.5, 0.5, 0), glm::vec2(0, 1)),
		Vertex(glm::vec3(0.5, 0.5, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1, 0)),
		Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(1, 1))
	};
	


	// Initializare (se creeaza contextul)
	if (!glfwInit ()) {
		fprintf (stderr, "ERROR: could not start GLFW3\n");
		return 1;
	} 

	// Se creeaza fereastra
	GLFWwindow* window = glfwCreateWindow (640, 480, "Workshop", NULL, NULL);
	if (!window) {
		// nu am reusit sa facem fereastra, oprim totul si dam mesaj de eroare
		printf ( "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	
	// Atasam contextul de fereastra
	glfwMakeContextCurrent (window);
                                  
	// Pornit extension handler-ul
	glewInit ();

	// Vedem versiunile
	const GLubyte* renderer = glGetString (GL_RENDERER); //renderer string
	const GLubyte* version = glGetString (GL_VERSION); // version string
	printf ("Renderer: %s\n", renderer);
	printf ("OpenGL version supported %s\n", version);

	/*
    GLfloat vertices[] = {
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
	
	GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Shader sh("../data/Shader");
	Sprite square(verts, sizeof(verts) / sizeof(verts[0]));
	Texture tex("../textures/player.jpg");
		
	while (!glfwWindowShouldClose(window)) {
	  
		// stergem ce s-a desenat anterior
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// facem swap la buffere (Double buffer)
		glfwSwapBuffers(window);

		sh.Bind();
		tex.Bind();
		square.Draw();

		glfwPollEvents();
	}
  
	glfwTerminate();
	_CrtDumpMemoryLeaks();

	return 0;
}