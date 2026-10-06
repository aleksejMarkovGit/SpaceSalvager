#include "GameplayManager.h"
#include "RandomNumber.h"

void GameplayManager::Init(const ResourceManager& resource, const WorldBound worldBounds){
	
	timerGameOver = timeToGameOver;
	m_worldBounds = worldBounds;

	const sf::Texture& textureFuel = resource.getTexture(Data::TEXTURE::FUEL);
	sf::Vector2f startPos = generateObjectPos();
	m_salvageObject.Init(textureFuel, startPos, sf::Vector2f(0.2f, 0.2f));
}

void GameplayManager::Reset(){
	timerGameOver = timeToGameOver;
	m_cargoCount = 0;

	sf::Vector2f newPos = generateObjectPos();
	m_salvageObject.Reset(newPos);
}

void GameplayManager::Input(bool interactive){
	m_interactive = interactive;
}

GameState GameplayManager::Update(const sf::Time dt, Ship& ship) {

	GameState gameState{GameState::NONE};

	sf::FloatRect shipRect = ship.getSprite().getGlobalBounds();
	sf::FloatRect salvageRect = m_salvageObject.getSprite().getGlobalBounds();

	if (shipRect.intersects(salvageRect) && m_interactive) {
		m_cargoCount++;
		ship.Repair(3);

		sf::Vector2f newPos = generateObjectPos();
		m_salvageObject.Reset(newPos);
	}

	if (ship.getHealth() == 0) {
		gameState = GameState::DisableControl;
		timerGameOver -= dt;
		if (timerGameOver.asSeconds() <= 0.f) {
			gameState = GameState::GameOver;
		}
	}
	else {
		timerGameOver = timeToGameOver;
		gameState = GameState::Run;
	}

	return gameState;
}

void GameplayManager::Draw(sf::RenderWindow & renderWin) const{
	renderWin.draw(m_salvageObject.getSprite());
}

sf::Vector2f GameplayManager::generateObjectPos(){
	const float m_ResOffset{ 100.f };

	sf::Vector2f pos;
	pos.x = randomGenerator.getFloat(m_worldBounds.left + m_ResOffset, m_worldBounds.right - m_ResOffset);
	pos.y = randomGenerator.getFloat(m_worldBounds.top + m_ResOffset, m_worldBounds.bottom - m_ResOffset);

	return pos;
}
