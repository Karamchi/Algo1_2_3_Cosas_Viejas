function [yval, plotvalsx, plotvalsy] = splineResuelto(t,x,y,pos,lim1,lim2)
    plotvalsx = [];
    plotvalsy = [];
    % Spline para (t,x(t)). Definir condiciones de borde (sujeto, natural, etc).
    x = [(x(2)-x(1))/(t(2)-t(1)), x, (x(end)-x(end-1))/(t(end)-t(end-1))]; % agregarndo valores para que sea sujeto
    ppx = spline(t,x);
    
    % Obtener el ultimo polinomio S_n(t).
    Sn = ppx.coefs(end,:);
    
    % Obs: Cada polinomio esta definido en el intervalo [0,1] en lugar de t(i),t(i+1).

    Sn(4) = Sn(4)-pos;
    lastpoly = @(z) polyval(Sn,z-t(end-1));

    % Obtener la raiz en t0.
    t0 = fzero(lastpoly, t(end));

    yval = (lim1+lim2)/2;
	% Alguna condicion de validacion para t0?
    if (t0>t(end) && t0<inf);
        y = [(y(2)-y(1))/(t(2)-t(1)), y, (y(end)-y(end-1))/(t(end)-t(end-1))];
        ppy = spline(t,y);
        yval = ppval(ppy,t0);
        plotvalsx = polyval(ppx.coefs(end,:),[0:0.2:t0-t(end)]);
        plotvalsy = polyval(ppy.coefs(end,:),[0:0.2:t0-t(end)]);
    end

end
