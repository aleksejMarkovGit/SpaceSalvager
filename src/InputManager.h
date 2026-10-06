#pragma once
#include <array>
#include "SFML/Graphics.hpp"

enum class Action : size_t {
	Thrust,
	RotateLeft,
	RotateRight,
	Interact,
	Reset,
	COUNT
};

struct ActionState {
	bool held{false};
	bool pressed{ false };
	bool released{ false };
};

struct KeyBinding {
	sf::Keyboard::Key Thrust{ sf::Keyboard::Up };
	sf::Keyboard::Key RotateLeft{ sf::Keyboard::Left };
	sf::Keyboard::Key RotateRight{ sf::Keyboard::Right };
	sf::Keyboard::Key Interact{ sf::Keyboard::E };
	sf::Keyboard::Key Reset{ sf::Keyboard::R };

	KeyBinding() {}
};

class InputManager
{
public:

	void SetBinding(const KeyBinding& binding);
	void BeginFrame();
	void ProcessEvent(const sf::Event& event);

	bool isHeld(Action action) const;
	bool isPressed(Action action) const;
	bool isReleased(Action action) const;

private:

	KeyBinding m_binding;
	std::array<ActionState, (size_t)Action::COUNT> m_states;

	bool TryGetAction(sf::Keyboard::Key key, Action& action);

	void KeyPressed(const sf::Event& event);
	void KeyReleased(const sf::Event& event);

	void ResetAll();
};

