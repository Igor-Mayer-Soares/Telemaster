#include "gravity.h"

gravity::gravity()
{
	memset(&y, 0, sizeof(y));
	memset(&u, 0, sizeof(u));
	memset(&internal, 0, sizeof(internal));
}

void gravity::update()
{
	internal.quat = u.quat->normalized();
	internal.Cbi = internal.quat.toRotationMatrix().transpose();
}

void gravity::get_output()
{
	y.g_b = internal.Cbi * Vector3d(0.0, 0.0, M_G);
}