#include "Player.h"

void Player::initVariables()
{
	this->moveTimerMax = 7.f;
	this->moveTimerUp = moveTimerMax;
	this->moveTimerDown = moveTimerMax;
	this->timerCrashMax = 100.f;
	this->timerCrash = timerCrashMax;
	this->speed = 0;
	this->hpMax = 3;
	this->hp = hpMax;
	this->coins = 0;
	isNitring = false;
}

void Player::updateTimer()
{
	this->moveTimerUp += 0.5f;
	this->moveTimerDown += 0.5f;
	this->timerCrash += 0.5f;
}

bool Player::canMoveUp()
{
	if (this->moveTimerUp > moveTimerMax) {
		this->moveTimerUp = 0.f;
		return true;
	}
	return false;
}

bool Player::canMoveDown()
{
	if (this->moveTimerDown > moveTimerMax) {
		this->moveTimerDown = 0.f;
		return true;
	}
	return false;
}

bool Player::canGetDamage()
{
	if (this->timerCrash > timerCrashMax) {
		this->timerCrash = 0.f;
		return true;
	}
	return false;
}

void Player::initTextures()
{
	//Frame
	if (!this->frame_texture.loadFromFile("Textures/player4.png"))
		std::cout << "Failed to load player`s frame texture";
	this->frame.setTexture(this->frame_texture);
	this->frame.setScale(0.7f, 0.7f);
	//Wheels
	if (!this->nitro_text.loadFromFile("Textures/fire_2.png"))
		std::cout << "Failed to load nitro`s frame texture";
	this->nitro_spr.setTexture(this->nitro_text);
	this->nitro_spr.setScale(0.7f, 0.7f);

	if (!this->wheel_texture.loadFromFile("Textures/red_wheel.png"))
		std::cout << "Failed to load player`s wheels texture";
	this->left_wh.setTexture(this->wheel_texture);
	this->right_wh.setTexture(this->wheel_texture);
	this->left_wh.setScale(0.7f, 0.7f);
	this->right_wh.setScale(0.7f, 0.7f);
	this->left_wh.setOrigin(46.f, 46.f);
	this->right_wh.setOrigin(46.f, 46.f);
}

void Player::initMusic()
{
	if (!(this->buffer_earn.loadFromFile("Sounds/coin_3.ogg")))
		std::cout << "Failed to load coin`s sound";
	this->earn_sound.setBuffer(buffer_earn);
	this->earn_sound.setVolume(100);
	//
	if (!(this->buffer_slip.loadFromFile("Sounds/slip.ogg")))
		std::cout << "Failed to load slip`s sound";
	this->slip_sound.setBuffer(buffer_slip);
	this->slip_sound.setVolume(100);
	//
	if (!(this->nitro_bf.loadFromFile("Sounds/nitro.wav")))
		std::cout << "Failed to load nitro sound";
	this->nitro_s.setBuffer(nitro_bf);
	this->nitro_s.setVolume(30);
	//

	if (!(this->nitro_pick_buff.loadFromFile("Sounds/nitro_pick.wav")))
		std::cout << "Failed to load nitro_pick sound";
	this->nitro_pick.setBuffer(nitro_pick_buff);
	this->nitro_pick.setVolume(100);
}


void Player::updateWindowBundsCollision(sf::RenderTarget* target)
{
	//Left
	if (this->frame.getGlobalBounds().left <= 0.f)
		this->frame.setPosition(0.f, this->frame.getGlobalBounds().top);
	//Right
	if (this->frame.getGlobalBounds().left +
		this->frame.getGlobalBounds().width >= target->getSize().x)
		this->frame.setPosition(target->getSize().x - this->frame.getGlobalBounds().width, this->frame.getGlobalBounds().top);
	//Top
	if (this->frame.getGlobalBounds().top <= 0.f)
		this->frame.setPosition(this->frame.getGlobalBounds().left, 0.f);
	//Down
	if (this->frame.getGlobalBounds().top +
		this->frame.getGlobalBounds().height >= target->getSize().y)
		this->frame.setPosition(this->frame.getGlobalBounds().left, target->getSize().y - this->frame.getGlobalBounds().height);
}

void Player::updateWheels()
{
	this->left_wh.setPosition(this->frame.getPosition().x + 102.f, this->frame.getPosition().y + 92.f);
	this->right_wh.setPosition(this->frame.getPosition().x + 352.f, this->frame.getPosition().y + 92.f);
}

const int Player::getSpeed() const
{
	return this->speed;
}


const sf::Sprite Player::getShape() const
{
	return this->frame;
}

const int Player::getLine() const
{
	return this->engine.getLine();
}

void Player::changeLine()
{
	int choice = rand() % 2;
	slip_sound.play();
	if (choice == 1)
	{
		for (int i = 0; i < choice + 1; i++)
		{
			engine.moveUp();
			engine.moveUp();
		}
	}
	else
	{
		for (int i = 0; i < choice + 1; i++)
		{
			engine.moveDown();
			engine.moveDown();
		}
	}
}

void Player::crash() {
	this->engine.crash();
	if (canGetDamage())
		this->hp--;
}


void Player::getNitro()
{
	engine.getNitro();
	nitro_pick.play();

}

void Player::mute()
{
	this->engine.voiceOff();
}

void Player::updateInput()
{
	this->speed = engine.getSpeed();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->engine.brake();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->engine.gas();
	}
	else {
		this->engine.Idle();
	}

	if (Keyboard::isKeyPressed(Keyboard::W) && canMoveUp())
	{
		this->engine.moveUp();
	}


	if (Keyboard::isKeyPressed(Keyboard::S) && canMoveDown())
	{
		//действия, когда нажали
		this->engine.moveDown();
	}

	if (Keyboard::isKeyPressed(Keyboard::LShift))
	{
		this->engine.nitro();
		isNitring = true;
		if (engine.canNitro())
		{
			if (nitro_s.getStatus() == SoundSource::Status::Stopped)
				nitro_s.play();
			isNitring = true;
		}
	}
	else {
		nitro_s.stop();
		isNitring = false;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		this->engine.gearDown();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		this->engine.gearUp();
	}
	this->left_wh.rotate(this->speed * 0.6f);
	this->right_wh.rotate(this->speed * 0.6f);
}

Player::Player(float x, float y)
{
	this->initMusic();
	this->frame.setPosition(45, 555);
	this->left_wh.setPosition(x + 102.f, y + 92.f);
	this->right_wh.setPosition(x + 352.f, y + 92.f);
	this->nitro_spr.setPosition(frame.getPosition().x - 200, frame.getPosition().y + 100);
	this->initVariables();
	this->initTextures();
}

Player::~Player()
{
}

void Player::getCoin()
{
	this->coins++;
	earn_sound.play();
}

const bool Player::getHp()
{
	return this->hp;
}

void Player::updateDash()
{
	int sp = engine.getSpeed();
	int rp = engine.getRpm();
	int gr = engine.getGear();
	int cn = this->coins;
	int nit = engine.getNitroCount();
	int hp = this->hp;
	dash.update(sp, rp, gr, cn, nit, hp);
}



void Player::update(sf::RenderTarget* target)
{
	this->updateTimer();
	this->updateWindowBundsCollision(target);
	this->updateInput();
	this->engine.work();
	this->updateWheels();
	this->updateDash();

}


void Player::render(sf::RenderTarget* target)
{
	this->engine.render(target);
	target->draw(this->frame);
	target->draw(this->left_wh);
	target->draw(this->right_wh);
	if (isNitring)
		target->draw(nitro_spr);
	dash.render(target);
}
