#include "World.hpp"
#include "Configs.hpp"

//---------------------
//--| Model Configs |--
//---------------------
//-- Robot Size (in Meter) :
double robotSize = 0.18;
double robotLineSize = 2.5;
//-- Window Scale (in Pixels) :
//- for 3K Monitors := 222
//- for 2k Monitors := 120
//- for 1k Monitors := 80
double modelScale = 100;
//-- Font Size Scale :
double fontSize = 1.2;
//-- Lines of Model Scale :
double lineSize = 4;
//-- Blue, Green, Red
double fieldLineBlue = 100;
double fieldLineGreen = 100;
double fieldLineRed = 100;
double fieldBGBlue = 0;
double fieldBGGreen = 0;
double fieldBGRed = 0;
double enemyGoalBlue = 200;
double enemyGoalGreen = 220;
double enemyGoalRed = 0;
double teamGoalBlue = 0;
double teamGoalGreen = 220;
double teamGoalRed = 220;
//-- Refresh Rate (ms)
double refreshRate = 20.0 / 1000.0;
//-- Mathematical
double rad = 0.0174533;
//-- Mouse Click Flag
int mouseFlag;
//-- Rotation Value with Mouse
double mouseRotationValue = 10;
//-- Click Area Radius
double clickAreaRadius = robotSize * modelScale;
//-- Mouse Distance to Center of Agent
double mouseDistance;
//-- Model Window Size
double modelLength = windowLength * half;
double modelWidth = windowWidth * half;

//---------------------
//--| Robot Configs |--
//---------------------
//-- Sharpness of Robot (in Degree) :
double robotSharpness = 140.0;
//-- Robot Spawining Position (According to Scale in Meter) :
double xSpawn = 0.5;
double ySpawn = 0.5;
double rotationSpawn = 0;
//-- Robot Colors
double robotBlue = 212;
double robotGreen = 255;
double robotRed = 127;
//-- Color Value When Clicked
int clickedColorValue = 0;
//-- Speed Increase/Decrease Value
double moveSpeedValue = 0.2;
double rotateSpeedValue = 0.4;

//-- Spawning Configuration in Constructor
World::World() {
  robot.setPosition(0, 0, M_PI);
  model.setPos(0, 0, M_PI);
  robot.setVelocity(0, 0, 0);
  field.fieldCreate();
  create();
  setMouseCallback("World", mouseAttacher, this);
  mouseFlag = 1;
  robot.storePosition(0, 0, 0, 0, 0, 0);
  updateWindow();
}

//-- Updates Frames of Program
int World::updateWindow() {
  while (true) {
    //-- Update Window Frame's Refresh Rate :
    sleep_for(milliseconds((int)refreshRate * 1000));
    create();
    creatModelField();
    robot.storePosition(robot.accessX(), robot.accessY(), robot.accessTheta(),
                        robot.accessVX(), robot.accessVY(),
                        robot.accessVTheta());
    if (robot.accessVX() != 0 || robot.accessVY() != 0 ||
        robot.accessVTheta() != 0) {
      status.updateHelpWindow(true);
    } else {
      status.updateHelpWindow(false);
    }
    if (robot.borderCheck() == 0) {
      if (robot.state() == 1) {
        status.updateStatus(1, robot.accessVX());
      } else if (robot.state() == 2) {
        status.updateStatus(2, robot.accessVY());
      } else if (robot.state() == 3) {
        status.updateStatus(3, robot.accessVTheta());
      } else if (robot.state() == 0) {
        status.updateStatus(0, 0);
      }
      switch (waitKey(1)) {
      case (int('l')):
        status.resetError();
        robot.setVelocity(robot.accessVX(), robot.accessVY(),
                          robot.accessVTheta() + rotateSpeedValue);
        model.setVelocity(model.accessVX(), model.accessVY(),
                          model.accessVTheta() + rotateSpeedValue);
        break;
      case (int('j')):
        status.resetError();
        robot.setVelocity(robot.accessVX(), robot.accessVY(),
                          robot.accessVTheta() - rotateSpeedValue);
        model.setVelocity(model.accessVX(), model.accessVY(),
                          model.accessVTheta() - rotateSpeedValue);
        break;
      case (int('i')):
        status.resetError();
        robot.setVelocity(robot.accessVX() + moveSpeedValue, robot.accessVY(),
                          robot.accessVTheta());
        model.setVelocity(model.accessVX() + moveSpeedValue, model.accessVY(),
                          model.accessVTheta());
        break;
      case (int(';')):
        status.resetError();
        robot.setVelocity(robot.accessVX(), robot.accessVY() + moveSpeedValue,
                          robot.accessVTheta());
        model.setVelocity(model.accessVX(), model.accessVY() + moveSpeedValue,
                          model.accessVTheta());
        break;
      case (int(',')):
        status.resetError();
        robot.setVelocity(robot.accessVX() - moveSpeedValue, robot.accessVY(),
                          robot.accessVTheta());
        model.setVelocity(model.accessVX() - moveSpeedValue, model.accessVY(),
                          model.accessVTheta());
        break;
      case (int('h')):
        status.resetError();
        robot.setVelocity(robot.accessVX(), robot.accessVY() - moveSpeedValue,
                          robot.accessVTheta());
        model.setVelocity(model.accessVX(), model.accessVY() - moveSpeedValue,
                          model.accessVTheta());
        break;
      //-- [j] --> Reset Key
      case (int('k')):
        robot.setVelocity(0, 0, 0);
        model.setVelocity(0, 0, 0);
        break;
      case (int('r')):
        robot.setPosition(0, 0, M_PI);
        robot.setVelocity(0, 0, 0);
        model.setPos(0, 0, M_PI);
        model.setVelocity(0, 0, 0);
        break;
      //-- [Q] --> Quit Key
      case (int('q')):
        destroyAllWindows();
        return 0;
      }
      if (mouseFlag == 0 || mouseFlag == -1 || mouseFlag == 2) {
        robot.setVelocity(0, 0, 0);
      }
      robot.update();
      model.updateSpeed();
    } else {
      robot.resetCheck();
      // robot.setVelocity(0, 0, 0);
      status.updateError(robot.error());
    }
  }
  return 0;
}

//-- Draws the Robot on Field
void World::create() {
  //-- Creates Agent and Model
  field.Access().copyTo(realWorld);
  //-------------
  //--| World |--
  //-------------
  int agentCenterXPixel =
      (-robot.accessX() + (windowLength * half)) * modelScale;
  int agentCenterYPixel = (robot.accessY() + (windowWidth * half)) * modelScale;
  double agentTheta = robot.accessTheta();
  int agentDirectionXPixel;
  int agentDirectionYPixel;
  int agentRightXPixel;
  int agentRightYPixel;
  int agentLeftXPixel;
  int agentLeftYPixel;
  int robotSizePixel = robotSize * modelScale;
  //-- Point Center
  Point agentCenter(agentCenterXPixel, agentCenterYPixel);
  //-- Point Direction
  agentDirectionXPixel = agentCenterXPixel - robotSizePixel * cos(agentTheta);
  agentDirectionYPixel = agentCenterYPixel - robotSizePixel * sin(agentTheta);
  Point agentDirection(agentDirectionXPixel, agentDirectionYPixel);
  //-- Point Right
  agentRightXPixel =
      agentCenterXPixel -
      robotSizePixel * cos(agentTheta + (robotSharpness * M_PI / 180));
  agentRightYPixel =
      agentCenterYPixel -
      robotSizePixel * sin(agentTheta + (robotSharpness * M_PI / 180));
  Point agentRight(agentRightXPixel, agentRightYPixel);
  //-- Point Left
  agentLeftXPixel =
      agentCenterXPixel -
      robotSizePixel * cos(agentTheta - (robotSharpness * M_PI / 180));
  agentLeftYPixel =
      agentCenterYPixel -
      robotSizePixel * sin(agentTheta - (robotSharpness * M_PI / 180));
  Point agentLeft(agentLeftXPixel, agentLeftYPixel);
  //-- DR Line
  line(realWorld, agentDirection, agentRight,
       Scalar(robotBlue - clickedColorValue, robotGreen - clickedColorValue,
              robotRed - clickedColorValue),
       robotLineSize, 8, 0);
  //-- DL Line
  line(realWorld, agentDirection, agentLeft,
       Scalar(robotBlue - clickedColorValue, robotGreen - clickedColorValue,
              robotRed - clickedColorValue),
       robotLineSize, 8, 0);
  //-- OR Line
  line(realWorld, agentCenter, agentRight,
       Scalar(robotBlue - clickedColorValue, robotGreen - clickedColorValue,
              robotRed - clickedColorValue),
       robotLineSize, 8, 0);
  //-- OL Line
  line(realWorld, agentCenter, agentLeft,
       Scalar(robotBlue - clickedColorValue, robotGreen - clickedColorValue,
              robotRed - clickedColorValue),
       robotLineSize, 8, 0);
  imshow("World", realWorld);
}

//-- Attach Mouse to Window
void World::mouseAttacher(int event, int x, int y, int flags, void *data) {
  World *pointer = reinterpret_cast<World *>(data);
  pointer->Mouse(event, x, y, flags);
}

//-- Offer Mouse Clicking Options
void World::Mouse(int event, int x, int y, int flags) {
  if (robot.borderCheck() == 0) {
    if (mouseFlag == 1) {
      switch (event) {
      //-- Click Left Button to Pick Agent
      case EVENT_LBUTTONDOWN:
        mouseDistance = sqrt(pow(-robot.accessX() * modelScale -
                                     (x - windowLength * half * modelScale),
                                 2) +
                             pow(robot.accessY() * modelScale -
                                     (y - windowWidth * half * modelScale),
                                 2));
        if (mouseDistance < clickAreaRadius) {
          clickedColorValue = 100;
          mouseFlag = -1;
        }
        break;
      }
    } else if (mouseFlag == -1) {
      switch (event) {
      //-- Set Agent Position to Cursor Position
      case EVENT_MOUSEMOVE:
        robot.setX(-(x - windowLength * half * modelScale) / modelScale);
        robot.setY((y - windowWidth * half * modelScale) / modelScale);
        break;
      //-- Click Left Button to Place Agent
      case EVENT_LBUTTONUP:
        // clickedColorValue = 0;
        robot.setVelocity(model.accessVX(), model.accessVY(),
                          model.accessVTheta());
        mouseFlag = 1;
        break;
      case EVENT_MOUSEHWHEEL:
        if (getMouseWheelDelta(flags) < 0) {
          robot.setTheta(robot.accessTheta() + mouseRotationValue * M_PI / 180);
        } else {
          robot.setTheta(robot.accessTheta() - mouseRotationValue * M_PI / 180);
        }
        break;
      case EVENT_MBUTTONDOWN:
        mouseFlag = 0;
        break;
      }
    } else if (mouseFlag == 0) {
      switch (event) {
      case EVENT_MOUSEMOVE:
        robot.setX(-(x - windowLength * half * modelScale) / modelScale);
        robot.setY((y - windowWidth * half * modelScale) / modelScale);
        break;
      //-- Double Click Left Button to Decrease Theta
      case EVENT_LBUTTONDOWN:
        robot.setTheta(robot.accessTheta() - mouseRotationValue * M_PI / 180);
        break;
      //-- Double Click Right Button to Increase Theta
      case EVENT_RBUTTONDOWN:
        robot.setTheta(robot.accessTheta() + mouseRotationValue * M_PI / 180);
        break;
      case EVENT_MBUTTONDOWN:
        mouseFlag = -1;
        break;
      }
    }
  } else {
    robot.resetCheck();
    robot.setVelocity(0, 0, 0);
    status.updateError(robot.error());
    updateWindow();
  }
}
void World::creatModelField() {
  fieldModel =
      Mat((windowWidth / 2) * modelScale, (windowLength / 2) * modelScale,
          CV_8UC3, Scalar(199, 144, 149));

  int agentCenterXPixel =
      (-model.accessX() / 2 + (windowLength * half)) * modelScale;
  int agentCenterYPixel =
      (model.accessY() / 2 + (windowWidth * half)) * modelScale;
  double agentTheta = model.accessTheta();
  int agentDirectionXPixel;
  int agentDirectionYPixel;
  int agentRightXPixel;
  int agentRightYPixel;
  int agentLeftXPixel;
  int agentLeftYPixel;
  int robotSizePixel = robotSize * modelScale;
  //-- Point Center
  Point agentCenter(agentCenterXPixel / 2, agentCenterYPixel / 2);
  //-- Point Direction
  agentDirectionXPixel = agentCenterXPixel - robotSizePixel * cos(agentTheta);
  agentDirectionYPixel = agentCenterYPixel - robotSizePixel * sin(agentTheta);
  Point agentDirection(agentDirectionXPixel / 2, agentDirectionYPixel / 2);
  //-- Point Right
  agentRightXPixel =
      agentCenterXPixel -
      robotSizePixel * cos(agentTheta + (robotSharpness * M_PI / 180));
  agentRightYPixel =
      agentCenterYPixel -
      robotSizePixel * sin(agentTheta + (robotSharpness * M_PI / 180));
  Point agentRight(agentRightXPixel / 2, agentRightYPixel / 2);
  //-- Point Left
  agentLeftXPixel =
      agentCenterXPixel -
      robotSizePixel * cos(agentTheta - (robotSharpness * M_PI / 180));
  agentLeftYPixel =
      agentCenterYPixel -
      robotSizePixel * sin(agentTheta - (robotSharpness * M_PI / 180));
  Point agentLeft(agentLeftXPixel / 2, agentLeftYPixel / 2);
  //-- DR Line
  line(fieldModel, agentDirection, agentRight, Scalar(0, 0, 255), robotLineSize,
       8, 0);
  //-- DL Line
  line(fieldModel, agentDirection, agentLeft, Scalar(0, 0, 255), robotLineSize,
       8, 0);
  //-- OR Line
  line(fieldModel, agentCenter, agentRight, Scalar(0, 0, 255), robotLineSize, 8,
       0);
  //-- OL Line
  line(fieldModel, agentCenter, agentLeft, Scalar(0, 0, 255), robotLineSize, 8,
       0);
  imshow("Model", fieldModel);
}