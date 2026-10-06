#include <iostream>
#include "Engine.h"

int Engine::Run(){

	std::cout << "================ GAME START! ================\n";
	
	try {
		Init();
		std::cout << "Game is Init \n";
		exitCode = EXIT_CODE::GOOD;
	}
	catch (ResourceManagerException& resEx) {
		std::cout << resEx.what() << std::endl;
		std::cout << "Game not Init :( goodbye...\n";
		exitCode = EXIT_CODE::RES_NOT_LOAD;
		return exitCode;
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
		std::cout << "Game not Init :( goodbye...\n";
		exitCode = EXIT_CODE::ERROR;
		return exitCode;
	}

	m_clock.restart();

	std::cout << "Start main loop \n";

	//main loop
	while (m_win.isOpen()) {
		
		Input();

		Update(m_clock.restart());

		Draw();
	}

	std::cout << "Game closed. Goodbye!\n";

	return exitCode;
}

void Engine::Init(){

	m_resourceLoader.LoadResource();

	InitFPSInfo();

	m_worldBound = { 0.f, (float)heightWin, 0.f, (float)widthWin };
	m_world.InitWorld(m_resourceLoader, m_worldBound);
	
	sf::VideoMode videoMode(widthWin, heightWin);
    m_win.create(videoMode, "Space Salvager", sf::Style::Default);
	m_win.setKeyRepeatEnabled(false);
	std::cout << "Create windows \"Space Salvager\" \n";

	m_hud.Init(m_resourceLoader, videoMode);

}

void Engine::InitFPSInfo(){
	const sf::Font& font = m_resourceLoader.getFont(Data::FONT::SANSATION);
	m_textFps.setFont(font);
	m_textFps.setCharacterSize(20);
	m_textFps.setFillColor(sf::Color::Yellow);
	m_textFps.setPosition(25.f, 10.f);
}






