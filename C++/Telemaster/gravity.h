#pragma once
#define _USE_MATH_DEFINES

#include "../libraries/Eigen/Eigen/Dense"
#include "sim.h"
#include <cstring>
#include <cmath>


using namespace Eigen;
using namespace std;

/* This class computes the aerodynamic forces and moments from Telemaster, based on AVL Data
* Inputs:
*   --> Quaternios [w, x, y, z]
*
* Outputs:
*   --> g_b Gravitational Acceleration at Body System [m/s^2]
*
*/
class gravity {
private:
    struct Internal
    {
        Quaterniond quat; // Quaternions [w, x, y, z]
        Matrix3d Cbi;     // Rotation Matrix, Inertial to Body System [-]
    } internal;
public:
    struct Input
    {
        Quaterniond *quat; // Quaternions [w, x, y, z]
    } u;

    struct Output
    {
        Vector3d g_b; // Gravitational Acceleration at Body System [m/s^2]
    } y;

    void update();
    void get_output();

    gravity();
};