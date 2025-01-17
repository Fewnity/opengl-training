//
// Created by gaetz on 04/12/2019.
//

#include "Scene_027_GregTess.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>
#include <cmath>
#include "CubeMesh.h"

bool isWireFrame = true;


Scene_027_GregTess::Scene_027_GregTess()
{
}

Scene_027_GregTess::~Scene_027_GregTess() {
	clean();
}

void Scene_027_GregTess::setGame(Game* _game) {
	game = _game;
}

GLuint vao;

void Scene_027_GregTess::load() {
	std::srand((int)std::time(nullptr));
	Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), SHADER_TECS(SHADER_NAME), SHADER_TESE(SHADER_NAME), "", SHADER_ID(SHADER_NAME));
	projection = Matrix4::createPerspectiveFOV(50.1f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glPatchParameteri(GL_PATCH_VERTICES, 3);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	cubeMesh = new CubeMesh();
	cubeMesh->load();

	shader = Assets::getShader(SHADER_ID(SHADER_NAME));

	cubes.emplace_back(0.0f, 0.0f, cubeMesh);
}

void Scene_027_GregTess::clean() {
	cubeMesh->clean();
	delete cubeMesh;
}

void Scene_027_GregTess::pause() {
}

void Scene_027_GregTess::resume() {
}

void Scene_027_GregTess::handleEvent(const InputState& inputState) {
}

void Scene_027_GregTess::update(float dt) {
	for (auto& cube : cubes) {
		cube.update();
	}
	float formerXPosition = cubes[0].getX();
	cubes[0].setPosition(newXPosition, cubes[0].getY());
	newXPosition = std::sinf(gameTime) / 4.0f;
	gameTime += dt * 3;
}

void Scene_027_GregTess::draw() {

	static const GLfloat bgColor[] = { 0.2f, 0.0f, 0.2f, 1.0f };

	glClearBufferfv(GL_COLOR, 0, bgColor);
	shader.use();
	shader.setMatrix4("proj_matrix", projection);
	shader.setInteger("tessLevel", 1 + (int)((0.5f + (std::sinf(gameTime) / 2.0f)) * 10));

	if(isWireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (auto& cube : cubes) 
	{
		cube.drawTesselation(shader);
	}
}
