cd('../')
main
cd('DES')
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Peso Máximo de Decolagem
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Tmax = 28.4;
T =  Tmax*0.7;
S = aircraft.S;

m = 2:1:10;

W = m.*9.80665;

T_W = T./W;
W_S = W./S;

% Stall
W_S_stall = 0.5*1.225*10^2*1.5;

% Cruise
Vcruise = sqrt(W_S.*(2/1.225*0.7));
T_W_cruise = (0.5*1.225.*Vcruise.^2*CD0)./W_S+(aircraft.k./(0.5*1.225.*Vcruise.^2).^2).*W_S;

% Subida
T_W_climb = deg2rad(5) + (CD0*(1.3^2/1.5))+aircraft.k*(1.5/1.3^2);

figure(1)
plot(W_S,T_W,'b',LineWidth=2)
hold on
plot([W_S_stall W_S_stall],[T_W(1) T_W(end)],'k--',LineWidth=2)
plot(W_S,T_W_cruise,'r--',LineWidth=2)
plot([W_S(1) W_S(end)],[T_W_climb T_W_climb],'g--',LineWidth=2)
xlabel('W/S [N/m^2]')
ylabel('T/W')
grid on
