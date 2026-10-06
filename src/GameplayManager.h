#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "WorldBound.h"
#include "SalvageObject.h"
#include "Ship.h"

enum class GameState {
	Run,
	DisableControl,
	GameOver,
	NONE
};

class GameplayManager{
public:
	
	void Init(const ResourceManager& resource, const WorldBound worldBounds);
	void Reset();
	void Input(bool interactive);
	GameState Update(const sf::Time dt, Ship& ship);
	void Draw(sf::RenderWindow& renderWin) const;

	size_t getCargoCount() const { return m_cargoCount; }

private:

	sf::Time timerGameOver;
	const sf::Time timeToGameOver{ sf::seconds(2.f) };

	sf::Vector2f generateObjectPos();
	
	WorldBound m_worldBounds;

	bool m_interactive{ false };
	SalvageObject m_salvageObject;

	size_t m_cargoCount{ 0 };
};

