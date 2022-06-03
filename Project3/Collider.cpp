#include "Collider.hpp"


ColliderManager& ColliderManager::instance() 
{
	static ColliderManager s_instance; 
	return s_instance;
}

void ColliderManager::update()
{
	std::set<ICollidable*> collided;
	for (int i = 0; i < colliders.size() - 1; i++)
	{
		for (int j = i + 1; j < colliders.size(); j++)
		{
			if (!checkCollide(colliders[i], colliders[j]))
			{
				collided.insert(colliders[i]);
				collided.insert(colliders[j]);
			}
		}
	}
	if (collided.size() > 0)
	{
		for (auto& collidedObj : collided)
		{
			collidedObj->onCollide();
		}
	}
}
void ColliderManager::registerCollider(ICollidable* obj) 
{
	colliders.push_back(obj);
}

void ColliderManager::unregisterCollider(ICollidable* obj) 
{
	colliders.erase(std::find(colliders.begin(), colliders.end(), obj));	
}

bool ColliderManager::checkCollide( ICollidable* obj1,  ICollidable* obj2)
{
	sf::Vector2f position1 = obj1->getPosition();
	sf::Vector2f position2 = obj2->getPosition();
	bool touch = sqrt(pow((position2.y - position1.y), 2) + pow((position2.x - position1.x), 2)) > obj1->getRadius() + obj2->getRadius();
	return touch;
}

void ColliderManager::reset()
{
	colliders.clear();
}


