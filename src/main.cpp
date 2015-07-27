//    ************************************************************
//    *                Double Pendulum Simulation                *
//    *                         June 2015                        *
//    ************************************************************
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../include/Pendulum.hh"
#include "../include/Tracer.hh"

#include <iostream>


const float gDisplayx = 800;
const float gDisplayy = 800;
int main() {
  //GAME SETUP
  sf::RenderWindow window(sf::VideoMode(gDisplayx,gDisplayy), "Double Pendulum Simulation");
  window.setFramerateLimit(60);

  // Initializing
  Pendulum pendulum( window.getSize().x, window.getSize().y );
  Tracer tracer( window.getSize().x, window.getSize().y );

  // Handling Time
  float t = 0.0;
  float dt = 1.0/60.0;
  float stepsize = 300.0;
  float m1 = 5.0;
  float m2 = m1;

  // Add a Title:
  sf::Font font;
  sf::Text title;
  if( !font.loadFromFile("fonts/arial.ttf")) {
    std::cerr << "ERROR: Font did not load properly." << std::endl;
  }
  title.setFont(font);
  title.setString("Double Pendulum Simulation");
  title.setCharacterSize(40);
  title.setColor(sf::Color::Green);
  sf::FloatRect recttemp = title.getLocalBounds();
  title.setPosition( (gDisplayx-recttemp.width)/2.0, 0.5*recttemp.height);

  sf::Text theta1;
  theta1.setFont(font);
  theta1.setCharacterSize(30);
  theta1.setColor(sf::Color::Green);
  std::string theta1string;
  theta1string = "Theta 1: " + pendulum.getThetaKnot1String() + " degrees";
  theta1.setString(theta1string);
  recttemp = theta1.getLocalBounds(); 
  theta1.setPosition( (gDisplayx-recttemp.width)/2.0, 2.7*(recttemp.height));

  sf::Text theta2;
  theta2.setFont(font);
  theta2.setCharacterSize(30);
  theta2.setColor(sf::Color::Green);
  std::string theta2string;
  theta2string = "Theta 2: " + pendulum.getThetaKnot2String() + " degrees";
  theta2.setString(theta2string);
  recttemp = theta2.getLocalBounds(); 
  theta2.setPosition( (gDisplayx-recttemp.width)/2.0, 4.1*(recttemp.height));

  while( window.isOpen() ) {
      sf::Event event;
      while( window.pollEvent(event) ) {
	if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ) {
	  window.close();
	}
      }
      // UPDATING
      pendulum.updatePendulum(t,stepsize, m1, m2);
      tracer.setPos(&pendulum);
      tracer.dissolve1(&pendulum);
      tracer.dissolve2(&pendulum);

      // DRAWINGS
      window.clear();
      window.draw(title);
      window.draw(theta1);
      window.draw(theta2);

      // Tracers
      window.draw(tracer);

      // Pendulum    
      window.draw( pendulum );

      window.display();   

      t+=dt;
 
  }
  return 0;
}
