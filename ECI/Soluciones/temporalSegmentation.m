function temporalSegmentation
    openVideoTest;
end

function openVideoTest
    videoReader = VideoReader('../../input/seg/oeci2015-cut.avi');    
    nFrames = videoReader.NumberOfFrames;    
    histH = 0;  
    histV = 0;
    j = 1;
    for k = 1 : nFrames
        disp(['processing frame: ' num2str(k)]);            
        U = read(videoReader, k); 
        nBins = 256; 
        normalize = 1;
        Uhsv = rgb2hsv(U);
        Uh = Uhsv(:,:,1);
        Uh = uint16(255 * Uh);
        Uv = uint16(255*Uhsv(:,:,3));
        Uvar = stdfilt(Uv);
        Uvar = uint8(255 * (Uvar ./ max(Uvar(:))));
        mask = ones(size(U));
        prevHistH = histH;
        prevHistV = histV;
        
        histH = Hhist(Uh, mask, nBins, normalize);
        histV = Hhist(Uvar, mask, nBins, normalize);
        
        if(sum(prevHistH) > 0)
            %implement here the custom bhattacharyya distance
            bhattacharyyaH = bhattacharyya(prevHistH, histH);
            bhattacharyyaV = bhattacharyya(prevHistV, histV);
            bhattacharyyaCoefs(j) = bhattacharyyaH * bhattacharyyaV;%log(bhattacharyyaH * bhattacharyyaV);
            j = j + 1;
        end
      
    end
    figure;
    plot(bhattacharyyaCoefs);  
end

%0 to 255 values to build histogram in input image
function H = Hhist(I, mask, nBins,Nind)
      

    if(nargin<3)
        Nind=0;
        % Default is un-normalized histogram
    end
    H=zeros(nBins, 1);
    for i=1:size(I,1)
        for j=1:size(I,2)
            if(mask(i, j) == 1)   
                val = I(i,j) + 1;               
                H(val) = H(val) + 1; 
            end
        end
    end
    % Un-Normalized histogram
    if(Nind==1)
        H = H./sum(H);
        % l1 normalization    
    end
end


function bdist = bhattacharyya(histogram1H, histogram2H)
    bins = size(histogram1H, 1);
    mean1H = double(mean(histogram1H));
    mean2H = double(mean(histogram2H));
    bcoeffSum = 0;
    for i=1:bins
        bcoeffSum = bcoeffSum + sqrt(double(histogram1H(i) * histogram2H(i)));
    end
    c1 = 1.0 / (sqrt(mean1H * mean2H * bins * bins));
    bdist = sqrt(1.0 - c1 * bcoeffSum);
    if(bdist == Inf)
        %bcoeff = 1;
        disp('suave');
    end

end