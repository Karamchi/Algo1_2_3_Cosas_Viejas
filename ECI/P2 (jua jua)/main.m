
function main
   mainVideoTest
end


function mainVideoTest
    videoReader = VideoReader('/media/libre/oeci2015-cut.avi') 
    nFrames = videoReader.NumberOfFrames;
    frameRate = videoReader.FrameRate;
    videoWriter = VideoWriter('/media/libre/cut1_360_preprocessed_LAB_2iter_.avi', 'Uncompressed AVI');
    videoWriter.FrameRate = frameRate;
    open(videoWriter);
    for k = 1 : 1
            disp(['processing frame: ' num2str(k)]);            
            U = read(videoReader, k);       
            F1 = processImage(U);    
	    figure; 
            imshow(F1);       
            writeVideo(videoWriter, F1);
           %end
    end
    close(videoWriter);
    
end
%used parameters for the paper IWOBI 2014
function F = processImage(U)
    %asigne los parametros pertinentes
    wSize = 21; sigma_s = wSize/3; sigma_r = 5; lambda = 2;
    fBilD = filterDeceivedBilateral(U, wSize, sigma_s, sigma_r, lambda); 
    fBilD = uint8(fBilD);
    F = fBilD;
end

%Input image must be from 0 to 255
function F = filterDeceivedBilateral(U, wSize, sigma_s, sigma_r, lambda)   
    %the image has to to have values from 0 to 1
    Unorm = double(U)/255;     
    sigma = [sigma_s, sigma_r];
    F = bfilterDeceived(Unorm, wSize, sigma, lambda);   
    %putting back everything
    F = 255 * F;
end

%Shows the image on a window
function showOnWindow(U, name)
    figure; 
    T = uint8(U);
    imshow(T);
    title(name);
end


