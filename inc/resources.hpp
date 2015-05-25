#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include<SFML/Graphics.hpp>
class ResourceStore{
	public:
		static sf::Texture* shoot;
		static void loadTexture(void);
};
#endif
