%% Producing signal for lock in amplifier

close all
config.fs = 125E6;
config.f = 1E6;
config.tMin = 0;
config.tMax = 1E-2;
config.m = 1;

t = linspace(config.tMin, config.tMax, config.fs*(config.tMax-config.tMin));

signal = config.m.*t.*sin(2*pi*config.f*t);

configJson = jsonencode(config);
fid = fopen('../test_data/LIA_input.txt','w');
fprintf(fid, configJson);
fclose(fid);

dataFilePath='../test_data/LIA_input.bin';
dataFileID = fopen(dataFilePath,'w');
fwrite(dataFileID, signal, 'double');
fclose(dataFileID);