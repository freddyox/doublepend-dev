#ifndef PENDULUM_HH
#define PENDULUM_HH

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>

class Pendulum : public sf::Drawable, public sf::Transformable
{
private:
  float mscreenwidth, mscreenheight;
  float screenoffset;

  sf::Vector2f pendulum1Size, pendulum2Size;
  float width1, height1, width2, height2;

  sf::Color pendulum1Color, pendulum2Color;

  float radius;
  sf::RectangleShape pendulum1, pendulum2;
  sf::CircleShape origin,middle,bottom;

  float omega, gravity, timer, conv, tracerang1, trancerang2;

  //RK4
  float theta1_knot, theta2_knot;
  double u1_knot, u2_knot, u3_knot, u4_knot;
  double u1_nth, u2_nth, u3_nth, u4_nth;

public:
  Pendulum(float,float); // dimensions of screen
  ~Pendulum() {};
  void draw(sf::RenderTarget&, sf::RenderStates) const;

  sf::Vector2f getPendulum1Size() { return pendulum1Size; }
  sf::Vector2f getPendulum2Size() {return pendulum2Size; }

  void updatePendulum(double, double, double, double);

  sf::Vector2f getPendulum1Position();
  sf::Vector2f getPendulum2Position();

  std::string getThetaKnot1String();
  std::string getThetaKnot2String();
  float getTheta1Knot() {return theta1_knot;} 
  float getTheta2Knot() {return theta2_knot;}
};
#endif
