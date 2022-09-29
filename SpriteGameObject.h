#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Utils.h"

using namespace sf;

class SpriteGameObject
{
protected:
	Sprite sprite;	

	SpriteGameObject(const SpriteGameObject& ref);
	SpriteGameObject& operator= (const SpriteGameObject& ref);

public:
	SpriteGameObject(Texture& tex, Vector2f pos = Vector2f());
	virtual ~SpriteGameObject();

	virtual void Init();
	virtual void Release();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	virtual void SetFlipX(bool flip);

	void SetOrigin(Origins origin);
	Vector2f GetSize() const;

	Vector2f GetPosition();
	void SetPosition(Vector2f pos);
	void Translate(Vector2f delta);
};

