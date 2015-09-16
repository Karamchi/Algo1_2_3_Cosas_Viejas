function temporalSegmentationSkeleton
    openVideoTest;
end

function openVideoTest  
    videoReader = VideoReader('/media/libre/oeci2015-cut.avi');   
    nFrames = videoReader.NumberOfFrames;    
    histH = 0;  
    histV = 0;
    j = 1;
    bhattacharyyaCoefs=zeros(nFrames);
    for k = 1 : nFrames
        %disp(['processing frame: ' num2str(k)]);
        U = read(videoReader, k); 
        nBins = 256; 
        normalize = 1;
        Uhsv = rgb2hsv(U);
        Uh = Uhsv(:,:,1);
        Uh = uint16(255 * Uh);
        Uv = uint16(255*Uhsv(:,:,3));
        
        Uvar=stdfilt(Uv);
        Uv=uint16(256*(Uvar./max(Uvar(:))));
        
        mask = uint16(ones(size(Uh)));
        %Remember to calculate the histogram of the variance
        prevHistH = histH;
        prevHistV = histV;
        
        histH = Hhist(Uh, mask, nBins, normalize);
        histV = Hhist(Uv, mask, nBins, normalize);
        
        %sum(sum(histH))
        if(sum(sum(prevHistH)) > 0)
            %implement here the custom bhattacharyya distance
            bhattacharyyaH = bhattacharyya(prevHistH, histH);
            bhattacharyyaV = bhattacharyya(prevHistV, histV);
            bhattacharyyaCoefs(j)=log(bhattacharyyaH*bhattacharyyaV);
            bhattacharyyaCoefs(j)
            j = j + 1;
        end
      
    end
    figure;     
    plot(bhattacharyyaCoefs);  
end

%0 to 255 values to build histogram in input image
function H = Hhist(I, mask, nBins,Nind)
     H = zeros(nBins,1);
     for i=1:nBins
         H(i) = sum(sum((I.*mask)==i));
     end
     H=H./sum(H(:)).*Nind;
end


function bdist = bhattacharyya(histogram1H, histogram2H)
    bdist=sqrt(1-(1/sqrt(mean(histogram1H)*mean(histogram2H)*256)*sum(sqrt(histogram1H).*sqrt(histogram2H))));

end