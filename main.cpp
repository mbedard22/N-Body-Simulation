#include "nbody.h"

int main(int argc, char * argv[]){
	int numBodies;
	double radius;
	double timeLimit = atof(argv[1]);
	double timeChange = atof(argv[2]);
	double timeCheck = 0;
	cin >> numBodies;
	cin >> radius;
	int windowSize = 1000;
	Universe myUniverse;
	
	for(int i = 0; i < numBodies; i++){
		CelestialBody* temp = new CelestialBody;
		cin >> *temp;
		temp->setRadius(radius);
		temp->setWindowSize(windowSize);
		temp->setSprite();
		myUniverse.pushToVector(temp);
	}

	sf:: RenderWindow window1(sf::VideoMode(windowSize,windowSize), "Universe");
	
	while(window1.isOpen()){
		sf::Event event;
		while(window1.pollEvent(event)){
			if(event.type == sf::Event::Closed)
				window1.close();
		}
		window1.clear();
		myUniverse.step(timeChange);
		for(int j = 0; j < numBodies; j++){ 
			window1.draw(*(myUniverse.getBody(j)));
		}
		window1.display();
		timeCheck += timeChange;
		if(timeCheck >= timeLimit)
			window1.close();
		
	}
	cout << numBodies << endl;
	cout << radius << endl;
	myUniverse.outputState();
	return 0;
}
