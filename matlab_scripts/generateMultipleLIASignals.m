%% Producing signals for lock in amplifier

close all
config.fs = 125E6;
config.f1 = 2E6;
config.f2 = 4E6;
config.tMin = 0;
config.tMax = 1E-2;
config.m = 1;

t = linspace(config.tMin, config.tMax, config.fs*(config.tMax-config.tMin));

signal1 = config.m.*t.*sin(2*pi*config.f1*t);
signal2 = config.m.*t.*sin(2*pi*config.f2*t);

configJson = jsonencode(config);
fid = fopen('../test_data/LIA_collection_input.txt','w');
fprintf(fid, configJson);
fclose(fid);

dataFilePath='../test_data/LIA_collection_input.bin';
dataFileID = fopen(dataFilePath,'w');
fwrite(dataFileID, signal1 + signal2, 'double');
fclose(dataFileID);