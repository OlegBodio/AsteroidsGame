#pragma once
#include "Framework.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Collider.hpp"
#include "Asteroid.hpp"


class MyFramework : public Framework
{
	int width;
	int height;
	bool fullscreen;
	sf::Clock clock;

	
	
	sf::RenderWindow window;
	sf::RectangleShape background;

public:

	std::shared_ptr<Player> p;
	BulletManager& BullManager = BulletManager::instance();
	AsteroidManager& AsterManager = AsteroidManager::instance();
	ColliderManager& CollManager = ColliderManager::instance();

	
	virtual void PreInit(int& width, int& height, bool& fullscreen) override;

	
	virtual bool Init() override;

	virtual void Close() override;

	
	virtual bool Tick() override;
	virtual void resetPlayer();
	
	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) override;

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) override;

	virtual void onKeyPressed(FRKey k) override;

	virtual void onKeyReleased(FRKey k) override;

	virtual const char* GetTitle();

	virtual ~MyFramework();
};


