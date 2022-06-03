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

	
	// дата не должна быть публичной
	sf::RenderWindow window;
	sf::RectangleShape background;

public:

	std::shared_ptr<Player> p;
	// не надо держать синглоты в классе. Просто получай инстанс когда надо
	BulletManager& BullManager = BulletManager::instance();
	AsteroidManager& AsterManager = AsteroidManager::instance();
	ColliderManager& CollManager = ColliderManager::instance();

	// no futd::string titlenction calls are available here, this function should only return width, height and fullscreen values 
	virtual void PreInit(int& width, int& height, bool& fullscreen) override;

	// return : true - ok, false - failed, application will exit
	virtual bool Init() override;

	virtual void Close() override;

	// return value: if true will exit the application
	virtual bool Tick() override;
	virtual void resetPlayer();
	// param: xrel, yrel: The relative motion in the X/Y direction 
	// param: x, y : coordinate, relative to window
	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) override;

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) override;

	virtual void onKeyPressed(FRKey k) override;

	virtual void onKeyReleased(FRKey k) override;

	virtual const char* GetTitle();

	virtual ~MyFramework();
};

//int run(MyFramework*);

