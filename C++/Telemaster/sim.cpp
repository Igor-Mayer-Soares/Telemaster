#include "sim.h"

sim sim::instance;

sim::sim()
{
    memset(&y, 0, sizeof(y));
    memset(&u, 0, sizeof(u));
    memset(&internal, 0, sizeof(internal));
}

void sim::update()
{
    internal.time += *u.dt;
}

double sim::getTime() const
{
    return internal.time;
}

double sim::getdt() const
{
    return *u.dt;
}

sim& sim::simTime()
{
    return instance;
}
