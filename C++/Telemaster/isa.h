#pragma once
#define _USE_MATH_DEFINES

#include "../libraries/Eigen/Eigen/Dense"
#include "sim.h"
#include <cstring>
#include <cmath>

using namespace Eigen;
using namespace std;

class isa {
private:
    struct Internal
    {
        double h;
        double h1;
        double h2;
        double h3;
        double L0;
        double L2;
        double g0;
        double m0;
        double R0;
        double R;
        double T0;
        double p0;
        double rho0;
        double T1;
        double p1;
        double rho1;
        double T2;
        double p2;
        double rho2;
        double gamma;
    } internal;
public:
    struct Input
    {
        Vector3d* r_i;      // Position, inertial frame [x,y,z] [m]
    } u;

    struct Output
    {
        double rho;
        double T;
        double p;
        double a;
    } y;

    void update();
    void get_output();

    isa();
};
