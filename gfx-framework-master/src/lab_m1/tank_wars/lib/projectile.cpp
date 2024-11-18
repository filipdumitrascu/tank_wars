#include "../headers/projectile.h"
#include "../headers/transforms2D.h"
#include "../headers/literals.h"

glm::vec2 projectile::CalculateCannonPeekPos(float oxTank, float oyTank, float frstTrpzHeight,
    float scndTrpzHeight, float cannonHeight, float angleTank, float angleCannon)
{
    float cannonPeekX = oxTank + cos(angleTank + glm::pi<float>() / 2.0f) * (frstTrpzHeight + scndTrpzHeight)
        + cannonHeight * cos(angleCannon + angleTank + glm::pi<float>() / 2.0f);

    float cannonPeekY = oyTank + sin(angleTank + glm::pi<float>() / 2.0f) * (frstTrpzHeight + scndTrpzHeight)
        + cannonHeight * sin(angleCannon + angleTank + glm::pi<float>() / 2.0f);

    return glm::vec2(cannonPeekX, cannonPeekY);
}

void projectile::AddProjectile(std::list<projectile::Projectile>& projectilesTank, float angleCannon,
    float angleTank, float oxTank, float oyTank, float cannonHeight,
    float frstTrpzHeight, float scndTrpzHeight)
{
    projectile::Projectile newProjectile{};
    newProjectile.position = projectile::CalculateCannonPeekPos(oxTank, oyTank, frstTrpzHeight,
        scndTrpzHeight, cannonHeight, angleTank, angleCannon);

    newProjectile.motion = glm::vec2(cos(angleCannon + angleTank + glm::pi<float>() / 2.0f),
        sin(angleCannon + angleTank + glm::pi<float>() / 2.0f)) * lit::initialSpeed;

    projectilesTank.push_back(newProjectile);
}

glm::mat3 projectile::GenerateProjectile(std::list<Projectile>::iterator& proj, float deltaTimeSeconds)
{
    proj->position += proj->motion * deltaTimeSeconds;
    proj->motion.y -= lit::gravity * deltaTimeSeconds;

    glm::mat3 modelMatrix = transforms2D::Translate(proj->position.x, proj->position.y);

    return modelMatrix;
}

bool projectile::CheckCollisionWithTank(glm::vec2 centerTank, float radius1,
    glm::vec2 centerProjectile, float radius2)
{
    float dist = glm::distance(centerTank, centerProjectile);
    return dist <= (radius1 + radius2);
}

bool projectile::CheckCollisionWithField(glm::vec2& projectile,
    std::vector<std::pair<float, float>>& fieldHeights, float projectileRadius)
{
    size_t square = (size_t)std::floor(projectile.x / lit::unitsPerPoint);

    if (square >= fieldHeights.size()) {
        return false;
    }

    float xA = fieldHeights[square].first;
    float yA = fieldHeights[square].second;

    float xB = fieldHeights[square + 1].first;
    float yB = fieldHeights[square + 1].second;

    float tCoef = (projectile.x - xA) / (xB - xA);

    float yField = yA * (1 - tCoef) + yB * tCoef;

    return (projectile.y - yField) <= projectileRadius;
}
