#include <stdio.h>

#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP


//Classe Interface pour les classes Scene, Character et Wall
class Drawable{
	protected:
	virtual void draw(sf::RenderWindow* window)=0;

};

#endif


