function Lch = CholFromLU(A)
    % Conseguir factorizacion LU de A
    [L,U,P] = lu(A);
    
    % Conseguir L de cholesky a partir de LU
    D = (inv(L))*U';  %#ok<*NASGU>
    
    % Considerar la funcion diag de MATLAB
    D2 = diag(diag(U));
    Lch = L*D2 ^(1/2);
    
    % Codigo para chequar que dio bien
    Ach = chol(A);
    for i = size(A,1)
        for j = size(A,2)
            if Ach(i,j) ~= Lch(i,j),
                error ('Son diferentes')
            end
        end
    end
end
