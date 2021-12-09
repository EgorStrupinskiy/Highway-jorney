#include "Menu.h"

void Menu::initTextures()
{
	if (!this->fone_texture.loadFromFile("Textures/fon_def2.png"))
		std::cout << "Failed to load road texture";
	if (!this->back_texture.loadFromFile("Textures/back.png"))
		std::cout << "Failed to load back texture";
	this->fone_spr.setTexture(back_texture);

	if (!this->butPlayText.loadFromFile("Textures/Buttons/but_play.png"))
		std::cout << "Failed to load butPlayText texture";
	if (!this->butPlayText_active.loadFromFile("Textures/Buttons/but_play_activate.png"))
		std::cout << "Failed to load butPlayText_active texture";
	this->butPlay_spr.setTexture(butPlayText);

	if (!this->butSetText.loadFromFile("Textures/Buttons/but_set.png"))
		std::cout << "Failed to load butSetText texture";
	if (!this->butSetText_active.loadFromFile("Textures/Buttons/but_set_activate.png"))
		std::cout << "Failed to load butSetText_active texture";
	this->butSet_spr.setTexture(butSetText);

	if (!this->butExitText.loadFromFile("Textures/Buttons/but_exit.png"))
		std::cout << "Failed to load butExitText texture";
	if (!this->butExitText_active.loadFromFile("Textures/Buttons/but_exit_activate.png"))
		std::cout << "Failed to load butExitText_active texture";
	this->butExit_spr.setTexture(butExitText);

	if (!this->set_text.loadFromFile("Textures/set.png"))
		std::cout << "Failed to load set_text texture";
	this->set_spr.setTexture(set_text);

	if (!(this->but_bf.loadFromFile("Sounds/but_sound.wav")))
		std::cout << "Failed to load gear sound";
	this->but_s.setBuffer(but_bf);
	this->but_s.setVolume(100);
}

//Texture butPlayText;
//Sprite butPlay_spr;
//Sprite butPlay_activate_spr;
//
//Texture butSetText;
//Sprite butSet_spr;
//Sprite butSet_activate_spr;
//
//Texture butExitText;
//Sprite butExit_spr;
//Sprite butExit_activate_spr;

void Menu::initVariables()
{
	this->flag = 0;
	this->timer = 200;
	this->timer = 200;
	this->moveTimerMax = 5.f;
	this->moveTimer = moveTimerMax;
	this->choice = 3;
	music.openFromFile("Sounds/menu.wav");
	music.setLoop(true);
	music.setVolume(30);
	this->soundCooldownMax = 10.f;
	this->soundCooldown = soundCooldownMax;
}

void Menu::updateSoundCooldown()
{
	soundCooldown += 0.5f;
}

void Menu::changeMusic()
{
	if (this->music.getStatus() == SoundSource::Status::Paused ||
		this->music.getStatus() == SoundSource::Status::Stopped)
		this->music.play();
	else
		this->music.pause();
}

void Menu::initPositions()
{

	this->fone_spr.setPosition(0.f, 0.f);
	this->butPlay_spr.setPosition(1250.f, 455.f);
	this->butSet_spr.setPosition(1250.f, 655.f);
	this->butExit_spr.setPosition(1250.f, 855.f);
}

void Menu::getTouches(sf::RenderWindow* window)
{
	this->moveTimer += 0.5f;
	if (Keyboard::isKeyPressed(Keyboard::W) && canMoveUp())
	{
		this->choice++;

		if (this->choice > 3)
		this->choice = 1;

		but_s.play();
	}


	if (Keyboard::isKeyPressed(Keyboard::S) && canMoveUp())
	{
		//действия, когда нажали
		this->choice--;
		if (this->choice < 1)
			this->choice = 3;
		but_s.play();
	}

	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		//действия, когда нажали
			this->flag = choice;

		but_s.play();
		if (flag == 3)
		{
			music.stop();
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::G))
		this->changeMusic();
}

bool Menu::canMoveUp()
{
	if (this->moveTimer > moveTimerMax) {
		this->moveTimer = 0.f;
		return true;
	}
	return false;
}

Menu::Menu()
{
	this->initTextures();
	this->initPositions();
	this->initVariables();
}


void Menu::run(sf::RenderTarget* target, sf::RenderWindow* window)
{
	this->render(target);
	this->update(window);
}

bool Menu::ChangeFon()
{
	if (timer < 0)
	{
		return true;
	}
	else {
		timer--;
	}
	return false;
}

bool Menu::needToStart()
{
	if (timerAfter < 0)
	{
		return false;///////////////////////////////////////////////
	}
}

void Menu::updateFon()
{
	this->fone_spr.setTexture(fone_texture);
}

int Menu::getFlag()
{
	return flag;
}

void Menu::updateButtons()
{
	butExit_spr.setTexture(butExitText);
	butSet_spr.setTexture(butSetText);
	butPlay_spr.setTexture(butPlayText);
	switch (choice)
	{
	case 3:
		butPlay_spr.setTexture(butPlayText_active);
		break;
	case 2:
		butSet_spr.setTexture(butSetText_active);
		break;
	case 1:
		butExit_spr.setTexture(butExitText_active);
		break;
	}
}

void Menu::render(sf::RenderTarget* target)
{
	target->draw(fone_spr);
	if (ChangeFon())
	{
		if (flag == 2)
			target->draw(set_spr);
		target->draw(butPlay_spr);
		target->draw(butSet_spr);
		target->draw(butExit_spr);
	}
}

void Menu::update(sf::RenderWindow* window)
{
	if (ChangeFon())
	{
		updateSoundCooldown();
		updateFon();
	}
	this->getTouches(window);
	this->updateButtons();

}
