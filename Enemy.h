#pragma once
#include "Land.h"
class Enemy
{
private:
	int speed;
	int type;
	int damage;
	int y;
	int line;
	float wh_pos_L_X;
	float wh_pos_L_Y;
	float wh_pos_R_X;
	float wh_pos_R_Y;
	float leftWheelPosX;
	float leftWheelPosY;
	float rightWheelPosX;
	float rightWheelPosY;

	Texture texture_frame;
	Sprite frame;
	Texture wheel_texture;
	Sprite left_wh;
	Sprite right_wh;

	void initTextures();

	void initVariables(int sp, int y, int type);
	void updatePos(int posY);

public:
	Enemy(float x, float y, int sp, int type);
	const sf::FloatRect getBounds() const;
	const sf::Sprite getShape() const;
	const int getLine() const;
	void crash();
	void changeSpeed(int speed);
	float getSpeed();
	void boost();

	void updateWheels();

	void update(int sp, int posY);
	void render(sf::RenderTarget* target);
};

