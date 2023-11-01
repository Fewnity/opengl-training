//
// Created by gaetz on 04/12/2019.
//

#include "Scene_026_Greg.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>
#include <cmath>
#include "CubeMesh.h"


Scene_026_Greg::Scene_026_Greg()
{
}

Scene_026_Greg::~Scene_026_Greg() {
	clean();
}

void Scene_026_Greg::setGame(Game* _game) {
	game = _game;
}

int texNoiseTexture;
int texNoiseTexture2;
int texNoiseTexture3;
int texNoiseTexture4;

void Scene_026_Greg::load() {
	std::srand((int)std::time(nullptr));
	Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", "", SHADER_ID(SHADER_NAME));
	projection = Matrix4::createPerspectiveFOV(50.1f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);

	cubeMesh = new CubeMesh();
	cubeMesh->load();

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glActiveTexture(GL_TEXTURE0);
	Assets::loadTexture("assets/textures/noiseTexture.png", "noiseTexture");
	texNoiseTexture = Assets::getTexture("noiseTexture").id;
	glBindTexture(GL_TEXTURE_2D, texNoiseTexture);

	glActiveTexture(GL_TEXTURE1);
	Assets::loadTexture("assets/textures/noiseTexture2.png", "noiseTexture2");
	texNoiseTexture2 = Assets::getTexture("noiseTexture2").id;
	glBindTexture(GL_TEXTURE_2D, texNoiseTexture2);

	glActiveTexture(GL_TEXTURE2);
	Assets::loadTexture("assets/textures/noiseTexture3.png", "noiseTexture3");
	texNoiseTexture3 = Assets::getTexture("noiseTexture3").id;
	glBindTexture(GL_TEXTURE_2D, texNoiseTexture3);

	glActiveTexture(GL_TEXTURE3);
	Assets::loadTexture("assets/textures/noiseTexture4.png", "noiseTexture4");
	texNoiseTexture4 = Assets::getTexture("noiseTexture4").id;
	glBindTexture(GL_TEXTURE_2D, texNoiseTexture4);

	shader = Assets::getShader(SHADER_ID(SHADER_NAME));

	cubes.emplace_back(0.0f, 0.0f, cubeMesh);
}

void Scene_026_Greg::clean() {
	cubeMesh->clean();
	delete cubeMesh;
}

void Scene_026_Greg::pause() {
}

void Scene_026_Greg::resume() {
}

void Scene_026_Greg::handleEvent(const InputState& inputState) {
}

float time2;

void Scene_026_Greg::update(float dt) {
	for (auto& cube : cubes) {
		cube.update();
	}
	float formerXPosition = cubes[0].getX();
	cubes[0].setPosition(newXPosition, cubes[0].getY());
	time2 += dt * 3;
}

void Scene_026_Greg::draw() {

	static const GLfloat bgColor[] = { 0.0f, 0.0f, 0.2f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, bgColor);
	shader.use();
	shader.setMatrix4("proj_matrix", projection);
	shader.setFloat("timeSin", 0.5f + (std::sinf(time2) / 2.0f));
	shader.setFloat("timeCos", 0.5f + (std::cosf(time2) / 2.0f));
	shader.setFloat("timeT2", time2 / 10);

	for (auto& cube : cubes) 
	{
		cube.draw(shader);
	}
}
