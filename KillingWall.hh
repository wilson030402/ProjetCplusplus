#include "Wall.hh"

//on considère que le KillingWall n'à que deux états:
// 0 inofensif, (temps que le mur )


#ifndef KILLINGWALL_HH
#define KILLINGWALL_HH

//l'état nothing pourrait être utile dans le cadre d'annimations
#define KILLING 1
#define NOTHING 0

//ce mur peux bouger son sprite, sa hitbox n'est valable que quand le décompte de l'état est nulle
class KillingWall: public Wall{
	public:
	
	//renvoie -1 si le joueur est dans un mur tueur 1 si dans un mur normal et 0 sinon
	int checkInWall(const sf::Vector2f& playerpos, const sf::Vector2f& playersize)override{		
		int tmp =Wall::checkInWall(playerpos, playersize);
		//std::cout<<"Wall::chekInWall() : "<<tmp<<std::endl;
   		playersize.y-15.0;
		playersize.x-15.0;
		if(state==KILLING && tmp==1){
			//traitement de la mort
			std::cout<<"mort"<<std::endl;
			return -1;
		}
		else{
			//std::cout<<"KillingWall::checkInWall() : return : "<< tmp<<std::endl;
			return tmp;
		}
	}
	int setState(int state){
		return this->state=state;
	}
	//redéfinition des constructeur
	//...........
	KillingWall(sf::Vector2f vect_left, sf::Vector2f vect_right):\
	Wall(vect_left, vect_right)\
	{
	state=0;
	cpt_state=0;
	}
	
	KillingWall(sf::Vector2f vect_left, sf::Vector2f vect_right, const std::string textName):\
	Wall(vect_left, vect_right, textName)\
	{
	state=0;
	cpt_state=0;
	}
	
	
	KillingWall(const KillingWall& wall):Wall(wall){
		this->state=wall.state;
		this->cpt_state=wall.cpt_state;
	}
	
	void move_left(float val) override{
		this->top_left.x-=val;
		this->bot_right.x-=val;
		this->sprite.move((-1)*val, 0.0);
	}
	private:
	int state;
	int cpt_state;
};



#endif
