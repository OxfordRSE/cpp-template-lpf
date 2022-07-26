%% Script to test the C++ lock in amplifier implementation

datacursormode on
% Read configuration parameters
metaFid = fopen('../test_data/LIA_input.txt','r');
metaJson = fscanf(metaFid,'%c');
fclose(metaFid);

config = jsondecode(metaJson);

% Read lock in amplified data

fNameOutput = '../test_data/LIA_output.bin';
fId = fopen(fNameOutput,'r');
nBytes=8;
s = dir(fNameOutput);
size = floor(s.bytes/nBytes);
signal = fread(fId, [1,size], 'double');

t = linspace(config.tMin, config.tMax, config.fs*(config.tMax-config.tMin));
idealSignal = config.m*t;
%normalize the signals
idealSignal = idealSignal/max(idealSignal);
signal = signal/max(signal);
subplot(1,2,1);
plot(t, signal);
hold on
plot(t, idealSignal);
hold off
legend('lock in amplifier signal', 'ideal signal');
xlabel('time [s]');
ylabel('signal [arb]');
title('lock in amplifier and ideal signal');

subplot(1,2,2);
plot(t, signal - idealSignal);
xlabel('time [s]');
ylabel('signal [arb]');
title('residual');