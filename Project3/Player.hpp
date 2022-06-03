#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.hpp"
#include "Constants.hpp"


static const std::string SPACESHIP_PATH = "spaceship.png";
/*
virtual sf::Vector2f getPosition() = 0;
virtual float getRadius() = 0;
virtual void onCollide() = 0;
*/
class Player: public ICollidable
{
private:
	float dx, dy; //speed
	bool isProtected = false;
	bool alive = true;
public:
	sf::Sprite sprite;
	Player(sf::Texture& tex);
	void update(float time);
	sf::FloatRect getRect() const;
	void setDX(float _dx);
	void setDY(float _dy);
	void addDx(float value);
	void addDy(float value);
	float getDx() const;
	float getDy() const;
	sf::Sprite* getSprite();
	virtual sf::Vector2f getPosition();
	virtual float getRadius();
	virtual void onCollide();
	virtual bool isAlive();
	virtual void setAlive(bool mode);
	virtual void reset();

};

class PlayerManager
{
	Player* p;
	PlayerManager() = default;
	PlayerManager(PlayerManager& Manager) {};
public:
	static PlayerManager& instance();
	void registerPlayer();
	void reset();
	void registerPlayer(Player* p_);
};
