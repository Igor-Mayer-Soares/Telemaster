%% Carregar modelos trimados e linearizados do Telemaster
cd("../")
main
cd("GNC/")
load("../MVO/Results/SteadyState.mat");

%% Decolagem
% Longitudinal:
%   1) 100% de manete de potência até atingir a 13 m/s;