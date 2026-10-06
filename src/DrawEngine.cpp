#include "Engine.h"

void Engine::Draw() {
	m_win.clear();

	m_world.Draw(m_win);
	m_hud.Draw(m_win);

	if (drawDebugInfo) {
		m_win.draw(m_textFps);
	}

	m_win.display();
}