close all;
clear all;
N=100;
M=64;
M1=randsrc(M,N,[-3 -1 1 3])+j*randsrc(M,N,[-3 -1 1 3]);
figure(1);
plot(real(M1), imag(M1),'ob')
grid on;
M2=[M1(1:M/2,:); zeros(M,N); M1(M/2+1:end,:)];
M3=ifft(M2);
s=reshape(M3,1,M*N*2);

figure(2);
pwelch(s);
figure(3);
plot(abs(s));
figure(4);
hist(real(s));
figure(5);
hist(angle(s));

%r=awgn(s,20, 'measured');
r=saleh(s*3);
M4= reshape(r,2*M,N);
M5=fft(M4);
figure(6);
plot(M5, 'ob');
grid on;
M6=[ M5(1:M/2,:); M5(M/2+1+M:end,:)];

figure(1);
hold on;
plot(real(M6), imag(M6),'rx');
plot(real(M1), imag(M1),'ob');
grid on;

figure(7);
plot(abs(s), abs(r), '.');
grid on;

figure(8);
plot(abs(s), rad2deg(unwrap(angle(r)-angle(s))),'.');
grid on;







