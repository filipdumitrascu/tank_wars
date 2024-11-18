#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "utils/glm_utils.h"

#include <list>
#include <vector>

namespace projectile
{
	struct Projectile {
		glm::vec2 position;
		glm::vec2 motion;
	};

	// Calculates cannon peek position.
	glm::vec2 CalculateCannonPeekPos(float oxTank, float oyTank, float frstHeightTrpz, float scndHeightTrpz,
		float cannonHeight, float angleTank, float angleCannon);

	// Adds one projectile to be rendered.
	void AddProjectile(std::list<projectile::Projectile>& projectilesTank, float angleCannon,
		float angleTank, float oxTank, float oyTank, float cannonHeight, float frstTrpzHeight, float scndTrpzHeight);
	
	// Renders the projectile.
	glm::mat3 GenerateProjectile(std::list<Projectile>::iterator& projectileIt, float deltaTimeSeconds);

	// Checks collison with tank
	bool CheckCollisionWithTank(glm::vec2 centerTank, float radius1,
		glm::vec2 centerProjectile, float radius2);

	// Checks collision with field
	bool CheckCollisionWithField(glm::vec2& projectile, std::vector<std::pair<float, float>>& fieldHeights,
		float projectileRadius);
}

#endif // !PROJECTILE_H
