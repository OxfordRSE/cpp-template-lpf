function [spectralPowerDensity,frequency,phase] = spectralPowerAndFrequency(timeSeries,fSamp,options)
% produces the single sided spectral power density of timeSeries using FFT
% timeSeries = rawData to be analysed, must be sampled at fixed frequency
% samplingFrequency = frequency of sampling for timeSeries
    L = length(timeSeries);
    if L==0
        error('spectralPowerAndFrequency: received timeSeries with unacceptable length L=%d \n',L);
    end
    if strcmp(options.DC,'subtract')
        A = timeSeries-mean(timeSeries);
    else
        A = timeSeries;
    end
    if strcmp(options.NFFT, 'nextPow2Low')
        NFFT = 2.^nextpow2(L)-1; % Next lower power of 2 from length of y
    elseif strcmp(options.NFFT, 'nextPow2High')
        NFFT = 2.^nextpow2(L)+1; % Next lower power of 2 from length of y
    elseif strcmp(options.NFFT, 'exact')
        NFFT = L;
    else
        error('spectralPowerAndFrequency: unknown option.NFFT = %s \n',option.NFFT)
    end
    Y = fft(A,NFFT);
    if mod(NFFT,2) == 0
        lastIndex = NFFT/2+1;
    else
        lastIndex = floor(NFFT/2) + 1;
    end 
    lastIndex;
    spectralPowerDensity = zeros(1, lastIndex);
    if strcmp(options.ampOrInt,'isAmplitude') 
        %fprintf('isAmplitude\n');
        spectralPowerDensity = (abs(Y(1:lastIndex)).^2)./L;
    elseif strcmp(options.ampOrInt,'isIntensity')
        %fprintf('isIntensity\n');
        spectralPowerDensity = (abs(Y(1:lastIndex)).^2)./L;
        %spectralPowerDensity = 1;
    else
        error('spectralPowerAndFrequency: unknown value of option ampOrInt = %s \n', options.ampOrInt);
    end
    %spectralPowerDensity(2:lastIndex-1) = 2*spectralPowerDensity(2:lastIndex-1);
    spectralPowerDensity(2:lastIndex-1) = 2*spectralPowerDensity(2:lastIndex-1);
    phase=angle(Y(1:lastIndex));
    frequency = fSamp/2.*linspace(0,1,lastIndex);
end

