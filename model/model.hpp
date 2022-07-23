#ifndef MODEL_HPP
#define MODEL_HPP
#include "Configs.hpp"

class Model {
private:
  double x;
  double y;
  double theta;
  double speedX;
  double speedY;
  double speedTheta;

public:
  // sets
  void setPos(double, double, double);
  void setVelocity(double, double, double);
  //   accesses
  double accessX();
  double accessY();
  double accessTheta();
  double accessVX();
  double accessVY();
  double accessVTheta();
  //
  void updateSpeed();
};

#endif // MODEL_HPP
