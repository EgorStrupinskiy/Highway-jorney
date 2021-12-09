#include "Enemy.h"

void Enemy::initTextures()
{
	float scaleFrameX = 0;
	float scaleFrameY = 0;
	float scaleWheel = 0;
	switch (this->type) {
	case 1:
		if (!this->texture_frame.loadFromFile("Textures/lancer_1.png"))
			std::cout << "Failed to load player`s frame texture";
		if (!this->wheel_texture.loadFromFile("Textures/green_wheel3.png"))
			std::cout << "Failed to load player`s wheels texture";
		scaleFrameX = 0.7;
		scaleFrameY = 0.7;
		scaleWheel = 1.1;
		this->left_wh.setOrigin(24.f, 24.f);
		this->right_wh.setOrigin(24.f, 24.f);
		break;
	case 2:
		if (!this->texture_frame.loadFromFile("Textures/aston_2.png"))
			std::cout << "Failed to load player`s frame texture";
		if (!this->wheel_texture.loadFromFile("Textures/red_wheel.png"))
			std::cout << "Failed to load player`s wheels texture";
		scaleFrameX = 1.f;
		scaleFrameY = 1.f;
		scaleWheel = 0.7;
		this->left_wh.setOrigin(46, 46);
		this->right_wh.setOrigin(46, 46);
		break;
	case 3:
		if (!this->texture_frame.loadFromFile("Textures/bmw_e60.png"))
			std::cout << "Failed to load player`s frame texture";
		if (!this->wheel_texture.loadFromFile("Textures/red_wheel.png"))
			std::cout << "Failed to load player`s wheels texture";
		scaleFrameX = 0.7;
		scaleFrameY = 0.7;
		scaleWheel = 0.7;
		this->left_wh.setOrigin(46, 46);
		this->right_wh.setOrigin(46, 46);
		break;
	}
	this->frame.setTexture(this->texture_frame);
	this->frame.setScale(scaleFrameX, scaleFrameY);
	//Wheels
	this->left_wh.setTexture(this->wheel_texture);
	this->right_wh.setTexture(this->wheel_texture);
	this->left_wh.setScale(scaleWheel, scaleWheel);
	this->right_wh.setScale(scaleWheel, scaleWheel);
}

void Enemy::initVariables(int sp, int y, int type)
{
	this->speed = sp - rand() % 7;
	if (speed < 10) speed = 70;
	this->type = type;
	this->damage = 1;
	this->y = y;
	this->line = (y - 450) / 110;
	switch (this->type) {
	case (1):
		this->leftWheelPosX = 124.f;
		this->leftWheelPosY = 118.f;
		this->rightWheelPosX = 375.f;
		this->rightWheelPosY = 118.f;
		break;
	case (2):
		this->leftWheelPosX = 88.f;
		this->leftWheelPosY = 88.f;
		this->rightWheelPosX = 345.f;
		this->rightWheelPosY = 88.f;
		break;
	case (3):
		this->leftWheelPosX = 98.f;
		this->leftWheelPosY = 97.f;
		this->rightWheelPosX = 350.f;
		this->rightWheelPosY = 97.f;
		break;
	}
}


const sf::FloatRect Enemy::getBounds() const
{
	return this->frame.getGlobalBounds();
}

const sf::Sprite Enemy::getShape() const
{
	return this->frame;
}

const int Enemy::getLine() const
{
	return this->line;
}

void Enemy::crash()
{
	this->speed = 5;
}

void Enemy::changeSpeed(int speed)
{
	this->speed = speed;
}

float Enemy::getSpeed()
{
	return this->speed;
}

void Enemy::boost()
{
	this->frame.setPosition(this->frame.getPosition().x + 40, this->frame.getPosition().y);
}

void Enemy::updateWheels()
{
	this->left_wh.setPosition(this->frame.getPosition().x + leftWheelPosX, this->frame.getPosition().y + leftWheelPosY);
	this->right_wh.setPosition(this->frame.getPosition().x + rightWheelPosX, this->frame.getPosition().y + rightWheelPosY);
}

Enemy::Enemy(float x, float y, int sp, int type)
{
	this->initVariables(sp, y, type);
	this->initTextures();
	this->frame.setPosition(x, y);
}

void Enemy::updatePos(int posY) {
	this->frame.setPosition(this->frame.getPosition().x, posY);
}

void Enemy::update(int sp, int posY)
{
	this->frame.move(- (sp - this->speed), 0.f);
	this->updatePos(posY + 300 + y);
	this->updateWheels();
	this->left_wh.rotate(this->speed * 0.6);
	this->right_wh.rotate(this->speed * 0.6);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->frame);
	target->draw(this->left_wh);
	target->draw(this->right_wh);
}
