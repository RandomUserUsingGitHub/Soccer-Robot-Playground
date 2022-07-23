#ifndef HELPWINDOW_HPP
#define HELPWINDOW_HPP

#include "Configs.hpp"

//-- Help Window Class
class HelpWindow {
    private:
        Mat helpWin;
        double Scale;
        double keySize;
        double keyLineSize;
        double keyPaddingLength;
        double keyPaddingWidth;
        double keyPositionX;
        double keyPositionY;
        double keyPressedValue;
        double keyFreeValue;
        double textPositionLength;
        double textPositionWidth;
        double keyTextBlue;
        double keyTextGreen;
        double keyTextRed;
        double keyInfoPositionX;
        double keyInfoPositionY;
        double spaceBetweenLines;
        double activityCirclePosition;
        double activityStatusPosition;
        double speedPositionLength;
        double statusPosition;
        double speedPositionWidth;
        double middleLength;
        double middleWidth;
        double activityCircleRadius;
        string status;
        string error;
        string speedStatus;
        int activeValue;
        int stoppedValue;
        bool active;
        int state;
        int fadingFluency;
        int fadingSpeed;
        int counter;
        int statusCircleSize;
    public:
        void updateHelpWindow(bool);
        HelpWindow();
        //-- Update Status of Changes
        void updateStatus(int, double);
        void updateError(string);
        int Fader();
        void resetError();
};

#endif // HELPWINDOW_HPP
