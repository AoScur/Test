#pragma once
#include "SFML/Graphics.hpp"
#include <random>

using namespace sf;

enum class Origins
{
	TL, TC, TR,
	ML, MC, MR,
	BL, BC, BR,
};

class Utils
{
private:
	static std::random_device rd;
	static std::mt19937 gen;

public:
	static void SetOrigin(Text& obj, Origins origin);
	static void SetOrigin(Sprite& obj, Origins origin);

	static int Range(int min, int maxExclude);
	static float Range(float min, float maxExclude);
};