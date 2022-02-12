#include "Game.h"
#include "Enemy.h"

void Game::checkMenu()
{
	int choice = menu.getFlag();
	if (choice == 3)
	{
		gameWorking = true;
	}

	if (choice == 1)
		this->window->close();
}

void Game::changeMusic()
{
	if (this->music.getStatus() == SoundSource::Status::Paused || 
		this->music.getStatus() == SoundSource::Status::Stopped)
		this->music.play();
	else
		this->music.pause();
}

void Game::initTextures()
{
	if (!this->end_texture.loadFromFile("Textures/end_2.png"))
		std::cout << "Failed to load player`s frame texture";
	this->end_spr.setTexture(this->end_texture);
	this->end_spr.setScale(1.f, 1.f);
}

void Game::initVariables()
{
	this->endGame = false;
	menuRunning = true;
	this->soundCooldownMax = 10.f;
	this->soundCooldown = soundCooldownMax;
}

void Game::initWindow()
{
	this->videomode = sf::VideoMode(1920, 1080);
	this->window = new sf::RenderWindow(this->videomode, "Drug_race");
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(true);
}

void Game::initEnemies()
{
	this->spawnTimerMax = 130.f;
	this->spawnTimer = 0;
}

void Game::initSounds()
{
	if (!(this->music.openFromFile("Sounds/snoop.ogg")))
		std::cout << "Failed to load a main music";
	this->music.setVolume(50);
	this->music.setLoop(true);
	if (!(this->contact_buff.loadFromFile("Sounds/contact.wav")))
		std::cout << "Failed to load contact sound";
	this->contact_sound.setBuffer(contact_buff);
	this->contact_sound.setVolume(100);

	if (!(this->buffer_crash.loadFromFile("Sounds/crash_1.ogg")))
		std::cout << "Failed to load crash sound";
	this->crash_sound.setBuffer(buffer_crash);
	this->crash_sound.setVolume(100);

}

void Game::updateEnemies(int speed, int posY)
{
	this->spawnTimer += 0.1f;
	if (this->spawnTimer > this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(2500, 450 + (rand() % 4) * 110, this->player.getSpeed(), rand() % 3 + 1));
		this->spawnTimer = 0.f;
	}
	for (int i = 0; i < this->enemies.size(); ++i)
	{	
		this->enemies[i]->update(speed, posY);

		//Remove enemy at the buttom
		if ((this->enemies[i]->getBounds().left < -10000) || (this->enemies[i]->getBounds().left > 5000))
		{
			this->enemies.erase(this->enemies.begin() + i);
		}
	}
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->render();
		this->update();
	}
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

void Game::mute()
{
	this->player.mute();
	this->music.pause();
}

Game::Game()
{
	initSounds();
	initTextures();
	initVariables();
	initWindow();
	initEnemies();
	initCoins();
	ShowCursor(false);
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

Game::~Game()
{
	delete this->window;
}


void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent)) {
		switch (this->sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
				this->window->close();

			if (this->sfmlEvent.key.code == sf::Keyboard::F)
				this->changeMusic();
			break;
		}
	}
}

void Game::updatePlayer()
{
	this->player.update(this->window);
}

sf::RenderWindow* Game::getWindow()
{
	return this->window;
}

void Game::renderGame()
{
	this->land.render(this->window);
	for (auto* coin : this->coins)
	{
		coin->render(this->window);
	}
	for (auto* enemy : this->enemies)
	{
		if (enemy->getLine() == 0)
			enemy->render(this->window);
	}
	for (auto* enemy : this->enemies)
	{
		if (enemy->getLine() == 1)
			enemy->render(this->window);
	}
	for (auto* enemy : this->enemies)
	{
		if (enemy->getLine() == 2)
			enemy->render(this->window);
	}
	for (auto* enemy : this->enemies)
	{
		if (enemy->getLine() == 3)
			enemy->render(this->window);
	}
	this->player.render(this->window);
	if (this->endGame == true)
		this->window->draw(this->end_spr);
}

void Game::render()
{
	this->window->clear();
	if (this->menu.getFlag() != 3)
		this->menu.render(this->window);
	else
		this->renderGame();
	this->window->display();
}

void Game::crash(int i)
{
	if (this->player.getShape().getGlobalBounds().left > this->enemies[i]->getBounds().left) {
		this->enemies[i]->crash();
	}
	this->player.crash();
	this->crash_sound.play();
	if (this->player.getHp() < 1)
	{
		this->endGame = true;
	}
}

void Game::updateSoundCooldown()
{
	soundCooldown += 0.5f;
}

void Game::initCoins()
{
	this->coinTimerMax = 8.f;
	this->coinTimer = 0;
}

void Game::updateCoins(int speed, int posY)
{
	this->coinTimer += 0.1f;
	if (this->coinTimer > this->coinTimerMax && coins.size() < 5)
	{
		int choice = rand() % 100 + 1;
		int type = 1;
		if (choice > 80 && choice < 90)
			type = 2;
		else if (choice > 89)
			type = 3;
		this->coins.push_back(new Coin(2000, 450 + (rand() % 4) * 110, this->player.getSpeed(), type));
		this->coinTimer = 0.f;
	}
	for (int i = 0; i < this->coins.size(); ++i)
	{
		this->coins[i]->update(speed, posY);

		//Remove enemy at the buttom
		if (this->coins[i]->getBounds().left < -400)
		{
			this->coins.erase(this->coins.begin() + i);
		}
	}
}

void Game::updateCollision()
{
	int speed;
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		if (abs( this->player.getShape().getGlobalBounds().top - this->enemies[i]->getBounds().top) < 20 &&
			abs(this->player.getShape().getGlobalBounds().left - this->enemies[i]->getBounds().left) < 440)
		{
			this->crash(i);
		}
		for (size_t j = 0; j < this->enemies.size(); j++)
		{
			if (i != j)
			{
				if (abs(this->enemies[i]->getBounds().top - this->enemies[j]->getBounds().top) < 20 &&
					abs(this->enemies[i]->getBounds().left - this->enemies[j]->getBounds().left) < 440)
				{
					if (this->enemies[i]->getBounds().left > 0 && this->enemies[i]->getBounds().left < 1920)
						contact_sound.play();
					if (this->enemies[i]->getSpeed() > this->enemies[j]->getSpeed())
					{
						int speed = this->enemies[i]->getSpeed();
						this->enemies[i]->changeSpeed(this->enemies[j]->getSpeed());
						this->enemies[j]->changeSpeed(speed);
						this->enemies[j]->boost();
					}
					else
					{
						int speed = this->enemies[j]->getSpeed();
						this->enemies[j]->changeSpeed(this->enemies[i]->getSpeed());
						this->enemies[i]->changeSpeed(speed);
						this->enemies[i]->boost();
					}
				}
			}
		}
	}
	for (size_t i = 0; i < this->coins.size(); i++)
	{
		if (abs(this->player.getShape().getGlobalBounds().top - this->coins[i]->getBounds().top) < 20 &&
			abs(this->player.getShape().getGlobalBounds().left - this->coins[i]->getBounds().left) < 440)
		{
			switch (coins[i]->getType())
			{
			case 1:
				this->player.getCoin();
				break;
			case 2:
				this->player.getNitro();
				break;
			case 3:
				this->player.changeLine();
				break;
			}
			coins.erase(coins.begin() + i);
		}
	}
	//Check the collision
}

void Game::updateGame()
{
	if (!this->endGame)
	{
		this->updateSoundCooldown();
		this->updatePlayer();
		this->updateCoins(player.getSpeed(), land.getPos().y);
		this->land.update(-this->player.getSpeed(), 0, player.getLine());
		this->updateEnemies(player.getSpeed(), land.getPos().y);
		this->updateCollision();
	}
	else {
		this->mute();
	}
}

void Game::updateMenu()
{
	menu.run(window, window);
}

void Game::update()
{
	this->pollEvents();
	checkMenu();
	if (!gameWorking)
		this->updateMenu();
	else
		this->updateGame();
}