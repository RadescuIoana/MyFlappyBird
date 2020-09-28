#pragma once
#include <include/glm.h>

class Pipes
{
public:
	float translateDown, translateUp;
	float dh, x;
	float farXR, farXL, farXEdgeR, farXEdgeL;
	float farYUp, farYDown, farYEdgeUp, farYEdgeDown;
	int checked;
	glm::mat3 upPipeMatrix, downPipeMatrix;

	Pipes();
	Pipes(float ax, float atranslateDown, float maxY, float birdSpace);
	~Pipes();

	void Pipes::Reset(float maxX, float maxY, float birdSpace);
	void Pipes::Slide(float maxX, float maxY, float birdSpace, float deltaTimeSeconds, float speed, int startMoving, int *score, float xBird, float birdRadius);

private:

};