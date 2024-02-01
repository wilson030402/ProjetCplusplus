#include <SFML/Graphics.hpp>
#include <vector>
#include "Drawable.hpp"


#ifndef WALL_HH
#define WALL_HH
//classe pour faire des murs/sols
class Wall: public Drawable{
	protected:
	sf::Vector2f top_left;
	sf::Vector2f bot_right;
	sf::Texture *texture;
	sf::Sprite sprite;
	public:
	
	//return 1 si on est dans un mur et 0 sinon
	virtual int checkInWall(const sf::Vector2f& playerpos, const sf::Vector2f& playersize) {
		
		if (((playerpos.x+playersize.x) > top_left.x && playerpos.x < bot_right.x) && \
        		((playerpos.y+playersize.y) > top_left.y && playerpos.y < bot_right.y)) {
        		return 1; // Player is inside the wall
    		}

		return 0; // Player is outside the wall
		}
	
	//dans ce cas elle permet simplement de différencier les murs classiques des murs tueurs
	virtual int getState(){
		return 0;
	}
	Wall(){
		top_left=sf::Vector2f(0.0, 0.0);
		bot_right=sf::Vector2f(0.0, 0.0);
	}
	Wall(sf::Vector2f vect_left, sf::Vector2f vect_right){
		top_left=vect_left;
		bot_right=vect_right;
		//mise à jour de la position
		
		sf::Vector2f size=getSize(vect_left, vect_right);
		texture=init_sprite(&sprite, "ressource/wall.jpg", vect_left, &size );
		sprite.setTexture(*texture);
		sprite.setOrigin(0, 0);
	}
	
	Wall(sf::Vector2f vect_left, sf::Vector2f vect_right, const std::string textName){
		top_left=vect_left;
		bot_right=vect_right;
		//mise à jour de la position
		
		sf::Vector2f size=getSize(vect_left, vect_right);
		texture=init_sprite(&sprite, textName, vect_left, &size );
		sprite.setTexture(*texture);
	}
	
	//constructeur par copie
	Wall(const Wall& wall){
		*this=wall;
	}
	
	//renvoie un pointeur vers un sprite
	sf::Sprite pxgetSprite(){
		return sprite;
	}
	
	//fonction pour dessiner les murs via la scene
	void draw(sf::RenderWindow* window){
		window->draw(this->sprite);
	}
	
	//surcharge d'opérateur pour le constructeur par copie
	Wall& operator=(const Wall& wallbis){
		
		this->top_left=wallbis.top_left;
		this->bot_right=wallbis.bot_right;
		this->texture=wallbis.texture;
		this->sprite=wallbis.sprite;
		return *this;
	}
	
	sf::Vector2f getTopLeft(){
		return this->top_left;
	}
	
	//méthode pour permettre à la scene de déplacer les murs, n'est pas utilisée 
	virtual void move_left(float val){
		
	}
	float getPosX(){
		return this->sprite.getPosition().x;
	}
	
};






#endif

