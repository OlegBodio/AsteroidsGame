#include "Player.hpp"


Player::Player(sf::Texture& tex)
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HIGH), "Test SHIP");
	ColliderManager& CollManager = ColliderManager::instance();
	PlayerManager& PlayManager = PlayerManager::instance();
	dx = dy = 0;
	sprite.setTexture(tex);
	sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HIGH / 2);
	window.clear();
	window.draw(sprite);
	CollManager.registerCollider(this);
	PlayManager.registerPlayer(this);
}

void Player::update(float time)// Тут кста зроблено так як ти і кажеш
{
	sf::FloatRect buf = sprite.getGlobalBounds();
	buf.left += dx * time;
	buf.top += dy * time;

	sprite.setPosition(buf.left, buf.top);
	dx = 0;
	dy = 0;
}

sf::FloatRect Player::getRect() const
{
	return sprite.getGlobalBounds();
}

void Player::setDX(float _dx)
{
	dx = _dx;
}

void Player::setDY(float _dy)
{
	dy = _dy;
}

void Player::addDx(float value)
{
	dx += value;
}

void Player::addDy(float value)
{
	dy += value;
}

float Player::getDx() const
{
	return dx;
}

float Player::getDy() const
{
	return dy;
}

sf::Sprite* Player::getSprite()
{
	sf::Sprite* buf = &sprite;
	return buf;
}

sf::Vector2f Player::getPosition()
{
	sf::FloatRect spriteBounds = sprite.getGlobalBounds();
	sf::Vector2f position(spriteBounds.left + spriteBounds.width / 2, spriteBounds.top + spriteBounds.height / 2);
	return position;
}

float Player::getRadius()
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

void Player::onCollide()
{ 
	alive = false;
}

bool Player::isAlive()
{
	return alive;
}
void Player::setAlive(bool mode)
{
	alive = mode;
}
void Player::reset() {
	ColliderManager& CollManager = ColliderManager::instance();
	alive = true;
	CollManager.registerCollider(this);
}

void PlayerManager::reset()
{
	p->reset();
}

PlayerManager& PlayerManager::instance()
{
	static PlayerManager s_instance;
	return s_instance;
}

void PlayerManager::registerPlayer(Player* p_)
{
	p = p_;
}
