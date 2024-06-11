%% Características Geométricas
aircraft.S  = 0.9324;
aircraft.c  = 0.42;
aircraft.ce = 0.0910;
aircraft.Se = aircraft.ce*0.425;
aircraft.ca = 0.0650;
aircraft.Sa = aircraft.ca*1.1;
aircraft.cr = 0.2;
aircraft.Sr = aircraft.cr*0.42;
aircraft.b = 2.22;
aircraft.A = aircraft.b^2/aircraft.S;
aircraft.e = 1.78*(1-0.045*aircraft.A^0.68)-0.64;
aircraft.k = 1/(pi*aircraft.A*aircraft.e);
aircraft.J = [1.054 0 0
              0 1.21 0
              0 0 0.992];
aircraft.m = 5;

aircraft.cg = [0.105 0 0];
aircraft.Vmax = 20;
aircraft.Vstall = 9;