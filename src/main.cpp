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
  double t = 0.0;
  double dt = 1.0/60.0;
  double stepsize = 50.0;
  double m1 = 1.0;
  double m2 = m1;

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

  sf::Text equalmass;
  if( m1 == m2 ) {
    equalmass.setFont(font);
    equalmass.setCharacterSize(20);
    equalmass.setColor(sf::Color::Green);
    equalmass.setString("Equal masses");
    recttemp = equalmass.getLocalBounds();
    equalmass.setPosition((gDisplayx+2*recttemp.width)/2.0, 4.7*(recttemp.height));
  }

  while( window.isOpen() ) {
      sf::Event event;
      while( window.pollEvent(event) ) {
	if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ) {
	  window.close();
	}
      }
      window.clear();

      // UPDATING
      pendulum.updatePendulum(t,stepsize, m1, m2);
      tracer.setPos(&pendulum);
      tracer.dissolve1(&pendulum);
      tracer.dissolve2(&pendulum);

      // DRAWINGS
      if(m1==m2) {
	//window.draw(equalmass);
      }
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
