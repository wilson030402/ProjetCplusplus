#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Character.hpp"
#include "Scene.hh"
#include "Gamemap.hh"
#include "Ground.hh"


 
#define NORAMP 0
#define RAMP 1
/*
g++ main.cpp -lsfml-graphics -lsfml-window -lsfml-system
*/

//Rappel:
//----->+X
// |
// V
//+Y



int main(){
	//---------------initialisation------------------
	sf::RenderWindow window(sf::VideoMode(800, 400), "Ma Fenêtre SFML");
	//std::cout<< "1er mur : "<<std::endl;
	Ground wallbis(310.0);
	
	//std::cout<< "1ere scene mur : "<<std::endl;
	Scene scene(sf::Vector2f(0.0, 0.0), sf::Vector2f(800.0, 400.0), "Hurdel_runner/sprites/spr_background/back.png");
	scene.addWall(wallbis);
	//std::cout<<"1\n";
	//std::cout<< "1er joueur : "<<std::endl;
	Character chara(sf::Vector2f(10.f, 10.f), sf::Vector2f(110.f, 150.f), \
	"Hurdel_runner/sprites/spr_player/saut0.png");
	
	Gamemap map;
	map.addPlayer(chara);
	chara.setState(0);
	map.addScene(scene);
	//std::cout<<"cpt_jump : "<<chara.getcpt_jump()<<",state : "<<chara.getstate()<<std::endl;
		
	
	//---------------initialisation------------------
	//gameloop
	while(window.isOpen()){
		sf::Event event;
//---------------Event handler-------------------------------		
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed){
				window.close();
			}
			
			//déplacement / intéractions
			if(event.type == sf::Event::KeyPressed){
				//std::cout<<event.key.code<<std::endl;
				switch(event.key.code){				
					//<-
					case(71/*sf::Keyboard::Left*/):
					map.move_player(-5.0f, 0.f);
					break;
					//->
					case(sf::Keyboard::Right):
					//std::cout<<"debudesespoir1\n";
					map.move_player(5.0f, 0.f);
					break;
					// A
					// |
					case(73/*sf::Keyboard::Up*/):
					map.move_player(0.0f, -5.0f);
					break;
					// |
					// V
					case(sf::Keyboard::Down):
					map.move_player(0.0f, 5.0f);
					break;
					case(sf::Keyboard::Space):
						
						if(!map.isOnGround() || map.getPlayersState()==1){
							map.jump();
						}
					break;
					
				}
				//std::cout<<"player.size x="<<chara.getSize().x<<", y="<<chara.getSize().y<<std::endl;
				//std::cout<<"player.position x="<<chara.getPosition().x<<", x="<< chara.getPosition().y<<std::endl;
			}
		}
//---------------Event handler-------------------------------
//-------------DRAWING--------------------------------------
		window.clear(sf::Color::Black);				
		//Draw function
		map.update(&window);
		
//-------------DRAWING--------------------------------------
	}
	return 1;
}
