#pragma once
#include "SFML/Graphics.hpp"
#include "BaseGameObject.h"

class Asteroid : public BaseGameObject {

public:

	void Init(const sf::Texture& texture, const sf::Vector2f startPos, const sf::Vector2f scale = sf::Vector2f(1.f,1.f));
	void Reset(const sf::Vector2f startPos);
	void Update(const sf::Time dt) override;

private:
	
	const float maxSpeed{ 700.f }; // px/s

	void correctSpeed();
};
