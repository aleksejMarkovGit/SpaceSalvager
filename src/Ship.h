#pragma once
#include "SFML/Graphics.hpp"
#include "BaseGameObject.h"

struct ShipControl {
	bool thrustOn{ false };
	bool rotateL{ false };
	bool rotateR{ false };
};

class Ship : public BaseGameObject {

public:

	void Init(const sf::Texture& textureIdle, const sf::Texture& textureThrust, const sf::Vector2f startPos, const sf::Vector2f scale = { 1.f, 1.f });
	void Reset(const sf::Vector2f startPos);
	void Update(const sf::Time dt) override;

	void setShipControl(const ShipControl& control);

	size_t getHealth() const { return m_health; }
	size_t getMaxHealth() const { return m_maxhealth; }

	void Repair(size_t addHealth);
	void TakeDamage(size_t damage);

private:

	size_t m_health{0};
	const size_t m_maxhealth{ 100 };

	const sf::Texture* m_idleTexture{nullptr};
	const sf::Texture* m_thrustTexture{nullptr};

	const float maxThrustForce{ 500.f };
	const float rotationSpeed{ 180.f }; 
	const float maxSpeed{ 700.f }; 

	bool thrustOn{ false };
	bool rotateL{ false };
	bool rotateR{ false };

	sf::Vector2f acceleration{ 0.f, 0.f };
	sf::Vector2f force{ 0.f, 0.f };
	float rotation{ 0.f }; //deg
	float currentThrust{ 0.f };
	float thrustPerSecond {250.f};
	
	void UpdatePosition(const sf::Time dt);
	void UpdateStateSystemShip(const sf::Time dt);
	void CorrectSpeed();
	void Animation();
};