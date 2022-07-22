%% Compares the filtered output of the MATLAB filter function to that of the C++ implementation 
close all;
fRef = '../test_data/reference_filtered_chirp_fMax=6.25E+07_fSamp=1.25E+08.bin'; % MATLAB data
fFilt= '../test_data/filtered_chirp_fMax=6.25E+07_fSamp=1.25E+08.bin'; % C++ data
fSamp = 1.25e0;
fMax = 6e07;

fIdRef = fopen(fRef,'r');
fIdFilt = fopen(fFilt,'r');
nBytes=8; % number of bytes per entry
sRef=dir(fRef);
sFilt=dir(fRef);
sizeRef = floor(sRef.bytes/nBytes);
sizeFilt= floor(sFilt.bytes/nBytes);
if sizeRef~=sizeFilt
    fclose(fIdRef);
    fclose(fIdFilt);
    error('data files are of different sizes')
    
else
    size = sizeRef;
    sRef = fread(fIdRef,[1,size],'double');
    sFilt = fread(fIdFilt,[1,size],'double');
    
    t = linspace(0, size/fSamp, size);
    figure;
    subplot(1,3,1);
    plot(t, sRef);
    hold on;
    plot(t, sFilt);
    legend('MATLAB filtered', 'C++ filtered');
    xlabel('time [s]');
    ylabel('signal [Arb]');
    title('filtered output from MATLAB and C++');
    subplot(1,3,2);
    plot(sRef-sFilt);
    xlabel('time [s]');
    ylabel('MATLAB minus C++ signal');
    title('difference of C++ and MATLAB outputs');
    subplot(1,3,3);
    plot(sRef,sRef-sFilt);
    xlabel('Reference signal');
    ylabel('MATLAB minus C++ outputs');
    title(' C++ - MATLAB outputs against signal amplitude');
  
end
