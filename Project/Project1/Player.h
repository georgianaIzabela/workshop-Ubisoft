#include "Window.h"
#include "Transform.h"
#include "Shader.h"
#include "Sprite.h"
#include <GLFW/glfw3.h> // GLFW helper library
using namespace std;

class Player
{
public:
	Player(Shader* shader, float size, string textureFile);
	virtual ~Player(void);
	
	void draw();
	void move(GLFWwindow* window);
	void setInBounds(float x, float y, float z);
	
private:
	Sprite* pSprite;
	Transform* transform;
	Shader* shader;
};
