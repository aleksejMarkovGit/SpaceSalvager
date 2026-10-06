#include "InputManager.h"

void InputManager::SetBinding(const KeyBinding& binding){
	m_binding = binding;
}

void InputManager::BeginFrame(){
	for (auto& state : m_states) {
		state.pressed = false;
		state.released = false;
	}
}

void InputManager::ProcessEvent(const sf::Event & event){
	if (event.type == sf::Event::KeyPressed) {
		KeyPressed(event);
	}
	else if (event.type == sf::Event::KeyReleased) {
		KeyReleased(event);
	}
	else if (event.type == sf::Event::LostFocus) {
		ResetAll();
	}
}

bool InputManager::isHeld(Action action) const {
	bool expression = action == Action::COUNT;
	
	if (expression) {
		return false;
	}

	return m_states.at((size_t)action).held;
}

bool InputManager::isPressed(Action action) const {
	bool expression = action == Action::COUNT;

	if (expression) {
		return false;
	}

	return m_states.at((size_t)action).pressed;
}

bool InputManager::isReleased(Action action) const {
	bool expression = action == Action::COUNT;

	if (expression) {
		return false;
	}

	return m_states.at((size_t)action).released;
}

bool InputManager::TryGetAction(sf::Keyboard::Key key, Action& action){

	if (key == m_binding.Thrust) {
		action = Action::Thrust;
	}
	else if (key == m_binding.RotateLeft) {
		action = Action::RotateLeft;
	}
	else if (key == m_binding.RotateRight) {
		action = Action::RotateRight;
	}
	else if (key == m_binding.Interact) {
		action = Action::Interact;
	}
	else if (key == m_binding.Reset) {
		action = Action::Reset;
	}
	else {
		return false;
	}

	return true;
}

void InputManager::KeyPressed(const sf::Event & event){
	Action action;
	if (TryGetAction(event.key.code, action)) {
		ActionState& state = m_states.at((size_t)action);

		if (!state.held) {
			state.pressed = true;
		}

		state.held = true;
	}
}

void InputManager::KeyReleased(const sf::Event & event){
	
	Action action;

	if (TryGetAction(event.key.code, action)) {
		ActionState& state = m_states.at((size_t)action);
		
		if (state.held) {
			state.released = true;
		}

		state.held = false;
	}
}

void InputManager::ResetAll(){
	for (auto& state : m_states) {
		state.pressed = false;
		state.released = false;
		state.held = false;
	}
}
