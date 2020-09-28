#include "Game.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Objects2D.h"
#include "Pipes.h"
#include "Bird.h"

using namespace std;

Game::Game()
{
}

Game::~Game()
{
}

int Game::TestCollision(Pipes pipe, Bird bird)
{

	float ecX1 = sqrt(pow(bird.radius, 2) - pow((pipe.farYDown - bird.centerY), 2)) + bird.centerX;  //pt margine 
	float ecX2 = sqrt(pow(bird.radius, 2) - pow((pipe.farYEdgeDown - bird.centerY), 2)) + bird.centerX;
	float ecX3 = sqrt(pow(bird.radius, 2) - pow((pipe.farYEdgeUp - bird.centerY), 2)) + bird.centerX;
	float ecX4 = sqrt(pow(bird.radius, 2) - pow((pipe.farYUp - bird.centerY), 2)) + bird.centerX;
	float ecY1 = sqrt(pow(bird.radius, 2) - pow((pipe.farXL - bird.centerX), 2)) + bird.centerY;
	float ecY2 = sqrt(pow(bird.radius, 2) - pow((pipe.farXEdgeL - bird.centerX), 2)) + bird.centerY;

	if (ecY1 >= 0 && ecY1 <= pipe.farYDown)
	{	
		return 1;
	}
	if (ecY2 >= pipe.farYDown && ecY2 <=pipe.farYEdgeDown)
	{
		return 1;
	}
	if (ecY1 >= pipe.farYUp && ecY1 <= maxY)
	{
		return 1;
	}
	if (ecY2 >= pipe.farYEdgeUp && ecY2 <= pipe.farYUp)
	{
		return 1;
	}
	if (ecX1 >= pipe.farXEdgeL && ecX1 <= pipe.farXL)
	{
		return 1;
	}
	if (ecX2 >= pipe.farXEdgeL && ecX2 <= pipe.farXEdgeR)
	{
		return 1;
	}
	if (ecX3 >= pipe.farXEdgeL && ecX3 <= pipe.farXEdgeR)
	{
		return 1;
	}
	if (ecX4 >= pipe.farXEdgeL && ecX4 <= pipe.farXL)
	{
		return 1;
	}
	return 0;
}

void Game::GameReset()
{
	gameOver = 0;
	startMoving = 0;
	speed = 100;
	score = 0;
	pipes.erase(pipes.begin(), pipes.end());

	for (int i = 0; i < 3; i++) {
		float translateDown = (float)(rand() % 340 + 380);
		Pipes p = Pipes((i + 1) * 400.0f, translateDown, maxY, birdSpace);
		pipes.push_back(p);
	}

	bird = Bird(maxY - 50, maxY / 2, maxX);

}

void Game::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	//initializare joc
	glm::vec3 birdStart = glm::vec3(0, 0, 0);
	glm::vec3 downPipeStart = glm::vec3(0, 0, 0);
	glm::vec3 upPipeStart = glm::vec3(0, (float)resolution.y, 0);
	maxX = (float)resolution.x;
	maxY = (float)resolution.y;
	gameOver = 0;
	startMoving = 0;
	speed = 100;
	score = 0;
	bird = Bird(maxY - 60, maxY / 2, maxX);
	birdSpace = bird.radius * 10; //300

	for (int i = 0; i < 3; i++)
	{
		float translateDown = (float)(rand() % 340 + 380);
		Pipes p = Pipes((i + 1) * 400.0f, translateDown, maxY, birdSpace);
		pipes.push_back(p);
	}

	//creare mesh-uri pentru pasare si obstacole
	Mesh* bird = Objects2D::CreateBird("bird", birdStart, glm::vec3(1.00f, 0.73f, 0.20f), glm::vec3(1, 0.1f, 0.85f), glm::vec3(0, 0, 0.5f), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), true);
	AddMeshToList(bird);

	Mesh* upPipe = Objects2D::CreateUpPipe("upPipe", upPipeStart, maxY, glm::vec3(0, 0.6f, 0), true);
	AddMeshToList(upPipe);

	Mesh* downPipe = Objects2D::CreateDownPipe("downPipe", downPipeStart, maxY, glm::vec3(0, 0.6f, 0), true);
	AddMeshToList(downPipe);
}


void Game::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.70f, 0.75f, 1.00f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Game::Update(float deltaTimeSeconds)
{
	RenderMesh2D(meshes["bird"], shaders["VertexColor"], bird.birdMatrixMove);
	for (int i = 0; i < 3; i++)
	{
		if (gameOver == 0)
		{
				pipes[i].Slide(maxX, maxY, birdSpace, deltaTimeSeconds, speed, startMoving, &score, bird.centerX, bird.radius);
		}

		RenderMesh2D(meshes["downPipe"], shaders["VertexColor"], pipes[i].downPipeMatrix);
		RenderMesh2D(meshes["upPipe"], shaders["VertexColor"], pipes[i].upPipeMatrix);	
	}

	bird.Move(deltaTimeSeconds, &gameOver);

	for (int i = 0; i < 3; i++)
	{
		if (TestCollision(pipes[i], bird) == 1)
		{
			gameOver = 1;
		}
	}
}

void Game::FrameEnd()
{
}

void Game::OnInputUpdate(float deltaTime, int mods)
{
}

void Game::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE)
	{
		if (gameOver == 0)
		{
			bird.Rise();
			if (startMoving == 0)
			{
				startMoving = 1;
			}
		}else 
		{
			printf("Bye, bye, birdie!\n");
			printf("Score: %d\n", score);
			GameReset();
		}
	}
}

void Game::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Game::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Game::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Game::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Game::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Game::OnWindowResize(int width, int height)
{
}

