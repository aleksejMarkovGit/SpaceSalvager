#pragma once

#include "SFML/Graphics.hpp"

struct PhysicalBody {
	sf::Vector2f position{0.f,0.f};
	sf::Vector2f velocity{0.f, 0.f};
	float mass{1.f};
	float restitution{0.9f};
	float collisionRadius{ 0.f };
};

class BaseGameObject {

protected:

	PhysicalBody m_physicalBody;
	sf::Sprite m_sprite;

public:

	virtual void Update(const sf::Time dt) = 0;

	PhysicalBody& getPhysicalBody() { return m_physicalBody; }
	const sf::Sprite& getSprite() const { return m_sprite; }

	virtual ~BaseGameObject() {}
};