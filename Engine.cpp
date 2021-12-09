#include "Engine.h"


void Engine::updateNitro()
{
	if (isNitring) {
		nitroCounter -= 0.5f;
		if (nitroCounter < nitroCounterMax)
		{
			isNitring = false;
			boost = 50;
			addSpeed = 0;
		}
	}
}

void Engine::initSounds()
{
	if (!(this->gear_bf.loadFromFile("Sounds/Engine/gear_2.wav")))
		std::cout << "Failed to load gear sound";
	this->gear_s.setBuffer(gear_bf);
	this->gear_s.setVolume(30);
	
	if (!(this->work_bf.loadFromFile("Sounds/Engine/engine_7.wav")))
		std::cout << "Failed to load engine sound";
	this->work_s.setBuffer(work_bf);
	this->work_s.setLoop(true);
	this->work_s.setVolume(20);
}


void Engine::updateSound()
{
	if (work_s.getStatus() == SoundSource::Status::Stopped)
		work_s.play();
	this->work_s.setPitch((this->rpm + (float)(gear * 500.f)) / 4000.f);
	this->work_s.setVolume(this->rpm / 80.f);
	if (work_s.getPitch() < 0.7f)
		this->work_s.setPitch(0.7f);
	if (work_s.getVolume() < 20)
		this->work_s.setVolume(20);
}

void Engine::initVariables()
{
	this->nitroCounter = 0;
	this->nitroCounterMax = 100;
	this->gear = 1;
	this->gearCount = 5;
	this->speed = 0;
	this->rpm = 800;
	this->maxRpm = 8500;
	this->line = 3;
	this->isNitring = false;
	this->boost = 50;
	this->addSpeed = 0;
	this->left = sf::Time(milliseconds(0));
	this->left = sf::Time(milliseconds(50));
}

Engine::Engine()
{
	this->initVariables();
	this->initSounds();
}

void Engine::voiceOff()
{
	this->work_s.stop();
}

bool Engine::canNitro()
{
	if (this->nitroCounter > 0)
		return true;
	return false;
}

float Engine::getNitroCount()
{
	return this->nitroCounter;
}

void Engine::getNitro()
{
	this->nitroCounter += 25;
	if (this->nitroCounter > 100)
		this->nitroCounter = 100;
}

void Engine::nitro()
{
	if (canNitro())
	{
		this->boost = 150;
		addSpeed = 20;
		this->isNitring = true;
	}
}

void Engine::brake()
{
	if (rpm > 800)
		rpm -= 100 / gear;
	else
		if (rpm > 300)
			rpm = 200;
}

void Engine::gas()
{
	if (rpm < maxRpm)
		rpm += boost/(gear);
}

void Engine::Idle() 
{
	if (rpm == 200) rpm = 800;
	if (rpm > 800)
		rpm -= 20 / gear;
}

void Engine::work()
{
	this->speed = (int)(((float)rpm / (float)maxRpm ) * ((float)maxSpeedPerGear[gear - 1] + addSpeed));
	this->updateNitro();
	this->updateSound();
}

void Engine::crash()
{
	this->rpm = 2500;
}

void Engine::gearDown()
{
	if ((gear > 1) && (rpm < 4000))
	{
		this->gear--;
		this->rpm = (int)((float)maxRpm * (float)speed / (float)maxSpeedPerGear[gear - 1]);
		if (rpm < 800) rpm = 800;
		if (rpm > maxRpm) rpm = maxRpm;
		gear_s.play();
	}
}

void Engine::gearUp()
{
	if ((gear < gearCount) && (rpm > 8000))
	{
		this->gear++;
		this->rpm = (int)((float)maxRpm * (float)speed / (float)maxSpeedPerGear[gear - 1]);
		if (rpm < 800) rpm = 800;
		if (rpm > maxRpm) rpm = maxRpm;
		gear_s.play();
	}
}

void Engine::moveUp()
{
	if ((this->line != 4) ) {
		this->line++;
	}
}

void Engine::moveDown()
{
	if ((this->line != 1)) {
		this->line--;
	}
}


const int Engine::getSpeed() const
{
	return this->speed;
}

const int Engine::getLine() const
{
	return this -> line;
}

const int Engine::getGear() const
{
	return this->gear;
}

const int Engine::getRpm() const
{
	return this->rpm;
}

void Engine::updateView() {
}

void Engine::render(sf::RenderTarget* target)
{
}
