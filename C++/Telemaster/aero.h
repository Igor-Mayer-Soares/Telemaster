#ifndef AERO_H
#define AERO_H
#define _USE_MATH_DEFINES

#include "../libraries/Eigen/Eigen/Dense"
#include <cstring>
#include <cmath>

using namespace Eigen;
using namespace std;

class aero{
private:

public:
    struct Input {
        Vector3d *v_b; // Linear velocity, body frame [u,v,w] [m/s]  
        Vector3d *w_b; // Angular velocity, body frame [p,q,r] [rad/s]
        VectorXd *Geo; // Main reference geometries [S,c,b,m,Aw,k] [m^2,m,m,kg,-,-]
        double *rho;   // Air Density [kg/m^3]
        Vector3d *cmd; // Control surfaces command [da,de,dr] [rad]
    } u;

    struct Output {
        Vector3d Faero_w; // Aerodynamics Forces, aerodynamic frame [D,Sa,La] [N]
        Vector3d Faero_b; // Aerodynamics Forces, body frame [X,Y,Z] [N]
        Vector3d Maero_b; // Aerodynamics Forces, body frame [L,M,N] [Nm]
        double alpha;     // Angle of attack [rad]
        double beta;      // Angle of sideslip [rad]
        double V;         // Airspeed [m/s]
        double CL, CD, CM;// Longitudinal Coefficients [CL,CD,CM] [-]
        Matrix3d Cba;     // Rotation Matrix, Aerodynamic to Body System [-]
    } y;

    struct Internal {
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
    } internal;

    void update();
    void get_output();

    aero();
};
    
#endif