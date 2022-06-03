#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "Collider.hpp"
#include "Player.hpp"
#include <cmath>
#include<set>
class Bullet : public ICollidable
{
private:
	sf::Vector2f speed;
	sf::Vector2f position;
	virtual void destroy();
public:
	sf::Sprite sprite;
	Bullet(const Player& p, sf::Vector2f& direction);//+
	void move(float time);//+
	virtual sf::Vector2f getPosition();//+
	virtual float getRadius();//+
	virtual void onCollide();
	virtual bool isOut();//+
};


class BulletManager
{
private:
	std::vector<std::shared_ptr<Bullet>> bullets = {};
	BulletManager(BulletManager& Manager) {};
	BulletManager() = default;
public:
	static BulletManager& instance();//+
	void createNewBullet(const Player& p, sf::Vector2f& direction);//+
	void update(float time, sf::RenderWindow& window);//+
	void drawAll(sf::RenderWindow& window);//+
	void destroyBullet(ICollidable* obj);
	void reset();
};


