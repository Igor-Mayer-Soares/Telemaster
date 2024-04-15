#include "dynamics.h"

Quaterniond quaternionDerivative(const Quaterniond& q, const Vector3d& omega) {
	Quaterniond q_dot;
	q_dot.w() = 0.5 * (-q.x() * omega.x() - q.y() * omega.y() - q.z() * omega.z());
	q_dot.x() = 0.5 * (q.w() * omega.x() + q.y() * omega.z() - q.z() * omega.y());
	q_dot.y() = 0.5 * (q.w() * omega.y() - q.x() * omega.z() + q.z() * omega.x());
	q_dot.z() = 0.5 * (q.w() * omega.z() + q.x() * omega.y() - q.y() * omega.x());
	return q_dot;
}

Quaterniond quaternionState(const Vector3d& euler) {
	Quaterniond quat(
		cos(euler.x() / 2.0) * cos(euler.y() / 2.0) * cos(euler.z() / 2.0) + sin(euler.x() / 2.0) * sin(euler.y() / 2.0) * sin(euler.z() / 2.0),
		sin(euler.x() / 2.0) * cos(euler.y() / 2.0) * cos(euler.z() / 2.0) - cos(euler.x() / 2.0) * sin(euler.y() / 2.0) * sin(euler.z() / 2.0),
		cos(euler.x() / 2.0) * sin(euler.y() / 2.0) * cos(euler.z() / 2.0) + sin(euler.x() / 2.0) * cos(euler.y() / 2.0) * sin(euler.z() / 2.0),
		cos(euler.x() / 2.0) * cos(euler.y() / 2.0) * sin(euler.z() / 2.0) - sin(euler.x() / 2.0) * sin(euler.y() / 2.0) * cos(euler.z() / 2.0)
	);
	return quat;
}

Vector3d quaternionToEuler(const Quaterniond& quat)
{
	Vector3d euler = quat.toRotationMatrix().eulerAngles(0,1,2);
	return euler;
}


dynamics::dynamics()
{
	memset(&y,		  0, sizeof(y));
	memset(&u,		  0, sizeof(u));
	memset(&x,	      0, sizeof(x));
	memset(&internal, 0, sizeof(internal));

	internal.Mgen = MatrixXd::Zero(6, 6);
	internal.FM = VectorXd::Zero(6, 1);
	Vector3d euler(0.0, 0.0, 0.0);
	internal.v_b << 15, 0.0, 0.0;
	internal.quat = quaternionState(euler);
	internal.r_i << 0.0, 0.0, -100;
	internal.w_b << 0.0, 0.0, 0.0;
}

void dynamics::update()
{
	internal.skew_wb << 0, -u.w_b->z(), u.w_b->y(),
					   u.w_b->z(), 0, -u.w_b->x(),
					   -u.w_b->y(), u.w_b->x(), 0;

	internal.quat = u.quat->normalized();
	internal.Cbi = internal.quat.toRotationMatrix().transpose();

	internal.Mgen << *u.mass * Matrix3d::Identity(), 0.0 * Matrix3d::Identity(),
				     0.0 * Matrix3d::Identity(), * u.Jbb;

	internal.Forces = (- (*u.mass * internal.skew_wb * *u.v_b) + *u.fa + *u.fp + *u.mass * *u.g_b)*0.0;
	internal.Moments = (- (internal.skew_wb * *u.Jbb * *u.w_b) + *u.ma + *u.mp)*0.0;
	
	internal.FM << internal.Forces, internal.Moments;

	internal.edot_b = internal.Mgen.inverse() * internal.FM; 

	internal.dquat = quaternionDerivative(*u.quat, *u.w_b);
}

void dynamics::update_states()
{
	x.v_b  = internal.v_b;
	x.quat = internal.quat_state;
	x.r_i = internal.r_i;
	x.w_b = internal.w_b;
}

void dynamics::get_dxdt()
{
	dxdt.dv_b << internal.edot_b(0), internal.edot_b(1), internal.edot_b(2);
	dxdt.dw_b << internal.edot_b(3), internal.edot_b(4), internal.edot_b(5);
	dxdt.dquat = internal.dquat;
	dxdt.dr_i = internal.Cbi.transpose() * *u.v_b;
}

void dynamics::get_output()
{
	y.v_b = x.v_b;
	y.quat = x.quat;
	y.r_i = x.r_i;
	y.w_b = x.w_b;
	y.euler = quaternionToEuler(x.quat);
}