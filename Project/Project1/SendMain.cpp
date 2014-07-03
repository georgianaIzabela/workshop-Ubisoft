#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>

#include <stb_image\stb_image.cpp>

using namespace std;
#define PI 3.14159

// Structura retine datele despre un obiect
typedef struct Object{
	 GLuint vao, vbo;
	 int nrVertices; // numarul de varfuri
}Object;

vector<Object> objects;

// Functie de incarcat continutul unui fisier intr-un buffer 
char * LoadFileInMemory(const char *filename)
{
	int size = 0;
	char *buffer = NULL;
	FILE *f = fopen(filename, "rb");
	if (f == NULL)
	{
		return NULL;
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	buffer = new char[size + 1];
	if (size != fread(buffer, sizeof(char), size, f))
	{
		delete[] buffer;
	}
	fclose(f);
	buffer[size] = 0;
	return buffer;
}

// Functia afiseaza pe ecran un obiect
void displayObject (Object obj, GLuint shader_programme) {
	glUseProgram(shader_programme);
	glBindVertexArray(obj.vao);
	glDrawArrays(GL_TRIANGLES, 0 , obj.nrVertices);
}


// Functie de desenare a unui triunghi
void createTriangle(float x, float y){
	
	GLuint vao, vbo;  
	Object triangle;
	
	float vertex_buff[] = {
		x + 0.0f,  y + 0.0f, 0.0f,
        x + 0.5f,  y + 0.0f, 0.0f,
		x + 0.25f, y + 0.5f, 0.0f
	};
  
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertex_buff, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(0);

	triangle.vao = vao;
	triangle.vbo = vbo;
	triangle.nrVertices = 3;
  
	objects.push_back(triangle);

}

// Functie pentru desenarea unui patrat
void createSquare(float x, float y){
	GLuint vao, vbo;
	Object square;

	float vertex_buff[] = {
		x + 0.0f,  y + 0.0f, 0.0f,
        x + 0.25f,  y + 0.0f, 0.0f,
		x + 0.25f,  y + 0.25f, 0.0f,
		x + 0.0f,  y + 0.0f, 0.0f,
		x + 0.25f,  y + 0.25f, 0.0f,
		x + 0.0f,  y + 0.25f, 0.0f
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 18*sizeof(GLfloat), vertex_buff, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(0); 

	
	square.vao = vao;
	square.vbo = vbo;
	square.nrVertices = 6;
	
	objects.push_back(square);

}

// Functie pentru desenarea unui cerc
void createCircle(int nrVertices) {
	
	Object circle;
	GLuint vao, vbo;
	int nr = 3 * ((nrVertices + 1) * 3 + 1); 
	int j = 3;
	float * vertexBuffer = new float[nr];
	float angle = 0, radius = 0.15f;
	float beta = 2 * (float)PI / nrVertices;
	
	// centrul cercului
	vertexBuffer[0] = 0.5f;
	vertexBuffer[1] = 0.75f;
	vertexBuffer[2] = 0.0f;
  
	// restul punctelor
	for(int i = 0; i <= nrVertices; i++) {

		// primul punct este centrul cercului
		vertexBuffer[j] = vertexBuffer[0]; 
		vertexBuffer[j + 1] = vertexBuffer[1]; 
		vertexBuffer[j + 2] = 0;
		j += 3;

		// al doilea punct
		vertexBuffer[j] = vertexBuffer[0] + sin(angle - 2 * beta) * radius; 
		vertexBuffer[j + 1] = vertexBuffer[1] + cos(angle - 2 * beta) * radius;
		vertexBuffer[j + 2] = 0;
		j += 3;
		
		// calculam noul punct
		vertexBuffer[j] = vertexBuffer[0] + sin(angle) * radius; 
		vertexBuffer[j + 1] = vertexBuffer[1] + cos(angle) * radius; 
		vertexBuffer[j + 2] = 0;
		j += 3;
		angle += beta;
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, nr * sizeof(GLfloat), vertexBuffer, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(0);
 
	delete [] vertexBuffer;

	circle.vao = vao;
	circle.vbo = vbo;
	circle.nrVertices = nr/3;
	
	objects.push_back(circle);

}

// exemplu de implementare
void FlipTexture(unsigned char* image_data,int x,int y , int n)
{
	//flip texture
	int width_in_bytes = x * 4;
	unsigned char *top = NULL;
	unsigned char *bottom = NULL;
	unsigned char temp = 0;
	int half_height = y / 2;

	for (int row = 0; row < half_height; row++) {
		top = image_data + row * width_in_bytes;
		bottom = image_data + (y - row - 1) * width_in_bytes;
		for (int col = 0; col < width_in_bytes; col++) {
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}
}


int main () {

	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	


	//glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	//glDebugMessageCallback(openglDebugCallback , NULL);
	//glEnable(GL_DEBUG_OUTPUT);


	// Initializare (se creeaza contextul)
	if (!glfwInit ()) {
		fprintf (stderr, "ERROR: could not start GLFW3\n");
		return 1;
	} 

	// Se creeaza fereastra
	GLFWwindow* window = glfwCreateWindow (640, 480, "Workshop1", NULL, NULL);
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

	const char * vertex_shader = LoadFileInMemory("../data/vertexShader.glsl");
	const char * fragment_shader = LoadFileInMemory("../data/fragmentShader.glsl");

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	delete[] vertex_shader;
	delete[] fragment_shader;

	// Creez alte shadere pentru a desena un triunghi de culoare diferita 
	/*const char * vertex_shader2 = LoadFileInMemory("../data/vertexShader.glsl");
	const char * fragment_shader2 = LoadFileInMemory("../data/fragmentShader2.glsl");

	GLuint vs2 = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs2, 1, &vertex_shader2, NULL);
	glCompileShader(vs2);
	GLuint fs2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs2, 1, &fragment_shader2, NULL);
	glCompileShader(fs2);
	GLuint shader_programme2 = glCreateProgram();
	glAttachShader(shader_programme2, fs2);
	glAttachShader(shader_programme2, vs2);
	glLinkProgram(shader_programme2);

	delete[] vertex_shader2;
	delete[] fragment_shader2;

	*/

	/*
	// Deseneaza obiecte pe ecran
	createSquare(-0.75f, 0.25f);
	createTriangle(-0.55f, -0.55f);
	createTriangle(-0.05f, -0.05f);
	createCircle (9);
	*/
	

	// desenez un patrat cu indexBuffer

    GLfloat vertices[] = {
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
	
	GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };
	GLuint vbo;
    GLuint elementBuffer;
	
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	
	
	// incarcare textura
	int x, y, n;
	int force_channels = 4;
	char* player_file = "../textures/player.jpg";

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glActiveTexture(GL_TEXTURE0);

	unsigned char* image_data = stbi_load(player_file, &x, &y, &n, force_channels);

	if (!image_data) {
		fprintf(stderr, "ERROR: could not load %s\n", player_file);
	}

	FlipTexture(image_data, x, y, n);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	// setam parametri de sampling	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //ce se intampla cand coordonata nu se inscrie in limite
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //ce se intampla cand coordonata nu se inscrie in limite
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // setam samplare cu interpolare liniara
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // setam samplare cu interpolare liniara
	
	delete [] image_data;

	int texture_location = glGetUniformLocation(shader_programme, "basic_texture");

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, tex);


		
	while (!glfwWindowShouldClose(window)) {
	  
		// stergem ce s-a desenat anterior
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof (float), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		
		glUniform1i(texture_location, 0); 
	
		glDrawElements(
			GL_TRIANGLES,      // mode
			6,    // count
			GL_UNSIGNED_INT,   // type
			(void*)0           // element array buffer offset
			);
	
		
		/* // afisez obiectele
		displayObject(objects[0], shader_programme);
		displayObject(objects[1], shader_programme);
		
		// un triunghi de culoare diferita
		displayObject(objects[2], shader_programme2);
		
		displayObject(objects[3], shader_programme);
		*/

		// facem swap la buffere (Double buffer)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
  
	glfwTerminate();
	_CrtDumpMemoryLeaks();

	return 0;
}