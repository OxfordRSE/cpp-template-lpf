close all;
fRef = '../test_data/reference_filtered_chirp_fMax=6E+07_fSamp=1E+08.bin';
fFilt= '../test_data/filtered_chirp_fMax=6E+07_fSamp=1E+08.bin';
fIdRef = fopen(fRef,'r');
fIdFilt = fopen(fFilt,'r');
nBytes=8; % number of bytes per entry
sRef=dir(fRef);
sFilt=dir(fRef);
sizeRef = floor(sRef.bytes/nBytes);
sizeFilt= floor(sFilt.bytes/nBytes);
if sizeRef~=sizeFilt
    fprintf('size of reference data = %10.0',sizeRef);
    fprintf('size of filtered data = %10.0',sizeFilt);
    fclose(fIdRef);
    fclose(fIdFilt);
else
    size = sizeRef
    sRef = fread(fIdRef,[1,size],'double');
    sFilt = fread(fIdFilt,[1,size],'double');
    subplot(1,2,1);
    plot(sRef);
    hold on;
    plot(sFilt);
    legend('matlab filtered', 'C++ filtered');
    xlabel('data point number');
    ylabel('low pass filtered signal');
    title('filtered outpus from matlab and C++');
    subplot(1,2,2);
    plot(sRef-sFilt);
    xlabel('data point number');
    ylabel('matlab minus C++ outputs');
    title('difference of filters');
end
