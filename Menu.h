#pragma once
#include "Land.h"

class Menu
{
private:
	void initTextures();
	void initVariables();

	float moveTimer;
	float moveTimerMax;
	int soundCooldown;
	int soundCooldownMax;


	void updateSoundCooldown();
	void changeMusic();

	SoundBuffer but_bf;
	Sound but_s;

	Texture set_text;
	Sprite set_spr;

	Event event;
	Texture fone_texture;
	Texture back_texture;
	Texture texture_after;
	Sprite fone_spr;

	Music music;

	Texture butPlayText;
	Texture butPlayText_active;
	Sprite butPlay_spr;

	Texture butSetText;
	Texture butSetText_active;
	Sprite butSet_spr;

	Texture butExitText;
	Texture butExitText_active;
	Sprite butExit_spr;
	int flag;

	int timer;
	int timerAfter;
	int choice;
	void initPositions();
	void getTouches(sf::RenderWindow* window);
	bool canMoveUp();
public:
	Menu();
	void run(sf::RenderTarget* target, sf::RenderWindow* window);
	bool ChangeFon();
	bool needToStart();
	void updateFon();
	int getFlag();
	void updateButtons();
	void render(sf::RenderTarget* target);
	void update(sf::RenderWindow* window);
};

