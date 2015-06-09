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

	float xPosition = 960, yPosition = 540, xVelocity = 0, yVelocity = 0, bulletTrajectoryX, bulletTrajectoryY,bulletFireAngle;
	int i = 0, j = 0, currentBullets = 0, bulletNum = 0, fired = 0;

	float bulletStats[4][10000] = { 0 };//stores bullet position & velocity (make into a vector array to save space)
	float(*p_bulletStats)[4][10000] = &bulletStats;

	sf::RenderWindow window(sf::VideoMode(1920,1080), "Aseroids"/*, sf::Style::Fullscreen*/);//creates window

	sf::Clock clock;
	float time = 0.f;

	window.setFramerateLimit(60);//sets game to 60fps

	/*main game loop. (change "i > -1" condition to in game button so if it is pressed, the loop stops*/
	while (i > -1){

		/*Creates triangle, i.e. ship, and sets location at center of screen and sets colour*/
		sf::CircleShape triangle(20, 3);
		triangle.setPosition(xPosition, yPosition);
		triangle.setFillColor(sf::Color::Blue);

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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && time > 0.4){

			clock.restart();//restarts firing delay

			fired = 1;
			
			/*stores bullet spawn position*/
			bulletStats[0][currentBullets] = xPosition;
			bulletStats[1][currentBullets] = yPosition;

			Bullet bulletObject;

			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);//gets mouse position

			/*determines direction to fire bullet*/
			bulletTrajectoryX = mousePosition.x - xPosition;
			bulletTrajectoryY = mousePosition.y - yPosition;

			bulletFireAngle = atan(bulletTrajectoryY / bulletTrajectoryX);//determines angle in radians

			/*determines bullet velocity components*/
			bulletStats[2][currentBullets] = bulletObject.bulletXVel(bulletTrajectoryX, xVelocity, bulletFireAngle);
			bulletStats[3][currentBullets] = bulletObject.bulletYVel(bulletTrajectoryY, yVelocity, bulletFireAngle);
		}

		/*Draws ship*/
		window.clear();
		window.draw(triangle);
		

		/*Draws bullets*/
		for (bulletNum = 0; bulletNum <= currentBullets; bulletNum++){

			sf::CircleShape bullet(3);
			bullet.setPosition(bulletStats[0][bulletNum], bulletStats[1][bulletNum]);//change spawn point to end of barel on ship instead of ship center
			bullet.setFillColor(sf::Color::Yellow);
			window.draw(bullet);//draws bullet
		}

		window.display();

		/*Updates bullet position*/
		for (bulletNum = 0; bulletNum <= currentBullets; bulletNum++){

			bulletStats[0][bulletNum] = bulletStats[0][bulletNum] + bulletStats[2][bulletNum];//sets bullet x position to previous position + bullet x velocity
			bulletStats[1][bulletNum] = bulletStats[1][bulletNum] + bulletStats[3][bulletNum];//sets bullet y position to previous position + bullet y velocity
			
			/*kills bullet if it exits screen & shifts array up to reuse elements*/
			if (killBullet(bulletStats, bulletNum, currentBullets) == 1){

				cout << bulletNum << " " << currentBullets << endl;

				//for (int m = 0; m < bulletNum; m++){
					//bulletStats[m][bulletNum] = bulletStats[m][bulletNum + 1];
					//bulletStats[m][bulletNum + 1] = 0;

					//&& (bulletNum + 1) <= currentBullets
				//}
			}
		}

		if (fired == 1){
			currentBullets++;
		}
	}
}