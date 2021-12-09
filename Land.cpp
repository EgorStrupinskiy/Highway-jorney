#include "Land.h"

void Land::initTextures()
{
	//Road
	if (!this->road_texture.loadFromFile("Textures/road_10.png"))
		std::cout << "Failed to load road texture";
	this->road_sprite1.setTexture(road_texture);
	this->road_sprite2.setTexture(road_texture);

	//Mountains
	if (!this->mount_texture.loadFromFile("Textures/mount_1.png"))
		std::cout << "Failed to load mountain texture";
	this->mount_sprite1.setTexture(mount_texture);
	this->mount_sprite1.setScale(1.6, 1);
	this->mount_sprite2.setTexture(mount_texture);
	this->mount_sprite2.setScale(1.6, 1);

	//Trees
	if (!this->tree_texture.loadFromFile("Textures/trees_4.png"))
		std::cout << "Failed to load trees texture";
	this->tree_sprite1.setTexture(tree_texture);
	this->tree_sprite2.setTexture(tree_texture);
	this->tree_sprite1.setScale(3, 2);
	this->tree_sprite2.setScale(3, 2);

	if (!this->sky_texture.loadFromFile("Textures/sky_2.png"))
		std::cout << "Failed to load sky texture";
	this->sky_spr1.setTexture(sky_texture);
	this->sky_spr2.setTexture(sky_texture);
	this->sky_spr1.setScale(1, 1);
	this->sky_spr2.setScale(1, 1);
}

void Land::initVariables()
{
	isMovingDown = false;
	isMovingUp = false;
	prevLine = 3;
}

void Land::updateScrolling()
{
	//Road
	if (road_sprite2.getPosition().x < 0) {
		this->road_sprite1.setPosition(road_sprite2.getPosition().x + 1920.f, road_sprite2.getPosition().y);
	}
	if (road_sprite1.getPosition().x < 0) {
		this->road_sprite2.setPosition(road_sprite1.getPosition().x + 1920.f, road_sprite1.getPosition().y);
	}
	if (road_sprite1.getPosition().x > 0) {
		this->road_sprite2.setPosition(road_sprite1.getPosition().x - 1920.f, road_sprite1.getPosition().y);
	}
	if (road_sprite2.getPosition().x > 0) {
		this->road_sprite1.setPosition(road_sprite2.getPosition().x - 1920.f, road_sprite2.getPosition().y);
	}

	//Mountains
	if (mount_sprite2.getPosition().x < 0) {
		this->mount_sprite1.setPosition(mount_sprite2.getPosition().x + 1780.f, mount_sprite2.getPosition().y);
	}
	if (mount_sprite1.getPosition().x < 0) {
		this->mount_sprite2.setPosition(mount_sprite1.getPosition().x + 1780.f, mount_sprite1.getPosition().y);
	}
	if (mount_sprite2.getPosition().x > 0) {
		this->mount_sprite1.setPosition(mount_sprite2.getPosition().x - 1780, mount_sprite2.getPosition().y);
	}
	if (mount_sprite1.getPosition().x > 0) {
		this->mount_sprite2.setPosition(mount_sprite1.getPosition().x - 1780, mount_sprite1.getPosition().y);
	}

	//Trees
	if (tree_sprite2.getPosition().x < 0) {
		this->tree_sprite1.setPosition(tree_sprite2.getPosition().x + 1780.f, tree_sprite2.getPosition().y);
	}
	if (tree_sprite1.getPosition().x < 0) {
		this->tree_sprite2.setPosition(tree_sprite1.getPosition().x + 1780.f, tree_sprite1.getPosition().y);
	}
	if (tree_sprite2.getPosition().x > 0) {
		this->tree_sprite1.setPosition(tree_sprite2.getPosition().x - 1780.f, tree_sprite2.getPosition().y);
	}
	if (tree_sprite1.getPosition().x > 0) {
		this->tree_sprite2.setPosition(tree_sprite1.getPosition().x - 1780.f, tree_sprite1.getPosition().y);
	}
	//Sky
	if (sky_spr2.getPosition().x < 0) {
		this->sky_spr1.setPosition(sky_spr1.getPosition().x + 3000.f, sky_spr1.getPosition().y);
	}
	if (sky_spr1.getPosition().x < 0) {
		this->sky_spr2.setPosition(sky_spr1.getPosition().x + 3000.f, sky_spr1.getPosition().y);
	}
	if (sky_spr2.getPosition().x > 0) {
		this->sky_spr1.setPosition(sky_spr2.getPosition().x - 3000.f, sky_spr2.getPosition().y);
	}
	if (sky_spr1.getPosition().x > 0) {
		this->sky_spr2.setPosition(sky_spr1.getPosition().x - 3000.f , sky_spr1.getPosition().y);
	}
}

void Land::initPositions()
{
	this->road_sprite1.setPosition(0.f, -300.f);
	this->road_sprite2.setPosition(2030.f, -300.f);
	this->mount_sprite1.setPosition(0.f, 110.f);
	this->mount_sprite2.setPosition(1750.f, 110.f);
	this->tree_sprite1.setPosition(0.f, 257.f);
	this->tree_sprite2.setPosition(1800.f, 257.f);
	this->sky_spr1.setPosition(0.f, -150.f);
	this->sky_spr2.setPosition(3000.f, -150.f);
	this->tree_sprite2.setPosition(1800.f, 257.f);
}



Land::Land()
{
	this->initTextures();
	this->initPositions();
	this->initVariables();
}



const int Land::getPosY() const
{
	return this->road_sprite1.getPosition().y;
}

void Land::moveView(float speedX, float speedY)
{
	//Move
	this->road_sprite1.move(speedX * 0.5, speedY);
	this->road_sprite2.move(speedX * 0.5, speedY);
	this->mount_sprite1.move(speedX * 0.02, speedY);
	this->mount_sprite2.move(speedX * 0.02, speedY);
	this->tree_sprite1.move(speedX * 0.2, speedY);
	this->tree_sprite2.move(speedX * 0.2, speedY);
	this->sky_spr1.move(speedX * 0.01, speedY);
	this->sky_spr2.move(speedX * 0.01, speedY);
	this->updateScrolling();
}

void Land::render(sf::RenderTarget* target)
{
	//Road
	target->draw(this->road_sprite2);
	target->draw(this->road_sprite1);
	//Sky
	target->draw(this->sky_spr1);
	target->draw(this->sky_spr2);
	//Mountains
	target->draw(this->mount_sprite1);
	target->draw(this->mount_sprite2);
	//Trees
	target->draw(this->tree_sprite1);
	target->draw(this->tree_sprite2);
}

void Land::update(float speedX, float speedY, int line)
{
	this->line = line;
	this->checkLines();
	this->speed = speedX;
	this->moveView(speedX, speedY);
	this->moveVertically();
}

void Land::moveVertically()
{
	float speedY;
	speedY = this->speed * 0.1f;
	if (speedY < -5.f)
		speedY = - 5.f;
	if (isMovingUp) {
		this->moveView(0.f, -speedY);
		if (this->getPos().y + 625 > this->line*110)
			isMovingUp = false;
	}
	else
		if (isMovingDown) {
			this->moveView(0.f, speedY);
			if (this->getPos().y + 620 < this->line * 110)
				isMovingDown = false;
		}
}

void Land::checkLines()
{
	if ((this->line > prevLine)) {
		prevLine = line;
		isMovingUp = true;
	}
	if ((this->line < prevLine)) {
		prevLine = line;
		isMovingDown = true;
	}
}

const::sf::Vector2f Land::getPos() const
{
	return this->road_sprite1.getPosition();
}
