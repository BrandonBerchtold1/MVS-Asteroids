#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "Asteroids.h"
#include "Parameters.h"

/*       NOTES
/* 
/* **********SETTINGS:   Auto    Release    x64  ************
/*
/* Add gravity to objects
/* Add asteroids and planets on new screens
/* Allow travel between screens so new objects exist in new screens(or change so ship stays in center and objects come and go, i perfer this)
/* implement classes and fix format
/* make gun function
/* add background that either moves or changes when ship moves between screens in game(i.e. ship exits screen on right with background A 
/*			and enters screen on left with slightly different background B with new objects in this screen, or ship is stationary and 
/*          background and objects move around it, i.e. player centric gmae play
/* upgrades change acceleration (make parameters file that holds acceleration, mass, fuel, spawn rate, etc...
/* lives/hitboxes
/* music, i.e. fired bullet, hit target, win, die, menu, upgrade, etc...
/* GUI, i.e. menu, difficulty, instructions, leader board, settings, etc...
/* fix velocity, i.e. calibrate as i had it calibrated or 1500 fps and we are at 60 noe :p
/* rotate ship in travel direction
/* texture ship, asteroids, and other objects
/* change bullets to rectangles pointing in travel direction, possibly add particle effects, add ability to fire multiple bullets, change spawn point
/*			to end of barrel or tip of ship instead of center of ship
/* does screen resolution affect stuff? if so change all values to multiples of screen dimensions.
/* triangle drift problem? it kind of drifts for no reason...

/*       ****outputs framerate*****
         sf::Time time = clock.getElapsedTime();
         cout << 1.0f / time.asSeconds() << endl;
         clock.restart().asSeconds();
/*
/* point in firing direction
/* erase killed bullet array value so ram dun't get used up
/*																																						*/

using namespace std;

int main(){

	float xPosition = 960, yPosition = 540, xVelocity = 0, yVelocity = 0, bulletTrajectoryX, bulletTrajectoryY, bulletFireAngle;
	int i = 0, j = 0, currentBullets = 0, bulletNum = 0, bulletColumnNum;

	float bulletStats[4][100] = { 0 };//stores bullet position & velocity (make into a vector array to save space)
	//vector<float> bulletInfo(4);

	sf::RenderWindow window(sf::VideoMode(1920,1080), "Aseroids"/*, sf::Style::Fullscreen*/);//creates window

	/*Anti Aliasing*/
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	/*clock for firing delay and frame rate limit*/
	sf::Clock clock;
	float time = 0.f;

	window.setFramerateLimit(60);//sets game to 60fps

	/*bullet*/
	sf::Texture texture;
	if (!texture.loadFromFile("zoidberg.png")){ //sphere
	}

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(0, 0));
	sprite.setScale(sf::Vector2f(0.06f, 0.06f));

	/*background*/
	sf::Texture texture1;
	if (!texture1.loadFromFile("Space.jpg")){
	}

	sf::Sprite sprite1;
	sprite1.setTexture(texture1);
	sprite1.setPosition(sf::Vector2f(0, 0));
	sprite1.setScale(sf::Vector2f(1.0f, 1.0f));

	/*ship*/
	sf::Texture ShipTex;
	if (!ShipTex.loadFromFile("Ship.png")){
	}

	sf::Sprite Ship;
	Ship.setTexture(ShipTex);
	Ship.setPosition(sf::Vector2f(0, 0));
	Ship.setScale(sf::Vector2f(0.3f, 0.3f));

	/*main game loop. (change "i > -1" condition to in game button so if it is pressed, the loop stops*/
	while (i > -1){

		Ship.setPosition(xPosition, yPosition);

		/*Creates triangle, i.e. ship, and sets location at center of screen and sets colour*/
		//sf::CircleShape triangle(20, 3);
		//triangle.setPosition(xPosition, yPosition);
		//triangle.setFillColor(sf::Color::Blue);

		/*closes window but replace with close window function, fix it first though
		closeWindow(&window);//closes window if "esc" or "x" window button in top right of window are pressed*/
		sf::Event event;
		while (window.pollEvent(event)){

			if (event.type == sf::Event::Closed){
				window.close();
			}

			if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Escape){
					window.close();
				}
			}
		}

		keyboardInput(&xVelocity, &yVelocity);//arrow keys change ship acceleration

		updatePositions(&xPosition, &yPosition, &xVelocity, &yVelocity);//ship position updated

		screenLoop(&xPosition, &yPosition);//if ship falls off screen, it gets looped back on screen (make it so it enters a new environment, not just the same one it left. add plaets with gavity)

		stopDrift(&xVelocity, &yVelocity);//stops spaceship from drifting too far, even though this is unrealistic!! >:(

		time = clock.getElapsedTime().asSeconds();

		/*creates max 1 bullet/sec and stores its parameters to bulletStats array*/
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && time > 0.04){

			clock.restart();//restarts firing delay

			currentBullets++;
			
			/*stores bullet spawn position*/
			bulletStats[0][currentBullets - 1] = xPosition;
			bulletStats[1][currentBullets - 1] = yPosition;

			Bullet bulletObject;

			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);//gets mouse position

			/*determines direction to fire bullet*/
			bulletTrajectoryX = mousePosition.x - xPosition;
			bulletTrajectoryY = mousePosition.y - yPosition;

			bulletFireAngle = atan(bulletTrajectoryY / bulletTrajectoryX);//determines angle in radians

			/*determines bullet velocity components*/
			bulletStats[2][currentBullets - 1] = bulletObject.bulletXVel(bulletTrajectoryX, xVelocity, bulletFireAngle);
			bulletStats[3][currentBullets - 1] = bulletObject.bulletYVel(bulletTrajectoryY, yVelocity, bulletFireAngle);
		}

		/*Draws ship*/
		window.clear();
		window.draw(sprite1);//draws background
		window.draw(Ship);
		//window.draw(triangle);
		
		

		/*Draws bullets*/
		for (bulletNum = 1; bulletNum <= currentBullets; bulletNum++){

			sprite.setPosition(bulletStats[0][bulletNum - 1], bulletStats[1][bulletNum - 1]);//change spawn point to end of barel on ship instead of ship center
			//sprite.setColor(sf::Color::Blue);
			window.draw(sprite);//draws bullet
			
		}

		window.display();

		/*Updates bullet position*/
		for (bulletNum = 1; bulletNum <= currentBullets; bulletNum++){

			bulletStats[0][bulletNum - 1] = bulletStats[0][bulletNum - 1] + bulletStats[2][bulletNum - 1];//sets bullet x position to previous position + bullet x velocity
			bulletStats[1][bulletNum - 1] = bulletStats[1][bulletNum - 1] + bulletStats[3][bulletNum - 1];//sets bullet y position to previous position + bullet y velocity
			
			/*kills bullet if it exits screen & shifts array up to reuse elements*/
			if (killBullet(bulletStats, bulletNum) == 1){

				cout << "1a(" << bulletStats[0][0] << ", " << bulletStats[1][0] << ")" << currentBullets << endl;
				cout << "2a(" << bulletStats[0][1] << ", " << bulletStats[1][1] << ")" << currentBullets << endl;
				cout << "3a(" << bulletStats[0][2] << ", " << bulletStats[1][2] << ")" << currentBullets << endl;
				cout << "4a(" << bulletStats[0][3] << ", " << bulletStats[1][3] << ")" << currentBullets << endl;











				/*shifts bullet values up one, replacing killed bullet*/
				while (bulletNum < currentBullets){

					cout << "A" << bulletStats[0][bulletNum - 1] << bulletStats[1][bulletNum - 1] << bulletStats[2][bulletNum - 1] << bulletStats[3][bulletNum - 1] << endl;
					for (bulletColumnNum = 0; bulletColumnNum < 4; bulletColumnNum++){
						bulletStats[bulletColumnNum][bulletNum - 1] = bulletStats[bulletColumnNum][bulletNum];	
					}

					//cout << "A" << bulletStats[0][bulletNum - 1] << bulletStats[1][bulletNum - 1] << bulletStats[2][bulletNum - 1] << bulletStats[3][bulletNum - 1] << endl;
					bulletNum++;
				}

				/*clears last bullet in array completing bullet shift*/
				for (bulletColumnNum = 0; bulletColumnNum < 4; bulletColumnNum++){
					bulletStats[bulletColumnNum][bulletNum - 1] = 0;
				}















				
				currentBullets--;//prevents blank bullets from spawning
				
				cout << "1b(" << bulletStats[0][0] << ", " << bulletStats[1][0] << ")" << currentBullets << endl;
				cout << "2b(" << bulletStats[0][1] << ", " << bulletStats[1][1] << ")" << currentBullets << endl;
				cout << "3b(" << bulletStats[0][2] << ", " << bulletStats[1][2] << ")" << currentBullets << endl;
				cout << "4b(" << bulletStats[0][3] << ", " << bulletStats[1][3] << ")" << currentBullets << endl;

			}
		}
	}
}