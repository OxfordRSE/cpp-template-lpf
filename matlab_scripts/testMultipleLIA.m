%% Script to test the C++ lock in amplifier implementation

datacursormode on
clear

figure("X odd signal");
% Read configuration parameters
metaFid = fopen('../test_data/LIA_collection_input.txt','r');
metaJson = fscanf(metaFid,'%c');
fclose(metaFid);

config = jsondecode(metaJson);

% Read lock in amplified data
fNameOutput1 = '../test_data/LIA_collection_output1_X.bin';
fId1 = fopen(fNameOutput1,'r');
nBytes=8;
s = dir(fNameOutput1);
size = floor(s.bytes/nBytes);
signal1 = fread(fId1, [1,size], 'double');

fNameOutput2 = '../test_data/LIA_collection_output2_X.bin';
fId2 = fopen(fNameOutput2,'r');
nBytes=8;
s = dir(fNameOutput2);
size = floor(s.bytes/nBytes);
signal2 = fread(fId2, [1,size], 'double');

t = linspace(config.tMin, config.tMax, config.fs*(config.tMax-config.tMin));
idealSignal = config.m*t;
%normalize the signals
idealSignal = idealSignal/max(idealSignal);
signal1 = signal1/max(signal1);
signal2 = signal2/max(signal2);

subplot(2,2,1);
plot(t, signal1);
hold on
plot(t, idealSignal);
hold off
legend('lock in amplifier signal', 'ideal signal');
xlabel('time [s]');
ylabel('signal [arb]');
title(sprintf('lock in amplifier and ideal signal\n lock in frequency: {%.2g} Hz', config.f1));

subplot(2,2,2);
plot(t, signal1 - idealSignal);
xlabel('time [s]');
ylabel('signal [arb]');
title('residual');

subplot(2,2,3);
plot(t, signal2);
hold on
plot(t, idealSignal);
hold off
legend('lock in amplifier signal', 'ideal signal');
xlabel('time [s]');
ylabel('signal [arb]');
title(sprintf('lock in amplifier and ideal signal\n lock in frequency: {%.2g} Hz', config.f2));

subplot(2,2,4);
plot(t, signal2 - idealSignal);
xlabel('time [s]');
ylabel('signal [arb]');
title('residual');

figure("Y odd signal");

% Read lock in amplified data
fNameOutput1 = '../test_data/LIA_collection_output1_Y.bin';
fId1 = fopen(fNameOutput1,'r');
nBytes=8;
s = dir(fNameOutput1);
size = floor(s.bytes/nBytes);
signal1 = fread(fId1, [1,size], 'double');

fNameOutput2 = '../test_data/LIA_collection_output2_Y.bin';
fId2 = fopen(fNameOutput2,'r');
nBytes=8;
s = dir(fNameOutput2);
size = floor(s.bytes/nBytes);
signal2 = fread(fId2, [1,size], 'double');

t = linspace(config.tMin, config.tMax, config.fs*(config.tMax-config.tMin));
idealSignal = config.m*t;
%normalize the signals
idealSignal = idealSignal/max(idealSignal);
signal1 = signal1/max(signal1);
signal2 = signal2/max(signal2);

subplot(2,2,1);
plot(t, signal1);
hold on
plot(t, idealSignal);
hold off
legend('lock in amplifier signal', 'ideal signal');
xlabel('time [s]');
ylabel('signal [arb]');
title(sprintf('lock in amplifier and ideal signal\n lock in frequency: {%.2g} Hz', config.f1));

subplot(2,2,2);
plot(t, signal1 - idealSignal);
xlabel('time [s]');
ylabel('signal [arb]');
title('residual');

subplot(2,2,3);
plot(t, signal2);
hold on
plot(t, idealSignal);
hold off
legend('lock in amplifier signal', 'ideal signal');
xlabel('time [s]');
ylabel('signal [arb]');
title(sprintf('lock in amplifier and ideal signal\n lock in frequency: {%.2g} Hz', config.f2));

subplot(2,2,4);
plot(t, signal2 - idealSignal);
xlabel('time [s]');
ylabel('signal [arb]');
title('residual');