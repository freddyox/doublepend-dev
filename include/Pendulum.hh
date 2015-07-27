#ifndef PENDULUM_HH
#define PENDULUM_HH

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>

class Pendulum : public sf::Drawable, public sf::Transformable
{
private:
  sf::Vector2f pendulumSize;
  float width,height;
  float mscreenwidth, mscreenheight;
  sf::Color pendulumColor;
  sf::RectangleShape pendulum;
  sf::CircleShape origin,bottom;
  float theta_knot;
  float omega;
  float gravity;
  float drag;
  float theta;
  float theta_dot;
  float timer;
  float conv,tracerang;

  //RK4
  float u1_knot, u2_knot, u1_nth, u2_nth;
public:
  Pendulum(float,float);
  ~Pendulum() {};
  void draw(sf::RenderTarget&, sf::RenderStates) const;
  sf::Vector2f getpendulumSize() { return pendulumSize; }
  void updatePendulum(float);
  void updatePendulumRK4(float,float);
  void chooseMethod(float,float);
  void addDrag(float);
  sf::Vector2f getPendulumPosition();
  std::string getThetaKnotString();
  float getThetaKnot() {return theta_knot;} 
};
#endif
