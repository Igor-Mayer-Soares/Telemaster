#include "airframe.h"

airframe::airframe()
{
    memset(&y, 0, sizeof(y));
    memset(&u, 0, sizeof(u));
    memset(&internal, 0, sizeof(internal));
}

void airframe::update()
{
}

void airframe::get_output()
{
    y.Jbb << 7.416, 0.0, 0.0,
             0.0, 9.755, 0.0,
             0.0, 0.0, 0.0153;
    y.mass = 10.0;
}
