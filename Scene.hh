//Scene.hh

//Classe qui contient le sprite de fond ainsi que les Hits Box des murs
#include <SFML/Graphics.hpp>
#include "function.hh"
#include "Wall.hh"
#include "KillingWall.hh"
#include <list>

#define DEBUG_ENABLED 1 //1 to show the wall on screen 0 otherwise

#ifndef SCENE_HPP
#define SCENE_HPP


class Scene{
	private:
	sf::Texture* texture;
	//on risque d'ajouter beaucoup de murs, voila pourquoi la structure les contenant est une liste
	std::list<Wall*> list_wall;
	sf::Sprite sprite;
	float lastcall;
	float lastcreate;
	public:
	
	Scene(sf::Vector2f pos, sf::Vector2f size, const std::string textName ){
		texture=init_sprite(&sprite, textName, pos, &size);
		sf::Vector2u tmp=texture->getSize();
		lastcall=0.0;
		lastcreate=0.0;
	}
	
	
	int nbWall=0;
	
	//return 1 if the position is in a wall and 0 otherwise
	int checkInWall(const sf::Vector2f& playerpos, const sf::Vector2f& playersize){
	
		int i=0; //debug
		for(const auto& obj :list_wall){
			//std::cout <<obj->getTopLeft().y<<std::endl;
			if(obj->checkInWall(playerpos, playersize)==-1){return -1;}
			
			
			if(obj->checkInWall(playerpos, playersize)==1){return 1;}
			i++; //debug
		}
		return 0;
	}
	
	
	void draw(sf::RenderWindow* window){
		window->draw(this->sprite);
		for(auto& obj :list_wall){
			window->draw( (obj->pxgetSprite()) );
			//std::cout<<"scene->draw()\n";
		}
	}
	void addWall(const KillingWall& wall){
		list_wall.push_back(new KillingWall(wall));
	}
	
	void addWall(const Wall& wall){
		list_wall.push_back(new Wall(wall));
	}
	
	
	sf::Sprite* pxgetSprite(){
		return &(this->sprite);
	}
	//méthode qui permet de mettre à jour l'état, la taille des murs tueurs ainsi que l'état du joueur 
	int update( float time){
	
	
		//génération des murs 1 mur peut être généré toutes les 0.4 ms
		if(time-lastcreate>1.0 && (list_wall.size()<(time/10)) ){
			this->generateKillerWall();
			lastcreate=time;
		}
		//déplacement des murs
		if(time-lastcall>0.01){
			    for (auto it = list_wall.begin(); it != list_wall.end();) {
				(*it)->move_left(3);
				
				if ((*it)->getPosX()< 0.0f) {
					
					//std::cout<< "nombre de murs : "<< list_wall.size()<<std::endl;
				    delete *it; // Libérer la mémoire de l'objet
				    it = list_wall.erase(it); // Supprimer l'élément de la liste et obtenir l'itérateur suivant	
				    //std::cout<< "après suppression : "<< list_wall.size()<<std::endl;
				} else {
				    ++it;
				}
			    }
			lastcall=time;
		}
		//tout les murs dont la position est hors champ doivent être détruits
		
		return 1;
	}
	
	
	//-----------//!\\ En travaux //!\\----------------
	//méthode dont le but est de génerer un mur tueur à une position aléatoire
	void generateKillerWall(){
		//std::cout<<"un mmur est générée";
		//la position est générée hors champ côté droit
		float pos=Randomfloat( 800.0, 1600.0);
		//std::cout<<", position : "<<pos<<std::endl;
		KillingWall killer(sf::Vector2f(pos, 250.0), sf::Vector2f(pos-40.0, 330.0),\
		 "Hurdel_runner/sprites/spr_hurdel/hurdel.png");
		killer.setState(1);
		//ajout de ce dernier
		addWall(killer);
	}
	//-----------//!\\ En travaux //!\\----------------
	
	
};



#endif

