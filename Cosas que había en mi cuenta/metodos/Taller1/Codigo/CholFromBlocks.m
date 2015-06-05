function Lch = CholFromBlocks(A)
    % Obtengo cholesky de una dimension menos
    s=size(A,1);
    L = chol(A(1:s-1,1:s-1), 'lower');
    
    % Calculo los valores que faltan y armo el resultado
    ultFila = (inv(L)*A(1:s-1,s))';
    
    ultElem = sqrt((A(s,s)-(ultFila*ultFila')));
    Zeros = zeros(s-1,1);
    Lch = [L Zeros; ultFila ultElem];
    
    
    % Codigo para chequar que dio bien
    Ach = tril(chol(A));
    for i = size(A,1)
        for j = size(A,2)
           if Ach(i,j)~=Lch(i,j)
               error('Son distintas')
           end
        end
    end
end

