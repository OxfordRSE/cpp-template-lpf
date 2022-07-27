%% Script to test the C++ lock in amplifier implementation

datacursormode on
clear
% Read configuration parameters
metaFid = fopen('../test_data/LIA_input.txt','r');
metaJson = fscanf(metaFid,'%c');
fclose(metaFid);

config = jsondecode(metaJson);

% Read lock in amplified data
fNameOutput1 = '../test_data/LIA_output_X.bin';
fId1 = fopen(fNameOutput1,'r');
nBytes=8;
s = dir(fNameOutput1);
size = floor(s.bytes/nBytes);
signal1 = fread(fId1, [1,size], 'double');

fNameOutput2 = '../test_data/LIA_output_Y.bin';
fId1 = fopen(fNameOutput2,'r');
nBytes=8;
s = dir(fNameOutput2);
size = floor(s.bytes/nBytes);
signal2 = fread(fId1, [1,size], 'double');

t = linspace(config.tMin, config.tMax, config.fs*(config.tMax-config.tMin));
idealSignal = config.m*t;
%normalize the signals
idealSignal = idealSignal/max(idealSignal);
signal1Norm = signal1/max(signal1);

subplot(2,2,1);
plot(t, signal1Norm);
hold on
plot(t, idealSignal);
hold off
legend('lock in amplifier signal', 'ideal signal');
xlabel('time [s]');
ylabel('signal [arb]');
title(sprintf('lock in amplifier and ideal signal\n lock in frequency: {%.2g} Hz', config.f));

subplot(2,2,2);
plot(t, signal1Norm - idealSignal);
xlabel('time [s]');
ylabel('signal [arb]');
title('residual');

subplot(2,2,3);
plot(t, signal1);
hold on
plot(t, signal2);
hold off
legend('X odd', 'Y odd');
xlabel('time [s]');
ylabel('signal [arb]');
title('X odd and Y odd signals');

subplot(2,2,4);
plot(t, signal1-signal2);
xlabel('time [s]');
ylabel('signal [arb]');
title('Residual between X odd and Y odd');