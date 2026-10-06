#include "World.h"
#include "RandomNumber.h"

void World::InitWorld(const ResourceManager& resource, const WorldBound worldBounds){

	m_worldBound = worldBounds;
	
	InitShip(resource);
	InitBackground(resource);
	InitAsteroid(resource);
	
	m_collisionManager.Init(worldBounds);
	m_gameplayManager.Init(resource, worldBounds);
}

void World::Reset(){
	float width = (m_worldBound.right - m_worldBound.left);
	float heigh = (m_worldBound.bottom - m_worldBound.top);
	m_ship.Reset(sf::Vector2f(width / 2.f, heigh / 2.f));

	for (auto & astertoid : m_asteroids) {
		sf::Vector2f pos;
		pos.x = randomGenerator.getFloat(m_worldBound.left, m_worldBound.right);
		pos.y = randomGenerator.getFloat(m_worldBound.top, m_worldBound.bottom);

		astertoid.Reset(pos);
	}

	m_collisionManager.Reset();
	m_gameplayManager.Reset();

	m_gameState = GameState::NONE;
}

void World::Input(const InputManager& inputManager){
	
	ShipControl shipControl;

	if (inputManager.isHeld(Action::RotateRight)) {
		shipControl.rotateR = true;
	}
	else if (inputManager.isHeld(Action::RotateLeft)) {
		shipControl.rotateL = true;
	}
	else {
		shipControl.rotateR = false;
		shipControl.rotateL = false;
	}

	if (inputManager.isHeld(Action::Thrust)) {
		shipControl.thrustOn = true;
	}
	else {
		shipControl.thrustOn = false;
	}

	m_ship.setShipControl(shipControl);

	m_gameplayManager.Input(inputManager.isPressed(Action::Interact));
}

void World::Update(const sf::Time dt){


	m_collisionManager.PushObject(m_ship);

	for (auto &asteroid : m_asteroids) {
		m_collisionManager.PushObject(asteroid);
	}

	m_ship.Update(dt);

	for (auto &asteroid : m_asteroids) {
		asteroid.Update(dt);
	}

	const CollisionsInformation& collsionsInfo = m_collisionManager.Update();
	ApplyCollisionInfo(collsionsInfo);

	m_gameState = m_gameplayManager.Update(dt, m_ship);
}

void World::Draw(sf::RenderWindow& renderWin) const {
	renderWin.draw(spriteBackground);

	for (auto &asteroid : m_asteroids) {
		renderWin.draw(asteroid.getSprite());
	}

	renderWin.draw(m_ship.getSprite());
	m_gameplayManager.Draw(renderWin);
}

HUDData World::getHudData() const{

	HUDData hudData;

	hudData.CargoCount = m_gameplayManager.getCargoCount();

	hudData.Health = m_ship.getHealth();
	hudData.HealthMax = m_ship.getMaxHealth();
	hudData.GameOver = (m_gameState == GameState::GameOver);

	return hudData;
}

void World::ApplyCollisionInfo(const CollisionsInformation & collsionsInfo){
	for (auto& collsionInfo : collsionsInfo) {
		
		if (collsionInfo.objectA == &m_ship || collsionInfo.objectB == &m_ship) {
			size_t damage = (size_t)(collsionInfo.impulseCollision / 50.f);
			m_ship.TakeDamage(damage);
		}
	}
}

void World::InitShip(const ResourceManager & resource){
	const sf::Texture& shipIdleTexture = resource.getTexture(Data::TEXTURE::SHIP_IDLE);
	const sf::Texture& shipThrustTexture = resource.getTexture(Data::TEXTURE::SHIP_THRUST);

	float width = (m_worldBound.right - m_worldBound.left);
	float heigh = (m_worldBound.bottom - m_worldBound.top);
	m_ship.Init(shipIdleTexture, shipThrustTexture, sf::Vector2f(width / 2.f, heigh / 2.f), sf::Vector2f(0.1f, 0.1f));
}

void World::InitBackground(const ResourceManager & resource){
	
	float width = (m_worldBound.right - m_worldBound.left);
	float heigh = (m_worldBound.bottom - m_worldBound.top);

	const sf::Texture& backgroundTexture = resource.getTexture(Data::TEXTURE::BACKGROUND);
	spriteBackground.setTexture(backgroundTexture);
	spriteBackground.setScale(width / spriteBackground.getLocalBounds().width, heigh / spriteBackground.getLocalBounds().height);
}

void World::InitAsteroid(const ResourceManager & resource){

	const sf::Texture& asteroidTexture = resource.getTexture(Data::TEXTURE::ASTEROID);

	for (auto& asteroid : m_asteroids) {
		sf::Vector2f pos;
		pos.x = randomGenerator.getFloat(m_worldBound.left, m_worldBound.right);
		pos.y = randomGenerator.getFloat(m_worldBound.top, m_worldBound.bottom);

		float scale = randomGenerator.getFloat(0.1f, 0.4f);

		asteroid.Init(asteroidTexture, pos, { scale, scale });
	}
}
