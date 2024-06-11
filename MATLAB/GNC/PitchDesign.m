clear
close all
cd('../')
main
cd('GNC')

%% Variáveis de Projeto

load('../MVO/Results/SteadyState.mat')
load_system("PitchHarness")

Pitch.tau           = 0.08;
Pitch.rmax_pos      = 0;
Pitch.rmax_neg      = 0;
Pitch.roll_ff       = 1;
Pitch.rate_p        = 0.55;
Pitch.rate_i        = 0.9;
Pitch.rate_imax     = 1;
Pitch.rate_d        = 0.1;
Pitch.rate_ff       = 3;
Pitch.rate_fltt     = 1;
Pitch.rate_flte     = 1;
Pitch.rate_fltd     = 1;
Pitch.rate_smax     = 1;
Pitch.rate_pdmx     = 1;
Pitch.rate_d_ff     = 0.05;
Pitch.rate_ntf      = 1;
Pitch.rate_nef      = 1;
Pitch.ControlRate   = 400;

Vcruise = 13;
V= Vcruise;

dt = 1/4000;
t = 0:dt:10;
t = t.';
u = zeros(length(t),4);
u(:,2)   = SteadyState(V).op.Inputs(2, 1).u;
u(:,3)   = SteadyState(V).op.Inputs(3, 1).u;
TO.u     = SteadyState(V).op.States(7).x;
TO.v     = SteadyState(V).op.States(8).x;
TO.w     = SteadyState(V).op.States(9).x;
TO.p     = SteadyState(V).op.States(4).x;
TO.q     = SteadyState(V).op.States(5).x;
TO.r     = SteadyState(V).op.States(6).x;
TO.phi   = SteadyState(V).op.States(1).x;
TO.theta = SteadyState(V).op.States(2).x;
TO.psi   = SteadyState(V).op.States(3).x;
TO.x     = SteadyState(V).op.States(10).x;
TO.y     = SteadyState(V).op.States(11).x;
TO.z     = SteadyState(V).op.States(12).x;
TO.alt0  = 0; 
