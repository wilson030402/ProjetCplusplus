#include <SFML/Graphics.hpp>
#include "function.hh"
#include "Drawable.hpp"

#ifndef CHARACTER_HH
#define CHARACTER_HH

#define CPTJUMP 17
#define DEAD -1
#define IDLE 0
#define JUMP 1
#define HIGHJUMP 2

//pour les sprites la méthide getPosition() permet d'avoir la position de clui-ci

class Character: public Drawable{
	
	private:
	//la variable "state" traduit l'état du joueur 
	int state;
	//la variable frame traduit le numéro de la frame dans la séquence
	int frame;
	int cpt_jump; //pour faire des animations il faut l'état de la dite animation
	sf::Texture* texture;
	sf::Vector2f hitbox;
	sf::Sprite sprite;
	float lastjump;
	float lastframe;
	
	public:
	
	//une méthode pour afficher des textures
	
	Character(sf::Vector2f pos, sf::Vector2f size, const std::string& textName ){
			//std::cout<<"Personnage : "<<std::endl;
			//std::cout<<"hitbox théorique x : "<<size.x<< ",y : "<<size.y<<std::endl;
			texture=init_sprite(&(this->sprite), textName, pos, &size);
			sf::Vector2u tmp=texture->getSize();
			//la méthode que j'utilise pour avoir une bonne taille (cf init_sprite)\
			de sprite multiplie par des coefficient et cela créer des problèmes de hitbox\
			 que je doit régler de manière empirique
			hitbox.x=size.x;
			hitbox.y=size.y;
			//std::cout<<"hitbox partique x : "<<hitbox.x<< ",y : "<<hitbox.y<<std::endl;
			
			state=IDLE; //aucune action n'est réalisé sur le personnage 
			cpt_jump=0;
			lastjump=0.0;
			frame=0;
			lastframe=0.0;
		}
		
		
	Character(const Character& chara){
			*this=chara;
		}
	Character(){
		this->state=0;
		lastjump=0.0;
		}
		
	void setState(int newstate){
			if(newstate==JUMP){
				state=newstate;
				cpt_jump=CPTJUMP;
			}
			if(newstate==DEAD){
				state=newstate;
			}
			if (newstate==IDLE){
				state=IDLE;
			}
			
		}
		
	void move(float x, float y){
		sprite.move(x, y);
	}
	void move(sf::Vector2f pos){
		sprite.move(pos.x, pos.y);
	}
		
		
	sf::Vector2f getPosition(){
		return this->sprite.getPosition();
	}
		
	void jump(){

		move(0, (-1.2)*cpt_jump );
		cpt_jump--;
	}
		
		//si isinWall = 0 alors le joueur meurt
	sf::Vector2f updateCaracter(float time){
		//std::cout<<"isinWall : "<<isinWall<<", state : "<<this->state<<std::endl;
		if(state==1 || state==2){
			if(cpt_jump<=0){
				state=IDLE;
			}
			else{
				if(time-lastjump>0.02){
					this->jump();
					lastjump=time;
				}
			}
		}
		updateframe(time);
		return this->getPosition();
		
	}
	int getState(){
		return this->state;
	}
	int getcpt_jump(){
		return cpt_jump;
	}
	sf::Vector2f getHitbox(){
		return this->hitbox;
		}
	sf::Vector2f getSize(){
		return this->hitbox;
	}
		
	//méthode permettant de choisir le bon fichier pour pouvoir avoir des animations efficaces
	void updateframe(float time){
		//std::cout<<"état du joueur : "<<state<<std::endl;
		if(state==JUMP){
		//traitement des 8 annimations du saut
			if(time-lastframe>0.2){
				this->texture->loadFromFile("Hurdel_runner/sprites/spr_player/saut"\
				+std::to_string(frame)+".png");
				sprite.setTexture(*texture);
				lastframe=time;
			}
			frame=(frame+1)%8;
		}
		if(state==IDLE){
			//traitement des 7 annimations de course
			if(time-lastframe>0.3){
				this->texture->loadFromFile("Hurdel_runner/sprites/spr_player/course"\
				+std::to_string(frame)+".png");
				sprite.setTexture(*texture);
				lastframe=time;
			}
			frame=(frame+1)%7;
		}
		
	}

		
		
	void draw(sf::RenderWindow* window){
		
		sf::Vector2f tmp=sf::Vector2f(800.0, 400.0);
		if(this->state==DEAD){
			init_sprite(&(this->sprite), "ressource/images.jpeg", sf::Vector2f(0.0, 0.0), &tmp);
			window->draw(this->sprite);	
			//std::cout<<"debug";	
		}
		else{
			window->draw(this->sprite);
		}
	}
		
	Character& operator=(const Character& charabis){
		this->state=charabis.state;
		this->cpt_jump=charabis.cpt_jump; //pour faire des animations il faut l'état de la dite animation
		this->texture=charabis.texture;
		this->hitbox=charabis.hitbox;
		this->sprite=charabis.sprite;
		return *this;
	}
};
#endif














