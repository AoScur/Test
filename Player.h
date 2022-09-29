#pragma once
#include "SpriteGameObject.h"
#include "Branch.h"
#include <vector>
#include <list>
#include "EffetLog.h"

class Player : public SpriteGameObject
{
protected:
	
	std::list<EffetLog*> unuseLogs;
	std::list<EffetLog*> useLogs;

	Texture texPlayer;
	Texture texRIP;
	Texture texLog;
	Sound soundChop;
	Sound soundDeath;
	Sprite axe;
	Sides pos;
	Vector2f centerPos;
	Vector2f axePos;
	bool isAlive;
	bool isPause;

	std::vector<Vector2f> originalPos;

public:
	
	bool isChop;

	Player(Texture& player, Texture& rip, Texture& axe, Sound& Chop, Sound& Death,bool& ispause);

	void Set(Vector2f center);
	virtual void Init();
	virtual void Release();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	virtual void SetPosition(Vector2f pos);
	virtual void SetFlipX(bool flip);

	void ShowLogEffect();

	bool GetAlive() const;
	Sides GetPos() const;

	void Die();
	void Chop(Sides side);
};

