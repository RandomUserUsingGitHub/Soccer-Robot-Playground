#ifndef WORLD_HPP
#define WORLD_HPP

//-- Includes Needed Files
#include "Field.hpp"
#include "HelpWindow.hpp"
#include "Robot.hpp"
#include "model.hpp"

class World {
private:
  Field field;
  Robot robot;
  HelpWindow status;
  Model model;
  Mat realWorld;
  Mat fieldModel;

public:
  World();
  int updateWindow();
  void create();
  void creatModelField();
  static void mouseAttacher(int, int, int, int, void *);
  void Mouse(int, int, int, int);
};

#endif // WORLD_HPP
