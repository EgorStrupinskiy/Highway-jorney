#include "dashboard.h"

void Dashboard::initVariables()
{
	this->gear = 1;
	this->gearCount = 5;
	this->speed = 0;
	this->rpm = 800;
	this->maxNitro = 5;
}

void Dashboard::initFont()
{
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
		std::cout << "ERROR IN FONT INITIALIZATION";
}

void Dashboard::initText()
{
	this->speedText.setFont(this->font);
	this->speedText.setFillColor(sf::Color::White);
	this->speedText.setCharacterSize(70);
	this->speedText.setString("TEST");
	//
	this->coinsText.setFont(this->font);
	this->coinsText.setFillColor(sf::Color::Yellow);
	this->coinsText.setCharacterSize(110);
	this->coinsText.setString("Coins");
}

void Dashboard::initTextures()
{
	if (!this->speedo_texture.loadFromFile("Textures/speed_4.png"))
		std::cout << "Failed to load speedo texture";
	this->speedo.setTexture(this->speedo_texture);
	this->speedo.setScale(1.2f, 1.2f);
	if (!this->row_texture.loadFromFile("Textures/row_2.png"))
		std::cout << "Failed to load row texture";
	this->rpm_row.setTexture(this->row_texture);
	this->rpm_row.setScale(1.5f, 1.5f);
	this->rpm_row.setOrigin(80.f, 15.f);
	this->speed_row.setTexture(this->row_texture);
	this->speed_row.setScale(1.5f, 1.5f);
	this->speed_row.setOrigin(80.f, 15.f);
	if (!this->nitro_texture.loadFromFile("Textures/nitro_2.png"))
		std::cout << "Failed to load nitro texture";
	this->nitro_spr.setTexture(this->nitro_texture);
	this->nitro_spr.setScale(1.2f, 1.2f);
	this->nitro_spr.setTextureRect(IntRect(0, 0, 248, 65));

	if (!this->brick_texture.loadFromFile("Textures/gear.png"))
		std::cout << "Failed to load gear texture";
	this->brick.setTexture(this->brick_texture);
	this->brick.setScale(1.2f, 1.2f);

	if (!this->butt_texture.loadFromFile("Textures/butt.png"))
		std::cout << "Failed to load button texture";
	this->butt.setTexture(this->butt_texture);
	this->butt.setScale(1.1f, 1.1f);

	if (!this->black_rect_text.loadFromFile("Textures/hp.png"))
		std::cout << "Failed to load hp_closer texture";
	this->black_rect.setTexture(this->black_rect_text);
	this->black_rect.setRotation(180.f);
}

void Dashboard::initPositions()
{
	this->speedo.setPosition(-218.f, 730.f);
	this->rpm_row.setPosition(750.f, 900.f);
	this->rpm_row.setRotation(235);
	this->speed_row.setPosition(1165.f, 900.f);
	this->speed_row.setRotation(220);
	this->speedText.setPosition(895, 988);
	this->coinsText.setPosition(1700, 950);
	this->brick.setPosition(417.f, 989.f);
	this->butt.setPosition(917.f, 810.f);
	this->nitro_spr.setPosition(75.f, 992.f);
	this->black_rect.setPosition(1580.f, 1080.f);
}

Dashboard::Dashboard()
{
	this->initTextures();
	this->initVariables();
	this->initFont();
	this->initText();
	this->initPositions();
}

void Dashboard::updateGui()
{
	std::stringstream ssSpeed;
	ssSpeed << this->speed;
	this->speedText.setString(ssSpeed.str());
	std::stringstream ssCoins;
	ssCoins << "X" << this->coins;
	this->coinsText.setString(ssCoins.str());
}

void Dashboard::updateGear()
{
	this->brick.setPosition(417.f + (gear - 1) * 9, 989.f + (gear - 1) * 17);
}

void Dashboard::updateHp()
{
	this->black_rect.setScale(- ( hp - 3) * 16.f, 1.4f);
}

void Dashboard::updateNitro()
{
	this->nitro_spr.setTextureRect(IntRect(0.f, 0.f, 248.f * (nitro / 100), 65.f));
}

void Dashboard::update(int speed, int rpm, int gear, int coins, float nitro, int hp)
{
	this->updateGear();
	this->rpm_row.setRotation(260 + 180.f * (rpm / 9000.f));
	this->speed_row.setRotation(220 + 180.f * (speed / 205.f));
	this->speed = speed;
	this->rpm = rpm;
	this->gear = gear;
	this->coins = coins;
	this->nitro = nitro;
	this->hp = hp;
	this->updateNitro();
	this->updateGui();
	this->updateHp();
}

const bool Dashboard::renderButt()
{
	if (this->rpm > 8000)
	{
		return true;
	} 
	return false;
}


void Dashboard::render(sf::RenderTarget* target)
{
	target->draw(this->speedo);
	target->draw(this->rpm_row);
	target->draw(this->speed_row);
	target->draw(this->speedText);
	target->draw(this->coinsText);
	target->draw(this->brick);
	target->draw(this->black_rect);
	if (renderButt()) target->draw(this->butt);
	target->draw(this->nitro_spr);
}

