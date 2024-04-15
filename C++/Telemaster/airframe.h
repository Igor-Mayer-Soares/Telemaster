#pragma once
#define _USE_MATH_DEFINES

#include "../libraries/Eigen/Eigen/Dense"
#include "sim.h"
#include <cstring>
#include <cmath>

using namespace Eigen;
using namespace std;

class airframe {
private:
    struct Internal
    {
    } internal;
public:
    struct Input
    {
    } u;

    struct Output
    {
        double mass;
        Matrix3d Jbb;
    } y;

    void update();
    void get_output();

    airframe();
};
