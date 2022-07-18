function coeff = lowPassFilterDesign()
%% Creates low pass filter coefficients and saves the coefficients to binary
    N = 1000;       % filter order 
    Fs = 125e6;     % sampling frequency 
    Fp = 1.3e6;      % passband edge in Hz
    Ap = 0.01;     % passband ripple in dB
    Ast = 80;      % stopband attenuation in dB
    Rp = (10^(Ap/20) - 1)/(10^(Ap/20) + 1);  % passband ripple in linear values
    Rst = 10^(-Ast/20);  % stop band attenuation in linear values
    coeff = firceqrip(N,Fp/(Fs/2),[Rp Rst],'passedge');

    % Writing the coefficients in binary 
    coeffFilePath = '../test_data/filterCoeff.bin'; 
    coeffFileID = fopen(coeffFilePath, 'w');
    fwrite(coeffFileID, coeff, 'double');  
end