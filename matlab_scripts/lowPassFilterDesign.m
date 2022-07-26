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
    
    % Write all filter parameters to json
    config.N = N;       % filter order 
    config.Fs = Fs;     % sampling frequency 
    config.Fp = Fp;      % passband edge in Hz
    config.Ap = Ap;     % passband ripple in dB
    config.Ast = Ast;      % stopband attenuation in dB
    config.Rp = Rp;  % passband ripple in linear values
    config.Rst = Rst;  % stop band attenuation in linear values
    configJson = jsonencode(config);
    fid = fopen('../test_data/filter_coefficients.txt','w');
    fprintf(fid, configJson);
    fclose(fid);


    % Writing the coefficients in binary 
    coeffFilePath = '../test_data/filter_coefficients.bin'; 
    coeffFileID = fopen(coeffFilePath, 'w');
    fwrite(coeffFileID, coeff, 'double');  
end