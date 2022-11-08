close all;
clear all;


%Generate the matrix of Hadamard sequences (function ”hadamard”) with Spreading
%Factor (SF) equal to 8. Note the individual sequences ( each sequence corresponds
%to one row or column of the Hadamard matrix). Verify the orthogonality of two
%selected sequences (zero scalar product).
SF=8;
H=hadamard(SF);
ort=H*H;
H(1,:)*H(3,:).';

%Generate the random binary antipodal data (1, -1) of length 100 corresponding to
%one user. You can make use of function "randsrc” for example.
Nbit=3;
user1=randsrc(1,Nbit);
user2=randsrc(1,Nbit);
user3=randsrc(1,Nbit);

send1=[];
send2=[];
send3=[];
%Spread the first users data using selected sequence from Hadamard matrix ( choose
%the 3-rd row of the matrix for example
for i=1:length(user1)
    send1=[send1 user1(i)*H(3,:)];
    send2=[send2 user2(i)*H(3,:)]; 
    send3=[send3 user3(i)*H(3,:)];
end


send=send1+send2+send3;

%Add the white gaussian noise to the received signal and observe its influence on
%the integrator (receiver) output. Change the SF to for example 64 and observe the
%change of error probability.
snr=0;
send=awgn(send,snr,'measured');
receive=reshape(send,SF,length(user1));


% According the same procedure as above, create the signals of three more users. (use
% the Hadamard sequences from 1st, 5th and 7th row of the Hadamard matrix). Add
% them together with the signal of the first user. Use the similar principle also for the
% model of the receiver.

nerr=0;
for i=1:length(user1)
    received_sig1(i)=  sign(sum(H(3,:).*receive(:,i)'));
    received_sig2(i)=  sign(sum(H(2,:).*receive(:,i)'));
    received_sig3(i)=  sign(sum(H(1,:).*receive(:,i)'));
    %if received_sig1(i)~=user1(i); nerr=nerr+1;
        %if received_sig2(i)~=user2(i); nerr=nerr+1;
            %if received_sig3(i)~=user3(i); nerr=nerr+1;
    end
end
ber=nerr/Nbit;


% Load the file ”msekvence.mat” consisting of 32-chip length m-sequence. Compare
% (graphically) the autocorelation functions of m-sequence and Hadamard sequences
% of the same length. (use the ”load” and ”xcorr” functions).
load('msekvence.mat')
figure;
subplot(1,3,1);plot(xcorr(msekvence));
grid on;
subplot(1,3,2);plot(xcorr(H(1,:)));
grid on;
subplot(1,3,3);plot(xcorr(H(7,:)));
grid on;








