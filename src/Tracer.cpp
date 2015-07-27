#include "../include/Tracer.hh"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

Tracer::Tracer(float displayx, float displayy) {
  mscreenwidth = displayx;
  mscreenheight = displayy;
  life = 3.0;
  float radius(1.0);
  sf::Color tracercolor = sf::Color::Red;
  sf::Color red = sf::Color::Red;
  sf::Color blue = sf::Color::Blue;
  sf::Color green = sf::Color::Green;
  sf::Color indigo = sf::Color(75,0,130);
  sf::Color yellow = sf::Color::Yellow;
  sf::Color orange = sf::Color(255,128,0);
  sf::Color violet = sf::Color(140,0,255);

  circletracer.setRadius(radius);
  sf::FloatRect originRect = circletracer.getLocalBounds();
  circletracer.setOrigin( (originRect.width)/2.0, (originRect.height)/2.0 );
}

void Tracer::draw( sf::RenderTarget& target, sf::RenderStates ) const {
  std::vector<sf::CircleShape>::const_iterator cit;
  for( cit = trace1.begin(); cit != trace1.end(); cit++ ) {
    target.draw( *cit );
  }
  for( cit = trace2.begin(); cit != trace2.end(); cit++ ) {
    target.draw( *cit );
  }
}

void Tracer::setPos(Pendulum* ptr) {
  sf::Vector2f x_knot1 = ptr->getPendulum1Position();
  sf::Vector2f x_knot2 = ptr->getPendulum2Position();
  
  circletracer.setPosition( x_knot1 );
  trace1.push_back( circletracer );
  circletracer.setPosition( x_knot2 );
  trace2.push_back( circletracer );
}

void Tracer::dissolve1(Pendulum* ptr) {
  srand(time(NULL));

  sf::Clock timer;
  sftime1 += timer.getElapsedTime();
  float life = sftime1.asSeconds();
  sf::Vector2f temp = ptr->getPendulum1Position();

  for( it=trace1.begin(); it != trace1.end(); it++) {
    sf::Vector2f tracerposition = (*it).getPosition();
    sf::Vector2f distanceVec = temp - tracerposition;
    float distance = sqrt( pow(distanceVec.x,2) + pow(distanceVec.y,2) );
    float ratio = 255/(0.1*distance);

    tracercolor = sf::Color(0,255,0,ratio);
    (*it).setFillColor( tracercolor );

    if( life > 0.00003 ) {
      trace1.erase(it);
      life = 0;
    }
  }
}

void Tracer::dissolve2(Pendulum* ptr) {
  srand(time(NULL));

  sf::Clock timer;
  sftime2 += timer.getElapsedTime();
  float life = sftime2.asSeconds();
  sf::Vector2f temp = ptr->getPendulum2Position();

  for( it=trace2.begin(); it != trace2.end(); it++) {
    sf::Vector2f tracerposition = (*it).getPosition();
    sf::Vector2f distanceVec = temp - tracerposition;
    float distance = sqrt( pow(distanceVec.x,2) + pow(distanceVec.y,2) );
    float ratio = 255/(0.1*distance);

    tracercolor = sf::Color(255,0,0,ratio);
    (*it).setFillColor( tracercolor );

    if(life > 0.00003) {
      trace2.erase(it);
      life = 0;
    }
  }
}
