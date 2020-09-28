#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Objects2D
{
	Mesh* CreateBird(std::string name, glm::vec3 center, glm::vec3 color1, glm::vec3 color2, glm::vec3 color3, glm::vec3 color4, glm::vec3 color5, bool fill);
	Mesh* CreateUpPipe(std::string name, glm::vec3 leftUpperCorner, float height, glm::vec3 color, bool fill);
	Mesh* CreateDownPipe(std::string name, glm::vec3 lefBottomCorner, float height, glm::vec3 color, bool fill);

}

