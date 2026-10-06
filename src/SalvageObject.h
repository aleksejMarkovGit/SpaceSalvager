#pragma once
#include "SFML/Graphics.hpp"

class SalvageObject{

public:
		
	void Init(const sf::Texture& texture, const sf::Vector2f startPos, const sf::Vector2f scale = { 1.f, 1.f });
	void Reset(sf::Vector2f startPos);
	const sf::Vector2f& getPos() const { return m_sprite.getPosition(); };
	void setPos(sf::Vector2f pos) { m_sprite.setPosition(pos); };
	const sf::Sprite& getSprite() const { return m_sprite; }

private:
	
	sf::Sprite m_sprite;
};

