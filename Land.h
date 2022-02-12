#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <Windows.h>

#include <sstream>

using namespace sf;

class Land
{
private:
	//Road
	Texture road_texture;
	Sprite road_sprite1;
	Sprite road_sprite2;

	//mount
	Texture mount_texture;
	Sprite mount_sprite1;
	Sprite mount_sprite2;
	//Tree
	Texture tree_texture;
	Sprite tree_sprite1;
	Sprite tree_sprite2;
	//Sky
	Texture sky_texture;
	Sprite sky_spr1;
	Sprite sky_spr2;

	int line;
	int prevLine;
	float speed;
	bool isMovingUp;
	bool isMovingDown;

	void initTextures();
	void initVariables();

	void updateScrolling();
	void initPositions();
public:
	Land();

	const int getPosY() const;
	void moveView(float speedX, float speedY);
	void render(sf::RenderTarget* target);
	void update(float speedX, float speedY, int line);

	void moveVertically();

	void checkLines();

	const::sf::Vector2f getPos() const;
};

