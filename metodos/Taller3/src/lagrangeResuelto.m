function [yval, plotvalsx, plotvalsy] = lagrangeResuelto(t,x,y,pos,lim1,lim2)
    plotvalsx = [];
    plotvalsy = [];

    % Lagrange para (t,x(t))
    [aux,px] = lagrangepolyResuelto(t,x,t(end));
    px(end) = px(end)-pos;

    % Definimos funcion lambda para poder usar fzero.
    lastpoly = @(z) polyval(px,z);

    % Obtener la raiz t0..
    t0 = fzero(lastpoly, t(end));
    px(end) = px(end)+pos;
    yval = (lim1+lim2)/2;
	% Alguna validacion para t0?
    if (t0>t(end))
		% Obtener la posicion del arquero.
        [yval,py] = lagrangepolyResuelto(t,y,t0);
		% Funciones a graficar.
        plotvalsx = polyval(px,[t(end):0.2:t0]);
        plotvalsy = polyval(py,[t(end):0.2:t0]);
    end
end
