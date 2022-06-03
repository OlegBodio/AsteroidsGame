#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Collider.hpp"
#include <iostream>
#include <set>
#include "Constants.hpp"



class Asteroid: public ICollidable
{
protected:
	sf::Vector2f position;
	sf::Vector2f speed;
public:
	sf::Sprite sprite;
	virtual void move(float time) = 0;
	virtual sf::Vector2f getPosition() = 0;
	virtual float getRadius() = 0;
	virtual void onCollide() = 0;
	virtual bool isOut() = 0;
};

class BigAsteroid: public Asteroid
{
private:
	void destroy();
public:
	BigAsteroid(const sf::Vector2f& position_, const sf::Vector2f& speed_, sf::Texture& image);
	virtual void move(float time);
	virtual sf::Vector2f getPosition();
	virtual float getRadius();
	virtual void onCollide();
	virtual bool isOut();
};

class AsteroidManager
{
private:
	std::vector<std::shared_ptr<Asteroid>> asteroids;
	unsigned count;
	unsigned counter = 0;
	sf::Texture bigAsteroid, smallAsteroid;
	AsteroidManager() = default;
	AsteroidManager(AsteroidManager& Manager) {};
public:
	static AsteroidManager& instance();
	void registerAsteroid();
	void init(unsigned count);
	void start(Player& p);
	void createNewAsteroid(const Player& p);
	void update(float time, Player& p, sf::RenderWindow& window);
	void drawAll(sf::RenderWindow& window);
	void destroyAsteroid(ICollidable* obj); 
	void addCounter(short value);
	virtual void CreateSmallAsteroid(float x, float y, sf::Vector2f& speed);
	void reset();
};

class SmallAsteroid : public Asteroid
{
private:
	void destroy();
public:
	SmallAsteroid(const sf::Vector2f& position_, const sf::Vector2f& speed_, sf::Texture& image);
	virtual void move(float time);
	virtual sf::Vector2f getPosition();
	virtual float getRadius();
	virtual void onCollide();
	virtual bool isOut();
};