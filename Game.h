#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Coin.h"
#include "Menu.h"

class Game
{
private:
	sf::VideoMode videomode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;
	bool menuRunning;
	int soundCooldown;
	int soundCooldownMax;
	
	Texture end_texture;
	Sprite end_spr;

	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;
	Music music;


	SoundBuffer contact_buff;
	Sound contact_sound;

	SoundBuffer buffer_crash;
	Sound crash_sound;

	float coinTimer;
	float coinTimerMax;
	std::vector<Coin*> coins;

	Player player;
	Coin coin;
	Land land;
	Menu menu;
	bool gameWorking;
	void checkMenu();

	void changeMusic();
	void initTextures();
	void initVariables();
	void initWindow();
	void initEnemies();
	void initSounds();
	void updateEnemies(int speed, int posY);
	void crash(int i);
	void updateSoundCooldown();
	void initCoins();
	void updateCoins(int speed, int posY);
public:
	void run();

	const bool getEndGame() const;
	void mute();
	Game();
	~Game();

	void pollEvents();
	void updatePlayer();
	sf::RenderWindow* getWindow();
	void renderGame();
	void update();
	void render();
	void updateCollision();
	void updateGame();
	void updateMenu();
};

