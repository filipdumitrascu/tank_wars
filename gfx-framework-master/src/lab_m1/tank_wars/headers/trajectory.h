#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "utils/glm_utils.h"
#include <vector>


namespace trajectory
{
	// Generates trajectory rectangle oriented as throwing under an angle.s
	glm::mat3 GenerateTrajectoryRectangle(glm::vec2& previousPoint, float x, float y);
}

#endif //! TRAJECTORY_H
