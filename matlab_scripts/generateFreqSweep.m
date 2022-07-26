%% Generate frequency sweep signal for low pass filter testing
close all;
fSamp = 125E6; % Sampling frequency 
fMin = 0.0; % minimum frequency in Hz
fMax = fSamp/2; % max ....
tMax=0.01;
g=2*pi*fMin;
dOmega = 2*pi()*(fMax-fMin);
a=dOmega/tMax; %after time tMax we need to have swept from fMin to f=fSamp/2;
%%
N=1000;
nPad = N/2;       % filter order 
t=linspace(0,tMax,fSamp*tMax);
S=sin((g+a/2.*t).*t); % create chirp signal

% Write out configuration to json
config.fs = fSamp;
config.fMin = fMin;
config.fMax = fMax;
config.tMin = 0;
config.tMax = tMax;
config.filterOrder = N;
configJson = jsonencode(config);
fid = fopen('../test_data/chirp_signal.txt','w');
fprintf(fid, configJson);
fclose(fid);

% write chirp signal to binary file
dataFilePath=sprintf('../test_data/chirp_signal.bin');
dataFileID = fopen(dataFilePath,'w');
fwrite(dataFileID,S,'double');
fclose(dataFileID);

% padding the time and unfiltered signal so that FFT comparison of
% filtered and non filtered signal can be made
tPadded=linspace(0,tMax+nPad/fSamp,length(t)+nPad);
sPadded = zeros(length(S)+nPad,1);
sPadded(nPad+1:end)=S;

% performing FFT of the unfiltered signal
options.DC='keep';
options.NFFT='exact';
options.ampOrInt='isAmplitude';
[spectralPowerDensity,frequency,phase] = spectralPowerAndFrequency(sPadded,fSamp,options);

subplot(3,2,1);
plot(tPadded,sPadded);
signalAxis1=gca;
title('raw signal');
xlabel('time [s]');
ylabel('Ampl. [arb.]');

subplot(3,2,2);
plot(frequency,spectralPowerDensity);
fourierAxis1=gca;
title('FFT of raw Signal');
xlabel('frequency [Hz]');
ylabel('Spectral Power Density [arb/Hz]');

% generate the filter coefficients
coeff = lowPassFilterDesign();

sFiltered = filter(coeff, 1, S);

% write the filtered signal in binary
filteredDataFilePath=sprintf('../test_data/reference_filtered_chirp_signal.bin');
filteredDataFileID = fopen(filteredDataFilePath,'w');
fwrite(filteredDataFileID,sFiltered,'double');
fclose(dataFileID);

subplot(3,2,3);
plot(t,sFiltered);
signalAxis2=gca;
title('filtered dataset');
xlabel('time in [s]');
ylabel('filtered signal [arb]');

sFilteredPadded=zeros(length(sPadded),1);
sFilteredPadded(1:end-nPad)=sFiltered;
[filteredspectralPowerDensity,filteredFrequency,filteredPhase] = spectralPowerAndFrequency(sFilteredPadded,fSamp,options);
subplot(3,2,4)
plot(filteredFrequency,filteredspectralPowerDensity);
fourierAxis2=gca;
title('FFT of filtered Signal');
xlabel('frequency [Hz]');
ylabel('Spectral Power Density [arb/Hz]');

sDiff=sPadded-sFilteredPadded;
subplot(3,2,5);
plot(tPadded,sDiff);
signalAxis3=gca;
title('raw-filtered signal');
xlabel('time [s]');
ylabel('Ampl. [arb.]');

spectralDiff=spectralPowerDensity-filteredspectralPowerDensity;
subplot(3,2,6)
plot(filteredFrequency,spectralDiff);
fourierAxis3=gca;
title('FFT-Raw - FFT-filtered');
xlabel('frequency [Hz]');
ylabel('difference of Spectral Power Densities [arb/Hz]');

linkaxes([signalAxis2, signalAxis1],'xy');
linkaxes([fourierAxis2, fourierAxis1],'xy');
linkaxes([signalAxis1, signalAxis3],'x');
linkaxes([fourierAxis1, fourierAxis3],'x');


