#ifndef TANK_H
#define TANK_H

#include "utils/glm_utils.h"

#include <vector>
#include <cmath>

namespace tank
{
	// Renders the tank body (2 trapezoids one flipped and one semicircle on top)
	glm::mat3 GenerateTankBody(float oxTank, float& oyTank, float& angleTank,
		std::vector<std::pair<float, float>>& fieldHeights, glm::ivec2 res);

	// Renders the cannon (one rectangle vertically)
	glm::mat3 GenerateCannon(float angleCannon, float height1, float height2);
}

#endif /* TANK_H */
