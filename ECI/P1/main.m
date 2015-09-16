function main
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
        disp(['processing frame: ' num2str(k)]);
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

        if(sum(sum(prevHistH)) > 0)
            %implement here the custom bhattacharyya distance
            bhattacharyyaH = jeffrey(prevHistH, histH);
            bhattacharyyaV = jeffrey(prevHistV, histV);
            bhattacharyyaCoefs(j)=log(bhattacharyyaH*bhattacharyyaV);
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
    bdist=sqrt(1-(1/sqrt(mean(histogram1H)*mean(histogram2H)*65536)*sum(sqrt(histogram1H).*sqrt(histogram2H))));
end

function mino2 = minowsky2(H1, H2)
    mino2=sqrt(sum((H1-H2).^2))
end

function mino1 = minowsky1(H1, H2)
    mino1=sum(abs(H1-H2))
end

function jeff = jeffrey(H1, H2)
    M=(H1+H2);
    bdistV=(H1.*log(2*H1./M)+H2.*log(2*H2./M));
    jeff=0;
    for i = 1:size(bdistV)
	if (bdistV(i)>=0 || bdistV(i)<0) %Necesario para eliminar los casos en los que uno o ambos histogramas valen 0
	    jeff=jeff+bdistV(i);
	end
    end
end
