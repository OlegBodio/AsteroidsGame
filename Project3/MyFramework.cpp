#include "MyFramework.hpp"

static  bool doClose = false;

namespace
{
	const char* TITLE = "Asteroids";
}

sf::FloatRect getRect(float lx, float ly, float width, float high)
{
	sf::FloatRect r(lx, ly, width, high);
	return r;
}

void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{

	 width = WINDOW_WIDTH;
	 height = WINDOW_HIGH;
	 fullscreen = false;
}

bool MyFramework::Init()
{
	try
	{
		//////////////////Створення вікна//////////////////////////////
		PreInit(width, height, fullscreen);
		sf::Vector2u windowSize(width, height);
		
		//////////////////Створення плеєра//////////////////////////////
		sf::Texture tShip;
		tShip.loadFromFile(SPACESHIP_PATH);
		std::shared_ptr<Player> prePlayer(new Player(tShip));
		p = prePlayer;
		
		////////////////////////////////////////////////////
		//////////////////настройка астероїда//////////////////////////////
		AsterManager.init(5);
		AsterManager.start(*p);
		return true;
	}
	catch(...)
	{
		return false;
	}
}

void MyFramework::Close()
{
	window.close();
	doClose = true;
}

int run(Framework* game)
{
	game->Init();
	while (true)
	{
		if (!game->Tick())
		{
			ColliderManager& CollManager = ColliderManager::instance();
				AsteroidManager& AsterManager = AsteroidManager::instance();
				BulletManager& BullManager = BulletManager::instance();
				PlayerManager& PlayManager = PlayerManager::instance();
				CollManager.reset();
				AsterManager.reset();
				BullManager.reset();
				PlayManager.reset();
		}
		else
		{
			break;
		}
	}
	return 0;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {};

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {};

void MyFramework::onKeyReleased(FRKey k) {};



const char* MyFramework::GetTitle() 
{ 
	return TITLE;
}

MyFramework::~MyFramework() 
{

}

bool MyFramework::Tick() 
{ 
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HIGH), "Game");
	sf::Texture backgroundTexture;// Не можу пояснити але факт, якщо присвоїти тектуру тут то фон відобразиться, інакше ні.
		backgroundTexture.loadFromFile(BACKGROUND_PATH);
		const sf::Texture* p_background = &backgroundTexture;
		background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HIGH)); //З ініту Не малюэться тоді фон, я пробував
		background.setTexture(p_background);
		window.draw(background);

		sf::Texture tShip;// ну і шляхом чергового костиля була вирішена проблема
		tShip.loadFromFile(SPACESHIP_PATH);
		p->sprite.setTexture(tShip);



		sf::Clock clock;
		srand(static_cast<unsigned int>(time(0)));

		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)//+
				{
					window.close();
					return true;
				}
			}
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//+
			{
				onKeyPressed(FRKey::LEFT);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//+
			{
				onKeyPressed(FRKey::RIGHT);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				onKeyPressed(FRKey::UP);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				onKeyPressed(FRKey::DOWN);
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2f position(event.mouseButton.x, event.mouseButton.y);
					BullManager.createNewBullet(*p, position);
				}
			}
			if (p->isAlive())
			{
				window.clear();
				window.draw(background);
				p->update(time);
				BullManager.update(time, window);
				AsterManager.update(time, *p, window);
				CollManager.update();
				window.draw(p->sprite);
				window.display();
			}
			else
			{
				break;
			}
			
		}
	return false; 
}

void MyFramework::onKeyPressed(FRKey k)
{
	if (k == FRKey::RIGHT)
	{
		if (p->getRect().left + p->getRect().width < WINDOW_WIDTH)
		{
			p->addDx(100.0);
		}
	}
	if (k == FRKey::LEFT)
	{
		if (p->getRect().left > 0)
		{
			p->addDx(-100.0);
		}
	}
	if (k == FRKey::DOWN)
	{
		if (p->getRect().top + p->getRect().height < WINDOW_HIGH)
		{
			p->addDy(100.0);
		}
	}
	if (k == FRKey::UP)
	{
		if (p->getRect().top > 0)
		{
			p->addDy(-100.0);
		}
	}

}

void MyFramework::resetPlayer()
{
	p->reset();
}
