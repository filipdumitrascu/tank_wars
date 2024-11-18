#include "../headers/tank.h"
#include "../headers/transforms2D.h"
#include "../headers/literals.h"


glm::mat3 tank::GenerateTankBody(float oxTank, float& oyTank, float& angleTank,
    std::vector<std::pair<float, float>>& fieldHeights, glm::ivec2 res)
{
    glm::mat3 modelMatrix = glm::mat3(1);

    if (oxTank < 0 || oxTank >= res.x) {
        oyTank = 0;
        float angle = 0;

        modelMatrix *= transforms2D::Translate(oxTank, oyTank) * transforms2D::Rotate(angle);
        return modelMatrix;
    }

    size_t square = (size_t) std::floor(oxTank / lit::unitsPerPoint);

    float xA = fieldHeights[square].first;
    float yA = fieldHeights[square].second;

    float xB = fieldHeights[square + 1].first;
    float yB = fieldHeights[square + 1].second;

    oyTank = yA + ((oxTank - xA) / (xB - xA)) * (yB - yA);
    angleTank = atan2(yB - yA, xB - xA);

    if (oyTank < 0) {
        oyTank = 0.0f;
        angleTank = 0.0f;
    }

    modelMatrix *= transforms2D::Translate(oxTank, oyTank) * transforms2D::Rotate(angleTank);

    return modelMatrix;
}

glm::mat3 tank::GenerateCannon(float angleCannon, float height1, float height2)
{
    glm::mat3 modelMatrixCannon = glm::mat3(1);

    float oyCenterTurret = height1 + height2;

    modelMatrixCannon = transforms2D::Translate(0, oyCenterTurret) * transforms2D::Rotate(angleCannon)
                       * transforms2D::Translate(0, -oyCenterTurret);
                                  
    return modelMatrixCannon;
}
