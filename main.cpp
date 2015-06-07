#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include "Asteroids.h"

/*       NOTES
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
/* 
/*																																						*/

using namespace std;

int main(){

	float i = 0, xPosition = 960, yPosition = 540, xVelocity = 0, yVelocity = 0, bulletTrajectoryX, bulletTrajectoryY, created = 0, 
		bulletX = xPosition, bulletY = yPosition, bulletXVel = xVelocity, bulletYVel = yVelocity, fired = 1;

	sf::RenderWindow window(sf::VideoMode(1920,1080), "Aseroids"/*, sf::Style::Fullscreen*/);//creates window

	sf::Clock clock;
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

			/*Gun, if right mouse btn pressed, bullet spawns and this loops until bullet leaves screen (make into function)*/
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || created == 1){

				/*Creates bullet*/
				sf::CircleShape bullet(5);
				bullet.setPosition(bulletX, bulletY);//change spawn point to end of barel on ship instead of ship center
				bullet.setFillColor(sf::Color::Red);
				
				/*draws ship and bullet (add multiple bullet firing capabilities with slight delay*/
				window.clear();
				window.draw(triangle);//draws ship
				window.draw(bullet);//draws bullet
				window.display();

				/*gets bullet trajectory*/
				if (fired = 1){
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);//gets mouse position

					/*determines direction vector*/
					bulletTrajectoryX = mousePosition.x - xPosition;
					bulletTrajectoryY = mousePosition.y - yPosition;

					fired = 0;//
				}

				/*sets bullet x velocity to ship velocity + component of trajectory velocity, (make function)*/
				bulletXVel = bulletXVel + .1f * bulletTrajectoryX / (bulletTrajectoryX + bulletTrajectoryY);				
				if (bulletXVel > 1){
					bulletXVel = 1;
				}

				if (bulletXVel < -1){
					bulletXVel = -1;
				}

				/*sets bullet y velocity to ship velocity + component of trajectory velocity(make function)*/
				bulletYVel = bulletYVel + .1f * bulletTrajectoryY / (bulletTrajectoryX + bulletTrajectoryY);
				if (bulletYVel > 1){
					bulletYVel = 1;
				}

				if (bulletYVel < -1){
					bulletYVel = -1;
				}

				/*updates bulet position*/
				bulletX = bulletX + bulletXVel;
				bulletY = bulletY + bulletYVel;

				//gun(xPosition, yPosition, &window);//fires gun by mouse click in direction pointed(***switch to space btn. fire when we can rotate ship image****)

				created = 1;

				/*kills bullet if it exits screen and resets for next firing*/
				if (bulletX > 1920 || bulletX < 0 || bulletY > 1080 || bulletY < 0){
					created = 0;
					bulletX = xPosition;
					bulletY = yPosition;
					bulletXVel = xVelocity;
					bulletYVel = yVelocity;
					fired = 1;
				}
			}

			/*if no bullet exists, just draws ship*/
			else{
				window.clear();
				window.draw(triangle);
				window.display();
			}

			/*outputs framerate*/
			sf::Time time = clock.getElapsedTime();
			cout << 1.0f / time.asSeconds() << endl;
			clock.restart().asSeconds();
		}
}