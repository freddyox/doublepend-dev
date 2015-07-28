#include "../include/Pendulum.hh"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cmath>
#include <sstream>

Pendulum::Pendulum(float displayx, float displayy, float L1, float L2, float mass1, float mass2, float grav, float h) {
  mscreenwidth = displayx;
  mscreenheight = displayy;
  screenoffset = 130.0;
  gravity = grav;
  m1 = mass1;
  m2 = mass2;
  stepsize = h; 

  // Initial Conditions:
  count = 0;
  conv = 3.14192 / 180.0;                    
  srand( time(NULL) );
  theta1_knot = rand()%180+90;        
  theta2_knot = rand()%180+90;        

  // RK4 (need radians)
  u1_knot = theta1_knot * conv;
  u2_knot = 0.0 * conv;
  u3_knot = theta2_knot * conv;
  u4_knot = 0.0 * conv;

  //Initialize RK4
  u1_nth = u1_knot;
  u2_nth = u2_knot;
  u3_nth = u3_knot;
  u4_nth = u4_knot;

  // Pendulum 1:
  width1 = 1.3;
  height1 = L1;
  sf::Vector2f pendulum1Size( width1,height1 );
  sf::Color pendulum1Color = sf::Color( sf::Color(74,235,219) );
  pendulum1.setSize( pendulum1Size );
  pendulum1.setOrigin( width1/2.0, 0.0 ); // center origin
  pendulum1.setFillColor( pendulum1Color );
  pendulum1.setPosition( mscreenwidth/2.0, mscreenheight/2.0 - height1/2.0 + screenoffset);
  pendulum1.setRotation( theta1_knot );

  // Pendulum 2:
  width2 = width1;
  height2 = L2;
  sf::Vector2f pendulum2Size( width2,height2 );
  sf::Color pendulum2Color = sf::Color::Blue;
  pendulum2.setSize( pendulum2Size );
  pendulum2.setOrigin( width2/2.0, 0.0 );
  pendulum2.setFillColor( pendulum1Color );
  pendulum2.setPosition( -height1*sin(u1_knot) + mscreenwidth/2.0, 
  			 height1*cos(u1_knot) + mscreenheight/2.0 - height1/2.0 + screenoffset );
  pendulum2.setRotation( theta2_knot );

  // Ball joints at origin, connecting pend1 to pend2 and bottom of pend2
  radius = 3.0;
  origin.setRadius(radius/1.2);
  sf::FloatRect originRect = origin.getLocalBounds();
  origin.setOrigin( (originRect.width)/2.0, (originRect.height)/2.0 );
  origin.setFillColor( pendulum1Color );
  origin.setPosition( mscreenwidth/2.0, mscreenheight/2.0 - height1/2.0 + screenoffset );  

  middle.setRadius(2*radius);
  originRect = middle.getLocalBounds();
  middle.setOrigin( (originRect.width)/2.0, (originRect.height)/2.0 );
  middle.setFillColor( sf::Color(247,121,10) );
  middle.setPosition( -height1*sin(u1_knot) + mscreenwidth/2.0, 
  		      height1*cos(u1_knot) + mscreenheight/2.0 - height1/2.0 + screenoffset);

  bottom.setRadius(2*radius);
  originRect = bottom.getLocalBounds();
  bottom.setOrigin( (originRect.width)/2.0, (originRect.height)/2.0 );
  bottom.setFillColor( sf::Color(247,121,10) );
  bottom.setPosition( -height1*sin(u1_knot) - height2*sin(u3_knot) + mscreenwidth/2.0, 
  		      height1*cos(u1_knot) + height2*cos(u3_knot) + mscreenheight/2.0-height1/2.0 + screenoffset ); 
}

void Pendulum::updatePendulum(double time) {
  timer = time;
  count++;
  if( count % 20 ) {
    double delta = 1/stepsize;

    // Calculate Omega1
    double l0 = (-gravity*(2*m1+m2)*sin(u1_nth) - m2*gravity*sin(u1_nth-2*u3_nth) - 2*sin(u1_nth-u3_nth)*m2*(pow(u4_nth,2)*height2 + pow(u2_nth,2)*height1*cos(u1_nth-u3_nth)) ) / ( height1*(2*m1+m2-m2*cos(2*u1_nth-2*u3_nth)) ); 
  
    double l1 = (-gravity*(2*m1+m2)*sin(u1_nth+delta*0.5*l0) - m2*gravity*sin(u1_nth+delta*0.5*l0-2*u3_nth) - 2*sin(u1_nth+delta*0.5*l0-u3_nth)*m2*(pow(u4_nth,2)*height2 + pow(u2_nth,2)*height1*cos(u1_nth+delta*0.5*l0-u3_nth)) ) / ( height1*(2*m1+m2-m2*cos(2*u1_nth-2*u3_nth)) );

    double l2 = (-gravity*(2*m1+m2)*sin(u1_nth+delta*0.5*l1) - m2*gravity*sin(u1_nth+delta*0.5*l1-2*u3_nth) - 2*sin(u1_nth+delta*0.5*l1-u3_nth)*m2*(pow(u4_nth,2)*height2 + pow(u2_nth,2)*height1*cos(u1_nth+delta*0.5*l1-u3_nth)) ) / ( height1*(2*m1+m2-m2*cos(2*u1_nth-2*u3_nth)) );

    double l3 = (-gravity*(2*m1+m2)*sin(u1_nth+delta*l2) - m2*gravity*sin(u1_nth+delta*l2-2*u3_nth) - 2*sin(u1_nth+delta*l2-u3_nth)*m2*(pow(u4_nth,2)*height2 + pow(u2_nth,2)*height1*cos(u1_nth+delta*l2-u3_nth)) ) / ( height1*(2*m1+m2-m2*cos(2*u1_nth-2*u3_nth)) ); 

    double u2soln = u2_nth+(delta/6.0)*(l0 + 2*l1 + 2*l2 + l3);

    // Calculate theta1
    double k0 = u2_nth;
    double k1 = u2_nth + delta*0.5*k0;
    double k2 = u2_nth + delta*0.5*k1;
    double k3 = u2_nth + delta*k2;
    double u1soln = u1_nth + (delta/6.0)*(k0 + 2*k1 + 2*k2 + k3);

    // Calculate omega2
    double t0 = (2*sin(u1_nth-u3_nth)*(pow(u2_nth,2)*height1*(m1+m2) + gravity*(m1+m2)*cos(u1_nth) + pow(u4_nth,2)*height2*m2*cos(u1_nth-u3_nth) ) ) / (height2*(2*m1+m2-m2*cos(2*u1_nth-2*u3_nth)));

    double t1 = (2*sin(u1_nth-u3_nth+delta*0.5*t0)*(pow(u2_nth,2)*height1*(m1+m2) + gravity*(m1+m2)*cos(u1_nth) + pow(u4_nth,2)*height2*m2*cos(u1_nth-u3_nth+delta*0.5*t0)) ) / (height2*(2*m1+m2-m2*cos(2*u1_nth-2*u3_nth+delta*0.5*t0)));

    double t2 = (2*sin(u1_nth-u3_nth+delta*0.5*t1)*(pow(u2_nth,2)*height1*(m1+m2) + gravity*(m1+m2)*cos(u1_nth) + pow(u4_nth,2)*height2*m2*cos(u1_nth-u3_nth+delta*0.5*t1)) ) / (height2*(2*m1+m2-m2*cos(2*u1_nth-2*u3_nth+delta*0.5*t1)));

    double t3 = (2*sin(u1_nth-u3_nth+delta*t2)*(pow(u2_nth,2)*height1*(m1+m2) + gravity*(m1+m2)*cos(u1_nth) + pow(u4_nth,2)*height2*m2*cos(u1_nth-u3_nth+delta*t2)) ) / (height2*(2*m1+m2-m2*cos(2*u1_nth-2*u3_nth+delta*t2)));

    double u4soln = u4_nth + (delta/6.0)*(t0 + 2*t1 + 2*t2 + t3);

    // Calculate theta2
    double w0 = u4_nth;
    double w1 = u4_nth + delta*0.5*w0;
    double w2 = u4_nth + delta*0.5*w1;
    double w3 = u4_nth + delta*w2;
    double u3soln = u3_nth + (delta/6.0)*(w0 + 2*w1 + 2*w2 + w3);

    u1_nth = u1soln;
    u2_nth = u2soln;
    u3_nth = u3soln;
    u4_nth = u4soln;

    pendulum1.setRotation( u1_nth / conv );
    pendulum2.setRotation( u3_nth / conv );

    pendulum2.setPosition( -height1*sin(u1_nth) + mscreenwidth/2.0, 
			   height1*cos(u1_nth) + mscreenheight/2.0 - height1/2.0 + screenoffset );
  }
}

sf::Vector2f Pendulum::getPendulum1Position() {
  sf::Vector2f temp( -height1*sin(u1_nth), height1*cos(u1_nth) );
  sf::Vector2f origin2pendulum( mscreenwidth/2.0, mscreenheight/2.0 - height1/2.0 + screenoffset);
  middle.setPosition( temp+origin2pendulum );
  return temp + origin2pendulum;
}

sf::Vector2f Pendulum::getPendulum2Position() {
  sf::Vector2f temp( -height1*sin(u1_nth) - height2*sin(u3_nth) + mscreenwidth/2.0, 
		     height1*cos(u1_nth) + height2*cos(u3_nth) + mscreenheight/2.0-height1/2.0 + screenoffset); 
  bottom.setPosition( temp );
 return temp;
}

std::string Pendulum::getThetaKnot1String() {
  std::ostringstream temp;
  temp << theta1_knot;
  std::string string_temp = temp.str();
  return string_temp;
}

std::string Pendulum::getThetaKnot2String() {
  std::ostringstream temp;
  temp << theta2_knot;
  std::string string_temp = temp.str();
  return string_temp;
}

void Pendulum::draw( sf::RenderTarget& target, sf::RenderStates) const {
  target.draw( pendulum1 );
  target.draw( pendulum2 );
  target.draw( origin );
  target.draw( middle );
  target.draw( bottom );
}
