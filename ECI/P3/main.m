
function main
   mainVideoTest
end


function mainVideoTest
    videoReader = VideoReader('/media/libre/oeci2015-cut.avi');   
    nFrames = videoReader.NumberOfFrames;
    frameRate = videoReader.FrameRate;
    videoWriter = VideoWriter('/media/libre/out.avi', 'Uncompressed AVI');
    videoWriter.FrameRate = frameRate;
    open(videoWriter);
    for k = 1 : 1
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
	lim=graythresh(Uh);
	%playersMask=Uh > lim;
	aux=im2bw(Uh,lim);
    aux = imfill(aux, 8, 'holes');
    %numPixTot = size(aux,1) * size(aux,2);
    %BW2 = bwareaopen(aux, 0.2 * numPixTot);
    %BW2comp = imcomplement(BW2);
    %BW2compG = bwareaopen(BW2comp, 0.1 * numPixTot);
    %BW2G = imcomplement(BW2compG);
	playersMask=aux;
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
    %UH=Uh/max(Uh(:));
    fieldMask = getFieldMask(Uh);    
    %Uh = Uhsv(:,:,3);
    Uh = Uh*255;
    Uh = stdfilt(Uh).^2/255;
    H = Hhist(log(Uh)/log(255), ones(size(Uh)), 256,0);
    for i=1:size(H)-1
	if (H(i)>H(i+1))
		H(i)=H(i+1);
	end
    end
	%Uh=uint16(256*(Uh./max(Uh(:))));
    playersCandsMask = getPlayersCandidatesMask(Uh);
%    F = playersCandsMask & fieldMask;
    F = playersCandsMask;
    F = bwareaopen(F, floor(0.00009 * numPixTot));
    %H = Hhist(Uvar, ones(size(Uvar)), 256,1);
    %Hlog = log(H+1);
end

function H = Hhist(I, mask, nBins,Nind)
    I = uint16((nBins-1) * I);
    if(nargin<3)
        Nind=0;
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
    if(Nind==1)
        H = H./sum(H);
    end
    H(1)=0;
end


%Shows the image on a window
function showOnWindow(U, name)
    figure; 
    T = uint8(U);
    imshow(T);
    title(name);
end


