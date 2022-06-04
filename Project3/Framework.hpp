#pragma once

#define FRAMEWORK_API extern "C" __declspec(dllimport)

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Framework.hpp"
#include <string>
#include <vector>
#include <cmath>
#include "Constants.hpp"



class Sprite;

FRAMEWORK_API Sprite* createSprite(const char* path);
FRAMEWORK_API void drawSprite(Sprite*, int x, int y);
FRAMEWORK_API void getSpriteSize(Sprite* s, int& w, int &h);
FRAMEWORK_API void destroySprite(Sprite* s);

FRAMEWORK_API void drawTestBackground();

FRAMEWORK_API void getScreenSize(int& w, int &h);


FRAMEWORK_API unsigned int getTickCount();

FRAMEWORK_API void showCursor(bool bShow);

enum class FRKey {
	RIGHT = sf::Keyboard::Key::Right ,
	LEFT = sf::Keyboard::Key::Left,
	DOWN = sf::Keyboard::Key::Down,
	UP = sf::Keyboard::Key::Up,
	COUNT = sf::Keyboard::Key::KeyCount
};

enum class FRMouseButton{
	LEFT = sf::Mouse::Button::Left,
	MIDDLE = sf::Mouse::Button::Middle,
	RIGHT = sf::Mouse::Button::Right,
	COUNT = sf::Mouse::Button::ButtonCount
};

class Framework {

public:
	// no function calls are available here, this function should only return width, height and fullscreen values
	virtual void PreInit(int& width, int& height, bool& fullscreen) = 0;

	// return : true - ok, false - failed, application will exit
	virtual bool Init() = 0;

	virtual void Close() = 0;

	// return value: if true will exit the application
	virtual bool Tick() = 0;

	// param: xrel, yrel: The relative motion in the X/Y direction 
	// param: x, y : coordinate, relative to window
	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) = 0;

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) = 0;

	virtual void onKeyPressed(FRKey k) = 0;

	virtual void onKeyReleased(FRKey k) = 0;

	virtual const char* GetTitle() = 0;

	virtual ~Framework() {};
};


FRAMEWORK_API int run(Framework*); 
