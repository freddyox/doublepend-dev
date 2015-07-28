#ifndef TRACER_HH
#define TRACER_HH

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>


#include "../include/Pendulum.hh"

class Pendulum;

class Tracer : public sf::Transformable, public sf::Drawable
{
private:
  float mscreenwidth, mscreenheight;
  sf::CircleShape circletracer;
  std::vector<sf::CircleShape> trace1,trace2;
  std::vector<sf::CircleShape>::iterator it;

  sf::Color tracercolor;
  float lifetime,life;
  sf::Time sftime1,sftime2;

public:
  Tracer(float,float);
  ~Tracer() {};
  void draw(sf::RenderTarget&, sf::RenderStates) const;
  void setPos(Pendulum*);
  void dissolve1(Pendulum*);
  void dissolve2(Pendulum*);
};
#endif
