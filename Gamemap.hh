#include "function.hh"
#include "Character.hpp"
#include "Scene.hh"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>


#ifndef GAMEMAP_HH
#define GAMEMAP_HH

#define DEAD -1

//simplement une collection d'entités et de scene
class Gamemap{
	private:
	int idcurrtscene; //number in th array ssociated with the scene where the player is
	//first scene
	Character player;
	std::vector<Scene> vect_scene;
	//variable permettant de savoir la vitesse de chute actuelle
	float gravtime;
	sf::Clock clock;
	sf::Time time;
	sf::Text timeText;
	sf::Font font;
	public:
	
	Gamemap(){
		idcurrtscene=0;
		time=clock.restart();
		std::cout<<"accès à Gamemap()"<<std::endl;
		gravtime=0.0;
		
		font.loadFromFile("Arial.ttf");
    		timeText.setFont(font);
    		timeText.setCharacterSize(24);
    		timeText.setFillColor(sf::Color::Black);
		timeText.setPosition(230.0f, 10.0f);

		}
		
		void addPlayer(Character chara){
			//std::cout<<"addPlayer"<<std::endl;
			player= Character(chara);
		}
		void addScene(Scene scene){
			//std::cout<<"addScene()"<<std::endl;
			
			vect_scene.push_back(Scene(scene));
			//std::cout<<"addScene()"<<std::endl;
			
		}
		
	int checkInWall(const sf::Vector2f& pos, const sf::Vector2f& size ){
		//si la position du joueur est dans un mur de la scene actuelle : renvoie 0
		int tmp=vect_scene[idcurrtscene].checkInWall(pos, size);
		if(tmp==1){
			return 1;
			}
		if(tmp==-1){
			return -1;
		}
		return 0;
	}
	//0 if the player can't move and 1 otherwise
	int move_player(float mouvx, float mouvy){
		sf::Vector2f tmp=player.getPosition();
		tmp.x=tmp.x+mouvx;
		tmp.y=tmp.y+mouvy;
		sf::Vector2f tmpsize= player.getSize();
		//std::cout<<"taille du joueur x : "<<player.getSize().x <<" y : "<<player.getSize().y <<std::endl;//debug
		//verifie tout les murs de la scene actuelle
		if(checkInWall(tmp, tmpsize)==1){
			return 0;
			}
		else{
			player.move(mouvx, mouvy);
			return 1;
		}
	}
	int killplayer(std::string debugstring){
		//std::cout<<"killplayer() : "<<debugstring<<std::endl;
		
		player.setState(DEAD);
		timeText.setCharacterSize(36);
    		timeText.setFillColor(sf::Color::Black);
		timeText.setPosition(400.0f, 200.0f);
		timeText.setString("Vous êtes morts");
			
		restart();
		return -1;
	}

	
	//renvoie 1 si nous sommes au sol et 0 sinon
	int isOnGround(){
		std::cout<<move_player(0,0)<<std::endl;
		return move_player(0, 1);
	}
	void jump(){
		//saut avec espace, on met l'état du joueur à "JUMP"
		player.setState(1);
	}

	void draw(sf::RenderWindow* window){
		//std::cout<<"number of element in the scene vector: "<<vect_scene.size()<<std::endl;
		vect_scene[0].draw(window);
		player.draw(window);
		window->draw(timeText);
		
	}
	
	
	void Gravity(float time){
			//permet de limiter le temps de telle sorte que la gravité ne dépenent pas du nombre de tour de boucle/secondes
			if(isOnGround() && time>gravtime){
				move_player( 0, 5);
				gravtime=time+0.05;
				}
	}
	
	//gestion de la mort pour l'instant la fonction restart me fais crash
	void restart(){
		float tmp=time.asSeconds()+3.0;
		while(time.asSeconds()<tmp);
		time=clock.restart();
		player.setState(0);
		timeText.setCharacterSize(24);
    		timeText.setFillColor(sf::Color::Black);
		timeText.setPosition(230.0f, 10.0f);
	}
	void update(){
		//mettre à jour le personnage
		time= clock.getElapsedTime();
		//tmp est un bool qui vaut 1 si le joueur est dans un mur
		vect_scene[idcurrtscene].update(time.asSeconds());	//pour mettre à jour les murs tueurs
		//std::cout<< "temps en secondes"<<time.asSeconds()<<std::endl;
		sf::Vector2f tmppos=player.getPosition();
		sf::Vector2f tmpsize=player.getSize();
		
		//si dans un mur tueur : met état mort
		//sinon laisse vivre
		int tmpbool=this->checkInWall(tmppos, tmpsize);
		//if(tmpbool<0){restart();}
		time= clock.getElapsedTime();
		player.updateCaracter(time.asSeconds());
		time= clock.getElapsedTime();
		this->Gravity(time.asSeconds());
		//mettre à jour le décor
		
		timeText.setString("Score : " + std::to_string(10*static_cast<int>(time.asSeconds())) );
		
		
	}
};


#endif

