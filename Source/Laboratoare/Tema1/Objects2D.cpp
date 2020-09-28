#include "Objects2D.h"

#include <Core/Engine.h>

Mesh* Objects2D::CreateBird(std::string name, glm::vec3 center, glm::vec3 color1, glm::vec3 color2, glm::vec3 color3, glm::vec3 color4, glm::vec3 color5, bool fill)
{
	std::vector<VertexFormat> vertices =
	{

		VertexFormat(center + glm::vec3(60, 30, 0), color1), //0 galben
		VertexFormat(center + glm::vec3(50, 26, 0), color1),  //1 galben
		VertexFormat(center + glm::vec3(50, 26, 0), color2),  //2 
		VertexFormat(center + glm::vec3(48, 30, 0), color1),  //3 galben
		VertexFormat(center + glm::vec3(48, 30, 0), color2),  //4
		VertexFormat(center + glm::vec3(52, 36, 0), color1),  //5 galben
		VertexFormat(center + glm::vec3(52, 36, 0), color2),  //6
		VertexFormat(center + glm::vec3(40, 20, 0), color2),  //7
		VertexFormat(center + glm::vec3(16, 20, 0), color2),  //8
		VertexFormat(center + glm::vec3(24, 36, 0), color2),  //9
		VertexFormat(center + glm::vec3(8, 12, 0), color2),  //10
		VertexFormat(center + glm::vec3(10, 14, 0), color3),  //11
		VertexFormat(center + glm::vec3(14, 36, 0), color3),  //12
		VertexFormat(center + glm::vec3(22, 42, 0), color3),  //13
		VertexFormat(center + glm::vec3(42, 52, 0), color2),  //14
		VertexFormat(center + glm::vec3(45, 47, 0), color2),  //15
		VertexFormat(center + glm::vec3(50, 54, 0), color2),  //16

	};
	
	vertices.push_back(VertexFormat(center + glm::vec3(54, 40, 0), color4));
	for (int i = 0; i < 3600; i++) {
		vertices.push_back(VertexFormat(center + glm::vec3(54, 40, 0) + glm::vec3(cos(i / 3600.0 * 2 * 3.14) * 1.5f, sin(i / 3600.0 * 2 * 3.14) * 1.5f, 0), color4));
	}
	vertices.push_back(VertexFormat(center + glm::vec3(48, 40, 0), color5));
	for (int i = 0; i < 3600; i++) {
		vertices.push_back(VertexFormat(center + glm::vec3(48, 40, 0) + glm::vec3(cos(i / 3600.0 * 2 * 3.14) * 6, sin(i / 3600.0 * 2 * 3.14) * 6, 0), color5));
	}

	
	Mesh* bird = new Mesh(name);
	std::vector<unsigned short> indices = 
	{
		0, 1, 3,
		0, 3, 5,
		6, 7, 8,
		6, 8, 9,
		7, 10, 8,
		8, 11, 12,
		8, 12, 9,
		9, 12, 13,
		6, 9, 14,
		6, 4, 7,
		4, 2, 7,
		14, 16, 15
	};
	for (int i = 17; i <= 3617 - 1; i++) {
		indices.push_back(17);
		indices.push_back(i + 1);
		indices.push_back(i);
	}
	for (int i = 3618; i <= 7218 - 1; i++) {
		indices.push_back(3618);
		indices.push_back(i + 1);
		indices.push_back(i);
	}

	if (!fill) {
		bird->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
	}

	bird->InitFromData(vertices, indices);
	return bird;
}

Mesh* Objects2D::CreateUpPipe(std::string name, glm::vec3 leftUpperCorner, float height, glm::vec3 color, bool fill)
{
	glm::vec3 upCorner = leftUpperCorner;
	float width = 100.0f;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(upCorner + glm::vec3(0, 0, 0), color),  //0
		VertexFormat(upCorner + glm::vec3(width, 0, 0), color),  //1
		VertexFormat(upCorner + glm::vec3(width, -height, 0), color),  //2
		VertexFormat(upCorner + glm::vec3(0, -height, 0), color),  //3
		VertexFormat(upCorner + glm::vec3(-3, -height, 0), color - glm::vec3(0, -0.2f, 0)),  //4
		VertexFormat(upCorner + glm::vec3(width + 3, -height, 0), color - glm::vec3(0, -0.2f, 0)),  //5
		VertexFormat(upCorner + glm::vec3(width + 3, -height - 40, 0), color - glm::vec3(0, -0.2f, 0)),  //6
		VertexFormat(upCorner + glm::vec3(-3, -height -40, 0), color - glm::vec3(0, -0.2f, 0)),  //7
	};

	Mesh* pipe = new Mesh(name);
	std::vector<unsigned short> indices =
	{
		0, 2, 1,
		0, 3, 2,
		4, 6, 5,
		4, 7, 6,
	};

	if (!fill) {
		pipe->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	pipe->InitFromData(vertices, indices);
	return pipe;
}

Mesh* Objects2D::CreateDownPipe(std::string name, glm::vec3 leftBottomCorner, float height, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	float width = 100.0f;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color), //0
		VertexFormat(corner + glm::vec3(width, 0, 0), color), //1
		VertexFormat(corner + glm::vec3(width, height, 0), color),  //2
		VertexFormat(corner + glm::vec3(0, height, 0), color),  //3
		VertexFormat(corner + glm::vec3(-3, height, 0), color - glm::vec3(0, -0.2f, 0)),  //4
		VertexFormat(corner + glm::vec3(width + 3, height, 0), color - glm::vec3(0, -0.2f, 0)),  //5
		VertexFormat(corner + glm::vec3(width + 3, height + 40, 0), color - glm::vec3(0, -0.2f, 0)),  //6
		VertexFormat(corner + glm::vec3(-3, height + 40, 0), color - glm::vec3(0, -0.2f, 0)),  //7
		
	};

	Mesh* pipe = new Mesh(name);
	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		0, 2, 3,
		4, 5, 6,
		4, 6, 7,
	};

	if (!fill) {
		pipe->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	pipe->InitFromData(vertices, indices);
	return pipe;
}