% mapeoAleatorio(fila,col,:) indica para cada pixel de watermark
% ubicado en (fila,col), cuales son las dos coordenadas del bloque que
% le corresponde en A (OJO QUE LAS COORDENADAS SON DEL BLOQUE, NO DE UN
% PIXEL EN A).
function mapeoAleatorio = mapearBitsABloquesAleatorios(imagen, wm, seed)
    % Cada pixel de watermark debe tener una coordenada en la división en bloques de la imágen portadora
    cantPixelsWM = size(wm,1)*size(wm,2); % cantidad de coordenadas random a generar
    m = size(imagen,1)/4;
    n = size(imagen,2)/4;
    % las coordenadas estarán en el rango ([1...m],[1...n]) (m = cantidad de bloques de 4x4 en filas, n = cant bloq 4x4 en columnas)
    
    % hay m*n pares ordenados cuyas coordenadas caen en ([1...m],[1...n])
    % entonces tomamos una permutación aleatoria de los números {1...m*n}, y
    % nos quedamos con los cantPixelsWM primeros (nos queda un número para cada píxel de
    % watermark).
    rand_stream = RandStream('mt19937ar','Seed',seed); % esto marca un seed (para que siempre obtenga lo mismo con el randperm)
    if m*n < cantPixelsWM,
        error('Hay más pixels en la marca de agua que bloques en la portadora.');
    end
    numerosAleatorios = randperm(rand_stream,m*n,cantPixelsWM);
    
    % Ahora mapeamos cada número a un par ordenado distinto (numero por filas los
    % elementos de una matrix de m filas y n columnas)
    paresAleatorios = zeros(size(wm,1),size(wm,2),2); % un par para cada pixel de watermark
    % Recorro los pixels de watermark y a cada uno le asigno un bloque en
    % la imagen A.
    for fila_wm=1:size(wm,1),
        for col_wm=1:size(wm,2),
            i = (fila_wm-1)*size(wm,2) + col_wm;                % mapeo de las coordenadas del pixel de watermark a un índice en el vector de numeros aleatorios
            fila    = floor((numerosAleatorios(i)-1)/n)+1;      % Ahora mapeo el numero aleatorio a un bloque de la imagen A.
            columna = mod((numerosAleatorios(i)-1),n)+1;        % Esto indica numero de bloque (en fila y columna), no la fila y columna de A.
            paresAleatorios(fila_wm,col_wm,1) = fila;
            paresAleatorios(fila_wm,col_wm,2) = columna;
        end
    end
    % paresAleatorios(fila,col,:) indica para cada pixel de watermark
    % ubicado en (fila,col), cuales son las dos coordenadas del bloque que
    % le corresponde en A (OJO QUE LAS COORDENADAS SON DEL BLOQUE, NO DE UN
    % PIXEL EN A).
    mapeoAleatorio = paresAleatorios;