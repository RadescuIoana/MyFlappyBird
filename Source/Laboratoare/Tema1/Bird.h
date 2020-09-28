#pragma once
#include <include/glm.h>
#include "Pipes.h"

class Bird
{
public:
	Bird();
	Bird(float maxY, float y, float maxX);
	~Bird();
	float speedRise, speedFall;
	float maxY;
	float rotAngle;
	float accRise, gravAcc;
	int rotations;
	float radius;
	float centerY, centerX;
	glm::mat3 birdMatrixMove, birdMatrixTranslate, birdMatrixRotate;
	void Bird::Move(float deltaTimeSeconds, int *gameOver);
	void Bird::Rise();
	void Bird::Fall();

private:

};