#ifndef NBODY_H
#define NBODY_H
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace std;

class CelestialBody : public sf::Drawable
{
	public:
	CelestialBody() = default;
	
	CelestialBody(double x, double y, double xVelo, double yVelo, double massiveness, string fileName, double uRadius, int sizeWindow);
	
	void setRadius(double r){
		universeRadius = r;
	}
	
	void setWindowSize(int sizeWindow){
		windowSize = sizeWindow;
	}

	void setCoords(double x, double y){
		xCoord = x;
		yCoord = y;
	}
	
	void setVelos(double x, double y){
		xVelocity = x;
		yVelocity = y;
	}

	void setSprite(void){
		celestialSprite.setPosition(((xCoord/universeRadius) * (windowSize/2)) + windowSize/2, -((yCoord/universeRadius) * (windowSize/2)) + windowSize/2);
	}

	double getXCoord(void){
		return xCoord;
	}

	double getYCoord(void){
		return yCoord;
	}

	double getXVelo(void){
		return xVelocity;
	}
	
	double getYVelo(void){
		return yVelocity;
	}
	
	double getMass(void){
		return mass;
	}

	string getText(void){
		return fileName;
	}
	private:
	double xCoord;
	double yCoord;
	double xVelocity;
	double yVelocity;
	double mass;
	int windowSize;
	string fileName;
	sf::Texture celestialTexture;
	sf::Sprite celestialSprite;
	double universeRadius;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
		target.draw(celestialSprite, states);
	}

	friend istream &operator>>(istream &input, CelestialBody &cb){
		string temp;
		input >> cb.xCoord >> cb.yCoord >> cb.xVelocity >> cb.yVelocity >> cb.mass >> temp;
		cb.fileName = temp;
		cb.celestialTexture.loadFromFile(temp);
		cb.celestialSprite.setTexture(cb.celestialTexture);
		return input;
	}
};

class Universe
{
	public:
	Universe() = default;
	~Universe(){
		for(vector<CelestialBody*>::iterator i = vectorOfBodies.begin(); i != vectorOfBodies.end(); ++i)
			delete *i;
	}
	void pushToVector(CelestialBody* temp){
		vectorOfBodies.push_back(temp);
	}
	CelestialBody* getBody(int iter){
	       return vectorOfBodies.at(iter);
	}

	void step(double timeStep);
	void outputState(void);
	private:
	double radius;
	vector<CelestialBody*> vectorOfBodies;
};
#endif
