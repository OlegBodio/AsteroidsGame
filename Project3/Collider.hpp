#pragma once
#include <SFML/Graphics.hpp>
#include<set>
#include<cmath>
#include<algorithm>
#include<iostream>
#include "Constants.hpp"

class ICollidable
{
public:
	virtual sf::Vector2f getPosition() = 0;
	virtual float getRadius() = 0;
	virtual void onCollide() = 0;
};

class ColliderManager
{
private:
	ColliderManager(ColliderManager& Manager) {};
	std::vector <ICollidable*> colliders = {};
	ColliderManager() = default;
	bool checkCollide(ICollidable* obj1, ICollidable* obj2);
public:
	void reset();
	void registerCollider(ICollidable* obj);
	void unregisterCollider(ICollidable* obj);
	static ColliderManager& instance();
	void update();
};