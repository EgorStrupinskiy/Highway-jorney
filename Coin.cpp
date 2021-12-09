#include "Coin.h"

void Coin::initTextures()
{
	switch (type)
	{
	case 1:
		if (!this->texture.loadFromFile("Textures/coin_2.png"))
			std::cout << "Failed to load coin`s texture\n";
		this->coin.setScale(0.25, 0.25);
		break;
	case 2:
		if (!this->texture.loadFromFile("Textures/fire.png"))
			std::cout << "Failed to load coin`s texture\n";
		this->coin.setScale(0.15, 0.15);
		break;
	case 3:
		if (!this->texture.loadFromFile("Textures/luzha3.png"))
			std::cout << "Failed to load luzha`s texture\n";
		this->coin.setScale(0.3f, 0.2f);
		break;
	}
	this->coin.setTexture(this->texture);
}

void Coin::initVariables(int sp, int y, int type)
{
	this->type = type;
	this->y = y;
	this->speed = sp - rand() % 7;
	this->line = (y - 450) / 110;
	if (speed < 10) speed = 70;
}

void Coin::updatePos(int posY)
{
	this->coin.setPosition(this->coin.getPosition().x, posY);
}

const int Coin::getType() const
{
	return this->type;
}

const sf::FloatRect Coin::getBounds() const
{
	return this->coin.getGlobalBounds();
}

const sf::Sprite Coin::getShape() const
{
	return this->coin;;
}

Coin::Coin(float x, float y, int sp, int type)
{
	this->initVariables(sp, y, type);
	this->initTextures();
	this->coin.setPosition(x, y);
}

Coin::Coin()
{
}

void Coin::update(int sp, int posY)
{
	this->coin.move(-(sp * 0.1f), 0.f);
	this->updatePos(posY + 300 + y);
}

void Coin::render(sf::RenderTarget* target)
{
	target->draw(this->coin);
}
