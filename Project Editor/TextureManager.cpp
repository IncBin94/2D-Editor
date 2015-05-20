#include "TextureManager.h"



TextureManager::TextureManager(const std::string& img, const sf::Vector2f Mrg, const sf::Color* AlphaMask ) : Margins(Mrg), MouseScale(1.f)
{
	sf::Image Mask;
	if(Mask.loadFromFile(img) )		// make a bool private func
	{
		if(AlphaMask != nullptr)
		{
			Alphaholder = *AlphaMask;  // dangerous
			Mask.createMaskFromColor(*AlphaMask);
		}
		
		
		m_Tiletxr.loadFromImage(Mask);
		m_TextureRectangle.setPosition(0, 0);
		m_TextureRectangle.setSize(sf::Vector2f((float)m_Tiletxr.getSize().x, (float)m_Tiletxr.getSize().y));
		m_TextureRectangle.setTexture(&m_Tiletxr);
		delete AlphaMask;


		TempUpdate(); // to dl
	}

}

void TextureManager::TempUpdate()	// private
{

	auto factx   = (Margins.x/2.f);
	auto facty   = (Margins.y)/2.f;

	auto endx    =  m_TextureRectangle.getPosition().x + m_TextureRectangle.getTexture()->getSize().x;
	auto endy    =  m_TextureRectangle.getPosition().y + m_TextureRectangle.getTexture()->getSize().y;

	for(auto ybegin = m_TextureRectangle.getPosition().y; ybegin < endy; ybegin += Margins.y)
		for(auto begin = m_TextureRectangle.getPosition().x; begin < endx ; begin += Margins.x)
		{
			sf::Vector2f temp( (begin + factx), (ybegin + facty) );
			m_VectCenterpoints.push_back(temp);
		}

	TextureFloatrect = m_TextureRectangle.getGlobalBounds();
	m_VectCenterpoints.shrink_to_fit();
}


bool TextureManager::Collide(sf::RectangleShape& MouseRect)
{
	if(MouseRect.getGlobalBounds().intersects(TextureFloatrect) ) return true;

	else
	return false;
}

void TextureManager::Controls(sf::RectangleShape& MouseRect, bool onClicked)
{
	for( auto &v : m_VectCenterpoints)
	{
		if(MouseRect.getGlobalBounds().contains(v))
		{
			float xcord = v.x - (Margins.x / 2.f);
			float ycord = v.y - (Margins.y / 2.f);

			MouseRect.setPosition(xcord, ycord);

			if(onClicked == true)
			{
				TexCords[0]  =  sf::Vector2f(MouseRect.getPosition().x, MouseRect.getPosition().y);
				TexCords[1]  =  sf::Vector2f(MouseRect.getPosition().x + Margins.x, MouseRect.getPosition().y);
				TexCords[2]  =  sf::Vector2f(MouseRect.getPosition().x + Margins.y, MouseRect.getPosition().y + Margins.y);
				TexCords[3]  =  sf::Vector2f(MouseRect.getPosition().x, MouseRect.getPosition().y + Margins.y);
			}
		}
	}


}

void TextureManager::Slot_MouseRectScale(float Factor) // newly implem .h Scale
{
	if( !(MouseScale == 1 && Factor < 0 )  ) MouseScale += Factor;
	
}