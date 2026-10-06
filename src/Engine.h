#pragma once

//sfml
#include "SFML/Graphics.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"

//other
#include "WorldBound.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "World.h"
#include "HUD.h"

enum EXIT_CODE : int {
	GOOD = 0,
	ERROR,
	RES_NOT_LOAD
};

class Engine {

public:

	int Run();

private:

	void Init();
	void InitFPSInfo();

	void Input();
	void Update(const sf::Time dt);
	void Draw();
	
	sf::Event m_event;
	sf::Clock m_clock;
	sf::RenderWindow m_win;

	InputManager m_inputManager;
	ResourceManager m_resourceLoader;
	World m_world;
	WorldBound m_worldBound;
	HUD m_hud;

    const int widthWin{ 1920 };
    const int heightWin{ 1080 };
	
	bool drawDebugInfo{ false };
	int exitCode{ EXIT_CODE::ERROR };

	sf::Text m_textFps;
};
