#include "isa.h"

isa::isa() 
{
    memset(&y, 0, sizeof(y));
    memset(&u, 0, sizeof(u));
    memset(&internal, 0, sizeof(internal));

    internal.h1 = 11;
    internal.h2 = 20;
    internal.h3 = 32;
    internal.L0 = -6.5e-3;
    internal.L2 = 1e-3;
    internal.g0 = 9.80665;
    internal.m0 = 28.96442;
    internal.R0 = 8314.32;
    internal.T0 = 288.15;
    internal.p0 = 1.01325e5;
    internal.rho0 = 1.2250;
    internal.gamma = 1.4;
}

void isa::update()
{
    internal.h = -u.r_i->z() / 1000.0;
    internal.R = internal.R0 / internal.m0;
    internal.T1 = internal.T0 + internal.L0 * internal.h1 * 1E3;
    internal.p1 = internal.p0 * pow((internal.T1 / internal.T0), (-internal.g0 / (internal.R * internal.L0)));
    internal.rho1 = internal.rho0 * pow((internal.T1 / internal.T0), -(1 + internal.g0 / (internal.R * internal.L0)));
    internal.T2 = internal.T1;
    internal.p2 = internal.p1 * exp(-internal.g0 / (internal.R * internal.T2) * (internal.h2 - internal.h1) * 1E3);
    internal.rho2 = internal.rho1 * exp(-internal.g0 / (internal.R * internal.T2) * (internal.h2 - internal.h1) * 1E3);
}

void isa::get_output()
{
    if (internal.h <= internal.h1) 
    {
        y.T = internal.T0 + internal.L0 * internal.h * 1E3;
        y.p = internal.p0 * pow((y.T / internal.T0), (-internal.g0 / (internal.R * internal.L0)));
        y.rho = internal.rho0 * pow((y.T / internal.T0), -(1 + internal.g0 / (internal.R * internal.L0)));
    }
    else if (internal.h <= internal.h2) 
    {
        y.T = internal.T1;
        y.p = internal.p1 * exp(-internal.g0 / (internal.R * y.T) * (internal.h - internal.h1) * 1E3);
        y.rho = internal.rho1 * exp(-internal.g0 / (internal.R * y.T) * (internal.h - internal.h1) * 1E3);
    }
    else if (internal.h <= internal.h3) 
    {
        y.T = internal.T2 + internal.L2 * (internal.h - internal.h2) * 1E3;
        y.p = internal.p2 * pow((y.T / internal.T2), (-internal.g0 / (internal.R * internal.L2)));
        y.rho = internal.rho2 * pow((y.T / internal.T2), -(1 + internal.g0 / (internal.R * internal.L2)));
    }
    y.a = sqrt(internal.gamma * internal.R * y.T);
}
