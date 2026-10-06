#include <algorithm>
#include <cmath>

#include "Asteroid.h"
#include "RandomNumber.h"

void Asteroid::Init(const sf::Texture & texture, const sf::Vector2f startPos, const sf::Vector2f scale){
	m_sprite.setTexture(texture);
	m_sprite.setScale(scale);
	m_physicalBody.mass = 10.f * scale.x;
	
	sf::FloatRect rectAsteroid = m_sprite.getLocalBounds();
	m_sprite.setOrigin(rectAsteroid.left + rectAsteroid.width / 2.f, rectAsteroid.top + rectAsteroid.height / 2.f);
	m_sprite.setPosition(startPos);
	m_physicalBody.position = startPos;

	sf::FloatRect rect = m_sprite.getGlobalBounds();
	m_physicalBody.collisionRadius = std::min(rect.width / 2.f, rect.height / 2.f) * 0.9f;

	sf::Vector2f startVelosity;
	startVelosity.x = randomGenerator.getFloat(-15.f, 15.f);
	startVelosity.y = randomGenerator.getFloat(-15.f, 15.f);

	m_physicalBody.velocity = startVelosity;
}

void Asteroid::Reset(const sf::Vector2f startPos){
	sf::FloatRect rectAsteroid = m_sprite.getLocalBounds();
	m_sprite.setOrigin(rectAsteroid.left + rectAsteroid.width / 2.f, rectAsteroid.top + rectAsteroid.height / 2.f);
	m_sprite.setPosition(startPos);
	m_physicalBody.position = startPos;

	sf::Vector2f startVelosity;
	startVelosity.x = randomGenerator.getFloat(-15.f, 15.f);
	startVelosity.y = randomGenerator.getFloat(-15.f, 15.f);

	m_physicalBody.velocity = startVelosity;
}

void Asteroid::Update(const sf::Time dt){

	correctSpeed();

	m_physicalBody.position += m_physicalBody.velocity * dt.asSeconds();
	m_sprite.setPosition(m_physicalBody.position);
}

void Asteroid::correctSpeed() {

	float speed = std::sqrt(m_physicalBody.velocity.x * m_physicalBody.velocity.x + m_physicalBody.velocity.y * m_physicalBody.velocity.y);

	if (speed > maxSpeed) {
		sf::Vector2f normalizeCoef;
		normalizeCoef = m_physicalBody.velocity / speed;
		m_physicalBody.velocity = normalizeCoef * maxSpeed;
	}
}