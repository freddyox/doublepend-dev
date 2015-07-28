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
#include <sstream>
#include <string>


const float gDisplayx = 800;
const float gDisplayy = 800;
int main() {
  //GAME SETUP
  sf::RenderWindow window(sf::VideoMode(gDisplayx,gDisplayy), "Double Pendulum Simulation");
  window.setFramerateLimit(60);

  // Handling Time
  double t = 0.0;
  double dt = 1.0/60.0;

  //////////////////////////////////////////////////////
  //                   Parameters                     //
  /////////////////////////////////////////////////////
  float gravity = 9.8;
  float stepsize = 50.0;
  float m1 = 1.0;
  float m2 = 1.0;
  float L1 = 150.0;
  float L2 = 110.0;
  // Initializing the Simulation
  Pendulum pendulum( window.getSize().x, window.getSize().y, L1, L2, 
		     m1, m2, gravity, stepsize);
  Tracer tracer( window.getSize().x, window.getSize().y );

  //////////////////////////////////////////////////////
  // TEXT 
  //////////////////////////////////////////////////////
  std::ostringstream temp,temp1;
  temp << m1;
  std::string m1string = temp.str();
  temp1 << m2;
  std::string m2string = temp1.str();

  // Add a Title:
  sf::Font font;
  sf::Text title;
  sf::Color textcolor = sf::Color::Blue;
  if( !font.loadFromFile("fonts/arial.ttf")) {
    std::cerr << "ERROR: Font did not load properly." << std::endl;
  }
  title.setFont(font);
  title.setString("Double Pendulum Simulation");
  title.setCharacterSize(40);
  title.setColor(textcolor);
  sf::FloatRect recttemp = title.getLocalBounds();
  title.setPosition( (gDisplayx-recttemp.width)/2.0, 0.5*recttemp.height);

  sf::Text theta1;
  theta1.setFont(font);
  theta1.setCharacterSize(30);
  theta1.setColor(textcolor);
  std::string theta1string;
  theta1string = "Theta 1: " + pendulum.getThetaKnot1String() + " degrees";
  theta1.setString(theta1string);
  recttemp = theta1.getLocalBounds(); 
  theta1.setPosition( (gDisplayx-recttemp.width)/2.0, 2.7*(recttemp.height));

  sf::Text theta2;
  theta2.setFont(font);
  theta2.setCharacterSize(30);
  theta2.setColor(textcolor);
  std::string theta2string;
  theta2string = "Theta 2: " + pendulum.getThetaKnot2String() + " degrees";
  theta2.setString(theta2string);
  recttemp = theta2.getLocalBounds(); 
  theta2.setPosition( (gDisplayx-recttemp.width)/2.0, 4.1*(recttemp.height));

  sf::Text masstext;
  if( m1 == m2 ) {
    masstext.setFont(font);
    masstext.setCharacterSize(30);
    masstext.setColor(textcolor);
    masstext.setString("Equal masses");
    recttemp = masstext.getLocalBounds();
    masstext.setPosition( (gDisplayx-recttemp.width)/2.0, 5.5*(recttemp.height));
  }
  else {
    masstext.setFont(font);
    masstext.setCharacterSize(30);
    masstext.setColor(textcolor);
    std::string unequalstring =  "m1 = " + m1string + ", m2 = " + m2string;
    masstext.setString( unequalstring );
    recttemp = masstext.getLocalBounds();
    masstext.setPosition( (gDisplayx-recttemp.width)/2.0, 5.5*(recttemp.height));
  }
  /////////////////////////////////////////////////////////////////////////////


  while( window.isOpen() ) {
      sf::Event event;
      while( window.pollEvent(event) ) {
	if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ) {
	  window.close();
	}
      }
      window.clear();

      // UPDATING
      pendulum.updatePendulum(t);
      tracer.setPos(&pendulum);
      tracer.dissolve1(&pendulum);
      tracer.dissolve2(&pendulum);

      // DRAWINGS
      window.draw(masstext);
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
