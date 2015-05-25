#include "resources.hpp"
sf::Texture* ResourceStore::shoot=NULL;
void ResourceStore::loadTexture(void){
	if(ResourceStore::shoot==NULL){
		ResourceStore::shoot=new sf::Texture();
		ResourceStore::shoot->loadFromFile("./res/img/shoot.png");
	}
}
