#include "aero.h"

aero::aero() : u{} {
    memset(&internal, 0, sizeof(Internal));
}

void aero::set_inputs(Input &u) {
    u.v_b = VectorXd::Zero(u.v_b.size());
    u.S = 0.0;
    u.V = 0.0;
    u.rho = 0.0;
}

Output aero::get_outputs(const Input &u){
    y.Faero_w = VectorXd::Zero(y.Faero_w.size());
    y.Maero_w = VectorXd::Zero(y.Maero_w.size());
    y.Faero_b = VectorXd::Zero(y.Faero_b.size());
    y.Maero_b = VectorXd::Zero(y.Maero_b.size());
    y.alpha = 0.0;
    y.beta = 0.0;

    return y;
}


