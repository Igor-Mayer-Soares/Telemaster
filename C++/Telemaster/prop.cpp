#include "prop.h"

prop::prop()
{
	memset(&y, 0, sizeof(y));
	memset(&u, 0, sizeof(u));
	memset(&internal, 0, sizeof(internal));
	internal.fuel_mass = 0.5;
}

void prop::update()
{
	if ((*u.cmd)(3) == 0.0)
	{
		internal.fuel_flow = 0;
		internal.RPM = 1450;
		internal.Thrust = 0;
	}
	else
	{
		internal.fuel_flow = 0.0008 * (*u.cmd)(3) + 0.0002;
		internal.RPM = 8E+06 * internal.fuel_flow;
		internal.Thrust = 0.0047 * internal.RPM;
	}
	internal.fuel_mass -= internal.fuel_flow * sim::simTime().getdt();
}

void prop::get_output()
{
	y.Fprop_b << internal.Thrust, 0.0, 0.0;
	y.Mprop_b << 0.0, 0.0, 0.0;
	y.RPM = internal.RPM;
	y.fuel_mass = internal.fuel_mass;
}