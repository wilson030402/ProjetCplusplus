


#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <random>


#ifndef FUNCTION_HPP
#define FUNCTION_HPP

//method getSize to know the size of a texture

sf::Vector2f getSize(sf::Vector2f vect_left, sf::Vector2f vect_right){
	return sf::Vector2f(vect_right.x-vect_left.x, vect_right.y-vect_left.y);
}

//fonction pour initialiser les spritesà la bonne taille
sf::Texture* init_sprite(sf::Sprite* sprite, const std::string textName, sf::Vector2f pos, sf::Vector2f *size ){
	sf::Texture *text= new sf::Texture;
	//text->create(static_cast<int>(size.x),static_cast<int>(size.y) );
	text->loadFromFile(textName);
	sf::Vector2u tmp=text->getSize();
	sf::Vector2f ratio;
	
	sprite->setPosition(pos);
	sprite->setTexture(*text);
	(ratio.x=size->x/static_cast<float>(tmp.x) );
	(ratio.y=size->y/static_cast<float>(tmp.y) );
	//std::cout<<"taille horizontale : "<< ratio.x<<"taille verticale : "<<ratio.y<<std::endl;
	sprite->scale(sf::Vector2f(ratio.x, ratio.y));
	
	//size->x *=ratio.x;
	//size->y *=ratio.y;
	return text; //permet de libérer la mémoire allouée pour la texture
}



//génère un nombre aléatoire entre a et b
float Randomfloat(float a, float b){
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<float> distribution(a, b);
	return distribution(generator);
}


#endif


