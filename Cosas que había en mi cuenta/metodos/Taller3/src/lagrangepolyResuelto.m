function [Res,P] = lagrangepolyResuelto(X,Y,XX)

% Make sure that X and Y are row vectors
if size(X,1) > 1;  X = X'; end
if size(Y,1) > 1;  Y = Y'; end
if size(X,1) > 1 || size(Y,1) > 1 || size(X,2) ~= size(Y,2)
  error('both inputs must be equal-length vectors')
end

N = length(X);

pvals = zeros(N,N);

% Calculate the polynomial weights for each order
for i = 1:N
  % the polynomial whose roots are all the values of X except this one
  pp = poly(X( (1:N) ~= i)); %Esto devuelve los coeficientes del polinomio que tiene como raices a los elemtnos de x, salvo i

  pvals(i,:) = pp./polyval(pp,X(i));
end

P = Y*pvals;

% output is YY corresponding to input XX
Res = polyval(P, XX);

end
