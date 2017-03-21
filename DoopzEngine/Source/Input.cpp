#include "Input.h"

Input::Input()
{
	
}

bool Input::GetKey(SDL_Keycode _key)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (keys.at(i) == _key)
		{
			return true;
		}
	}

	return false;
}

void Input::KeyDown(SDL_Keycode _key)
{
	if (!GetKey(_key))
	{
		keys.push_back(_key);
	}
}

void Input::KeyUp(SDL_Keycode _key)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (keys.at(i) == _key)
		{
			keys.erase(keys.begin() + i);
			i--;
		}
	}
}

bool Input::GetButton(int _button)
{
	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons.at(i) == _button)
		{
			return true;
		}
	}

	return false;
}

void Input::ButtonDown(int _button)
{
	if (!GetButton(_button))
	{
		buttons.push_back(_button);
	}
}

void Input::ButtonUp(int _button)
{
	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons.at(i) == _button)
		{
			buttons.erase(buttons.begin() + i);
			i--;
		}
	}
}

void Input::UpdateMousePos(float _x, float _y)
{
	mousePos[0] = _x;
	mousePos[1] = _y;
}

std::vector<float> Input::GetMousePos()
{
	return mousePos;
}

void Input::Update()
{

	if (SDL_PollEvent(&m_event) != 0)
	{
		switch (m_event.type)
		{
		case SDL_KEYDOWN:
			KeyDown(m_event.key.keysym.sym);
			break;

		case SDL_KEYUP:
			KeyUp(m_event.key.keysym.sym);
			break;

		case SDL_QUIT:
			KeyDown(SDLK_ESCAPE);
			break;

		case SDL_MOUSEBUTTONDOWN:
			ButtonDown(m_event.button.button);
			break;

		case SDL_MOUSEBUTTONUP:
			ButtonUp(m_event.button.button);
			break;

		case SDL_MOUSEMOTION:
			UpdateMousePos(m_event.motion.x, m_event.motion.y);
			break;

		}

	}
}