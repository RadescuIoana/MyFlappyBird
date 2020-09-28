#include "Bird.h"

#include "Bird.h"
#include "Transform2D.h"
#include <math.h>

Bird::Bird()
{

}

Bird::Bird(float amaxY, float ay, float amaxX)
{
	speedRise = 0;
	speedFall = 0;
	rotAngle = 0.05f;
	accRise = 100;
	gravAcc = 40;
	rotations = 0;
	maxY = amaxY;
	birdMatrixTranslate = glm::mat3(1) * Transform2D::Translate(amaxX / 15, amaxY / 2);
	birdMatrixRotate = glm::mat3(1);
	birdMatrixMove = birdMatrixTranslate;
	radius = 30;
	centerY =  30 + birdMatrixMove[2][1];
	centerX = 30 + birdMatrixMove[2][0];
}

Bird::~Bird()
{
}   

void Bird::Move(float deltaTimeSeconds, int *gameOver)
{
	if (speedRise > 0)
		{
			if (birdMatrixTranslate[2][1] >= maxY)
			{
				Fall();
				birdMatrixTranslate *= Transform2D::Translate(0, -speedFall);
				centerY -= speedFall;
				if (rotations > -5)
				{
					birdMatrixRotate *= Transform2D::Translate(30, 30);
					birdMatrixRotate *= Transform2D::Rotate(-rotAngle);
					birdMatrixRotate *= Transform2D::Translate(-30, -30);
					rotations--;
				}

				birdMatrixMove = glm::mat3(1) * birdMatrixTranslate * birdMatrixRotate;
			}
			birdMatrixTranslate *= Transform2D::Translate(0, speedRise);
			centerY += speedRise;
			if (rotations < 10)
			{
				birdMatrixRotate *= Transform2D::Translate(30, 30);
				birdMatrixRotate *= Transform2D::Rotate(rotAngle);
				birdMatrixRotate *= Transform2D::Translate(-30, -30);
				rotations++;
			}
			birdMatrixMove = glm::mat3(1) * birdMatrixTranslate * birdMatrixRotate;
			speedRise -= accRise * deltaTimeSeconds;

			if (speedRise < 0)
			{
				Fall();
				birdMatrixTranslate *= Transform2D::Translate(0, -speedFall);
				centerY -= speedFall;
				if (rotations > -5)
				{
					birdMatrixRotate *= Transform2D::Translate(30, 30);
					birdMatrixRotate *= Transform2D::Rotate(-rotAngle);
					birdMatrixRotate *= Transform2D::Translate(-30, -30);
					rotations--;
				}
				birdMatrixMove = glm::mat3(1) * birdMatrixTranslate * birdMatrixRotate;
			}
		}
		if (speedFall > 0)
		{
			if (birdMatrixTranslate[2][1] <= 0)
			{
				speedFall = 0;
				speedRise = 0;
				(*gameOver) = 1;
			}
			birdMatrixTranslate *= Transform2D::Translate(0, -speedFall);
			centerY -= speedFall;
			if (rotations > -15)
			{
				birdMatrixRotate *= Transform2D::Translate(30, 30);
				birdMatrixRotate *= Transform2D::Rotate(-rotAngle);
				birdMatrixRotate *= Transform2D::Translate(-30, -30);
				rotations--;
			}
			birdMatrixMove = glm::mat3(1) * birdMatrixTranslate * birdMatrixRotate;
			speedFall += gravAcc * deltaTimeSeconds;
		}
		
}

void Bird::Rise()
{
	speedRise = 20;
	speedFall = 0;
} 

void Bird::Fall()
{
	speedRise = 0;
	speedFall = 0.2f;
}

