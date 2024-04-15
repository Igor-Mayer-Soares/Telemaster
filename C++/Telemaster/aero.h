#pragma once
#define _USE_MATH_DEFINES

#include "../libraries/Eigen/Eigen/Dense"
#include "sim.h"
#include <cstring>
#include <cmath>
#include "airframe.h"


using namespace Eigen;
using namespace std;

/* This class computes the aerodynamic forces and moments from Telemaster, based on AVL Data
* Inputs:
*   --> Linear velocity, body frame, plus wind components [u-wx,v-wy,w-wz] [m/s]
*   --> Wing Velocity [wx,wy,wz] [m/s]
*   --> Angular velocity, body frame [p,q,r] [rad/s]
*   --> Air Density [kg/m^3]
*   --> Control surfaces command [da,de,dr] [rad]
* 
* Outputs:
*   --> Aerodynamics Forces, aerodynamic frame [D,Sa,La] [N]
*   --> Aerodynamics Forces, body frame [X,Y,Z] [N]
*   --> Aerodynamics Forces, body frame [L,M,N] [Nm]
*   --> Angle of attack [rad]
*   --> Angle of sideslip [rad]
*   --> Airspeed [m/s]
*   --> Longitudinal Coefficients [CL,CD,CM] [-]
*   --> Rotation Matrix, Aerodynamic to Body System [-]
* 
*/
class aero {
private:
    struct Internal
    {
        double alpha; // Angle of attack [rad]
        double beta;  // Angle of sideslip [rad]
        double V;     // Airspeed [m/s]
        double CL0, CLa, CLde, CLq;   // Lift Derivatives 
        double CM0, CMa, CMde, CMq;   // Pitch Moment Derivatives
        double CD0, CDde, CDda, CDdr; // Drag Derivatives
        double CYb, CYda, CYdr, CYp, CYr; // Side Force Derivatives
        double Clb, Clda, Cldr, Clp, Clr; // Roll Moment Derivatives
        double Cnb, Cnda, Cndr, Cnp, Cnr; // Yaw Moment Derivatives
        double CD, CY, CL; // Force Derivatives
        double Cl, CM, Cn; // Moment Derivatives
        double D, Y, L; // Forces
        double l, M, N; // Moments
        Matrix3d Cba; // Rotation Matrix, Aerodynamic to Body System [-]
        double S;     // Reference area [m^2]
        double c;     // Reference chord [m]
        double b;     // Reference length [m]
        double Aw;    // Aspect Ratio [-]
        double k;     // Oswald Factor [-]
        Vector3d V_rel; // Relative Velocity [V_b-Wind] [m/s]
    } internal;
public:
    struct Input 
    {
        Vector3d *v_b; // Linear velocity, body frame [u,v,w] [m/s]  
        Vector3d *w_b; // Angular velocity, body frame [p,q,r] [rad/s]
        double   *rho; // Air Density [kg/m^3]
        VectorXd *cmd; // Control surfaces command [da,de,dr,dt] [rad]
        Vector3d *Wind;// Wind velocity [wx,wy,wz] [m/s]
    } u;

    struct Output 
    {
        Vector3d Faero_w; // Aerodynamics Forces, aerodynamic frame [D,Sa,La] [N]
        Vector3d Faero_b; // Aerodynamics Forces, body frame [X,Y,Z] [N]
        Vector3d Maero_b; // Aerodynamics Forces, body frame [L,M,N] [Nm]
        double alpha;     // Angle of attack [rad]
        double beta;      // Angle of sideslip [rad]
        double V;         // Airspeed [m/s]
        double CL, CD, CM;// Longitudinal Coefficients [CL,CD,CM] [-]
        Matrix3d Cba;     // Rotation Matrix, Aerodynamic to Body System [-]
    } y;

    void update();
    void get_output();

    aero();
};