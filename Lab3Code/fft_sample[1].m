function [ Mag, phase, freq ] = fft_sample( data, sample_rate)
%computes DFT using FFT function 
G = fft(data);        
%smallest measurable frequency
spectralResolution = sample_rate/length(data);
%largest measurable frequency
f_Nyquist = sample_rate/2;      
%define range of frequencies
freq = 0:spectralResolution:f_Nyquist;  
%calculate magnitude in volts
Mag = abs(G(1:length(freq)))/length(data);
Mag(2:end-1)= 2*Mag(2:end-1);   
%Calcualte phase of signal
phase = angle(G)*180/pi;
end