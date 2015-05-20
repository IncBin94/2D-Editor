#include "TopTile.h"

TopTile::TopTile(TextureManager* Ptr) : p_TextureManager(Ptr)
{
	
}

bool TopTile::Initialize(unsigned int Width, unsigned int Height) // to be in constructor ?
{

	pTexture = p_TextureManager->GetTexture();
	auto mar = p_TextureManager->GetOriginalMargins();

	m_VertexArr.setPrimitiveType(sf::PrimitiveType::Quads);
	m_VertexArr.resize( Width * Height * 4 );

	for (unsigned int i = 0; i < Width; ++i)
		for (unsigned int j = 0; j < Height; ++j)
		{
			sf::Vertex* quad = &m_VertexArr[(i + j * Width) * 4];

			quad[0].position = sf::Vector2f(i * static_cast<float> (mar.x), j * static_cast<float> (mar.y) );
            quad[1].position = sf::Vector2f((i + 1) * static_cast<float> (mar.x), j * static_cast<float> (mar.y) );
            quad[2].position = sf::Vector2f((i + 1) * static_cast<float> (mar.x), (j + 1) * static_cast<float> (mar.y) );
            quad[3].position = sf::Vector2f(i * static_cast<float> (mar.x), (j + 1) * static_cast<float> (mar.y) );

			m_vertexVect.push_back(quad);

         }

    m_vertexVect.shrink_to_fit();
	return true;
}



void TopTile::Update(sf::RectangleShape& MouseRect, const sf::Vector2f& MouseCord, bool Click)
{
	
	auto Margins = p_TextureManager->GetOriginalMargins(); // to avoid ( Multiple Calls of get margins func )
	sf::Vector2f Origin;
	auto thick = MouseRect.getOutlineThickness();
	MouseRect.setOutlineThickness(0);

	for( auto &v : m_vertexVect)
	{
		float left    =  v[0].position.x;
		float top     =  v[0].position.y;
		float wid	  =  static_cast<float>  (Margins.x);
		float height  =  static_cast<float>  (Margins.y);

		const sf::FloatRect Rect(left, top, wid, height);

		if( Rect.contains( MouseCord ))		// check once
		{
			Origin.x = v[0].position.x;
			Origin.y = v[0].position.y;
			MouseRect.setPosition(Origin);

		}

		if( Click == true )		// rework for better perfo
		{

			sf::FloatRect Frect = MouseRect.getGlobalBounds();

			if( Frect.intersects(Rect ) )
			{
				auto TextureCors = p_TextureManager->GetTextureCords();

				v[0].texCoords   = TextureCors[0]; // random cords
				v[1].texCoords   = TextureCors[1];
				v[2].texCoords   = TextureCors[2];
				v[3].texCoords   = TextureCors[3];
			}


		}
	}
	MouseRect.setOutlineThickness(thick);
}


void TopTile::AutoFill()
{
	auto cr = p_TextureManager->GetTextureCords();

	for( auto &v : m_vertexVect)
	{
		v[0].texCoords   = cr[0]; // random cords
		v[1].texCoords   = cr[1];
		v[2].texCoords   = cr[2];
		v[3].texCoords   = cr[3];
	}

}


bool TopTile::TileCollision(const sf::Vector2f& MsCord)
{
	if( m_VertexArr.getBounds().contains(MsCord) ) return true;
	else
	return false;

}

void TopTile::Wareframe(bool On)
{
	On == true ? m_VertexArr.setPrimitiveType(sf::PrimitiveType::LinesStrip) :  m_VertexArr.setPrimitiveType(sf::PrimitiveType::Quads);

}

TopTile::~TopTile()
{

}

// modulis for factor 32 / 16 = 2