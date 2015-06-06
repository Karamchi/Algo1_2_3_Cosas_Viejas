%% leo imagen de entrada
close all, clear all;
I = imread('~/metodos/Taller1/Codigo/Senales/64x64/lena.pgm');
I = imread('~/metodos/Taller1/Codigo/Senales/64x64/fingerprint.pgm');
%I = imread('~/metodos/Taller1/Codigo/Senales/256x256/flinstones.pgm');
%I = imread('~/metodos/Taller1/Codigo/Senales/256x256/ladrillos.pgm');
% I = imread('~/Senales/Senaleslena.pgm');
% I = imread('~/Senales/Senaleslena.pgm');

figure,imshow(I),title('Imagen original');

%% agrego ruido uniforme 
sr = 64; % a partir de 64 (aprox) el filtrado vale la pena
IR = double(I) + randi([-sr,sr], size(I));
IR = uint8(IR);
figure,imshow(IR),title(['Imagen ruidosa. Interv=+-' num2str(sr)]);

%% Armado del sistema
Lambda = 1;
Dim = size(IR);
NInc = prod(Dim);

% Armado del vector resultado
Utilde = Lambda*double(IR(:));

% Armado de la matriz a resolver
B = -1*ones(NInc,5);
B(:,3) = (Lambda+4)*ones(NInc,1);
d = [-Dim(1) -1 0 1 Dim(1)];
A = spdiags(B,d,NInc,NInc);

%% Ej 2)
%Contraejemplo de matriz simétrica que no es SDP:
A2=[-1 0;0 -1]
%Contraejemplo de matriz definida positiva no simétrica:
B2=[1 1;0 1]


%% P2) 7)
s=size(A,1)

for i = (1:s),
    A=A(1:s-i, 1:s-i)
    if abs(det(A))<=10.^-8, 
         error('Hay una submatriz singular, entonces no tiene factorizacion LU');
    end
end


%% Ej 4)
%Ejemplo de matriz inversible que no tiene factorización LU:
A4= [1 0 0;0 0 1;0 1 0]          
%Demostración de que LU implica inversible:
%A=LU

%Sabemos que existe U^(-1) y L^(-1) porque son U y L son triangulares.
%=>Existe su producto
%U^(-1)·L^(-1)=(LU)^(-1)=A^(-1)

        
%% Vectores aleatorios para ver si es defpos (solo para imagenes de 64x64)

s=size(A,1)
for i=(1:1000),
    x=rand(1,s)
    res=x*A*x'
    if res<=-10.^-8,
        error('No es simétrica definida positiva')
    end  
end

%% P3) 7) a)
% A_ii > 0 para todo 1 <= i <= n
s=size(A,1)
for i=(1:s),
    if A(i,i)<=10.^-8,
        error('Un punto de la diagonal no es positivo')
    end
end

%% P3) 7) b)
% A es no singular

if abs(det(A)) <= 10.^-8,
    error('A es singular')
end
%% P3) 7) c)
% Todas las submatrices principales de A son definidas positivas:
% Sylvester's Criterion (solo para imagenes de 64x64 y aun asi puede tardar unos minutos)


s=size(A,1)

for i = (1:s),
    A=A(1:s-i, 1:s-i)
    h=eig(A)
    for j=(1:size(h)),
        if h(j,1)<=10^-8,
            error ('No es definida positiva')
        end
    end 
end

%% P3) 7) d)
% |A_ii|^2 <= A_ii * A_jj para todo 1 <= i, j <= n

s=size(A,1)

for i=(1:s),
    for j=(1:s),
        if A(i,j).^2 > A(i,i)*A(j,j),
            error ('El cuadrado de un elemento cualquiera es mayor a la multiplicacion de dos elementos de la diagonal')
        end
    end
end

%% Resolucion del sistema

% Resolucion directa
Usol = A\Utilde;

% Resolucion cholesky de matlab
L = chol(A,'lower');
Usol = (L'\(L\Utilde));
 
% Resolucion cholesky por bloques
L = CholFromBlocks(A);
Usol =(L'\(L\Utilde));

% Resolucion cholesky LU
%L = CholFromLU(A);
Usol =(L'\(L\Utilde));

% Escalamiento y reshape para mostrar la imagen
Usol = Usol - min(Usol);
Usol = Usol / max(Usol);
Usol = uint8(Usol*255);
IFS = reshape(Usol,Dim);

figure,imshow(IFS);
figure,imshow([I,IR,IFS]),title(['Imagen filtrada, lambda=' num2str(Lambda)]);
%% calculo psnr
[p,m] = psnr(I(2:end-1,2:end-1), IR(2:end-1,2:end-1));

fprintf('Calidad imagen ruidosa.\n');
fprintf('PSNR=%g, ECM=%g\n',p,m);

[p,m] = psnr(I(2:end-1,2:end-1), IFS(2:end-1,2:end-1));
fprintf('Calidad imagen filtrada.\n');
fprintf('PSNR=%g, ECM=%g\n',p,m);

%%
figure;
S1 = edge(I,'canny');
S2 = edge(IR,'canny');
S3 = edge(IFS,'canny');
imshow([S1,S2,S3]);
