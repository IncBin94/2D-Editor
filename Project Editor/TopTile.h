#ifndef TOPTILE_H
#define TOPTILE_H

#include <SFML\Graphics.hpp>
#include "TextureManager.h"


class TopTile : public sf::Drawable , public sf::Transformable
{

private:

	sf::VertexArray          m_VertexArr;
	std::vector<sf::Vertex*> m_vertexVect;

	TextureManager*          p_TextureManager;
	const sf::Texture*       pTexture;

	TopTile(const TopTile&) {};

public:

	bool Initialize(unsigned int, unsigned int);
	void Wareframe(bool);
	void Update(sf::RectangleShape&, const sf::Vector2f&, bool);
	bool TileCollision(const sf::Vector2f&);
	void AutoFill();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
		states.texture	  = pTexture;
        target.draw(m_VertexArr, states);
    }

	TopTile(TextureManager*);
	~TopTile();
	

};

#endif