function [X] = gausssei(A,b,x0)
    D = diag(diag(A));
    L = tril(-A)+D;
    U = triu(-A)+D;
    C = inv(D-L)*b;
    T = inv(D-L)*U;
    X = x0;
    while (norm(A*X - b) > 0.000001)
        X = T*X + C;
    end
end
