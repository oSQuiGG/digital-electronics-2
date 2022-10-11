close all;
clear all;
fc=100;
fs=1000;
t=0:1/fs:1;
s=cos(2*pi*fc*t);
figure(1);
plot(t,s)
figure(2);
stem(t,s)
grid on;



n=length(s);
fft_s=fftshift(abs(fft(s)));
f=-n/2:(n/2-1);
figure(3);
plot(f,fft_s)
grid on;


nfft=n;
window=rectwin(nfft);
[pxx,f]=pwelch(s,window,0,nfft,fs);
dp_hz=10*log10(pxx);
figure(4);
plot(f,dp_hz)
grid on;

load qpsk;
qpsk_cut=qpsk(6:1965);
mat=reshape(real(qpsk_cut),10,1960/10);
figure(5);

for i=1:size(mat,2)
    symb=mat(:,i);
    plot(symb(1:end))
    hold on;
end
figure(6);
eyediagram(real(qpsk),10);
%plot(qpsk)
%plot((qpsk(1:100)));
%eyedriagram(qpsk,10)


