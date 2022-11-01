%Optical receiver
%Task
close all;
clear all;
 

% Calculate the theoretical BER in the range < 0, 10 > dB with step 0.1 dB. Do not
% forget that you need to convert the ratio Eb/N0 from the logarithmic units in order
% to substitute it into equation 3.1.
EbNodb = [0:0.5:10];
EbNo = 10.^(EbNodb./10);
pe=0.5.*erfc(sqrt(EbNo));
%pe = qfunc(sqrt(2*EbNo));
semilogy(EbNodb, pe);
grid on;


% Generate the random symbols ±1 using the function randsrc, that you already know
% from the previous lab. More the symbols you will use, more the BER estimate will
% be precise. Try to estimate the minimal numbel of random BPSK symbols needed
% to estimate the error probability of 1 · 10−5

Nsym=1e6;
syms=randsrc(1,Nsym);
for i=1:length(EbNo)
    sigma=sqrt(1/(2*EbNo(i)));
    % Add the gaussian noise with the desired variance to the binary symbols using the function randn.
    n=sigma*randn(1,Nsym);
     r=syms+n;
     dec=sign(r);
      nerr(i)=numel(find(syms~=dec));
       BER(i)=nerr(i)/length(syms);
end
hold on;

plot(EbNodb, BER, 'r*')