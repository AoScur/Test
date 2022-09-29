#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

// static �Լ��� �̿��ؼ�
// Ű���� �� ���콺 �Է��� �˻��� �� �ִ� Ŭ����

using namespace sf;
using namespace std;

class InputManager
{
private:
	//static vector<Keyboard::Key> downList;
	//static vector<Keyboard::Key> ingList;
	//static vector<Keyboard::Key> upList;

	static vector<bool> downList2;
	static vector<bool> ingList2;
	static vector<bool> upList2;
public:
	static void ClearInput();
	static void UpdateInput(Event& ev);

	static bool GetKeyDown(Keyboard::Key key);
	static bool GetKey(Keyboard::Key key);
	static bool GetKeyUp(Keyboard::Key key);
};