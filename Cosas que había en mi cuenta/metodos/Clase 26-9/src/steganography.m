%% Parámetros:
% rutaImagen    = string con la ruta a la imágen donde vamos a embeber el 
%                 watermark.
% rutaWatermark = ídem para la imágen del watermark. Debe ser "chica"
%                 (30x30 aprox).
% tol           = La tolerancia debajo de la cual un float se considera
%                 cero. Por default vale 1e-5.
% seed          = Semilla para la selección de bloques aleatorios en la
%                 imágen (donde se guarda cada bit del watermark). Por
%                 default vale 0.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function steganography(rutaImagen, rutaWatermark, T,  tol, seed)
    % Argumentos default
    if nargin < 3,
        T = 5e-2;
    end
    if nargin < 4,
        tol = 1e-5;
    end
    if nargin < 5,
        seed = 0;
    end
    
    % Levantamos datos
    A  = cargarPortadora(rutaImagen);
    wm = cargarWatermark(rutaWatermark);
    
    figure(1); imshow(A); title('IMAGEN ORIGINAL');
    figure(2); imshow(wm); title('WATERMARK ORIGINAL'); truesize(size(wm).*15);

    paresAleatorios = mapearBitsABloquesAleatorios(A,wm,seed);
    
    
    
    imwrite(A,'portadora.png');
    %% Codificación de bits

    % Esto pasa la imagen en escala de grises al rango [0,1] para trabajar
    % en doubles. Si T >> 1 y algun elemento de la matriz supera 1, se
    % satura cuando se pasa de vuelta a imagen.
    A = im2double(A);

    % A es la imagen completa portadora (grayscale, es decir 1 capa)
    % wm es la imagen para esconder (binaria)

    for fila_wm=1:size(wm,1),
        for col_wm=1:size(wm,2),
            % ¿en que bloque vamos a codificar este bit de watermark?
            bloque_coord = [paresAleatorios(fila_wm,col_wm,1), paresAleatorios(fila_wm,col_wm,2)];
            % ¿donde esta ese bloque en la imagen A? (los bloques son de 4x4)
            % (posicion i,j en la matriz A del elemento sup izq del bloque)
            pos_en_A = (bloque_coord.*4)-3;
            % Ahora si, el bloque:
            B_k = A(pos_en_A(1):pos_en_A(1)+3 , pos_en_A(2):pos_en_A(2)+3);
            
            % SVD: B_k = U*S*V'
            [U,S,V] = hallarSVD(B_k,tol);
            
            % Codificar 1 o 0:
            S(3,3) = S(2,2);
            if wm(fila_wm, col_wm) == 1,
                S(2,2) = S(2,2) + T;
            end
            if S(1,1) < S(2,2),
                S(1,1) = S(2,2);
            end
            B_k = U*S*V';
            
            % Impactar cambios de B_k en A:
            A(pos_en_A(1):pos_en_A(1)+3 , pos_en_A(2):pos_en_A(2)+3) = B_k;
        end
    end
    
    % Simulamos guardado en un archivo en escala de grises (es lo mismo que
    % hace imwrite()) A vuelve a ser una imagen
    A = uint8(255*mat2gray(A, [0 1]));
    
    figure(3);
    imshow(A);
    title('IMAGEN + WATERMARK');
    
    
    %% Extraer watermark:
    
    A = im2double(A);
    
    wm_extracted = zeros(size(wm,1),size(wm,2));

    for fila_wm=1:size(wm,1),
        for col_wm=1:size(wm,2),
            % ¿en que bloque tenemos codificado este bit de watermark?
            bloque_coord = [paresAleatorios(fila_wm,col_wm,1), paresAleatorios(fila_wm,col_wm,2)];
            % ¿donde esta ese bloque en la imagen A? (los bloques son de 4x4)
            % (posicion i,j en la matriz A del elemento sup izq del bloque)
            pos_en_A = (bloque_coord.*4)-3;
            % Ahora si, el bloque:
            B_k = A(pos_en_A(1):pos_en_A(1)+3 , pos_en_A(2):pos_en_A(2)+3);
            
            % SVD: B_k = U*S*V'
            [U,S,V] = hallarSVD(B_k,tol);
            
            % Decodificar 1 o 0:
            if S(2,2) - S(3,3) > T/2,
                wm_extracted(fila_wm,col_wm) = 1;
            else
                wm_extracted(fila_wm,col_wm) = 0;
            end
        end
    end

    figure(4);
    imshow(wm_extracted);
    truesize(size(wm).*15);
    title('WATERMARK RECUPERADA');
    
    % error = cantidad de bits mal reconstruidos
    error = sum(sum(~((wm_extracted & wm) | (~wm_extracted & ~wm))));
    disp(['El error en la reconstrucción fue de ',num2str( 100*error/(size(wm,1)*size(wm,2)) ),' %']);