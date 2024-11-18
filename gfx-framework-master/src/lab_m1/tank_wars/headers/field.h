#ifndef FIELD_H
#define FIELD_H

#include "utils/glm_utils.h"

#include <vector>
#include <cmath>

namespace field
{
	// Calculates y coordinate 
	float CalculateY(glm::ivec2& resolution, float t);

	// Stores (x, y) for every point on field
	void BuildField(glm::ivec2& resolution,
		std::vector<std::pair<float, float>>& fieldHeights);

	// Renders field
	glm::mat3 GenerateField(float xA, float xB, float yA, float yB);

	// Deforms field
	void DeformsField(glm::vec2 projectilePos, float deformRadius,
		std::vector <std::pair<float, float>>& fieldHeights);

	// Balances field
	void BalanceField(std::vector<std::pair<float, float>>& fieldHeights,
		float deltaTime, float heightThreshold, float balanceFactor);
}

#endif // !FIELD_H
