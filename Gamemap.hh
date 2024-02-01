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
	
	//constructeur par défaut
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
	//permet d'ajouter un joueur
	void addPlayer(Character chara){
		//std::cout<<"addPlayer"<<std::endl;
		player= Character(chara);
	}
	
	//ajoute une scene au vecteur de scene
	void addScene(Scene scene){
		//std::cout<<"addScene()"<<std::endl;
		
		vect_scene.push_back(Scene(scene));
		//std::cout<<"addScene()"<<std::endl;
		
	}
	
	//prend en paramètre la position du joueur et renvoie -1 si le joueur est dans un mur tueur, 1 si il est dans un mur classique et 0 si il est libre de bouger
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
	
	//fonction pour tuer le joueur en écrivant "vous êtes morts" à l'écran 
	int killplayer(){
		
		player.setState(DEAD);
		timeText.setCharacterSize(36);
    		timeText.setFillColor(sf::Color::Black);
		timeText.setString("Vous etes morts");
		
		return -1;
	}

	
	//renvoie 1 si nous sommes au sol et 0 sinon
	int isOnGround(){
		std::cout<<move_player(0,0)<<std::endl;
		return move_player(0, 1);
	}
	
	//accède à l'état du joueur pour qu'il soit en mode Jump et saute de lui même à chaque actualisation
	void jump(){
		//saut avec espace, on met l'état du joueur à "JUMP"
		switch(player.getState()){
			case(0):
			player.setState(1);
			break;
			case(1):
			player.setState(2);
			break;
			
		};
	}

	//fonction pour dessiner les sprites de tout les objets contenues dans la classe Gamemap
	void draw(sf::RenderWindow* window){
		//std::cout<<"number of element in the scene vector: "<<vect_scene.size()<<std::endl;
		vect_scene[0].draw(window);
		player.draw(window);
		window->draw(timeText);
		
	}
	
	//permet de remettre
	void Gravity(float time){
			//permet de limiter le temps de telle sorte que la gravité ne dépenent pas du nombre de tour de boucle/secondes et quelle ne s'éxecute pas si le joueur est au sol
			if(isOnGround() && time>gravtime){
				move_player( 0, 5);
				gravtime=time+0.05;
				}
	}
	//fonction pour recommencer une partie

	int getPlayersState(){
		return player.getState();
	}
	
	void wait(){	
		float tmp=time.asSeconds()+3.0;
		while(time.asSeconds()<tmp){
			time=clock.getElapsedTime();
		}
	}
	//met à jour tout les sprites ainsi que l'état du joueur renvoie 0 si tout se passe bien et 1 si on doit attendre pour afficher quelquechose
	void update(sf::RenderWindow *window){
		
		timeText.setString("Score : " + std::to_string(10*static_cast<int>(time.asSeconds())) );
		//mettre à jour le personnage
		time= clock.getElapsedTime();
		//tmp est un bool qui vaut 1 si le joueur est dans un mur
		vect_scene[idcurrtscene].update(time.asSeconds());	//pour mettre à jour les murs tueurs
		
		//si dans un mur tueur : met état mort
		int tmpbool=this->checkInWall(player.getPosition(), player.getSize());
		if(tmpbool<0){killplayer();}
		time= clock.getElapsedTime();
		player.updateCaracter(time.asSeconds());
		time= clock.getElapsedTime();
		this->Gravity(time.asSeconds());
		
		//mise à jour des textures:
		this->draw(window);
		window->display();
		if(tmpbool<0){
			this->wait();
			window->close();
		}
	}
};


#endif

