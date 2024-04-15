#include "aero.h"
#include "prop.h"
#include "sim.h"
#include "dynamics.h"
#include "gravity.h"
#include "isa.h"
#include <iostream>

void step()
{

}

int main() {
    // Create an instance of the aero class
    aero* s_aero = new aero;
    prop* s_prop = new prop;
    gravity* s_gravity = new gravity;
    dynamics* s_dynamics = new dynamics;
    isa* s_isa = new isa;
    airframe* s_airframe = new airframe;

    double dt = 1;

    Vector3d Wind = Vector3d::Zero();
    VectorXd cmd(4);
    cmd << 0.0, 0.0, 0.0, 0.785;

    Vector3d mp = Vector3d::Zero();
    
    sim::simTime().u.dt = &dt;

    s_isa->u.r_i = &s_dynamics->x.r_i;

    s_aero->u.v_b = &s_dynamics->x.v_b;
    s_aero->u.Wind = &Wind;
    s_aero->u.w_b = &s_dynamics->x.w_b;
    s_aero->u.cmd = &cmd;
    s_aero->u.rho = &s_isa->y.rho;
    s_prop->u.cmd = &cmd;
    s_gravity->u.quat = &s_dynamics->x.quat;

    s_dynamics->u.v_b = &s_dynamics->x.v_b;
    s_dynamics->u.w_b = &s_dynamics->x.w_b;
    s_dynamics->u.r_i = &s_dynamics->x.r_i;
    s_dynamics->u.quat = &s_dynamics->x.quat;
    s_dynamics->u.cmd = &cmd;
    s_dynamics->u.Jbb = &s_airframe->y.Jbb;
    s_dynamics->u.mass = &s_airframe->y.mass;
    s_dynamics->u.fa = &s_aero->y.Faero_b;
    s_dynamics->u.ma = &s_aero->y.Maero_b;
    s_dynamics->u.fp = &s_prop->y.Fprop_b;
    s_dynamics->u.mp = &s_prop->y.Mprop_b;
    s_dynamics->u.g_b = &s_gravity->y.g_b;

    s_airframe->get_output();
    s_dynamics->update_states();

    for (int i = 0; i < 1 / dt; ++i) {
        sim::simTime().update();

        s_isa->update();
        s_isa->get_output();

        s_aero->update();
        s_aero->get_output();

        s_prop->update();
        s_prop->get_output();

        s_gravity->update();
        s_gravity->get_output();

        s_dynamics->update();
        s_dynamics->get_dxdt();      
    }

    std::cout << "Aerodynamics Forces, aerodynamic frame [D,Sa,La] [N]: " << s_aero->y.Faero_w.transpose() << std::endl;
    std::cout << "Aerodynamics Forces, body frame [X,Y,Z] [N]: " << s_aero->y.Faero_b.transpose() << std::endl;
    std::cout << "Aerodynamics Moments, body frame [L,M,N] [Nm]: " << s_aero->y.Maero_b.transpose() << std::endl;
    std::cout << "Angle of attack [deg]: " << s_aero->y.alpha * (180 / M_PI) << std::endl;
    std::cout << "Angle of sideslip [deg]: " << s_aero->y.beta * (180 / M_PI) << std::endl;
    std::cout << "Airspeed [m/s]: " << s_aero->y.V << std::endl;
    std::cout << "CL: " << s_aero->y.CL << std::endl;
    std::cout << "CD: " << s_aero->y.CD << std::endl;
    std::cout << "CM: " << s_aero->y.CM << std::endl;
    std::cout << "Cba: " << s_aero->y.Cba << std::endl;
    std::cout << "Fprop: " << s_prop->y.Fprop_b.transpose() << std::endl;
    std::cout << "RPM: " << s_prop->y.RPM << std::endl;
    std::cout << "Fuel Mass: " << s_prop->y.fuel_mass << std::endl;
    std::cout << "Time: " << sim::simTime().getTime() << std::endl;
    std::cout << "Gravity Vector: " << s_gravity->y.g_b.transpose() << std::endl;
    std::cout << "r_i: " << s_dynamics->y.r_i.transpose() << std::endl;
    std::cout << "v_b: " << s_dynamics->y.v_b.transpose() << std::endl;
    std::cout << "w_b: " << s_dynamics->y.w_b.transpose() << std::endl;
    std::cout << "a: " << s_isa->y.a << std::endl;
    std::cout << "rho: " << s_isa->y.rho << std::endl;
    std::cout << "T: " << s_isa->y.T << std::endl;
    std::cout << "p: " << s_isa->y.p << std::endl;

    delete s_aero;
    delete s_prop;
    delete s_dynamics;
    delete s_gravity;
    delete s_isa;
    delete s_airframe;

    return 0;
}

