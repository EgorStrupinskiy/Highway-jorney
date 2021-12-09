#pragma once
#include "Land.h"
class Dashboard
{
private:
	sf::Font font;
	sf::Text speedText;	
	sf::Text coinsText;
	
	Texture speedo_texture;
	Sprite speedo;
	//
	Texture row_texture;
	Sprite rpm_row;
	Sprite speed_row;
	//
	Texture brick_texture;
	Sprite brick;
	//
	Texture butt_texture;
	Sprite butt;
	//
	Texture nitro_texture;
	Sprite nitro_spr;

	Texture black_rect_text;
	Sprite black_rect;

	int hp;
	int gearCount;
	int speed;
	int gear;
	int coins;
	int rpm;
	float nitro;
	int maxNitro;

	void initVariables();
	void initFont();
	void initText();

	void initTextures();
	void initPositions();
public:
	Dashboard();
	void updateGui();
	void updateGear();
	void updateHp();
	void updateNitro();
	void update(int speed, int rpm, int gear, int coins, float nitro, int hp);

	const bool renderButt();

	void render(sf::RenderTarget* target);
};