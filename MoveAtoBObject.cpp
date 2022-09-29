#include "MoveAtoBObject.h"

MoveAtoBObject::MoveAtoBObject(Texture& tex, Vector2f pos)
	:SpriteGameObject(tex, pos)
{	
		
}

MoveAtoBObject::~MoveAtoBObject()
{
	
}

void MoveAtoBObject::Init()
{		
	speed = (rand() % (speedRange.y - speedRange.x)) + speedRange.x;

	startPos.y = (rand() % (yRange.y - yRange.x)) + yRange.x;

	endPos.y = startPos.y;

	SetPosition(startPos);
}

void MoveAtoBObject::Update(float dt)
{
	Vector2f pos = GetPosition();
	float distanceX = endPos.x - pos.x;

	if (abs(distanceX) < 10)
		Init();		

	Translate(direction * speed * dt);
}

void MoveAtoBObject::Set(Vector2i sRange, Vector2i yRange, Vector2f start, Vector2f end)
{
	speedRange = sRange;
	this->yRange = yRange;
	startPos = start;
	endPos = end;

	direction = (endPos.x > startPos.x) ? Vector2f(1, 0) : Vector2f(-1, 0);
}