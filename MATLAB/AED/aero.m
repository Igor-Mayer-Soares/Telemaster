%% Load
load('AVL/Results/LatCoeffs.mat')
load('AVL/Results/LonCoeffs.mat')
%% Salvar
% Definindo os valores de Alpha e as outras colunas
Alpha = TableAlpha.Alpha;
CL0 = 0.3647;
CD0 = 0.05917;
CM0 = -0.00310;
CLa = TableAlpha.CLa;
Cma = TableAlpha.Cma;
CLq = TableAlpha.CLq;
Cmq = TableAlpha.Cmq;
CLde = TableAlpha.CLd02;
Cmde = TableAlpha.Cmd02;

% Criando uma grade para interpolação
alpha = linspace(min(Alpha), max(Alpha), 100); % Altere o número de pontos conforme necessário

% Interpolando os valores para cada coluna
CLa = interp1(Alpha, CLa, alpha, 'spline');
CMa = interp1(Alpha, Cma, alpha, 'spline');
CLq = interp1(Alpha, CLq, alpha, 'spline');
CMq = interp1(Alpha, Cmq, alpha, 'spline');
CLde = interp1(Alpha, CLde, alpha, 'spline');
CMde = interp1(Alpha, Cmde, alpha, 'spline');

% Definindo os valores de Beta e as outras colunas
Beta = [-10; -5; 0; 5; 10];
Cldr = -1.65e-04;
Clda = -0.003694;
CYdr = -0.003885;
CYda = 2.80e-04;
Cndr = 0.001778;
Cnda = 1.1e-04;
CYb = TableBeta.CYb';
Clb = TableBeta.Clb';
Cnb = TableBeta.Cnb';
CYp = TableBeta.CYp';
Clp = TableBeta.Clp';
Cnp = TableBeta.Cnp';
CYr = TableBeta.CYr';
Clr = TableBeta.Clr';
Cnr = TableBeta.Cnr';

% Criando uma grade para interpolação
beta = linspace(min(Beta), max(Beta), 100); % Altere o número de pontos conforme necessário

% Interpolando os valores para cada coluna
CYb = interp1(Beta, CYb, beta, 'spline');
Clb = interp1(Beta, Clb, beta, 'spline');
Cnb = interp1(Beta, Cnb, beta, 'spline');
CYp = interp1(Beta, CYp, beta, 'spline');
Clp = interp1(Beta, Clp, beta, 'spline');
Cnp = interp1(Beta, Cnp, beta, 'spline');
CYr = interp1(Beta, CYr, beta, 'spline');
Clr = interp1(Beta, Clr, beta, 'spline');
Cnr = interp1(Beta, Cnr, beta, 'spline');


%% Hinge Moments
% elevator
Hmele = [-20 20].';
Hmalpha = [-10 15].';
HM_ele = [-4.37E-03 -5.53E-03
          5.88E-03  4.33E-03];

% rudder
Hmrud = [-20 20].';
Hmbeta = [-10 10].';
HM_rud = [4.14E-03  2.64E-03
         -2.64E-03 -4.14E-03];

% aileron
HM_ail = [-0.00458 0.00458];

save('alpha.mat','alpha','-v7.3')
save('Hmalpha.mat','Hmalpha','-v7.3')
save('beta.mat','beta','-v7.3')
save('Hmbeta.mat','Hmbeta','-v7.3')
save('CL0.mat','CL0','-v7.3') 
save('CM0.mat','CM0','-v7.3') 
save('CD0.mat','CD0','-v7.3') 
save('CLa.mat','CLa','-v7.3') 
save('CLde.mat','CLde','-v7.3') 
save('CLq.mat','CLq','-v7.3') 
save('CMa.mat','CMa','-v7.3') 
save('CMde.mat','CMde','-v7.3') 
save('CMq.mat','CMq','-v7.3')  
save('CYb.mat','CYb','-v7.3') 
save('CYda.mat','CYda','-v7.3') 
save('CYdr.mat','CYdr','-v7.3') 
save('CYp.mat','CYp','-v7.3') 
save('CYr.mat','CYr','-v7.3') 
save('Clb.mat','Clb','-v7.3') 
save('Clda.mat','Clda','-v7.3') 
save('Cldr.mat','Cldr','-v7.3') 
save('Clp.mat','Clp','-v7.3') 
save('Clr.mat','Clr','-v7.3') 
save('Cnb.mat','Cnb','-v7.3') 
save('Cnda.mat','Cnda','-v7.3') 
save('Cndr.mat','Cndr','-v7.3') 
save('Cnp.mat','Cnp','-v7.3') 
save('Cnr.mat','Cnr','-v7.3')
save('Hmele.mat','Hmele','-v7.3')
save('Hmrud.mat','Hmrud','-v7.3')
save('HM_ele.mat','HM_ele','-v7.3')
save('HM_rud.mat','HM_rud','-v7.3')
save('HM_ail.mat','HM_ail','-v7.3')
