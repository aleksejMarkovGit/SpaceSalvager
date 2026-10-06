#include "Engine.h"
#include <string>

void Engine::Update(const sf::Time dt) {
	m_textFps.setString("fps = " + std::to_string(1.f / dt.asSeconds()));

	if (m_world.getState() != GameState::GameOver) {
		m_world.Update(dt);
	}
	else if (m_inputManager.isPressed(Action::Reset)) {
		m_world.Reset();
	}

	m_hud.Update(m_world.getHudData());
}