#include <SFML\Graphics.hpp>

#include "TopTile.h"
#include <sstream>
#include <iostream>

#define MAP_COLLISION 1
#define TEXTURE_COLLISION 2


class GameManager
{


private:
	sf::RectangleShape		  MouseRec;
	sf::Vector2f		      MouseCordonates;

	sf::Text Text;   // temp
	sf::Font font;
	sf::Clock Clk;

	static GameManager		*Instance;
	sf::RenderWindow		*MainWindow;
	TextureManager			*pTexture_mgr_Instance;
	TopTile			        *pTile_Instance;

	GameManager(const GameManager&) {}
	GameManager() {}
	GameManager& operator=( const GameManager& ) {}
	~GameManager() {}

	void Update();
	void HandleEvents(unsigned int);
	inline unsigned int HandleCollisions();
	void Draw();

public:

	static GameManager* GetInstance();

	void Initialize(const std::string&, const sf::Vector2i, const sf::Vector2i, const sf::Vector2i, const sf::Color* = nullptr);
	void MainLoop();
	void Destroy();

	
};

