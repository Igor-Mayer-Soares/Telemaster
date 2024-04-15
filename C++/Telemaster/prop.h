#pragma once
#define _USE_MATH_DEFINES

#include "../libraries/Eigen/Eigen/Dense"
#include "sim.h"
#include <cstring>
#include <cmath>

using namespace Eigen;
using namespace std;

/* This class computes the forces and moments from DLE 55c Motor
* Inputs:
*   --> Control surfaces command [da,de,dr,dt] [rad]
*
* Outputs:
*   --> Propulsion Forces, body frame [X,Y,Z] [N]
*   --> Rotation per Minute [RPM]
*   --> Fuel mass [kg]
*/
class prop {
private:
    struct Internal
    {
        double fuel_flow;
        double Thrust;
        double RPM;
        double fuel_mass;
    } internal;
public:
    struct Input 
    {
        VectorXd *cmd; // Control surfaces command [da,de,dr,dt] [rad]
    } u;

    struct Output 
    {
        Vector3d Fprop_b;
        Vector3d Mprop_b;
        double RPM;
        double fuel_mass;
    } y;

    void update();
    void get_output();

    prop();
};