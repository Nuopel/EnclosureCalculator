%% Calculate if the speaker need to be a closed box or could be a bass reflex.
% Define the characteristics of the speakers

clear variables; close all;clc;
addpath('Toolbox')
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%       User part      %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Define speaker bass characteristics
speaker.name='3FE22';
speaker.fs=110;
speaker.Qes=0.5;
% speaker.Qtc=0.2;
speaker.Qts=0.45;
speaker.Qms=5;
speaker.Vas=0.95;

speaker.dD=8;% diameter of the speaker membrane  [cm]
speaker.r=speaker.dD/2; %radius 
speaker.tD1=2.5; % Inner depth of cone to base of dust cap [cm]
% speaker.dD1=2.5; %Diameter of dust cap [cm]
% speaker.hD1=1; %Height of dust cap  [cm]

speaker.Re=6.7; %equivalent resistor [Ohm]
speaker.Mms=2.8;% equivalent mass of the speaker [g]
speaker.Le=0.15;% inductance of the speaker [mH]
speaker.Bl=4.5;% N/A
% load('Savedspeaker/DaytonDC200.mat')
%% Define speaker tweeter characteristics
speaker2.name='28-847SE';
speaker2.fs=850;
speaker2.Qes=1.47;
speaker2.Qts=0.87;
speaker2.Qms=2.13;
speaker2.Mms=0.32;

speaker2.dD=2.548;% diameter of the speaker membrane  [cm]
speaker2.r=speaker.dD/2; %radius 
speaker2.tD1=0.5; % Inner depth of cone to base of dust cap [cm]

speaker2.dD1=2.5; %Diameter of dust cap [cm]
speaker2.hD1=0.8; %Height of dust cap  [cm]

speaker2.Re=7.8;
speaker2.Le=0.016;

%% Options
ct.diffraction=0;% boolean variable 1 for diffraction of the enclosure edge 0 else;
bassreflex.dv=speaker.r/2;% size of the vent for the BassReflex


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%     Program part     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
EBP=speaker.fs/speaker.Qes;
fprintf('The EBP value is : %g \n',EBP);
if EBP<50
    fprintf('It''s advised to do a closed enclosure')
else
    fprintf('It''s could be possible to do a closed enclosure or a bass reflex\n')
end

ct.enter=input('Begin calculation ?');
%% Define constant
% define the ratio of the enclosure dimension (Vance Dickason p148) 
ct.width=1.6;%front size
ct.height=2.6;% height of the enclosure
ct.length=1;%deepness of the enclosure

%%%%%%%%%%%%%%%%%%%%%
%%% Closed Box
[closedbox,abak] = ClosedBoxCalculator(speaker,ct);
fprintf('\nClosed box calculation and Akabak script done\n')

%%%%%%%%%%%%%%%%%%%%%
%%% Bass reflex
[bassreflex] =  BassReflexCalculator( speaker,ct,bassreflex );
fprintf('\nBass Reflex calculation and Akabak script done\n ')

%%%%%%%%%%%%%%%%%%%%
%%%  Filter part  %%

%% Filtre second ordre Linkwitz-Riley
% The Filter should be at least 2.8 * fs
Filter.f=1600; 
Filter.Rh=6;
Filter.Rl=8;
Filter.C1=0.0796/(Filter.Rh*Filter.f);
Filter.L1=0.3183*Filter.Rh/Filter.f;
Filter.C2=0.0796/(Filter.Rl*Filter.f);
Filter.L2=0.3183*Filter.Rl/Filter.f;


%% Filtre  tweeter anti resonant 
if isfield(speaker2,'Re') && isfield(speaker2,'Qes') && isfield(speaker2,'fs') && isfield(speaker2,'Qms')
Filter.Ct=0.1592/(speaker2.Re*speaker2.Qes*speaker2.fs);
Filter.Lt=0.1592*speaker2.Re*speaker2.Qes/speaker2.fs;
Filter.Rc=speaker2.Re+speaker2.Qes*speaker2.Re/speaker2.Qms;
else
    fprintf('\nUnable to calculate the antiresonant Filter for the tweeter due to lack of informations\n')
end
%% Filtre  attenuateur tweeter 

Filter.A=-2;
Filter.Z=8;
Filter.R2=10^(Filter.A/20)*Filter.Z/(1-10^(Filter.A/20));
Filter.R1=Filter.Z-1/(1/Filter.R2+1/Filter.Z);

%% Filtre compensation d'impedance boomer
if isfield(speaker,'Le') && isfield(speaker,'Re') 
Filter.Rcb=1.25*speaker.Re;
Filter.Cb=speaker.Le*1e-3/Filter.Rcb^2;
else
    fprintf('\nUnable to calculate the impedance compesation \n Filter for the tweeter due to lack of informations\n')
end 
%% clear
% clear ct