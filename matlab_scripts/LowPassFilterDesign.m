N = 1000;       % filter order 
Fs = 125e6;     % sampling frequency 
Fp = 1.3e6;      % passband edge in Hz
Ap = 0.01;     % passband ripple in dB
Ast = 80;      % stopband attenuation in dB
Rp = (10^(Ap/20) - 1)/(10^(Ap/20) + 1);  % passband ripple in linear values
Rst = 10^(-Ast/20);  % stop band attenuation in linear values
NUM = firceqrip(N,Fp/(Fs/2),[Rp Rst],'passedge');
fvtool(NUM,'Fs',Fs)
filterCoeffs=tf(NUM);
numerator=filterCoeffs.Numerator;
coeffs=cell2mat(numerator)'
coeffFilePath = 'H:\PaMIr\Source code\Robinson_LPF_example\out-of-core-low-pass-filter\cmake-build-debug\filterCoeff.dat';
coeffFileID = fopen(coeffFilePath,'w');
fprintf(coeffFileID,'%12.4e',coeffs);
fclose(coeffFileID);