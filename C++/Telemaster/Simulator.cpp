#include "aero.h"
#include <iostream>

int main() {
    // Create an instance of the aero class
    aero *myAero = new aero;

    Vector3d v_b(230.0834, 0, 5.7067);
    VectorXd Geo(6);
    Geo << 116, 3.862, 32.757, 55788, 9.2502, 0.0492;
    Vector3d cmd = Vector3d::Zero();
    Vector3d w_b = Vector3d::Zero();
    double rho = 0.3639;

    myAero->u.v_b = &v_b;
    myAero->u.w_b = &w_b;
    myAero->u.Geo = &Geo;
    myAero->u.cmd = &cmd;
    myAero->u.rho = &rho;

    myAero->update();

    myAero->get_output();

    std::cout << "Aerodynamics Forces, aerodynamic frame [D,Sa,La] [N]: " << myAero->y.Faero_w.transpose() << std::endl;
    std::cout << "Aerodynamics Forces, body frame [X,Y,Z] [N]: " << myAero->y.Faero_b.transpose() << std::endl;
    std::cout << "Aerodynamics Forces, body frame [L,M,N] [Nm]: " << myAero->y.Maero_b.transpose() << std::endl;
    std::cout << "Angle of attack [deg]: " << myAero->y.alpha << std::endl;
    std::cout << "Angle of sideslip [deg]: " << myAero->y.beta << std::endl;
    std::cout << "Airspeed [m/s]: " << myAero->y.V << std::endl;
    std::cout << "CL: " << myAero->y.CL << std::endl;
    std::cout << "CD: " << myAero->y.CD << std::endl;
    std::cout << "CM: " << myAero->y.CM << std::endl;
    std::cout << "Cba: " << myAero->y.Cba << std::endl;

    delete myAero;

    return 0;
}
