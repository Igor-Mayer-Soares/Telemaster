%% Script para inicializar a simulação
clear
close all
clc
addpath(genpath('../MATLAB'))
dt = 1/4000;
t = 0:dt:10;
t = t.';
u = zeros(length(t),4);
%% Carregar Banco Aerodinâmico
arquivos = dir(fullfile('AED/', '*.mat'));

for cont = 1:length(arquivos)
    % Carregue o arquivo .mat
    load(fullfile('AED/', arquivos(cont).name));
end

%% Geometria
Telemaster

%% Decolagem
TakeOff

%% Motor
DLE55c

%% Acelerador
% Teórico

%% Profundor
% Teórico

%% Leme
% Teórico