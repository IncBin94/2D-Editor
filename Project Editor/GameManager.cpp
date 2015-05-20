#include "GameManager.h"

GameManager* GameManager::Instance = nullptr;

GameManager* GameManager::GetInstance()
{
	if( Instance == nullptr ) return Instance = new GameManager;

	else
	return Instance;
}

void GameManager::Destroy()
{
	if( Instance != nullptr ) 
	{
		delete MainWindow;
		delete pTexture_mgr_Instance;
		delete pTile_Instance;
		delete Instance;
	}

}


void GameManager::Initialize(const std::string& img, const sf::Vector2i mrg, const sf::Vector2i Resolution, const sf::Vector2i Size, const sf::Color* alphamask)
{
	

	pTexture_mgr_Instance = new TextureManager(img, static_cast<sf::Vector2f>(mrg), alphamask);
	pTile_Instance        = new TopTile(pTexture_mgr_Instance);
	MainWindow            = new sf::RenderWindow(sf::VideoMode(Resolution.x, Resolution.y), "Project Editor", sf::Style::Fullscreen);

	pTile_Instance->Initialize(Size.x, Size.y);

	MouseRec.setFillColor(sf::Color::Transparent);
	MouseRec.setOutlineColor(sf::Color::Blue);
	MouseRec.setSize(pTexture_mgr_Instance->GetOriginalMargins());
	MouseRec.setFillColor(sf::Color(255,255,255,100));

	font.loadFromFile("arial.ttf");
	Text.setFont(font);
	Text.setCharacterSize(21);
	Text.setColor(sf::Color::Red);
	Text.setStyle(sf::Text::Bold);
	Text.setPosition(650,0);

	//pTexture_mgr_Instance->TempUpdate(); // to avoid ( use it dynamicaly when implementing a GUI for Rectangle , currently just on 0.0 cords )
}

void GameManager::HandleEvents(unsigned int State)
{


	if( sf::Keyboard::isKeyPressed(sf::Keyboard::W) )
	{
		pTexture_mgr_Instance->GetRekt().setPosition(10000,10000); // temporary solution xD

	}
	else if( sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
	{
		pTexture_mgr_Instance->GetRekt().setPosition(0,0);

	}

	else if( State == TEXTURE_COLLISION )
	{
		pTexture_mgr_Instance->Controls(MouseRec, sf::Mouse::isButtonPressed(sf::Mouse::Left) );
		MouseRec.setOutlineThickness(1.f);
		MouseRec.setOutlineColor(sf::Color::Red);
		MouseRec.setSize(pTexture_mgr_Instance->GetOriginalMargins());

	}
	
	else if( State == MAP_COLLISION )
	{
		pTile_Instance->Update(MouseRec, MouseCordonates, sf::Mouse::isButtonPressed(sf::Mouse::Left) );
		MouseRec.setOutlineThickness(2.f);
		MouseRec.setOutlineColor(sf::Color::Green);
		MouseRec.setSize(pTexture_mgr_Instance->GetOriginalMargins() * pTexture_mgr_Instance->GetCurrentScale() );
	}
	


}

unsigned int GameManager::HandleCollisions()
{

	if( pTexture_mgr_Instance->Collide(MouseRec) && pTexture_mgr_Instance->GetRekt().getPosition().x == 0)          
	{
		return TEXTURE_COLLISION;
	}
	else if( pTile_Instance->TileCollision(MouseCordonates) )  return MAP_COLLISION;

	return NULL;
}

void GameManager::Draw()
{

	MainWindow->draw(*pTile_Instance);
	MainWindow->draw(pTexture_mgr_Instance->GetRekt());
	MainWindow->draw(this->MouseRec);

}



void GameManager::Update()
{
	auto win  = MainWindow;
	auto marg = pTexture_mgr_Instance->GetOriginalMargins();

	std::ostringstream StrP2;
	StrP2 << "X: " <<MouseCordonates.x << " " << "Y: " << MouseCordonates.y;
	std::string scoreP2(StrP2.str());

	Text.setString(scoreP2);
	


	MouseCordonates = static_cast<sf::Vector2f> (sf::Mouse::getPosition(*static_cast<sf::Window*>(win)));
	MouseRec.setPosition(MouseCordonates);

	this->HandleEvents( HandleCollisions() );

}

void GameManager::MainLoop()
{
	while (MainWindow->isOpen())
    {
        sf::Event event;
        while (MainWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                MainWindow->close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Z)
					pTile_Instance->AutoFill();
				if (event.key.code == sf::Keyboard::B)
					pTile_Instance->Wareframe(true);
				if (event.key.code == sf::Keyboard::C)
					pTile_Instance->Wareframe(false);
			}
			if (event.type == sf::Event::MouseWheelMoved)
			{

				pTexture_mgr_Instance->Slot_MouseRectScale(static_cast<float>(event.mouseWheel.delta));

			}
		}

	
		this->Update();
		MainWindow->clear(sf::Color::White);
		this->Draw();
		MainWindow->draw(Text);
        MainWindow->display();
	}

}