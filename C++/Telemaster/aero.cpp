#include "aero.h"

aero::aero() : u{ nullptr, nullptr, nullptr, nullptr}, internal {}, y{}
{
}

void aero::update() 
{
    // Aerodynamics System
    internal.V = u.v_b->norm();
    internal.alpha = atan2(u.v_b->z(), u.v_b->x());
    internal.beta = asin(u.v_b->y()/internal.V);
    internal.Cba = AngleAxisd(internal.alpha, Vector3d(0.0,-1.0,0.0)) * AngleAxisd(internal.beta, Vector3d(0.0, 0.0, -1.0));

    // Aerodynamics Derivatives
    internal.CL0  = 0.3647;
    internal.CM0  = -0.0031;
    internal.CD0  = 0.05917;
    internal.CDde =  2E-07 * pow(internal.alpha,2)  - 2E-05 * internal.alpha - 0.0007;
    internal.CLa  = -0.0017 * pow(internal.alpha, 2) - 0.0126 * internal.alpha + 4.4523;
    internal.CLde = -4E-06 * pow(internal.alpha, 2) - 2E-06 * internal.alpha + 0.0101;
    internal.CLq  = -0.001 * pow(internal.alpha, 2) - 0.004 * internal.alpha + 8.0732;
    internal.CMa  = 0.0005 * pow(internal.alpha, 2) + 9E-05 * internal.alpha - 0.9113;
    internal.CMde = 7E-06 * pow(internal.alpha, 2) - 2E-07 * internal.alpha - 0.0221;
    internal.CMq  = 0.0013 * pow(internal.alpha, 2) - 1E-05 * internal.alpha - 8.782;
    internal.CDda = 1E-05 * internal.alpha;
    internal.CDdr = 5E-05 * internal.alpha;
    internal.CYb  = 0.0002 * pow(internal.alpha, 2) - 0.3462;
    internal.CYda = 0.000289;
    internal.CYdr = -0.003914;
    internal.CYp  = -1E-05 * pow(internal.beta, 2) + 0.0943;
    internal.CYr  = -5E-05 * pow(internal.beta, 2) + 0.2988;
    internal.Clb  = 3E-05 * pow(internal.beta, 2) - 0.0488;
    internal.Clda = -0.003809;
    internal.Cldr = -0.000165;
    internal.Clp  = 6E-05 * pow(internal.beta, 2) - 0.3977;
    internal.Clr  = -2E-05 * pow(internal.beta, 2) + 0.1078;
    internal.Cnb  = -8E-05 * pow(internal.beta, 2) + 0.1308;
    internal.Cnda = 0.00011;
    internal.Cndr = 0.001833;
    internal.Cnp  = 4E-06 * pow(internal.beta, 2) - 0.0291;
    internal.Cnr  = 2E-05 * pow(internal.beta, 2) - 0.1366;

    // Aerodynamics Coefficients
    

    if (internal.V == 0.0)
    {
        internal.CL = 0.0;
        internal.CD = 0.0;
        internal.CM = 0.0;
        internal.CY = 0.0;
        internal.Cl = 0.0;
        internal.Cn = 0.0;
    }
    else
    {
        internal.CL = internal.CL0 + internal.CLa * internal.alpha + internal.CLde * (u.cmd->y() * 180.0 / M_PI) + internal.CLq * ((u.w_b->y() * (*u.Geo)(1)) / (2.0 * internal.V));
        internal.CD = internal.CD0 + internal.CDda * (u.cmd->x() * 180.0 / M_PI) + internal.CDde * (u.cmd->y() * 180.0 / M_PI) + internal.CDdr * (u.cmd->z() * 180.0 / M_PI) + pow(internal.CL, 2) * (*u.Geo)(5);
        internal.CM = internal.CM0 + internal.CMa * internal.alpha + internal.CMde * (u.cmd->y() * 180.0 / M_PI) + internal.CMq * ((u.w_b->y() * (*u.Geo)(1)) / (2.0 * internal.V));
        internal.CY = internal.CYb * internal.beta + internal.CYda * (u.cmd->x() * 180.0 / M_PI) + internal.CYdr * (u.cmd->z() * 180.0 / M_PI) + internal.CYp * ((u.w_b->x() * (*u.Geo)(2)) / (2.0 * internal.V)) + internal.CYr * ((u.w_b->z() * (*u.Geo)(2)) / (2.0 * internal.V));
        internal.Cl = internal.Clb * internal.beta + internal.Clda * (u.cmd->x() * 180.0 / M_PI) + internal.Cldr * (u.cmd->z() * 180.0 / M_PI) + internal.Clp * ((u.w_b->x() * (*u.Geo)(2)) / (2.0 * internal.V)) + internal.Clr * ((u.w_b->z() * (*u.Geo)(2)) / (2.0 * internal.V));
        internal.Cn = internal.Cnb * internal.beta + internal.Cnda * (u.cmd->x() * 180.0 / M_PI) + internal.Cndr * (u.cmd->z() * 180.0 / M_PI) + internal.Cnp * ((u.w_b->x() * (*u.Geo)(2)) / (2.0 * internal.V)) + internal.Cnr * ((u.w_b->z() * (*u.Geo)(2)) / (2.0 * internal.V));
    }

    internal.D = 0.5 * (*u.rho) * pow(internal.V, 2) * internal.CD * (*u.Geo)(0);
    internal.Y = 0.5 * (*u.rho) * pow(internal.V, 2) * internal.CY * (*u.Geo)(0);
    internal.L = 0.5 * (*u.rho) * pow(internal.V, 2) * internal.CL * (*u.Geo)(0);
    internal.l = 0.5 * (*u.rho) * pow(internal.V, 2) * internal.Cl * (*u.Geo)(0) * (*u.Geo)(2);
    internal.M = 0.5 * (*u.rho) * pow(internal.V, 2) * internal.CM * (*u.Geo)(0) * (*u.Geo)(1);
    internal.N = 0.5 * (*u.rho) * pow(internal.V, 2) * internal.Cn * (*u.Geo)(0) * (*u.Geo)(2);
}

void aero::get_output() 
{ 
    y.alpha = internal.alpha;
    y.beta  = internal.beta;
    y.V = internal.V;
    y.CL = internal.CL;
    y.CD = internal.CD;
    y.CM = internal.CM;
    y.Faero_w << internal.D, internal.Y, internal.L;
    y.Faero_b = internal.Cba * -y.Faero_w;
    y.Maero_b << internal.l, internal.M, internal.N;
    y.Cba << internal.Cba;
}
