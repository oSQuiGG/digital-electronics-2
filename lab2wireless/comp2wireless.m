close all;
clear all;



fc=100;
fs=1000;
ts=1/fs;
t=-2:ts:2;
s=(1+0.5*cos(2*pi*5*t)).*cos(2*pi*fc*t);
figure(1)
subplot(2,1,1);
plot(t,s);
grid on;
title('band-pass signal');


N=length(s);
S=fftshift(abs(fft(s)))/N;
df=fs/N;
f=-fs/2:df:fs/2-df;
subplot(2,1,2)
plot(f,S);
grid on;
title('spectra of signal');


sa=hilbert(s);
so=sa.*exp(-j*2*pi*fc*t);
figure(2);

subplot(2,3,1);
plot(t,real(so));
grid on;
title('real part of the complex envelop');

subplot(2,3,2);
plot(t,imag(so));
title('imag part of the complex envelop');

subplot(2,3,3);
plot(t,abs(so));
title('complex envlop');

Sa=fftshift(abs(fft(sa)))/N;
subplot(2,3,4);
plot(f,Sa);
grid on;
title('spectrum of analytical signal');

So=fftshift(abs(fft(so)))/N;
subplot(2,3,5);
plot(f,So);
grid on;
title('spectrum of complex envelop');

snew=real(so).*cos(2*pi*fc*t)-imag(so).*sin(2*pi*fc*t);
figure(3);
plot(f,snew-s);
grid on;
title('comparison');
m=max(snew-s);
fprintf('\n the maximum difference between the two signals is=%i.1e \n' ,m);
