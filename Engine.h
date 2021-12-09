#pragma once
#include "Land.h"

class Engine
{
private:
	int maxSpeedPerGear[5] = { 40, 70, 100, 130, 170 };
	short gear;
	short gearCount;
	short speed;
	int rpm;
	int maxRpm;
	bool isGearing;
	int line;
	bool isNitring;
	int boost;
	int addSpeed;
	float nitroCounter;
	float nitroCounterMax;
	void updateNitro();
	void initSounds();
	void updateSound();

	SoundBuffer gear_bf;
	Sound gear_s;

	SoundBuffer work_bf;
	Sound work_s;

	sf::Time left;
	sf::Time right;

public:
	void initVariables();
	Engine();
	void voiceOff();
	bool canNitro();
	float getNitroCount();
	void getNitro();
	void nitro();
	void brake();
	void gas();
	void Idle();
	void work();
	void moveUp();
	void moveDown();
	void crash();

	void gearDown();
	void gearUp();

	const int getSpeed() const;
	const int getRpm() const;
	const int getLine() const;
	const int getGear() const;

	void updateView();
	void render(sf::RenderTarget* target);
};

