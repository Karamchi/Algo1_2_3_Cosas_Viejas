%% Primero testeamos hallarSVD:
tol = 9999e-4;
tol_svd = 1e-5;

rng(0);

for rangoDeA = 1:4, % es probabilistico
    for it = 1:500,
        A = floor(255.9999.*rand(rangoDeA,4)); % matriz random entre 0 y 255 (pixels)
        
        if rangoDeA == 1,
            multiplicador = rand();
            A(2,:) = multiplicador*A(1,:);
            multiplicador = rand();
            A(3,:) = multiplicador*A(1,:);
            multiplicador = rand();
            A(4,:) = multiplicador*A(1,:);
        elseif rangoDeA == 2,
            promedio = rand();
            A(3,:) = promedio*A(1,:) + (1-promedio)*A(2,:);
            promedio = rand();
            A(4,:) = promedio*A(1,:) + (1-promedio)*A(2,:);
        elseif rangoDeA == 3,
            promedio1 = rand();
            promedio2 = (1-promedio1)*rand(); % promedio2 in [0...1-promedio1]
            A(4,:) = promedio1*A(1,:) + promedio2*A(2,:) + (1-promedio1-promedio2)*A(3,:);
        end
        
        [U1,S1,V1] = svd(A);
        [U2,S2,V2] = hallarSVD(A,tol_svd);
        
        if    min(min(abs(U2*S2*V2' - A) < tol)) == 0 || min(min(abs(S2-S1) < tol))         == 0 ...
           || min(min(abs(U2*U2'-eye(4)) < tol)) == 0 || min(min(abs(V2*V2'-eye(4)) < tol)) == 0,
            disp(rangoDeA);
            disp(min(min(abs(U2*S2*V2' - A) < tol)));
            disp(min(min(abs(S2-S1) < tol)));
            disp(min(min(abs(U2*U2'-eye(4)) < tol)));
            disp(min(min(abs(V2*V2'-eye(4)) < tol)));
            error('Hay error numérico en hallarSVD.');
        end
    end
end

% Un caso especial...
A = 0.8902 * ones(4);
[U1,S1,V1] = svd(A);
[U2,S2,V2] = hallarSVD(A,tol_svd);
if    min(min(abs(U2*S2*V2' - A) < tol)) == 0 || min(min(abs(S2-S1) < tol))         == 0 ...
   || min(min(abs(U2*U2'-eye(4)) < tol)) == 0 || min(min(abs(V2*V2'-eye(4)) < tol)) == 0,
    disp(rangoDeA);
    disp(min(min(abs(U2*S2*V2' - A) < tol)));
    disp(min(min(abs(S2-S1) < tol)));
    disp(min(min(abs(U2*U2'-eye(4)) < tol)));
    disp(min(min(abs(V2*V2'-eye(4)) < tol)));
    error('Falló el caso especial...');
end

% Otro caso especial...
A = [ 1 1 0 1; 1 1 1 1; 0 0 0 0; 1 1 1 1];
[U1,S1,V1] = svd(A);
[U2,S2,V2] = hallarSVD(A,tol_svd);
if    min(min(abs(U2*S2*V2' - A) < tol)) == 0 || min(min(abs(S2-S1) < tol))         == 0 ...
   || min(min(abs(U2*U2'-eye(4)) < tol)) == 0 || min(min(abs(V2*V2'-eye(4)) < tol)) == 0,
    disp(rangoDeA);
    disp(min(min(abs(U2*S2*V2' - A) < tol)));
    disp(min(min(abs(S2-S1) < tol)));
    disp(min(min(abs(U2*U2'-eye(4)) < tol)));
    disp(min(min(abs(V2*V2'-eye(4)) < tol)));
    error('Falló el otro caso especial...');
end

disp('hallarSVD ... OK');


%% Test con esteganografia

% steganography(imPortadora, watermark, T, tolerancia, seed);
steganography('../imagenes/lena.png','../watermarks/wm-2.png',5e-2,1e-5,0);

%steganography('../imagenes/lena.png','../watermarks/wm-1.png',5e-2,1e-5,0)



%%% Mas ruido
%steganography('../imagenes/paisaje.png','../watermarks/wm-1.png',5e-2,1e-5,0)

%%% Menos ruido
%steganography('../imagenes/habitacion_lisa.png','../watermarks/wm-1.png',5e-2,1e-5,0)

%%% Imagenes lisas
%steganography('../imagenes/negro.png','../watermarks/wm-1.png',1e-2,1e-5,0)
%steganography('../imagenes/blanco.png','../watermarks/wm-1.png',1e-2,1e-5,0)
