#include <algorithm>
#include <cmath>

#include "Ship.h"
#include "MathFunction.h"

void Ship::Init(const sf::Texture& textureIdle, const sf::Texture& textureThrust, const sf::Vector2f startPos, const sf::Vector2f scale) {
	
	m_idleTexture = &textureIdle;
	m_thrustTexture = &textureThrust;
	
	m_sprite.setTexture(*m_idleTexture);
	m_sprite.setScale(scale);
	
	m_physicalBody.mass = 1.f;

	sf::FloatRect rectShip = m_sprite.getLocalBounds();
	m_sprite.setOrigin(rectShip.left + rectShip.width / 2.f, rectShip.top + rectShip.height / 2.f);
	m_sprite.setPosition(startPos);

	m_physicalBody.position = startPos;

	sf::FloatRect rect = m_sprite.getGlobalBounds();

	float widthCollision = (rect.width * 0.8f) / 2.f;
	float heightCollision = (rect.height * 0.8f) / 2.f;

	m_physicalBody.collisionRadius = std::min(widthCollision, heightCollision);

	m_health = m_maxhealth;
}

void Ship::Reset(const sf::Vector2f startPos){

	m_sprite.setTexture(*m_idleTexture);

	sf::FloatRect rectShip = m_sprite.getLocalBounds();
	m_sprite.setOrigin(rectShip.left + rectShip.width / 2.f, rectShip.top + rectShip.height / 2.f);
	m_sprite.setPosition(startPos);

	m_physicalBody.position = startPos;
	m_health = m_maxhealth;

	currentThrust = 0.f;
	rotation = 0.f;
	force = { 0.f, 0.f };
	acceleration = { 0.f, 0.f };
	m_physicalBody.velocity = { 0.f, 0.f };

	thrustOn = false;
	rotateL = false;
	rotateR = false;
}

void Ship::Update(const sf::Time dt){
	UpdateStateSystemShip(dt);
	Animation();
	UpdatePosition(dt);
}


void Ship::setShipControl(const ShipControl& control){
	thrustOn = control.thrustOn;
	rotateL = control.rotateL;
	rotateR = control.rotateR;
}

void Ship::Repair(size_t addHealth){

	m_health += addHealth;

	if (m_health > m_maxhealth) {
		m_health = m_maxhealth;
	}
}

void Ship::TakeDamage(size_t damage){

	if (damage > m_health) {
		m_health = 0;
	}
	else {
		m_health -= damage;
	}
}

void Ship::UpdatePosition(const sf::Time dt){
	
	using namespace MyMath;

	sf::Vector2f unitVec;
	unitVec.x = std::sin(MathFunction::deg2rad(rotation));
	unitVec.y = -1.f * std::cos(MathFunction::deg2rad(rotation));

	force = currentThrust * unitVec;
	acceleration = force / m_physicalBody.mass;
	m_physicalBody.velocity += acceleration * dt.asSeconds();
	CorrectSpeed();
	m_physicalBody.position += m_physicalBody.velocity * dt.asSeconds();

	m_sprite.setRotation(rotation);
	m_sprite.setPosition(m_physicalBody.position);
}

void Ship::UpdateStateSystemShip(const sf::Time dt){
	if (rotateR && m_health != 0) {
		rotation += (rotationSpeed * dt.asSeconds());
	}
	else if (rotateL && m_health != 0) {
		rotation -= (rotationSpeed * dt.asSeconds());
	}

	if (thrustOn && m_health != 0) {
		currentThrust += thrustPerSecond * dt.asSeconds();
		if (currentThrust > maxThrustForce) currentThrust = maxThrustForce;
	}
	else {
		currentThrust = 0.f;
	}
}

void Ship::CorrectSpeed(){

	float speed = MyMath::MathFunction::getVectorLength(m_physicalBody.velocity);

	if (speed > maxSpeed) {
		sf::Vector2f normalizeCoef;
		normalizeCoef = m_physicalBody.velocity / speed;
		m_physicalBody.velocity = normalizeCoef * maxSpeed;
	}
}

void Ship::Animation(){
	if (thrustOn && m_health != 0) {
		m_sprite.setTexture(*m_thrustTexture);
	}
	else {
		m_sprite.setTexture(*m_idleTexture);
	}
}
