#pragma once

#include <array>
#include <exception>
#include <string>
#include "SFML/Graphics.hpp"

namespace Data{

	enum class TEXTURE : size_t {
		BACKGROUND,
		SHIP_THRUST,
		SHIP_IDLE,
		ASTEROID,
		FUEL,
		SIZE
	};

	enum class FONT : size_t {
		SANSATION,
		SIZE
	};
}

class ResourceManager {
	
public:

	void LoadResource();
	const sf::Texture& getTexture(Data::TEXTURE name) const;
	const sf::Font& getFont(Data::FONT name) const;

private:
	std::array<sf::Texture, (size_t)Data::TEXTURE::SIZE> dataBaseTexture;
	std::array<sf::Font, (size_t)Data::FONT::SIZE> dataBaseFont;

	bool resIsLoad{ false };
};

class ResourceManagerException : public std::exception {
public:
	ResourceManagerException(const std::string& message) : m_message(message) {}

	const char* what() const noexcept override {
		return m_message.c_str();
	}

private:

	std::string m_message;
};
