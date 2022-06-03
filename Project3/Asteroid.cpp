#include "Asteroid.hpp"
#include "Player.hpp"
#include "Collider.hpp"
#include<iostream>

BigAsteroid::BigAsteroid(const sf::Vector2f& position_, const sf::Vector2f& speed_, sf::Texture& image)
{
	position = position_;
	speed = speed_;
	sprite.setTexture(image);
	sprite.setPosition(position);
}
void BigAsteroid::move(float time)
{
	sf::Vector2f step(time * 25  * speed.x, time * 25 * speed.y); 
	sprite.setPosition(sprite.getPosition() + step);
}

sf::Vector2f BigAsteroid::getPosition()
{
	sf::FloatRect spriteBounds = sprite.getGlobalBounds();
	sf::Vector2f position(spriteBounds.left + spriteBounds.width / 2, spriteBounds.top + spriteBounds.height / 2);
	return position;
}

float BigAsteroid::getRadius()
{
	sf::FloatRect spriteBounds = sprite.getGlobalBounds();
	if (spriteBounds.width > spriteBounds.height)
	{
		return spriteBounds.width / 2;
	}
	else
	{
		return spriteBounds.height / 2;
	}
}

void BigAsteroid::onCollide()
{
	AsteroidManager& AsManager = AsteroidManager::instance();
	AsManager.CreateSmallAsteroid(getPosition().x + sprite.getGlobalBounds().width, getPosition().y + sprite.getGlobalBounds().height, speed);
	AsManager.CreateSmallAsteroid(getPosition().x - sprite.getGlobalBounds().width * 2, getPosition().y - sprite.getGlobalBounds().height, speed);
	destroy(); 
	
}

void BigAsteroid::destroy()
{
	AsteroidManager::instance().destroyAsteroid(this);
}

bool BigAsteroid::isOut()
{
	sf::Vector2f position = getPosition();
	return((position.x >= WINDOW_WIDTH) || (position.x <= 0) || (position.y >= WINDOW_HIGH) || (position.y <= 0));
}

void AsteroidManager::start(Player& p)
{
	while (counter < count)
	{
		createNewAsteroid(p);
	}
}

AsteroidManager& AsteroidManager::instance()
{
	static AsteroidManager s_instance;
	return s_instance;
}

void AsteroidManager::CreateSmallAsteroid(float x, float y, sf::Vector2f& speed)
{
	if (counter < count)
	{
		float p1 = x;
		float p2 = y;
		float s1 = speed.x;
		float s2 = speed.y;
		ColliderManager& CollManager = ColliderManager::instance();
		std::shared_ptr<Asteroid> newAsteroid(new SmallAsteroid(sf::Vector2f(p1, p2), sf::Vector2f(s1, s2), smallAsteroid));
		asteroids.push_back(newAsteroid);
		CollManager.registerCollider(newAsteroid.get());
		counter++;
	}
}

void AsteroidManager::init(unsigned count_)
{
	bigAsteroid.loadFromFile(BIG_ASTEROID_PATH);
	smallAsteroid.loadFromFile(SMALL_ASTEROID_PATH);
	count = count_;
}

void AsteroidManager::createNewAsteroid(const Player& p) 
{
	float p1 = rand() % WINDOW_WIDTH;
	float p2 = rand() % WINDOW_HIGH;
	float s1 = rand() % 5;
	float s2 = rand() % 5;
	sf::FloatRect pRect = p.getRect();
	float xCenter = pRect.left + pRect.width / 2;
	float yCenter = pRect.top - pRect.height / 2;
	ColliderManager& CollManager = ColliderManager::instance();
	if (sqrt(pow(p1 - xCenter, 2) + pow(p2 - yCenter, 2)) > 150)
	{
		std::shared_ptr<Asteroid> newAsteroid(new BigAsteroid(sf::Vector2f(p1, p2), sf::Vector2f(s1, s2), bigAsteroid));
		asteroids.push_back(newAsteroid);
		CollManager.registerCollider(newAsteroid.get());
		counter++;
	}
}

void AsteroidManager::destroyAsteroid(ICollidable* obj)
{
	for (const auto& ptr : asteroids)
	{
		if (ptr.get() == obj)
		{
			ColliderManager& CollManager = ColliderManager::instance();
			CollManager.unregisterCollider(obj);
			asteroids.erase(std::find(asteroids.begin(), asteroids.end(), ptr));
			counter -= 1;
		}
	}
}

void AsteroidManager::update(float time, Player& p, sf::RenderWindow& window) // Прийшов сюди
{
	std::set<std::shared_ptr<ICollidable>> out;
	for (const auto& asteroid : asteroids)
	{
		if (asteroid->isOut())
		{
			out.insert(asteroid);
		}
		asteroid->move(time);
	}
	for (auto& obj : out)
	{
		destroyAsteroid(obj.get());
	}
	AsteroidManager& AsterManager = AsteroidManager::instance();
	AsterManager.start(p);
	AsterManager.drawAll(window);
}

void AsteroidManager::drawAll(sf::RenderWindow& window)
{
	for (const auto& asteroid : asteroids)
	{
		window.draw(asteroid->sprite);
	}
}

void AsteroidManager::reset()
{
	asteroids.clear();
	counter = 0;
}


SmallAsteroid::SmallAsteroid(const sf::Vector2f& position_, const sf::Vector2f& speed_, sf::Texture& image)
{
	AsteroidManager& Astermanager = AsteroidManager::instance();
	position = position_;
	speed = speed_;
	sprite.setTexture(image);
	sprite.setPosition(position);
}

sf::Vector2f SmallAsteroid::getPosition()
{
	sf::FloatRect spriteBounds = sprite.getGlobalBounds();
	sf::Vector2f position(spriteBounds.left + spriteBounds.width / 2, spriteBounds.top + spriteBounds.height / 2);
	return position;
}

float SmallAsteroid::getRadius()
{
	sf::FloatRect spriteBounds = sprite.getGlobalBounds();
	if (spriteBounds.width > spriteBounds.height)
	{
		return spriteBounds.width / 2;
	}
	else
	{
		return spriteBounds.height / 2;
	}
}

void SmallAsteroid::move(float time)
{
	sf::Vector2f step(time * 50 * speed.x, time * 50 * speed.y);
	sprite.setPosition(sprite.getPosition() + step);
}

void SmallAsteroid::destroy()
{
	AsteroidManager::instance().destroyAsteroid(this);
}
 	

void SmallAsteroid::onCollide()
{
	destroy();
}

bool SmallAsteroid::isOut()
{
	sf::Vector2f position = getPosition();
	return((position.x >= WINDOW_WIDTH) || (position.x <= 0) || (position.y >= WINDOW_HIGH) || (position.y <= 0));
}

