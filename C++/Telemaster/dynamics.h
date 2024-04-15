#pragma once
#define _USE_MATH_DEFINES

#include "../libraries/Eigen/Eigen/Dense"
#include "sim.h"
#include <cstring>
#include <cmath>

using namespace Eigen;
using namespace std;


Quaterniond quaternionDerivative(const Quaterniond& q, const Vector3d& omega);
Quaterniond quaternionState(const Vector3d& euler);
Vector3d quaternionToEuler(const Quaterniond& quat);
/* This class computes the 6DoF equations
* Inputs:
*   --> Linear velocity, body frame [u,v,w] [m/s]
*   --> Angular velocity, body frame [p,q,r] [rad/s]
*   --> Quaternions [w, x, y, z]
*   --> Control surfaces command [da,de,dr,dt] [rad]
*   --> Position, inertial frame [x,y,z] [m]
*   --> Aerodynamic Forces, body frame [N]
*   --> Aerodynamic Moments, body frame [Nm]
*   --> Propulsion Forces, body frame [N]
*   --> Aerodynamic Moments, body frame [Nm]
*   --> Distance between xcg and origin [m]
*   --> Gravitational Acceleration at Body System [m/s^2]
*   --> Inertia [kgm^2]
*   --> Mass [kg]
*
* Outputs:
*   --> Derivative, Linear velocity, body frame [u,v,w] [m/s]  
*   --> Derivative, Angular velocity, body frame [p,q,r] [rad/s]
*   --> Derivative, Quaternions [w,x,y,z]
*   --> Derivative, Position, inertial frame [x,y,z] [m]
*/
class dynamics {
private:
    struct Internal
    {
        Matrix3d skew_wb;   // Skew-simmetric matrix, Angular velocity, body frame
        Quaterniond quat;   // Quaternions [w, x, y, z]
        Matrix3d Cbi;       // Rotation Matrix, Body to Inertial Frame
        MatrixXd Mgen;      // Generalized Mass Matrix
        VectorXd edot_b;    // Linear and Angular accelerations, Body Frame [m/s^2; rad/s^2]
        Vector3d n_b;       // Load Factor, Body Frame [m/s^2]
        Vector3d n_i;       // Load Factor, Inertial Frame [m/s^2]
        Vector3d Forces;    // Sum of all forces acting in the body [N]
        Vector3d Moments;   // Sum of all Moments acting in the body [Nm]
        VectorXd FM;        // [Forces;Moments]
        Quaterniond dquat;  // Derivative Quaternions [w, x, y, z]
        Vector3d v_b;
        Quaterniond quat_state;
        Vector3d r_i;
        Vector3d w_b;

    } internal;
public:
    struct Input
    {
        Vector3d* v_b;      // Linear velocity, body frame [u,v,w] [m/s]
        Vector3d* w_b;      // Angular velocity, body frame [p,q,r] [rad/s]
        Quaterniond* quat;  // Quaternions [w, x, y, z]
        VectorXd* cmd;      // Control surfaces command [da,de,dr,dt] [rad]
        Vector3d* r_i;      // Position, inertial frame [x,y,z] [m]
        Vector3d* fa;       // Aerodynamic Forces, body frame [N]
        Vector3d* ma;       // Aerodynamic Moments, body frame [Nm]
        Vector3d* fp;       // Propulsion Forces, body frame [N]
        Vector3d* mp;       // Aerodynamic Moments, body frame [Nm]
        Vector3d *g_b;      // Gravitational Acceleration at Body System [m/s^2]
        Matrix3d* Jbb;      // Inertia [kgm^2]
        double* mass;       // Mass [kg]
    } u;

    struct Derivatives
    {
        Vector3d dv_b;      // Derivative, Linear velocity, body frame [u,v,w] [m/s]  
        Vector3d dw_b;      // Derivative, Angular velocity, body frame [p,q,r] [rad/s]
        Quaterniond dquat;  // Derivative, Quaternions [w, x, y, z]
        Vector3d dr_i;      // Derivative, Position, inertial frame [x,y,z] [m]
    } dxdt;

    struct States
    {
        Vector3d v_b;      // Linear velocity, body frame [u,v,w] [m/s]  
        Vector3d w_b;      // Angular velocity, body frame [p,q,r] [rad/s]
        Quaterniond quat;  // Quaternions [w, x, y, z]
        Vector3d r_i;      // Position, inertial frame [x,y,z] [m]
        Vector3d euler;    // Attitude, euler angles
    } x;

    struct Outputs
    {
        Vector3d v_b;      // Linear velocity, body frame [u,v,w] [m/s]  
        Vector3d w_b;      // Angular velocity, body frame [p,q,r] [rad/s]
        Quaterniond quat;  // Quaternions [w, x, y, z]
        Vector3d r_i;      // Position, inertial frame [x,y,z] [m]
        Vector3d euler;    // Attitude, euler angles
    } y;

    void update();
    void update_states();
    void get_dxdt();
    void get_output();
    dynamics();
};

