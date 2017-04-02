#ifndef _INPUT_H
#define _INPUT_H

#include <SDL.h>
#include <vector>

class Input
{

public:
	Input();
	bool GetKey(SDL_Keycode _key);
	bool GetButton(int _button);
	bool GetButtonDown(int _button);
	std::vector<float> GetMousePos();
	void Update();

private:
	SDL_Event m_event;

	std::vector<SDL_Keycode> keys;
	void KeyUp(SDL_Keycode _key);
	void KeyDown(SDL_Keycode _key);
	

	
	std::vector<int> buttons;
	std::vector<int> buttonsDown;
	void ButtonUp(int _button);
	void ButtonDown(int _button);
	
	std::vector<float> mousePos = { 0,0 };
	void UpdateMousePos(float _x, float _y);

	};

#endif