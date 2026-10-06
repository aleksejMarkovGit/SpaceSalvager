#include "Engine.h"

void Engine::Input() {

	m_inputManager.BeginFrame();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		m_win.close();
	}

	while (m_win.pollEvent(m_event)) {
		if (m_event.type == sf::Event::Closed) {
			m_win.close();
		}

		if (m_event.type == sf::Event::KeyPressed) {
			if (m_event.key.code == sf::Keyboard::F1) {
				drawDebugInfo = !drawDebugInfo;
			}
		}

		m_inputManager.ProcessEvent(m_event);
	}

	m_world.Input(m_inputManager);
}