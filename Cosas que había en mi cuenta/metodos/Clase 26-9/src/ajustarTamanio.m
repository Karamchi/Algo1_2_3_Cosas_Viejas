% Toma una imágen y elimina las últimas filas/columnas tal que tenga
% cantidad de filas y de columnas múltiplo de 4.
function A = ajustarTamanio(imagen)
    filas    = size(imagen,1);
    columnas = size(imagen,2);
    
    filas    = filas    - mod(filas,4);
    columnas = columnas - mod(columnas,4);
    A = imagen(1:filas,1:columnas);