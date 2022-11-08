close all;
clear all;


N=100;
SYM=randsrc(1,N,[1 -1]) + j*randsrc(1,N,[1 -1]);
plot(SYM,'o');
scatterplot(SYM);
samples_per_symb=4;
h=rcosine(1,samples_per_symb,'sqrt',0.3,5);
figure(1);
stem(h);

symbi=real(SYM);
symbq=imag(SYM);
symbi_up=upsample(symbi, samples_per_symb);
symbq_up=upsample(symbq, samples_per_symb);

figure(2);
stem(symbi_up);

symb_if=filter(h,1,symbi_up);
symb_qf=filter(h,1,symbq_up);
s=symb_if+j*symb_qf;
figure(3);
plot(s);
grid on;
hold on;

plot(s((length(h)-1)/2+1:samples_per_symb:end),'r*');
eyediagram(real(s),samples_per_symb);

reci=filter(h,1,real(s));
recq=filter(h,1,imag(s));
rec_sym=reci+j*recq;
figure(5);
plot(rec_sym);
grid on;
hold on;
plot(rec_sym(2*(length(h)-1)/2+1:samples_per_symb:end),'r*');
eyediagram(real(rec_sym), samples_per_symb);