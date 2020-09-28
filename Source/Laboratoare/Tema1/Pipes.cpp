#include "Pipes.h"
#include "Transform2D.h"

Pipes::Pipes()
{
}

Pipes::Pipes(float ax, float atranslateDown, float maxY, float birdSpace)
{
	x = ax;
	translateDown = -atranslateDown;
	dh = maxY + translateDown + 40;
	translateUp = dh + birdSpace + 40;
	farXR = 100 + x;
	farXL = x;
	farXEdgeR = 103 + x;
	farXEdgeL = -3 + x;
	farYEdgeUp = translateUp;
	farYDown = dh - 40;
	farYUp = farYEdgeUp + 40;
	farYEdgeDown = dh;
	checked = 0;
	downPipeMatrix = glm::mat3(1);
	upPipeMatrix = glm::mat3(1);
}

Pipes::~Pipes()
{
}

void Pipes::Reset(float maxX, float maxY, float birdSpace)
{
	x = maxX;
	translateDown = -1 * (rand() % 340 + 380);
	dh = maxY + translateDown + 40;
	translateUp = dh + birdSpace + 40;
	farXR = 100 + x;
	farXL = x;
	farXEdgeR = 103 + x;
	farXEdgeL = -3 + x;
	farYEdgeUp = translateUp;
	farYDown = dh - 40;
	farYUp = farYEdgeUp + 40;
	farYEdgeDown = dh;
	checked = 0;
}

void Pipes::Slide(float maxX, float maxY, float birdSpace, float deltaTimeSeconds, float speed, int startMoving, int *score, float xBird, float birdRadius)
{	
	downPipeMatrix = glm::mat3(1);
	upPipeMatrix = glm::mat3(1);

	if (checked == 0 && xBird - birdRadius >= x)
	{
		(*score)++;
		checked = 1;
	}

	if (x <= -100)
	{
		Reset(maxX, maxY, birdSpace);
			
	}

	downPipeMatrix *= Transform2D::Translate(x, translateDown);
	upPipeMatrix *= Transform2D::Translate(x, translateUp);
	if (startMoving == 1)
	{
		x -= deltaTimeSeconds * speed;
		farXR -= deltaTimeSeconds * speed; 
		farXL -= deltaTimeSeconds * speed;
		farXEdgeR -= deltaTimeSeconds * speed;
		farXEdgeL -= deltaTimeSeconds * speed;
	}
		
}

