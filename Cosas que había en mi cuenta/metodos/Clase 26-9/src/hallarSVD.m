% SVD sobre matriz B cuadrada.
function [U,S,V] = hallarSVD(B, tol)
    n = size(B,1);

    % Calculamos A'A
    BtB = B'*B;
    
    % Autovalores y autovectores de A'A
    [P,D] = eig(BtB); % ya vienen los autovectores ortogonales en las columnas de P, asociados a los autovalores en la diagonal de D.

    % Reordenarlos (autovalores de mayor a menor)
    [autovaloresOrdenados,permutacion] = sort(diag(D), 'descend');
    D = diag(autovaloresOrdenados);
    tempP = zeros(size(P));
    for i=1:length(permutacion),
        tempP(:,i) = P(:,permutacion(i));
    end
    P = tempP;
    % P y D tienen los autovectores y autovalores ordenados respectivamente

    %% EJERCICIOS

    % Calculamos V y S
    V = P;
    S = sqrt(D);

    % Calculamos rango de B (cantidad de valores singulares no nulos)
    rango = 0;

    for i=1:n
        if abs(S(i,i)) < to1,
            rango = i-1;
                break;
        end
    end
    
    
    % Calculamos columnas de U asociadas a valores singulares positivos
    % A = USV'   sii    AV = US   sii   Av_1 = s_1 u_1  sii  u_1 = Av_1 / s_1
    U=zeros(n);
    for i=1:rango,
        U(:,i) = (1/S(i,i)) * B * V(:,i);
    end



    %% Si no es rango completo, COMPLETAMOS BASE + GRAM-SCHMIDT
    if rango < n,
        % pongo como filas los vectores ortogonales que ya tengo (u_1...u_r)
        subespacio = U(:,1:rango)';
        % busco vectores canonicos que sean LI con los otros
        I = eye(n);
        for i=1:(n-rango), % cantidad de vectores a agregar
            for j=1:n,
                % pruebo si el j-esimo canonico es li con el subespacio que ya tenia
                eJ = I(j,:); % canonico fila
                % Dado que las filas de subespacio son li, quisiera ver si
                % el eJ es comb lineal de ellas o no. 
                combLineal = eJ/subespacio; % Resuelve el sistema x*sub = x1*fila1(sub) + ... + xn*filan(sub) = eJ   (x vector fila)
                if max(abs( combLineal*subespacio - eJ )) > tol, % Si no es comb lineal (matlab usó LLS)
                    subespacio = [subespacio; eJ];
                    break;
                end
            end
        end
        %%% Ahora ortogonalizamos: gram-schmidt
        for i=(rango+1):n, % para cada vector canonico que agregue
            ortogonalizado = subespacio(i,:);
            for j=1:(i-1),
                ortogonalizado = ortogonalizado - ( dot(subespacio(j,:),ortogonalizado)/dot(subespacio(j,:),subespacio(j,:)) )*subespacio(j,:);
            end
            subespacio(i,:) = (1/norm(ortogonalizado,2)) * ortogonalizado;
        end
        U = subespacio';
    end
    
    %% Check de errores al ortogonalizar.
    if max(max(isnan(U)))==1 || max(max(isnan(V)))==1 || max(max(isnan(S)))==1,
        warning('La factorización SVD falló. Revisar el parámetro de tolerancia.');
        disp('B_k='); disp(B);
        disp('U=');   disp(U);
        disp('S=');   disp(S);
        disp('V=');   disp(V);
        disp('Rango Estimado='); disp(rango);
        disp(' ');
    end
    
