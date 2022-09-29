#pragma once
#include "SpriteGameObject.h"

enum class Sides
{
    Left,
    Right,
    None,
};

class Branch : public SpriteGameObject
{
private:
    Sides side;
    SpriteGameObject* tree;

public:
    Branch(Texture& tex, SpriteGameObject* _tree)
        : SpriteGameObject(tex), tree(_tree)
    {
    }

    virtual void Init() override;
    void SetSide(Sides side);
    Sides GetSide();
};

