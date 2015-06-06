function A = cargarPortadora(rutaImagen),
    A = imread(rutaImagen);
    if size(A,3) ~= 1,
        A = rgb2gray(A);
    end
    A = ajustarTamanio(A); % para que filas y columnas sean multiplo de 4