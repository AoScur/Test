#include "InputManager.h"
#include <iostream>

//list<Keyboard::Key> InputManager::downList;
//list<Keyboard::Key> InputManager::ingList;
//list<Keyboard::Key> InputManager::upList;

vector<bool> InputManager::downList2(Keyboard::Key::KeyCount);
vector<bool> InputManager::ingList2(Keyboard::Key::KeyCount);
vector<bool> InputManager::upList2(Keyboard::Key::KeyCount);

void InputManager::ClearInput()
{
	/*downList.clear();
	upList.clear();*/
	fill(downList2.begin(), downList2.end(), false);
	fill(upList2.begin(), upList2.end(), false);
}

void InputManager::UpdateInput(Event& ev)
{
	switch (ev.type)
	{
	case Event::EventType::KeyPressed:
		//if (!GetKey(ev.key.code))
		if (ev.key.code != Keyboard::Key::Unknown &&
			!ingList2[ev.key.code])
		{
			downList2[(int)ev.key.code] = true;
			ingList2[(int)ev.key.code] = true;
			/*downList.push_back(ev.key.code);
			ingList.push_back(ev.key.code);*/
		}
		break;
	case Event::EventType::KeyReleased:
		if (ev.key.code != Keyboard::Key::Unknown)
		{

			ingList2[(int)ev.key.code] = false;
			upList2[(int)ev.key.code] = true;
		}
		break;
	}
}
bool InputManager::GetKeyDown(Keyboard::Key key)
{
	return downList2[(int)key];
	/*return find(downList.begin(), downList.end(), key) !=
		downList.end();*/
}
bool InputManager::GetKey(Keyboard::Key key)
{
	return ingList2[(int)key];
	/*return find(ingList.begin(), ingList.end(), key) !=
		ingList.end();*/
}
bool InputManager::GetKeyUp(Keyboard::Key key)
{
	return upList2[(int)key];
	/*return find(upList.begin(), upList.end(), key) !=
		upList.end();*/
}