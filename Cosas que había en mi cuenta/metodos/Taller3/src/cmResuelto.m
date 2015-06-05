function [yval, plotvalsx, plotvalsy] = cmResuelto(t,x,y,pos,lim1,lim2)
    plotvalsx = [];
    plotvalsy = [];
    
    % Cuadrados minimos para (t,x(t)).
    pcmx = polyfit(t, x, 1);
    
    % encontrar una raiz para pcmx - pos = 0.
    pcmx(end) = pcmx(end)-pos;
    lastpoly = @(z) polyval(pcmx,z);
    t0 = fzero(lastpoly, t(end));
    
    pcmx(end) = pcmx(end) + pos;
    yval = (lim1+lim2)/2; %Ver
	
	% Algun criterio de validacion para t0?
    if (t0>t(end) && t0<inf);
		% Cuadrados minimos para (t,y(t))
        pcmy = polyfit(t, y, 1);
		% posicion para el arquero.
        yval = polyval(pcmy,t0);
		if yval<lim1;
            yval = lim1;
        end
        if yval>lim2;
             yval=lim2;
        end
        % graficar la funcion.
        plotvalsx = polyval(pcmx,[t(end):0.2:t(end)+20]); 
        plotvalsy = polyval(pcmy,[t(end):0.2:t(end)+20]); 
    end
end

%%
%El sistema Ax=B para (t,x(t)) de t sería:
%A=[t,ones(n)] (n es la cantidad de valores de x)
%x=[a,b] (los coeficientes del polinomio a obtener, que en este caso es
%lineal)
%B=[x]
%Para (t,y(t)), es igual, salvo que
%B=[y]
