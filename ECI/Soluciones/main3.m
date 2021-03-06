
function main3
   mainVideoTest
end


function mainVideoTest
    videoReader = VideoReader('/media/libre/oeci2015-cut.avi');    
    %videoReader = VideoReader('../../input/seg/cut1_360_processed_LAB_2iter.avi');   
    nFrames = videoReader.NumberOfFrames;
    frameRate = videoReader.FrameRate;
    videoWriter = VideoWriter('/media/libre/segNoDBF.avi', 'Uncompressed AVI');
    videoWriter.FrameRate = frameRate;
    open(videoWriter);
    for k = 1 : nFrames
            disp(['processing frame: ' num2str(k)]);            
            U = read(videoReader, k);       
            F1 = segmentImage(U); 
            F1 = uint8(255*F1);
            writeVideo(videoWriter, F1);          
    end
    close(videoWriter);
    
end
%Calculates the football field mask
function BW2G = getFieldMask(Uh)
    Ufield = zeros(size(Uh));
    %green values
    Ufield(Uh > 0.16 & Uh < 0.22) = 1;
    Ufield = imfill(Ufield, 8, 'holes');
    numPixTot = size(Ufield,1) * size(Ufield,2);
    %eliminate spurious regions
    BW2 = bwareaopen(Ufield, 0.2 * numPixTot);
    BW2comp = imcomplement(BW2);
    BW2compG = bwareaopen(BW2comp, 0.1 * numPixTot);
    BW2G = imcomplement(BW2compG);
    %greek logo
    BW2G(1:85, 420:640) = 0;
end

function playersMask = getPlayersCandidatesMask(Uh)
    %lets use the chromatic information variance (Hue)    
    %layer h goes from 0 to 1
    Uh = uint8(255 * Uh);
    %asigne los parametros pertinentes
    Uvar = stdfilt(Uh, ones(5)).^2;
    %UvarNorm = uint8(255.0*(Uvar ./ max(Uvar(:))));
    Uvar(Uvar > 255) = 255;
    %otsu tresholding
    level = graythresh(Uvar);
    %applies the thresold
    Uvar01 = Uvar / 255;
    Uthresh = im2bw(Uvar01, level);
    %Uvar = uint8(Uvar);
    playersMask = imfill(Uthresh, 'holes');
end

%used parameters for the paper IWOBI 2014
function F = segmentImage(U)
    numPixTot = size(U,1) * size(U,2);
    %for simplification we take the image from row 85, to avoid banners and
    %audience
    %rowAudience = 1;
    %U = U(rowAudience:size(U,1), :,:);
    Uhsv = rgb2hsv(U);
    %lets use the chromatic information variance (Hue)
    Uh = Uhsv(:,:,1);
    fieldMask = getFieldMask(Uh);    
    playersCandsMask = getPlayersCandidatesMask(Uh);
    F = playersCandsMask & fieldMask;
    F = bwareaopen(F, floor(0.0007 * numPixTot));
    %H = Hhist(Uvar, ones(size(Uvar)), 256,1);
    %Hlog = log(H+1);
end

function H = Hhist(I, mask, nBins,Nind)
    I = uint16((nBins-1) * I);
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


%Shows the image on a window
function showOnWindow(U, name)
    figure; 
    T = uint8(U);
    imshow(T);
    title(name);
end


