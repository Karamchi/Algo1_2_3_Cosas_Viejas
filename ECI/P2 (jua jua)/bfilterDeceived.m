
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Pre-process input and select appropriate filter.
function B = bfilterDeceived(A, w, sigma, lambda)  
    if ~isfloat(A) || ~sum([1,3] == size(A,3)) || ...
          min(A(:)) < 0 || max(A(:)) > 1
       error(['Input image A must be a double precision ',...
              'matrix of size NxMx1 or NxMx3 on the closed ',...
              'interval [0,1].']);      
    end
    % Apply either grayscale or color bilateral filtering.
    if size(A,3) == 3
       B = bfltColorDeceived(A, w, sigma(1),sigma(2), lambda);     
    end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Implements bilateral filter for color images.
%sigma range is multiplied by 100
function B = bfltColorDeceived(A, w, sigma_d,sigma_r, lambda)    
    % Convert input sRGB image to CIELab color space. 
    disp('using the CIELAB color space')
    %CIE LAB AB values go from 0 to 100
    A = colorspace('Lab<-RGB', A); 
    L =  filterUM_laplacianLAB(A, lambda);  
    B = bfil2LAB_deceived(A, L, w, sigma_d,sigma_r);
    % Convert filtered image back to sRGB color space.   
    B = colorspace('RGB<-Lab',B);
end



function B = bfil2LAB_deceived(A, Laplacian, w, sigma_d,sigma_r)
   [X,Y] = meshgrid(1:size(A,1), 1:size(A,2));
   G = exp(-X.^2-Y.^2)/(2*sigma_d^2);
   for i = 1:size(A,1)
       for j=2:size(A,2)
            iMin = max(i-w,1);
            iMax = min(i-w,size(A,1));
            jMin = max(j-w,1);
            jMax = min(j-w,size(A,2));
            I=A(iMin:iMax,jMin:jMax,:);
            L=Laplacian(iMin:iMax,jMin:jMax,:);
            %"Gaussian range weights"
            dL = I(:,:,1) -A(i,j,1);
            da = I(:,:,2) -A(i,j,2);
            db = I(:,:,3) -A(i,j,3);
            H = exp(-(dL.^2+da.^2+db.^2)/(2+sigma_r^2));
            %"Bilateral filter response"
            F = H.*G((iMin-i+w+1:iMax-i+w+1),(jMin-j+w+1:jMax-j+w+1));
            norm_F=sum(F(:));
            %"The Laplacian deceive consists on weighting the gaussian function with the original image, and using the image values of the laplacian image"
            B(i,j,1) = sum(sum(F.*L(:,:,1)))/norm_F;
            B(i,j,2) = sum(sum(F.*L(:,:,2)))/norm_F;
            B(i,j,3) = sum(sum(F.*L(:,:,3)))/norm_F;
       end
   end
end

%Regular non adaptive unsharped masking with laplacian filter
%normalizacion incorrecta
%Tercer metodo a utilizar
function F = filterUM_laplacianLAB(U, lambda1)
    Z = filterLaplacian2(U);   
    lim = max(U(:));
   % normalization
    maxZ = max(abs(Z(:)));
    Z = lim * (Z ./ maxZ);
    %unsharp masking
    F = U + lambda1 .* Z; 

end
%applies a 11x11 laplacian mask
function F = filterLaplacian2(U)
    h =  fspecial('log', 17, 0.005);
    h =  -h;
    F = imfilter(U, h); 
end
