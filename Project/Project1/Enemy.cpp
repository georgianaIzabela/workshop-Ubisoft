#include "Enemy.h"

Enemy::Enemy(Shader* shader, float size, int type, string textureFile)
{

	Vertex verts[] = {
		Vertex(glm::vec3(size, size, 0), glm::vec2(1, 1)),
		Vertex(glm::vec3(size, -size, 0), glm::vec2(1, 0)),
		Vertex(glm::vec3(-size, -size, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(-size, size, 0), glm::vec2(0, 1))
	};

	this->type = type;

	if (type == 1) {
		textureFile.append("enemy1.png");
	} else {
		textureFile.append("enemy2.png");
	}
		
	
	eSprite = new Sprite(verts, sizeof(verts) / sizeof(verts[0]), textureFile.c_str());
	this->shader = shader;
	this->transform = new Transform;
}


Enemy::~Enemy(void)
{
	delete eSprite;
	delete transform;
}

void Enemy::move() 
{
	float step = 0.01f;
	float max = 0.8f;
	float x, y, z;
	
	x = transform->GetPos().x;
	y = transform->GetPos().y;
	z = transform->GetPos().z;

	if (type == 1) {
		static float fps = 0.0f;
		y += sinf(fps) / 200;
		fps += step;
	}

	static int asc = 1;
	x += asc * step;
	if (x < max && x > -max) {
		transform->SetPos(glm::vec3(x, y, z));
	} else {
		if ( x < 0)
			transform->SetPos(glm::vec3(-max, y, z));
		else 
			transform->SetPos(glm::vec3(max, y, z));
		asc *= -1;
	}

	shader->Update(*transform);
}

void Enemy::draw() 
{
	eSprite->Draw();
}