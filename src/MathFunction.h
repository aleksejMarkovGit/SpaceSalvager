#pragma once

#include <cmath>
#include "SFML/System/Vector2.hpp"

namespace MyMath {

	const float PI{ 3.14159265358f };

	class MathFunction {
	public:

		static float deg2rad(float deg) {
			float rad = deg * (PI / 180.f);
			return rad;
		}

		template<class Type>
		static Type getVectorLength(sf::Vector2<Type> vector) {
			Type result = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
			return result;
		}
	};
}
