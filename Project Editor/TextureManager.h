#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML\Graphics.hpp>

class TextureManager
{
private:
	
	sf::Texture m_Tiletxr;

	sf::FloatRect TextureFloatrect;

	sf::RectangleShape m_TextureRectangle;

	std::vector<sf::Vector2f> m_VectCenterpoints;

	sf::Color Alphaholder;

	sf::Vector2f TexCords[4]; // temp

	const sf::Vector2f Margins;

	float MouseScale;

	// non copyable
	TextureManager& operator= (const TextureManager&){} 

    TextureManager (const TextureManager&){}

	// temp to jump on public ( member in constructor) next updating the texture palette via GUI
	void TempUpdate(); 

public:

	bool Collide(sf::RectangleShape&);
	void Controls(sf::RectangleShape&, bool);
	void Slot_MouseRectScale(float);

	const sf::Vector2f&              GetOriginalMargins() const { return Margins; }
	const std::vector<sf::Vector2f>& GetCenters()         const { return m_VectCenterpoints; }
	const sf::Vector2f* const        GetTextureCords()    const { return &TexCords[0]; }
	const sf::Color&				 GetAlphaColor()      const { return Alphaholder; }	// ?
	const sf::Texture* const		 GetTexture()		  const { return &m_Tiletxr; }
	float							 GetCurrentScale()    const { return MouseScale; };
	sf::RectangleShape&				 GetRekt()			  { return m_TextureRectangle; } // modified non const made XD

	TextureManager(const std::string&, const sf::Vector2f, const sf::Color* = nullptr);
	~TextureManager() {}

};

#endif