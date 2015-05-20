#include <SFML/Graphics.hpp>
#include "GameManager.h"



void main()
{
	GameManager::GetInstance()->Initialize("Zelda.png", sf::Vector2i(16,16), sf::Vector2i(1360,768), sf::Vector2i(1360/16,60), nullptr );
	GameManager::GetInstance()->MainLoop();
	GameManager::GetInstance()->Destroy();
	
}