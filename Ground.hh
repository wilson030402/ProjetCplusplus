#include "Wall.hh"

#ifndef GROUND_HH
#define GROUND_HH

class Ground: public Wall{
	private:
	float ypos;
	public:
	Ground(){
		this->ypos=400;
	}
	Ground(float hauteur ){
		this->ypos=hauteur;
	}
	
	//vérifie simplement que le joueur nest pas sous le sol
	int checkInWall(const sf::Vector2f& playerpos, const sf::Vector2f& playersize)override{
		if((playerpos.y+playersize.y) > this->ypos ) {
        		return 1; // Player is inside the wall
    		}
		return 0; // Player is outside the wall
	}
	float getPosX(){
		return 0.0;
	}
	
	//le sol ne possédant pas de sprite, il est nécessaire de redéfinir la méthode draw de telle sorte que la méthode mère ne soit pas appelée
	void draw(sf::RenderWindow* window)override{
		//pas d'appel
	}
};


#endif


