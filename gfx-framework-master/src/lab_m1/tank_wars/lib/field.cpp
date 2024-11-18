#include "../headers/field.h"
#include "../headers/literals.h"
#include "../headers/transforms2D.h"

#include <cmath>

float field::CalculateY(glm::ivec2& resolution, float t)
{
    // Mapping function's y (0 <-> 2 * maxAmpl) to resolution y (0 <-> res.y) 
    float y = 0.25f * sin(t) + 0.5f * sin(3.0f * t) + 2.0f * sin(0.75f * t) + lit::maxAmplitude;
    y *= resolution.y / (lit::maxAmplitude * 4.0f); // 4.0f to shrink it

    return y;
}

void field::BuildField(glm::ivec2& resolution,
    std::vector<std::pair<float, float>>& fieldHeights)
{
    float t{};
    float y{};

    fieldHeights.reserve((size_t) (resolution.x / lit::unitsPerPoint));

    for (float x = 0; x <= resolution.x; x += lit::unitsPerPoint) {
        // Mapping resolution's x (0 <-> res.x) to choosen function's x (start <-> finish) 
        t = lit::startInterval + (lit::finishInterval - lit::startInterval)
           * (x - 0.0f) / (resolution.x - 0.0f);

        y = field::CalculateY(resolution, t);

        fieldHeights.push_back(std::make_pair(x, y));
    }
}

glm::mat3 field::GenerateField(float xA, float yA, float xB, float yB)
{
    glm::mat3 modelMatrix = glm::mat3(1);

    float slope = (yB - yA) / (xB - xA);

    modelMatrix *= transforms2D::Translate(xA, yA) * transforms2D::Shear(slope)
        * transforms2D::Scale((xB - xA) / lit::fieldSquareSide, std::max(yB, yA));

    return modelMatrix;
}

void field::DeformsField(glm::vec2 projectilePos, float deformRadius,
    std::vector<std::pair<float, float>>& fieldHeights)
{
    float smallestX = projectilePos.x - deformRadius;
    float biggestX = projectilePos.x + deformRadius;

    // More than these portions of field cannot be affected.
    size_t firstSquare = (size_t)std::floor(smallestX / lit::unitsPerPoint);
    size_t lastSquare = (size_t)std::floor(biggestX / lit::unitsPerPoint);

    for (size_t i = firstSquare; i <= lastSquare; ++i) {
        if (i < 0 || i >= fieldHeights.size()) {
            continue;
        }
        
        float xSquare = fieldHeights[i].first;
        float& ySquare = fieldHeights[i].second;

        // Checks if the portion of the field is affected.
        if (glm::distance(glm::vec2(xSquare, ySquare), projectilePos) <= deformRadius) {
            // Circle equation.
            ySquare = (float) (projectilePos.y 
                - sqrt(pow(deformRadius, 2) - pow(xSquare - projectilePos.x, 2)));
        }
    }   
}

void field::BalanceField(std::vector<std::pair<float, float>>& fieldHeights,
    float deltaTime, float heightThreshold, float balanceFactor)
{
    for (size_t i = 0; i < fieldHeights.size() - 1; ++i) {
        float& y1 = fieldHeights[i].second;
        float& y2 = fieldHeights[i + 1].second;

        if (std::abs(y1 - y2) > heightThreshold) {
            // distance * a balance factor
            float epsilon = std::abs(y1 - y2) * balanceFactor * deltaTime;

            if (y1 > y2) {
                y1 -= epsilon;
                y2 += epsilon;
                continue;
            }

            y1 += epsilon;
            y2 -= epsilon;
        }
    }
}
