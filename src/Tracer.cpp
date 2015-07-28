#include "../include/Tracer.hh"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

Tracer::Tracer(float displayx, float displayy) {
  mscreenwidth = displayx;
  mscreenheight = displayy;

  lifetime = 1e-4;

  float radius(1.0);
  sf::Color tracercolor = sf::Color::Red;

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
  sf::Clock timer;
  sftime1 += timer.getElapsedTime();
  float life = sftime1.asSeconds();

  for( it=trace1.begin(); it != trace1.end(); it++) {
    float ratio = 0.5*life/lifetime;
    if( ratio < 1) {
      tracercolor = sf::Color(0, 255, 0, 255*ratio);
      (*it).setFillColor( tracercolor );
    }
    else {
      tracercolor = sf::Color(0, 255, 0);
      (*it).setFillColor( tracercolor );
    }
  }
}

void Tracer::dissolve2(Pendulum* ptr) {
  sf::Clock timer;
  sftime2 += timer.getElapsedTime();
  float life = sftime2.asSeconds();

  for( it=trace2.begin(); it != trace2.end(); it++) {
    float ratio = life*2/lifetime;
    if( ratio < 1 ){
      tracercolor = sf::Color(255, 0, 0, 255*ratio);
      (*it).setFillColor( tracercolor );
    }
    else {
      tracercolor = sf::Color(255, 0, 0);
      (*it).setFillColor( tracercolor );
    }
  }
}

