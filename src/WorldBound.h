#pragma once

struct WorldBound {
	float top{ 0.f };
	float bottom{ 0.f };

	float left{ 0.f };
	float right{ 0.f };

	WorldBound() {}

	WorldBound(float topBound, float bottomBound, float leftBound, float rightBound) :
		top(topBound),
		bottom(bottomBound),
		left(leftBound),
		right(rightBound) {}
};