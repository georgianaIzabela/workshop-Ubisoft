#include "Player.h"

Player::Player(Shader* shader, float size, string textureFile) {
	Vertex verts[] = {
		Vertex(glm::vec3(size, size, 0), glm::vec2(0, 1)),
		Vertex(glm::vec3(size, -size, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(-size, -size, 0), glm::vec2(1, 0)),
		Vertex(glm::vec3(-size, size, 0), glm::vec2(1, 1))
	};

	this->pSprite = new Sprite(verts, sizeof(verts) / sizeof (verts[0]), textureFile.c_str());
	this->shader = shader;
	this->transform = new Transform;


}
	

Player::~Player(void) {
	delete pSprite;
	delete transform;
}

void Player::draw() {
	pSprite->Draw();
}


void Player::setInBounds(float x, float y, float z) {
	
	const float xmax = 0.8f;
	const float ymax = 0.8f;
	
	if (fabs(x) < xmax && fabs(y) < ymax ) {
		transform->SetPos(glm::vec3(x, y, z));
	} else
		if (fabs(x) >= xmax && fabs(y) >= ymax) {
			transform->SetPos(glm::vec3(x < 0 ? -xmax : xmax, y < 0 ? -ymax : ymax, z));
	}else {
		if (fabs(y) >= ymax) {
			transform->SetPos(glm::vec3(x, y < 0 ? -ymax : ymax, z));
		} else {
				transform->SetPos(glm::vec3(x < 0 ? -xmax : xmax, y, z));
		}
	}
}
void Player::move(GLFWwindow* window) {
	const float counter = 0.01f;
	float x, y, z;
	x = transform->GetPos().x;
	y = transform->GetPos().y;
	z = transform->GetPos().z;

	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_UP)) {
		y += counter;
	}
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_DOWN)) {
		y -= counter;
	}
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_LEFT)) {
		x -= counter;
	}
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_RIGHT)) {
		x += counter;
	}
	
	setInBounds(x, y, z);

	shader->Update(*transform);
}
