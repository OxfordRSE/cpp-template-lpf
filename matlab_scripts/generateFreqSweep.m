% generate frequency sweep signal for LPF testing
close all;
fSamp = 125E6; % 
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
tPadded=linspace(0,tMax+nPad/fSamp,length(t)+nPad);
S=10*sin((g+a/2.*t).*t);
sPadded = zeros(length(S)+nPad,1);
sPadded(nPad+1:end)=S;
options.DC='keep';
options.NFFT='exact';
options.ampOrInt='isAmplitude';
[spectralPowerDensity,frequency,phase] = spectralPowerAndFrequency(sPadded,fSamp,options);
subplot(3,2,1);
plot(tPadded(1:end),sPadded(1:end));
signalAxis1=gca;
title('raw signal');
xlabel('time [s]');
ylabel('Ampl. [arb.]');
%
subplot(3,2,2);
plot(frequency,spectralPowerDensity);
fourierAxis1=gca;
title('FFT of raw Signal');
xlabel('frequency [Hz]');
ylabel('Spectral Power Density [arb/Hz]');
%
Fs = fSamp;     % sampling frequency 
Fp = 1.3e6;      % passband edge in Hz
Ap = 0.01;     % passband ripple in dB
Ast = 80;      % stopband attenuation in dB
Rp = (10^(Ap/20) - 1)/(10^(Ap/20) + 1);  % passband ripple in linear values
Rst = 10^(-Ast/20);  % stop band attenuation in linear values
NUM = firceqrip(N,Fp/(Fs/2),[Rp Rst],'passedge');
sFiltered = filter(NUM,1,S);
subplot(3,2,3);
plot(t,sFiltered);
signalAxis2=gca;
title('filtered dataset');
xlabel('time in [s]');
ylabel('filtered signal [arb]');
%
sFilteredPadded=zeros(length(sPadded),1);
sFilteredPadded(1:end-nPad)=sFiltered;
[filteredspectralPowerDensity,filteredFrequency,filteredPhase] = spectralPowerAndFrequency(sFilteredPadded(1:end),fSamp,options);
subplot(3,2,4)
plot(filteredFrequency,filteredspectralPowerDensity);
fourierAxis2=gca;
title('FFT of filtered Signal');
xlabel('frequency [Hz]');
ylabel('Spectral Power Density [arb/Hz]');
%
sDiff=sPadded-sFilteredPadded;
subplot(3,2,5);
plot(tPadded,sDiff);
signalAxis3=gca;
title('raw-filtered signal');
xlabel('time [s]');
ylabel('Ampl. [arb.]');
%
spectralDiff=spectralPowerDensity-filteredspectralPowerDensity;
subplot(3,2,6)
plot(filteredFrequency,spectralDiff);
fourierAxis3=gca;
title('FFT-Raw - FFT-filtered');
xlabel('frequency [Hz]');
ylabel('difference of Spectral Power Densities [arb/Hz]');
%
linkaxes([signalAxis2, signalAxis1],'xy');
linkaxes([fourierAxis2, fourierAxis1],'xy');
linkaxes([signalAxis1, signalAxis3],'x');
linkaxes([fourierAxis1, fourierAxis3],'x');


