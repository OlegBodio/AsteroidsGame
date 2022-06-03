#include "Bullet.hpp"

Bullet::Bullet(const Player& p,  sf::Vector2f& direction)
{
	static sf::Clock cooldown;
	float time = cooldown.getElapsedTime().asSeconds(); //ќсь вона ц€ дельта так
	if (time > 1)
	{
		sf::FloatRect start = p.getRect();
		position = sf::Vector2f(start.left + start.width / 2, start.top - 20);
		sf::Texture tex;
		tex.loadFromFile("data/bullet.png");
		sprite.setTexture(tex);
		sprite.setPosition(position);
		direction = direction - position;
		double mag = 1 / (sqrt(direction.x * direction.x + direction.y * direction.y));
		speed = sf::Vector2f(direction.x * mag, direction.y * mag);
		cooldown.restart(); // перезапуск
	}
}

sf::Vector2f Bullet::getPosition()
{
	sf::FloatRect spriteBounds = sprite.getGlobalBounds();
	sf::Vector2f position(spriteBounds.left + spriteBounds.width / 2, spriteBounds.top + spriteBounds.height / 2);
	return position;
 }

float Bullet::getRadius()
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

void Bullet::move(float time)
{
	sf::Vector2f step(time * 100 * speed.x, time * 100 * speed.y);
	sprite.setPosition(sprite.getPosition() + step);
}

BulletManager& BulletManager::instance()
{
	static BulletManager s_instance;
	return s_instance;
}

void BulletManager::createNewBullet(const Player& p, sf::Vector2f& direction)
{
	ColliderManager& CollManager = ColliderManager::instance();
	std::shared_ptr<Bullet> newBullet(new Bullet(p, direction));
	CollManager.registerCollider(newBullet.get());
	bullets.push_back(newBullet);
}

bool Bullet::isOut()
{
	sf::Vector2f position = getPosition();
	return((position.x >= WINDOW_WIDTH) || (position.x <= 0) || (position.y >= WINDOW_HIGH) || (position.y <= 0));
}

void BulletManager::update(float time, sf::RenderWindow& window)
{
	BulletManager& BullManager = BulletManager::instance();
	std::set<std::shared_ptr<Bullet>> out;
	for (const auto& bullet : bullets)
	{
		if (bullet->isOut())
		{
			out.insert(bullet);
		}
		bullet->move(time);
	}
	for (auto& obj : out)
	{
		destroyBullet(obj.get());
	}
	BullManager.drawAll(window);
}

void BulletManager::drawAll(sf::RenderWindow& window)
{
	for (const auto& bullet : bullets)
	{
		window.draw(bullet->sprite);
	}
}

void BulletManager::destroyBullet(ICollidable* obj)
{
	for (const auto& ptr : bullets)
	{
		if (ptr.get() == obj)
		{
			ColliderManager& CollManager = ColliderManager::instance();
			CollManager.unregisterCollider(obj);
			bullets.erase(std::find(bullets.begin(), bullets.end(), ptr));

		}
	}
}

void Bullet::onCollide()
{
	destroy();
}

void Bullet::destroy()
{
	BulletManager::instance().destroyBullet(this);
}

void BulletManager::reset()
{
	bullets.clear();
}

