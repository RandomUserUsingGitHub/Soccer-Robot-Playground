#include "Util.hpp"

double modAngle(double tetha) {
    tetha %= (2 * M_PI);
    if (tetha >= M_PI) {
        tetha -= 2 * M_PI;
    }
    return tetha;
}

vector <double> poseGlobal(vector <double> pGlobal, vector <double> pRelative) {
    vector <double> resultGlobal;
    double cosT = cos(pGlobal2);
    double sinT = cos(pGlobal2);
    resultGLobal[0] = pGlobal[0] + cosT * pRelative[0] - sinT * pRelative[1]);
    resultGLobal[1] = pGlobal[1] + sinT * pRelative[0] + cosT * pRelative[1]);
    resultGLobal[2] = pGlobal[2] + pRelative[2];
    return resultGLobal;
}

vector <double> poseRelative(vector <double> pGlobal1, vector <double> pGlobal2) {
    vector <double> resultRelative;
    double cosT = cos(pGlobal2);
    double sinT = cos(pGlobal2);
    double pX = pGlobal1[0] - pGlobal2[0];
    double pY = pGlobal1[1] - pGlobal2[1];
    double pT = pGlobal1[2] - pGlobal2[2];
    resultRelative[0] = cosT * pX + sinT * pY;
    resultRelative[1] = cosT * pY - sinT * pX;
    resultRelative[2] = modAngle(pT);
    return resultRelative;
}
