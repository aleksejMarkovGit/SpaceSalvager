#pragma once

//sfml
#include "SFML/Graphics.hpp"
//other
#include "ResourceManager.h"

struct HUDData {
	size_t CargoCount{0};

	size_t Health{ 0 };
	size_t HealthMax{ 0 };

	bool GameOver{false};
};

enum class ModHUD {
	Game,
	GameOver,
	NONE
};

class HUD {

public:

	void Init(const ResourceManager& resManager, const sf::VideoMode videoMode);
	void Update(const HUDData& hudData);
	void Draw(sf::RenderWindow& renderer) const;

private:

	void UpdateGameOverOverlay(const HUDData & hudData);
	void UpdateGameOverlay(const HUDData & hudData);

	void UpdateScoreOverlay(const HUDData & hudData);
	void UpdateHealthOverlay(const HUDData & hudData);

	void DrawGameOverlay(sf::RenderWindow & renderer) const;
	void DrawGameOverOverlays(sf::RenderWindow & renderer) const;

	sf::VideoMode m_videoMode;
	ModHUD m_modHud{ ModHUD::NONE };

	sf::Text m_textGameOver;
	sf::Text m_textResCount;
	sf::Text m_textHealth;
	sf::Text m_textRestart;

	void InitHealthBar(const sf::VideoMode videoMode);

	sf::RectangleShape m_healthBar;
	sf::RectangleShape m_healthBarBorder;

	const float m_widthHealthBar{ 400.f };
	const float m_heightHealthBar{ 40.f };
};
