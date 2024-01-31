#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Character.hh" //4eme test
#include "Scene.hh" // 1er test : Wall, 2nd test Scene
#include "Gamemap.hh" //3eme test
#include <list>

//code permettant le debug d'éléments précis, au seins d'une ou plusieurs classes
int main(){
	//---------------initialisation------------------
	sf::RenderWindow window(sf::VideoMode(800, 400), "test individuel de classe");
	//KillingWall wall(sf::Vector2f(10.0, 250.0), sf::Vector2f(300.0, 300.0), "ressource/herbe.jpeg" );
	//wall.setState(1);
	Wall wallbis(sf::Vector2f(200.0, 300.0), sf::Vector2f(400.0, 400.0), "ressource/herbe.jpeg" );
	Scene scene(sf::Vector2f(0.0, 0.0), sf::Vector2f(800.0, 400.0), "ressource/background_zelda.jpeg");
	//scene.addWall(wall);
	scene.addWall(wallbis);
	
	
	Character chara(sf::Vector2f(260.f, 10.f), sf::Vector2f(120.f, 180.f), "ressource/chara.png");
	
	Gamemap map;
	map.addPlayer(chara);
	map.addScene(scene);
	
	//---------------initialisation------------------
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed){
				window.close();
				}
			}
		map.test();
		window.clear(sf::Color::Black);
		map.update();
		map.draw(&window);
		map.Gravity(2.33);
		window.display();		
		}
	return 1;
}





