//Name: Matthew Bedard	
#include "nbody.h"


CelestialBody::CelestialBody(double x, double y, double xVelo, double yVelo, double massiveness, string fileName, double uRadius, int sizeWindow){
	xCoord = x;
	yCoord = y;
	xVelocity = xVelo;
	yVelocity = yVelo;
	mass = massiveness;
	celestialTexture.loadFromFile(fileName);
	celestialSprite.setTexture(celestialTexture);
	universeRadius= uRadius;
	windowSize = sizeWindow;
}


void Universe::step(double timeStep){
	double netForce;
	double netForceX;
	double netForceY;
	double deltaX;
	double deltaY;
	double distance;
	double accelX;
	double accelY;
	double newVeloX;
	double newVeloY;

	for(vector<CelestialBody*>::iterator i = vectorOfBodies.begin(); i != vectorOfBodies.end(); i++){
		netForce = 0;
		netForceX = 0;
		netForceY = 0;		
				 
		for(vector<CelestialBody*>::iterator j = vectorOfBodies.begin(); j != vectorOfBodies.end(); j++){
			if((*j) == (*i)){
				continue;
			}
			deltaX = ((*j)->getXCoord()) - ((*i)->getXCoord()); 
			deltaY = ((*j)->getYCoord()) - ((*i)->getYCoord());
			distance = sqrt((deltaX * deltaX) + (deltaY * deltaY));
			netForce = (6.67e-11 * ((*i)->getMass()) * ((*j)->getMass())) / (distance * distance);
			netForceX += (netForce * (deltaX / distance));
			netForceY += (netForce * (deltaY / distance));
		}
		
		accelX = netForceX / (*i)->getMass();
		accelY = netForceY / (*i)->getMass();
		newVeloX = (*i)->getXVelo() + (accelX * timeStep);
		newVeloY = (*i)->getYVelo() + (accelY * timeStep);
		(*i)->setVelos(newVeloX, newVeloY);
		(*i)->setCoords(((*i)->getXCoord() + (timeStep * newVeloX)), ((*i)->getYCoord() + (timeStep * newVeloY)));	
		(*i)->setSprite();
	}




}

void Universe::outputState(void){
	cout << setprecision(4) << left << scientific;
	for(vector<CelestialBody*>::iterator i = vectorOfBodies.begin(); i != vectorOfBodies.end(); i++){
		cout.width(12); cout << (*i)->getXCoord();
	        cout.width(12); cout << (*i)->getYCoord(); 
		cout.width(12); cout << (*i)->getXVelo(); 
		cout.width(12); cout << (*i)->getYVelo();
	        cout.width(12); cout << (*i)->getMass(); 
		cout.width(12); cout << (*i)->getText() << endl;
	}

}
