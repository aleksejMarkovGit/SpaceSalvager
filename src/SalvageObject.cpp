#include "SalvageObject.h"

void SalvageObject::Init(const sf::Texture & texture, const sf::Vector2f startPos, const sf::Vector2f scale) {

	m_sprite.setTexture(texture);
	m_sprite.setPosition(startPos);
	m_sprite.setScale(scale);
}

void SalvageObject::Reset(sf::Vector2f startPos){
	m_sprite.setPosition(startPos);
}

