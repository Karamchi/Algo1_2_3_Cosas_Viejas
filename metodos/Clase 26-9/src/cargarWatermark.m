function wm=cargarWatermark(rutaArchivo)
    wm = imread(rutaArchivo);
    if size(wm,3) ~= 1,
        wm = rgb2gray(wm);
    end
    if ~islogical(wm),
        wm = im2bw(wm, 0.8); % pasar a imagen binaria
    end