clear

%% Criar Dado

alpha = -10:5:15;
beta = -10:5:10;
de = [-15 15];
da = [-10 10];
dr = [-15 15];

cd('AVL')

for cont = 1:length(alpha)
    fid = fopen('alpha.run','w');
    fprintf(fid,'load\n');
    fprintf(fid,'Telemaster.avl\n');
    fprintf(fid,'mass\n');
    fprintf(fid,'Telemaster.mass\n');
    fprintf(fid,'mset 0\n');
    fprintf(fid,'oper\n');
    fprintf(fid,'a a %6.4f\n',alpha(cont));
    fprintf(fid,'x\n');
    fprintf(fid,'st\n');
    fprintf(fid,'Results\\A%s\n',string(alpha(cont)));
    fprintf(fid,'quit');
    fclose(fid);
    system('avl.exe < alpha.run')
    
    fid = fopen(strcat('Results\A',string(alpha(cont))), 'r');
    fileContents = fscanf(fid, '%c');
    fclose(fid);

    patterns = {'Alpha','CLtot', 'CDtot', 'e', 'CLa', 'Cma', 'CLq', 'Cmq', 'CLd02', 'Cmd02'};
    
    % Inicializar uma matriz para armazenar os valores
    paramValues = nan(1, numel(patterns));

    % Iterar sobre os padrões e extrair os valores correspondentes
    for cont1 = 1:numel(patterns)
        % Encontrar os valores correspondentes ao padrão atual
        match = regexp(fileContents, [patterns{cont1}, ' =\s*([-+]?[0-9]*\.?[0-9]+(?:[eE][-+]?[0-9]+)?)'], 'tokens');
    
        % Se houver uma correspondência, extrair o valor
        if ~isempty(match)
            % Extrair o valor e convertê-lo para double
            paramValues(cont1) = str2double(match{1}{1});
        end
    end

    % Criar a tabela com os valores extraídos
    TableAlpha(cont,:) = array2table(paramValues, 'VariableNames', patterns);
end
save('Results\LonCoeffs','TableAlpha','-mat');
clear paramValues
for cont = 1:length(beta)
    fid = fopen('beta.run','w');
    fprintf(fid,'load\n');
    fprintf(fid,'Telemaster.avl\n');
    fprintf(fid,'mass\n');
    fprintf(fid,'Telemaster.mass\n');
    fprintf(fid,'mset 0\n');
    fprintf(fid,'oper\n');
    fprintf(fid,'b b %6.4f\n',beta(cont));
    fprintf(fid,'x\n');
    fprintf(fid,'st\n');
    fprintf(fid,'Results\\B%s\n',string(beta(cont)));
    fprintf(fid,'quit');
    fclose(fid);
    system('avl.exe < beta.run')


    fid = fopen(strcat('Results\B',string(beta(cont))), 'r');
    fileContents = fscanf(fid, '%c');
    fclose(fid);

    patterns = {'Beta', 'CYb', 'Clb', 'Cnb', 'CYp', 'Clp', 'Cnp', 'CYr', 'Clr', 'Cnr', 'CYd01', 'Cld01', 'Cnd01', 'CYd03', 'Cld03', 'Cnd03'};
    
    % Inicializar uma matriz para armazenar os valores
    paramValues = nan(1, numel(patterns));

    % Iterar sobre os padrões e extrair os valores correspondentes
    for cont1 = 1:numel(patterns)
        % Encontrar os valores correspondentes ao padrão atual
        match = regexp(fileContents, [patterns{cont1}, ' =\s*([-+]?[0-9]*\.?[0-9]+(?:[eE][-+]?[0-9]+)?)'], 'tokens');
    
        % Se houver uma correspondência, extrair o valor
        if ~isempty(match)
            % Extrair o valor e convertê-lo para double
            paramValues(cont1) = str2double(match{1}{1});
        end
    end

    % Criar a tabela com os valores extraídos
    TableBeta(cont,:) = array2table(paramValues, 'VariableNames', patterns);
end
save('Results\LatCoeffs','TableBeta','-mat');

cd('..\')