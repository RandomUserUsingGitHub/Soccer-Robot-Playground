#include "HelpWindow.hpp"

//---------------------------------
//--| Help Window Configuration |--
//---------------------------------
//-- Help Window Size
double helpWindowWidth = fieldLength / 1.3;
double helpWindowLength = fieldWidth / 2;
//-- Activity Circle Colors and Attributes
int activityStateValue = 0;
int stopStateValue = 0;
int counter = 0;
int state = 1;
//-- Help Window Background Color Config
int windowColorBlue = 20;
int windowColorGreen = 20;
int windowColorRed = 20;
//-- Help Window Font Size
double helpWindowFontSize;
//-- Help Window Text Colors
int helpWindowTextBlue = 255 ;
int helpWindowTextGreen = 255;
int helpWindowTextRed = 0;

//-- Constructor to Set Default Values
HelpWindow::HelpWindow() {
    Scale = modelScale * 12;
    if (Scale >= 2500){
        helpWindowFontSize = 1.6;
    } else if (Scale > 1550 && Scale < 2500) {
        helpWindowFontSize = 1.1;
    } else {
        helpWindowFontSize = 0.7;
    }
    //-- Config Display Values
    state = 1;
    counter = 0;
    fadingSpeed = 1;
    activeValue = 0;
    stoppedValue = 0;
    fadingFluency = 2;
    // positionW = 0.0625;
    // positionS = 0.1250;
    // positionD = 0.1875;
    // positionA = 0.2500;
    // positionP = 0.3125;
    // positionC = 0.3750;
    // positionM = 0.4375;
    // positionR = 0.5000;
    // positionQ = 0.5625;
    // positionText = 0.0625;
    // positionError = 0.7500;
    // positionStatus = 0.1200;
    // positionStatusCircle = 0.6875;
    // positionUpdateSpeed = 0.8125;
    // statusCircleSize = modelScale / 15;
    // keyPressedValue = 241,167,254
    middleLength = helpWindowLength * half * modelScale;
    middleWidth = helpWindowWidth * half * modelScale;

    textPositionLength = helpWindowLength * modelScale / 80;
    textPositionWidth = helpWindowWidth * modelScale / 90;
    keySize = helpWindowLength * modelScale / 8;
    keyLineSize = lineSize * 2;
    keyPaddingLength = helpWindowLength * modelScale / 20;
    keyPaddingWidth = helpWindowWidth * modelScale / 60;
    keyPositionX = helpWindowLength * modelScale * 0.09;
    keyPositionY = helpWindowWidth * modelScale * 0.1;
    keyTextBlue = 209;
    keyTextGreen = 240;
    keyTextRed = 170;
    keyInfoPositionX = helpWindowLength * modelScale / 70;
    keyInfoPositionY = helpWindowWidth * modelScale / 3.5;
    spaceBetweenLines = helpWindowWidth * modelScale / 25;
    activityCirclePosition = helpWindowWidth * modelScale * 0.93;
    activityStatusPosition = activityCirclePosition + spaceBetweenLines;
    statusPosition = helpWindowLength * modelScale / 12;
    activityCircleRadius = modelScale * 0.1;
    speedPositionWidth = helpWindowWidth * modelScale * 0.89;
    speedPositionLength = helpWindowLength * modelScale / 3.1;
}

//-- Makes Help Window
void HelpWindow::updateHelpWindow(bool value) {
    //-- Set Active/Deactive Value
    active = value;
    //-- Creates Help Window
    helpWin = Mat(helpWindowWidth * modelScale, helpWindowLength * modelScale, CV_8UC3, Scalar(10,10,10));
    //-- Definition of Points and Strings
    //- Key I :
    string keyI = "I";
    string infoI = "Increase Velocity in X Axis";
    Point keyI1(keyPositionX + keyPaddingLength + (keySize) * 2, keyPositionY - (keySize + keyPaddingWidth));
    Point posKeyI(keyPositionX + keyPaddingLength + (keySize) * 2.5 - textPositionLength, keyPositionY - (keySize * half + keyPaddingWidth) + textPositionWidth);
    Point keyI2(keyPositionX + keyPaddingLength + (keySize) * 3, keyPositionY + keySize - (keySize + keyPaddingWidth));
    rectangle(helpWin, keyI1, keyI2, Scalar(136,117,54), keyLineSize, 8, 0);
    putText(helpWin, keyI, posKeyI, FONT_HERSHEY_TRIPLEX, helpWindowFontSize, Scalar(keyTextBlue, keyTextGreen, keyTextRed));
    //- Key H :
    string keyH = "H";
    string infoH = "Increase Velocity in Y Axis";
    Point keyH1(keyPositionX, keyPositionY);
    Point posKeyH(keyPositionX + keyPaddingLength - textPositionLength, keyPositionY + keySize * half + textPositionWidth);
    Point keyH2(keyPositionX + keySize, keyPositionY + keySize);
    rectangle(helpWin, keyH1, keyH2, Scalar(136,117,54), keyLineSize, 8, 0);
    putText(helpWin, keyH, posKeyH, FONT_HERSHEY_TRIPLEX, helpWindowFontSize, Scalar(keyTextBlue, keyTextGreen, keyTextRed));
    //- Key J :
    string keyJ = "J";
    string infoJ = "Decrease Rotation Velocity";
    Point keyJ1(keyPositionX + (keySize + keyPaddingLength) * 1, keyPositionY);
    Point posKeyJ(keyPositionX + (keySize + keyPaddingLength) * 1.05 + keyPaddingLength - textPositionLength, keyPositionY + keySize * half + textPositionWidth);
    Point keyJ2(keyPositionX + keySize + (keySize + keyPaddingLength) * 1, keyPositionY + keySize);
    rectangle(helpWin, keyJ1, keyJ2, Scalar(136,117,54), keyLineSize, 8, 0);
    putText(helpWin, keyJ, posKeyJ, FONT_HERSHEY_TRIPLEX, helpWindowFontSize, Scalar(keyTextBlue, keyTextGreen, keyTextRed));
    //- Key K :
    string keyK = "K";
    string infoK = "Stops Agent";
    Point keyK1(keyPositionX + (keySize + keyPaddingLength) * 2, keyPositionY);
    Point posKeyK(keyPositionX + (keySize + keyPaddingLength) * 2 + keyPaddingLength - textPositionLength, keyPositionY + keySize * half + textPositionWidth);
    Point keyK2(keyPositionX + keySize + (keySize + keyPaddingLength) * 2, keyPositionY + keySize);
    rectangle(helpWin, keyK1, keyK2, Scalar(136,117,54), keyLineSize, 8, 0);
    putText(helpWin, keyK, posKeyK, FONT_HERSHEY_TRIPLEX, helpWindowFontSize, Scalar(keyTextBlue, keyTextGreen, keyTextRed));
    //- Key L :
    string keyL = "L";
    string infoL = "Increase Rotation Velocity";
    Point keyL1(keyPositionX + (keySize + keyPaddingLength) * 3, keyPositionY);
    Point posKeyL(keyPositionX + (keySize + keyPaddingLength) * 3.05 + keyPaddingLength - textPositionLength, keyPositionY + keySize * half + textPositionWidth);
    Point keyL2(keyPositionX + keySize + (keySize + keyPaddingLength) * 3, keyPositionY + keySize);
    rectangle(helpWin, keyL1, keyL2, Scalar(136,117,54), keyLineSize, 8, 0);
    putText(helpWin, keyL, posKeyL, FONT_HERSHEY_TRIPLEX, helpWindowFontSize, Scalar(keyTextBlue, keyTextGreen, keyTextRed));
    //- Key Semicolon :
    string keySemicolon = ";";
    string infoSemicolon = "Decrease Velocity in Y Axis";
    Point keysemicolon1(keyPositionX + (keySize + keyPaddingLength) * 4, keyPositionY);
    Point posKeySemicolon(keyPositionX + (keySize + keyPaddingLength) * 4.1 + keyPaddingLength - textPositionLength, keyPositionY + keySize * 0.45 + textPositionWidth);
    Point keysemicolon2(keyPositionX + keySize + (keySize + keyPaddingLength) * 4, keyPositionY + keySize);
    rectangle(helpWin, keysemicolon1, keysemicolon2, Scalar(136,117,54), keyLineSize, 8, 0);
    putText(helpWin, keySemicolon, posKeySemicolon, FONT_HERSHEY_TRIPLEX, helpWindowFontSize, Scalar(keyTextBlue, keyTextGreen, keyTextRed));
    //- Key Colon :
    string keyColon = ",";
    string infoColon = "Decrease Velocity in X Axis";
    Point keyColon1(keyPositionX + keyPaddingLength + (keySize) * 3, keyPositionY + (keySize + keyPaddingWidth));
    Point posKeyColon(keyPositionX + keyPaddingLength + (keySize) * 3.5 - textPositionLength, keyPositionY + keySize * 2 - textPositionWidth);
    Point keyColon2(keyPositionX + keyPaddingLength + (keySize) * 4, keyPositionY + keySize + (keySize + keyPaddingWidth));
    rectangle(helpWin, keyColon1, keyColon2, Scalar(136,117,54), keyLineSize, 8, 0);
    putText(helpWin, keyColon, posKeyColon, FONT_HERSHEY_TRIPLEX, helpWindowFontSize, Scalar(keyTextBlue, keyTextGreen, keyTextRed));

    //-- Keys Information
    //- Key I
    Point textI(keyPositionX + keyPaddingLength, keyInfoPositionY);
    Point defineI(keyInfoPositionX, keyInfoPositionY);
    putText(helpWin, infoI, textI, FONT_HERSHEY_SIMPLEX, helpWindowFontSize * 0.7, Scalar(keyTextBlue, keyTextGreen, keyTextRed));
    putText(helpWin, "I > ", defineI, FONT_HERSHEY_SIMPLEX, helpWindowFontSize * 0.7, Scalar(95,169,225));
    //- Key H
    Point textH(keyPositionX + keyPaddingLength, keyInfoPositionY + spaceBetweenLines * 1);
    Point defineH(keyInfoPositionX, keyInfoPositionY + spaceBetweenLines * 1);
    putText(helpWin, infoH, textH, FONT_HERSHEY_SIMPLEX, helpWindowFontSize * 0.7, Scalar(keyTextBlue, keyTextGreen, keyTextRed));
    putText(helpWin, "H > ", defineH, FONT_HERSHEY_SIMPLEX, helpWindowFontSize * 0.7, Scalar(95,169,225));
    //- Key J
    Point textJ(keyPositionX + keyPaddingLength, keyInfoPositionY + spaceBetweenLines * 2);
    Point defineJ(keyInfoPositionX, keyInfoPositionY + spaceBetweenLines * 2);
    putText(helpWin, infoJ, textJ, FONT_HERSHEY_SIMPLEX, helpWindowFontSize * 0.7, Scalar(keyTextBlue, keyTextGreen, keyTextRed));
    putText(helpWin, "J > ", defineJ, FONT_HERSHEY_SIMPLEX, helpWindowFontSize * 0.7, Scalar(95,169,225));
    //- Key K
    Point textK(keyPositionX + keyPaddingLength, keyInfoPositionY + spaceBetweenLines * 3);
    Point defineK(keyInfoPositionX, keyInfoPositionY + spaceBetweenLines * 3);
    putText(helpWin, infoK, textK, FONT_HERSHEY_SIMPLEX, helpWindowFontSize * 0.7, Scalar(keyTextBlue, keyTextGreen, keyTextRed));
    putText(helpWin, "K > ", defineK, FONT_HERSHEY_SIMPLEX, helpWindowFontSize * 0.7, Scalar(95,169,225));
    //- Key L
    Point textL(keyPositionX + keyPaddingLength, keyInfoPositionY + spaceBetweenLines * 4);
    Point defineL(keyInfoPositionX, keyInfoPositionY + spaceBetweenLines * 4);
    putText(helpWin, infoL, textL, FONT_HERSHEY_SIMPLEX, helpWindowFontSize * 0.7, Scalar(keyTextBlue, keyTextGreen, keyTextRed));
    putText(helpWin, "L > ", defineL, FONT_HERSHEY_SIMPLEX, helpWindowFontSize * 0.7, Scalar(95,169,225));
    //- Key ;
    Point textSemicolon(keyPositionX + keyPaddingLength, keyInfoPositionY + spaceBetweenLines * 5);
    Point defineSemicolon(keyInfoPositionX, keyInfoPositionY + spaceBetweenLines * 5);
    putText(helpWin, infoSemicolon, textSemicolon, FONT_HERSHEY_SIMPLEX, helpWindowFontSize * 0.7, Scalar(keyTextBlue, keyTextGreen, keyTextRed));
    putText(helpWin, "; > ", defineSemicolon, FONT_HERSHEY_SIMPLEX, helpWindowFontSize * 0.7, Scalar(95,169,225));
    //- Key ,
    Point textColon(keyPositionX + keyPaddingLength, keyInfoPositionY + spaceBetweenLines * 6);
    Point defineColon(keyInfoPositionX, keyInfoPositionY + spaceBetweenLines * 6);
    putText(helpWin, infoColon, textColon, FONT_HERSHEY_SIMPLEX, helpWindowFontSize * 0.7, Scalar(keyTextBlue, keyTextGreen, keyTextRed));
    putText(helpWin, ", > ", defineColon, FONT_HERSHEY_SIMPLEX, helpWindowFontSize * 0.7, Scalar(95,169,225));

    //-- Velocity Vector Viewer
    Point speedChange(middleLength - speedPositionLength, speedPositionWidth);
    putText(helpWin, speedStatus, speedChange, FONT_HERSHEY_DUPLEX, helpWindowFontSize / 1.5, Scalar(179,222,245));

    //-- Activity Status
    Point activityCircle(middleLength, activityCirclePosition);
    Point activityStatus(middleLength - statusPosition, activityStatusPosition);
    circle(helpWin, activityCircle, activityCircleRadius, Scalar(0, Fader(), stoppedValue), -1, 8, 0);
    putText(helpWin, status, activityStatus, FONT_HERSHEY_DUPLEX, helpWindowFontSize / 1.7, Scalar(0, activeValue, stoppedValue));
    
    //-- Show Help Window
    imshow("Help Window", helpWin);
}

//-- Update Status of Speed Change (Movement and Rotation)
void HelpWindow::updateStatus(int option, double velocity) {
    if (option == 1) {
        speedStatus = "X Axis Velocity Changed";
    } else if (option == 2) {
        speedStatus = "Y Axis Velocity Changed";
    } else if(option == 3) {
        speedStatus = "Rotation Velocity Changed";
    } else if (option == 0){
        speedStatus = " ";
    }
}

//-- Update Help Window Border Error
void HelpWindow::updateError(string err) {
    error = err;
}

//-- Reset Error Data
void HelpWindow::resetError()
{
    error = " ";
}

//-- Fader Function for Activity Circle
int HelpWindow::Fader() {
    int temp1 = activeValue;
    int temp2 = stoppedValue;
    if (active == true) {
        status = "On Move";
        stoppedValue = 0;
        activeValue = activeValue + state * fadingFluency;
        if (counter % fadingSpeed == 0) {
            if (activeValue > 255) {
                state = -1;
            } else if (activeValue < 0) {
                state = 1;
                activeValue = temp1;
            }
        } else if (counter > 100) {
            counter = 0;
        }
    } else {
        status = "Stopped";
        activeValue = 0;
        stoppedValue = stoppedValue + state * fadingFluency;
        if (counter % fadingSpeed == 0) {
            if (stoppedValue > 255) {
                state = -1;
            } else if (stoppedValue < 0) {
                state = 1;
                stoppedValue = temp2;
            }
        } else if (counter > 100) {
            counter = 0;
        }
    }
    counter++;
    return activeValue;
}