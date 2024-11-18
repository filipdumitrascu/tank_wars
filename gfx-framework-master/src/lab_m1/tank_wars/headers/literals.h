#ifndef LITERALS_H
#define LITERALS_H

namespace lit
{	
	// proportions
	constexpr float frstTrpzTpLnPrprtn{ 22.04f };
	constexpr float frstTrpzBttmLnPrprtn{ 17.85f };
	constexpr float scndTrpzTpLnPrprtn{ 23.16f };
	constexpr float scndTrpzBttmLnPrprtn{ 27.42f };
	constexpr float frstTrpzHghtPrprtn{ 53.94f };
	constexpr float scndTrpzHghtPrprtn{ 95.0f };
	constexpr float cnBsPrprtn{ 210.0f };
	constexpr float cnnnHghtPrprtn{ 27.5f };
	constexpr float trrtRdsPrprtn{ 64.7f };
	constexpr float prjctlRdsPrprtn{ 460.0f };

	// trajectory
	constexpr float trajectoryHeight{ 2.5f };
	constexpr float trajectoryBase{ 1.0f };

	// deform
	constexpr float deformRadius{ 100.0f };
	constexpr float balanceFactor{ 0.5f };
	constexpr float heigthThreshold{ 12.5f };

	// throwing under an angle
	constexpr float initialSpeed{ 500.0f };
	constexpr float gravity{ 300.0f };

	// tank
	constexpr float maxTankLife{ 10.0f };

	// lifebar
	constexpr float lifeBarDistance{ 100.0f };

	// field
	constexpr float maxAmplitude{ 2.5f };
	constexpr float startInterval{ 6.0f };
	constexpr float finishInterval{ 24.0f };
	constexpr float unitsPerPoint{ 10.0f };
	constexpr float fieldSquareSide{ 1.0f };

	// colors
	constexpr glm::vec3 origin{ glm::vec3(0.0f, 0.0f, 0.0f) };
	constexpr glm::vec3 darkYellow{ glm::vec3(0.6f, 0.6f, 0) };
	constexpr glm::vec3 brown{ glm::vec3(0.5f, 0.25f, 0) };
	constexpr glm::vec3 darkBrown{ glm::vec3(0.36f, 0.25f, 0.20f) };
	constexpr glm::vec3 green{ glm::vec3(0, 0.95f, 0) };
	constexpr glm::vec3 darkGreen{ glm::vec3(0, 0.5f, 0) };
	constexpr glm::vec3 black{ glm::vec3(0, 0, 0) };
	constexpr glm::vec3 white{ glm::vec3(1, 1, 1) };

	// backgroud
	constexpr float backgroundRed{ 0.678f };
	constexpr float backgroundGreen{ 0.847f };
	constexpr float backgroundBlue{ 0.902f };
}

#endif // !LITERALS_H
