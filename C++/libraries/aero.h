#ifndef AERO_H
#define AERO_H

#ifndef EIGEN_DENSE_H
#define EIGEN_DENSE_H
#include "Eigen/Eigen/Dense"
#endif // EIGEN_DENSE_H

#include <iostream>
#include <cstring>

using namespace Eigen;
using namespace std;

struct Input {
    VectorXd v_b; // Linear velocity, body frame [m/s]  
    double S;     // Reference area [m^2]
    double V;     // Airspeed [m/s]
    double rho;   // Air Density [kg/m^3]
    
};

struct Output {
    VectorXd Faero_w; // Aerodynamics Forces, aerodynamic frame [N]
    VectorXd Maero_w; // Aerodynamics Forces, aerodynamic frame [N]
    VectorXd Faero_b; // Aerodynamics Forces, body frame [N]
    VectorXd Maero_b; // Aerodynamics Forces, body frame [N]
    double alpha;     // Angle of attack [deg]
    double beta;      // Angle of sideslip [deg]
};

class aero{
private:
    struct Internal {
        double CL0;
        double CDde;
        double CLa;
        double CLde;
        double CLq;
        double Cma;
        double Cmde;
        double Cmq;
        double CDda;
        double CDdr;
        double CYb;
        double CYda;
        double CYdr;
        double CYp;
        double CYr;
        double Clb;
        double Clda;
        double Cldr;
        double Clp;
        double Clr;
        double Cnb;
        double Cnda;
        double Cndr;
        double Cnp;
        double Cnr;
        double Da;
        double Sa;
        double La;
    } internal;

public:
    void set_inputs(Input &u);

    Output get_outputs(const Input &u);

    aero();
};
    
#endif