#include "model.hpp"
#include "Configs.hpp"

double Model::accessX() { return x; }
double Model::accessY() { return y; }
double Model::accessTheta() { return theta; }
double Model::accessVX() { return speedX; }
double Model::accessVY() { return speedY; }
double Model::accessVTheta() { return speedTheta; }
void Model::setPos(double X, double Y, double Theta) {
  x = X;
  y = Y;
  theta = Theta;
}
void Model::setVelocity(double sX, double sY, double sTheta) {
  speedX = sX;
  speedY = sY;
  speedTheta = sTheta;
}

void Model::updateSpeed() {
  double gloSpeedX = speedX * cos(theta) + speedY * sin(-theta);
  double gloSpeedY = speedY * cos(-theta) + speedX * sin(theta);

  x += gloSpeedX * refreshRate;
  y -= gloSpeedY * refreshRate;

  theta += speedTheta * refreshRate;
}