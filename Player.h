#pragma once
#include "Engine.h"
#include "Land.h"
#include "Dashboard.h"


class Player
{
private:
	int speed;
	int hp;
	int hpMax;
	int coins;
	bool sPressed;
	Land land;
	float moveTimerUp;
	float moveTimerDown;
	float moveTimerMax;
	float timerCrash;
	float timerCrashMax;
	//Sources
	Texture frame_texture;
	Texture wheel_texture;
	Sprite left_wh;
	Sprite right_wh;
	Sprite frame;
	bool isNitring;

	Texture nitro_text;
	Sprite nitro_spr;

	SoundBuffer buffer_earn;
	Sound earn_sound;

	SoundBuffer buffer_slip;
	Sound slip_sound;

	SoundBuffer buffer_nitro;
	Sound nitro_sound;

	SoundBuffer nitro_bf;
	Sound nitro_s;

	SoundBuffer nitro_pick_buff;
	Sound nitro_pick;

	Engine engine;
	Dashboard dash;

	void initVariables();
	void updateTimer();
	bool canMoveUp();
	bool canMoveDown();
	bool canGetDamage();
	void initTextures();
	void initMusic();
public:
	Player(float x = 0.f, float y = 0.f);
	~Player();

	void mute();
	void updateInput();
	void updateWindowBundsCollision(sf::RenderTarget* target);
	void updateWheels();
	const int getSpeed() const;
	const sf::Sprite getShape() const;
	const int getLine() const;
	void changeLine();
	void crash();
	void getNitro();

	void getCoin();
	const bool getHp();
	void updateDash();
	void update(sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

