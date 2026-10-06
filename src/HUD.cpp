#include "HUD.h"

#include <sstream>

void HUD::Init(const ResourceManager & resManager, const sf::VideoMode videoMode) {
	
	m_videoMode = videoMode;

	const sf::Font& hudFont = resManager.getFont(Data::FONT::SANSATION);
	const sf::Color textHudColor = sf::Color(41,249,246);

	m_textResCount.setFont(hudFont);
	m_textResCount.setFillColor(textHudColor);

	m_textHealth.setFont(hudFont);
	m_textHealth.setPosition((float)m_videoMode.width / 2, 95.f);
	m_textHealth.setFillColor(textHudColor);
	m_textHealth.setCharacterSize(30);

	m_textGameOver.setFont(hudFont);
	m_textGameOver.setString("GAME OVER.");
	m_textGameOver.setFillColor(textHudColor);
	m_textGameOver.setCharacterSize(100);
	sf::FloatRect rectGameOverText = m_textGameOver.getLocalBounds();
	m_textGameOver.setOrigin(rectGameOverText.left + rectGameOverText.width / 2.f, rectGameOverText.top + rectGameOverText.height / 2.f);
	m_textGameOver.setPosition((float)m_videoMode.width / 2, (float)m_videoMode.height / 2);

	m_textRestart.setFont(hudFont);
	m_textRestart.setString("PRESS R TO RESTART");
	m_textRestart.setFillColor(textHudColor);
	m_textRestart.setCharacterSize(50);
	sf::FloatRect rectRestartText = m_textRestart.getLocalBounds();
	m_textRestart.setOrigin(rectRestartText.left + rectRestartText.width / 2.f, rectRestartText.top + rectRestartText.height / 2.f);
	m_textRestart.setPosition((float)m_videoMode.width / 2, (float)m_videoMode.height / 2 + 80);

	InitHealthBar(videoMode);
}

void HUD::Update(const HUDData & hudData){

	if (hudData.GameOver) {
		m_modHud = ModHUD::GameOver;
		UpdateGameOverOverlay(hudData);
	}
	else {
		m_modHud = ModHUD::Game;
		UpdateGameOverlay(hudData);
	}
}

void HUD::Draw(sf::RenderWindow & renderer) const{
	
	switch (m_modHud)
	{
	case ModHUD::Game:
		DrawGameOverlay(renderer);
		break;
	case ModHUD::GameOver:
		DrawGameOverOverlays(renderer);
		break;
	default:
		break;
	}
}

void HUD::UpdateGameOverOverlay(const HUDData & hudData){
	m_textResCount.setCharacterSize(75);
	sf::FloatRect rectFontRes = m_textResCount.getLocalBounds();
	m_textResCount.setOrigin(rectFontRes.left + rectFontRes.width / 2.f, rectFontRes.top + rectFontRes.height / 2.f);
	m_textResCount.setPosition((float)m_videoMode.width / 2, (float)m_videoMode.height / 2 - 150);
}

void HUD::UpdateGameOverlay(const HUDData & hudData){
	UpdateScoreOverlay(hudData);
	UpdateHealthOverlay(hudData);
}

void HUD::UpdateScoreOverlay(const HUDData & hudData){

	std::stringstream ssRes;
	ssRes << "SCORE: " << hudData.CargoCount;
	m_textResCount.setString(ssRes.str());
	m_textResCount.setCharacterSize(30);
	sf::FloatRect rectFontRes = m_textResCount.getLocalBounds();
	m_textResCount.setOrigin(rectFontRes.left + rectFontRes.width / 2.f, rectFontRes.top + rectFontRes.height / 2.f);
	m_textResCount.setPosition((float)m_videoMode.width / 2, 45.f);
}

void HUD::UpdateHealthOverlay(const HUDData & hudData){

	std::stringstream ssHealth;
	ssHealth << "HEALTH: " << hudData.Health << " / " << hudData.HealthMax;
	m_textHealth.setString(ssHealth.str());
	sf::FloatRect rectFontHealth = m_textHealth.getLocalBounds();
	m_textHealth.setOrigin(rectFontHealth.left + rectFontHealth.width / 2.f, rectFontHealth.top + rectFontHealth.height / 2.f);

	float healthBarSizeCoef = (float)hudData.Health / (float)hudData.HealthMax;
	m_healthBar.setSize(sf::Vector2f(m_widthHealthBar * healthBarSizeCoef, m_heightHealthBar));
}

void HUD::DrawGameOverlay(sf::RenderWindow & renderer) const{
	renderer.draw(m_textResCount);
	renderer.draw(m_healthBarBorder);
	renderer.draw(m_healthBar);
	renderer.draw(m_textHealth);
}

void HUD::DrawGameOverOverlays(sf::RenderWindow & renderer) const{
	renderer.draw(m_textResCount);
	renderer.draw(m_textGameOver);
	renderer.draw(m_textRestart);
}

void HUD::InitHealthBar(const sf::VideoMode videoMode){

	sf::Vector2f sizeHealthBar(m_widthHealthBar, m_heightHealthBar);
	sf::Vector2f positionHealthBarBorder((float)videoMode.width / 2, 95.f);
	sf::Vector2f positionHealthBar;
	positionHealthBar.x = positionHealthBarBorder.x - (sizeHealthBar.x / 2.f);
	positionHealthBar.y = positionHealthBarBorder.y - (sizeHealthBar.y / 2.f);

	m_healthBarBorder.setPosition(positionHealthBarBorder);
	m_healthBar.setPosition(positionHealthBar);

	m_healthBarBorder.setOrigin(sizeHealthBar.x / 2.f, sizeHealthBar.y / 2.f);

	m_healthBar.setSize(sizeHealthBar);
	m_healthBarBorder.setSize(sizeHealthBar);
	m_healthBar.setFillColor(sf::Color::Red);
	m_healthBarBorder.setOutlineColor(sf::Color(41, 249, 246));
	m_healthBarBorder.setFillColor(sf::Color::Transparent);
	m_healthBarBorder.setOutlineThickness(2.f);
}
