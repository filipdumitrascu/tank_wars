#include "headers/tank_wars.h"
#include "headers/field.h"
#include "headers/literals.h"
#include "headers/objects2D.h"
#include "headers/projectile.h"
#include "headers/tank.h"
#include "headers/trajectory.h"
#include "headers/transforms2D.h"

#include <algorithm>
#include <vector>
#include <list>

using namespace m1;


TankWars::TankWars()
{
    oxTank1 = 100.0f;
    oxTank2 = 0.0f;

    oyTank1 = 0.0f;
    oyTank2 = 0.0f;

    angleCannon1 = RADIANS(-30.0f);
    angleCannon2 = RADIANS(75.0f);

    angleTank1 = 0.0f;
    angleTank2 = 0.0f;

    frstTrpzTopLen = 0.0f;
    scndTrpzTopLen = 0.0f;

    frstTrpzBottomLen = 0.0f;
    scndTrpzBottomLen = 0.0f;

    frstTrpzHeight = 0.0f;
    scndTrpzHeight = 0.0f;

    cannonBase = 0.0f;
    cannonHeight = 0.0f;

    turretRadius = 0.0f;
    projectileRadius = 0.0f;

    tank1Life = (int)lit::maxTankLife;
    tank2Life = (int)lit::maxTankLife;
}

TankWars::~TankWars()
{
}

void TankWars::CreateMeshes()
{
    glm::ivec2 res = window->GetResolution();

    frstTrpzTopLen = res.x / lit::frstTrpzTpLnPrprtn;
    frstTrpzBottomLen = res.x / lit::frstTrpzBttmLnPrprtn;

    scndTrpzTopLen = res.x / lit::scndTrpzTpLnPrprtn;
    scndTrpzBottomLen = res.x / lit::scndTrpzBttmLnPrprtn;

    frstTrpzHeight = res.y / lit::frstTrpzHghtPrprtn;
    scndTrpzHeight = res.y / lit::scndTrpzHghtPrprtn;

    cannonBase = res.x / lit::cnBsPrprtn;
    cannonHeight = res.y / lit::cnnnHghtPrprtn;

    turretRadius = res.y / lit::trrtRdsPrprtn;
    projectileRadius = res.x / lit::prjctlRdsPrprtn;

    Mesh* sand = objects2D::CreateSquare("sand", lit::origin, lit::fieldSquareSide, lit::darkYellow);

    Mesh* tankBody1 = objects2D::CreateTrapezoidsWithCircle("tankBody1", lit::origin, frstTrpzTopLen, frstTrpzBottomLen,
        scndTrpzTopLen, scndTrpzBottomLen, turretRadius, frstTrpzHeight, scndTrpzHeight, lit::brown, lit::darkBrown);

    Mesh* tankBody2 = objects2D::CreateTrapezoidsWithCircle("tankBody2", lit::origin, frstTrpzTopLen, frstTrpzBottomLen,
        scndTrpzTopLen, scndTrpzBottomLen, turretRadius, frstTrpzHeight, scndTrpzHeight, lit::green, lit::darkGreen);

    Mesh* tankCannon = objects2D::CreateRectangle("tankCannon", tankBody1->vertices[5].position, cannonBase, cannonHeight,
        lit::black, true);

    Mesh* projectile = objects2D::CreateCircle("projectile", lit::origin, projectileRadius, lit::black);
    Mesh* trajectory = objects2D::CreateRectangle("trajectory", lit::origin, lit::trajectoryBase, lit::trajectoryHeight, lit::white, true);

    Mesh* healthBarOutLine = objects2D::CreateRectangle("healthBarOutLine", lit::origin, frstTrpzBottomLen, frstTrpzHeight, lit::white, false);
    Mesh* healthBar = objects2D::CreateRectangle("healthBar", lit::origin, frstTrpzBottomLen, frstTrpzHeight, lit::white, true);

    AddMeshToList(sand);

    AddMeshToList(tankBody1);
    AddMeshToList(tankBody2);

    AddMeshToList(tankCannon);
    AddMeshToList(projectile);

    AddMeshToList(trajectory);
    AddMeshToList(healthBarOutLine);

    AddMeshToList(healthBar);
}

void TankWars::RenderTank(int tankLife, float oxTank, float& oyTank, float& angleTank, float angleCannon,
    std::vector<std::pair<float, float>>& fieldHeights, const std::string& name)
{
    if (tankLife <= 0) {
        return;
    }

    glm::mat3 modelMatrixTank = tank::GenerateTankBody(oxTank, oyTank, angleTank, fieldHeights, window->GetResolution());
    RenderMesh2D(meshes[name], shaders["VertexColor"], modelMatrixTank);

    glm::mat3 modelMatrixCannon = modelMatrixTank * tank::GenerateCannon(angleCannon, frstTrpzHeight, scndTrpzHeight);
    RenderMesh2D(meshes["tankCannon"], shaders["VertexColor"], modelMatrixCannon);

    glm::vec2 startPos = projectile::CalculateCannonPeekPos(oxTank, oyTank, frstTrpzHeight, scndTrpzHeight,
        cannonHeight, angleTank, angleCannon);

    RenderTrajectory(startPos, angleCannon, angleTank);
    RenderLifeBar(tankLife, oxTank, oyTank);
}

void TankWars::RenderProjectiles(int& tankLife, float oxTank, float oyTank, float angleTank, float deltaTimeSeconds,
    std::vector<std::pair<float, float>>& fieldHeights, std::list<projectile::Projectile>& projectilesTank)
{
    for (auto it = projectilesTank.begin(); it != projectilesTank.end();) {
        glm::mat3 modelMatrixProjectile = projectile::GenerateProjectile(it, deltaTimeSeconds);

        if (it->position.x < 0 || it->position.x > window->GetResolution().x || it->position.y < 0) {
            it = projectilesTank.erase(it);
            continue;
        }

        glm::vec2 tankCenter{};
        tankCenter.x = oxTank + cos(angleTank + glm::pi<float>() / 2.0f)
            * ((frstTrpzHeight + scndTrpzHeight + turretRadius) / 2.0f);

        tankCenter.y = oyTank + sin(angleTank + glm::pi<float>() / 2.0f)
            * ((frstTrpzHeight + scndTrpzHeight + turretRadius) / 2.0f);

        if (tankLife > 0 && projectile::CheckCollisionWithTank(tankCenter, frstTrpzBottomLen / 2.0f, it->position, 2.0f)) {
            it = projectilesTank.erase(it);
            tankLife--;

            continue;
        }

        if (projectile::CheckCollisionWithField(it->position, fieldHeights, projectileRadius)) {
            field::DeformsField(it->position, lit::deformRadius, fieldHeights);
            it = projectilesTank.erase(it);
            continue;
        }

        RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrixProjectile);
        ++it;
    }
}

void TankWars::RenderTrajectory(glm::vec2& startPos, float angleCannon, float angleTank)
{
    float x{};
    float y{ 1.0f };

    float t{};
    glm::vec2 previousPoint = startPos;

    while (y >= 0.0f) {
        /* 
            x = vt cos(alpha)
            y = vt sin(alpha) - 1/2 * g t^2
        */
        x = startPos.x + lit::initialSpeed * t * cos(angleCannon + angleTank + glm::pi<float>() / 2.0f);
        y = startPos.y + lit::initialSpeed * t * sin(angleCannon + angleTank + glm::pi<float>() / 2.0f)
            - 0.5f * lit::gravity * (float) std::pow(t, 2);

        t += 0.05f;

        glm::mat3 modelMatrixTrajectory = trajectory::GenerateTrajectoryRectangle(previousPoint, x, y);

        RenderMesh2D(meshes["trajectory"], shaders["VertexColor"], modelMatrixTrajectory);

        previousPoint = glm::vec2(x, y);
    }
}

void TankWars::RenderLifeBar(int tankLife, float oxTank, float oyTank)
{
    glm::mat3 modelMatrixOutline = transforms2D::Translate(oxTank, oyTank + lit::lifeBarDistance);
    RenderMesh2D(meshes["healthBarOutLine"], shaders["VertexColor"], modelMatrixOutline);

    float scaleX = tankLife / lit::maxTankLife;

    glm::mat3 modelMatrixFilled = transforms2D::Translate(oxTank - (1.0f - scaleX) * frstTrpzBottomLen / 2.0f,
        oyTank + lit::lifeBarDistance) * transforms2D::Scale(scaleX, 1);

    RenderMesh2D(meshes["healthBar"], shaders["VertexColor"], modelMatrixFilled);
}

void TankWars::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();

    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));

    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();

    GetCameraInput()->SetActive(false);

    // Creates the meshes used to build entities.
    CreateMeshes();

    // Builds the field heights coordinates.
    field::BuildField(resolution, fieldHeights);

    oxTank2 = resolution.x - 200.f;
}

void TankWars::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(lit::backgroundRed, lit::backgroundGreen, lit::backgroundBlue, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void TankWars::Update(float deltaTimeSeconds)
{
    glm::mat3 modelMatrixField = glm::mat3(1);

    field::BalanceField(fieldHeights, deltaTimeSeconds, lit::heigthThreshold, lit::balanceFactor);

    // field generation
    for (size_t i = 0; i < fieldHeights.size() - 1; ++i) {
        modelMatrixField = field::GenerateField(fieldHeights[i].first, fieldHeights[i].second,
            fieldHeights[i + 1].first, fieldHeights[i + 1].second);

        RenderMesh2D(meshes["sand"], shaders["VertexColor"], modelMatrixField);
    }

    // tanks generation
    RenderTank(tank1Life, oxTank1, oyTank1, angleTank1, angleCannon1, fieldHeights, "tankBody1");
    RenderTank(tank2Life, oxTank2, oyTank2, angleTank2, angleCannon2, fieldHeights, "tankBody2");

    // projectiles generation
    RenderProjectiles(tank2Life, oxTank2, oyTank2, angleTank2, deltaTimeSeconds, fieldHeights, projectilesTank1);
    RenderProjectiles(tank1Life, oxTank1, oyTank1, angleTank1, deltaTimeSeconds, fieldHeights, projectilesTank2);

}

void TankWars::FrameEnd()
{
}

void TankWars::OnInputUpdate(float deltaTime, int mods)
{
    if (window->KeyHold(GLFW_KEY_W)) {
        if (angleCannon1 > -glm::pi<float>() / 2.0f) {
            angleCannon1 -= RADIANS(30.0f) * deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        oxTank1 -= 100.0f * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        if (angleCannon1 < glm::pi<float>() / 2.0f) {
            angleCannon1 += RADIANS(30.0f) * deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        oxTank1 += 100.0f * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_UP)) {
        if (angleCannon2 > -glm::pi<float>() / 2.0f) {
            angleCannon2 -= RADIANS(30.0f) * deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_LEFT)) {
        oxTank2 -= 100.0f * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_DOWN)) {
        if (angleCannon2 < glm::pi<float>() / 2.0f) {
            angleCannon2 += RADIANS(30.0f) * deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        oxTank2 += 100.0f * deltaTime;
    }
}

void TankWars::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_SPACE && tank1Life > 0) {
        projectile::AddProjectile(projectilesTank1, angleCannon1, angleTank1, oxTank1, oyTank1,
            cannonHeight, frstTrpzHeight, scndTrpzHeight);
    }

    if (key == GLFW_KEY_ENTER && tank2Life > 0) {
        projectile::AddProjectile(projectilesTank2, angleCannon2, angleTank2, oxTank2, oyTank2,
            cannonHeight, frstTrpzHeight, scndTrpzHeight);
    }
}

void TankWars::OnKeyRelease(int key, int mods)
{
}

void TankWars::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void TankWars::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void TankWars::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void TankWars::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void TankWars::OnWindowResize(int width, int height)
{
}
