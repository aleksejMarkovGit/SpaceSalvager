#pragma once

#include <array>

#include "SFML/Graphics.hpp"
#include "Ship.h"
#include "Asteroid.h"
#include "WorldBound.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "GameplayManager.h"
#include "InputManager.h"
#include "HUD.h"

class World {

public:

	void InitWorld(const ResourceManager& resource, const WorldBound worldBounds);
	void Reset();
	void Input(const InputManager& inputManager);
	void Update(const sf::Time dt);
	void Draw(sf::RenderWindow& renderWin) const;

	HUDData getHudData() const;
	GameState getState() const { return m_gameState; }

private:

	void ApplyCollisionInfo(const CollisionsInformation& collsionsInfo);

	void InitShip(const ResourceManager& resource);
	void InitBackground(const ResourceManager& resource);
	void InitAsteroid(const ResourceManager& resource);
	
	WorldBound m_worldBound;
	sf::Sprite spriteBackground;
	CollisionManager m_collisionManager;
	GameplayManager m_gameplayManager;
	GameState m_gameState{ GameState::NONE };

	//World objects
	Ship m_ship;
    std::array<Asteroid, 30> m_asteroids;
};
