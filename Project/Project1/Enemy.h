#pragma once
#include "Shader.h"
#include "Sprite.h"
using namespace std;

class Enemy
{
public:
	
	Enemy(Shader* shader, float size, int type,  string textureFile);
	virtual ~Enemy(void);
	void move();
	void draw();
	
	Sprite* eSprite;
	Shader* shader;
	Transform* transform;
	int type;
};
