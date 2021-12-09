#pragma once
#include "Land.h"
class Coin
{
private:
	Texture texture;
	Sprite coin;
	int speed;
	int line;
	int y;
	int type;

	void initTextures();

	void initVariables(int sp, int y, int type);
	void updatePos(int posY);
public:

	const int getType() const;
	const sf::FloatRect getBounds() const;
	const sf::Sprite getShape() const;
	Coin(float x, float y, int sp, int type);
	Coin();
	void update(int sp, int posY);
	void render(sf::RenderTarget* target);
};

