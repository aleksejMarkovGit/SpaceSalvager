#include "ResourceManager.h"

void ResourceManager::LoadResource(){

	if (!resIsLoad) {

        //===Texture===
		sf::Texture& textureBackground = dataBaseTexture.at((size_t)Data::TEXTURE::BACKGROUND);
        if (!textureBackground.loadFromFile("res/texture/backgrounds.png")) throw ResourceManagerException("backgrounds.png is not loaded");

		sf::Texture& texturThrustShip = dataBaseTexture.at((size_t)Data::TEXTURE::SHIP_THRUST);
        if (!texturThrustShip.loadFromFile("res/texture/ship.png")) throw ResourceManagerException("ship.png is not loaded");

		sf::Texture& textureShipIdle = dataBaseTexture.at((size_t)Data::TEXTURE::SHIP_IDLE);
        if (!textureShipIdle.loadFromFile("res/texture/shipIdle.png")) throw ResourceManagerException("ship_noThrust.png is not loaded");

		sf::Texture& textureAsteroid = dataBaseTexture.at((size_t)Data::TEXTURE::ASTEROID);
        if (!textureAsteroid.loadFromFile("res/texture/asteroid.png")) throw ResourceManagerException("asteroid.png is not loaded");

		sf::Texture& textureFuel = dataBaseTexture.at((size_t)Data::TEXTURE::FUEL);
        if (!textureFuel.loadFromFile("res/texture/fuel.png")) throw ResourceManagerException("fuel.png is not loaded");

        //===Font===
		sf::Font& gameFont = dataBaseFont.at((size_t)Data::FONT::SANSATION);
        if (!gameFont.loadFromFile("res/fonts/sansation.ttf")) throw ResourceManagerException("sansation.ttf is not loaded");

		//
		resIsLoad = true;
	}
}

const sf::Texture& ResourceManager::getTexture(Data::TEXTURE name) const{
	return dataBaseTexture.at((size_t)name);
}

const sf::Font& ResourceManager::getFont(Data::FONT name) const{
	return dataBaseFont.at((size_t)name);
}
