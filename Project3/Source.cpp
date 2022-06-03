#include "MyFramework.hpp"
#include "Framework.hpp"

int main()
{
	std::shared_ptr<Framework> game(new MyFramework);
	
	//game->Init();
	run(game.get());
	return 0;
}




