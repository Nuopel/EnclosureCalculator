function [ Filter ] = Filtering3way( Filter.order )
  % [ Filter ] = Filtering3way( Filter )
  % 
  % Author1: Samuel Dupont
  % Date:    December 2016 
  % 
  % Function   : Filtering3way 
  % 
  % Description: Generate the filter coefficients for 3 ways systems
  %              
  %              This based on the work :
  %              Enceintes Acoustiques & Haut parleurs by Vance Dickason
  %              (loudspeaker cookbook in english version)
  % 
  % Parameters : 
  %            
  % 
  % Return     : 
  % 
  % Examples of Usage: 
  % 

%% Calcul de filtres type A and type B
% Type A -> Fh/fl = 10   , Type B -> Fh/fl = 8 
% fh = high frequency cut off, fl = low frequency cut off

    Filter.fh = 3200;
    Filter.A.fl = Filter.fh/10;
    Filter.B.fl = Filter.fh/8;

%% verif self loss
    if Filter.A.fl < 300 
           fprintf('\n The low frequency cut off Type A is inferior to 300  fl = %g. \n',Filter.A.fl);
           fprintf('It needed to calculate the loss induced by the self Ll \n');
           fprintf('Ll=20 * log10(R_m/(R_m+R_s)) , R_m = impedance hp , R_s = resistance of the self\n ')


    end
    if Filter.B.fl < 300 
    fprintf('\n The low frequency cut off Type A is inferior to 300  fl = %g. \n',Filter.B.fl);
           fprintf('It needed to calculate the loss induced by the self Ll \n');
           fprintf('Ll=20 * log10(R_m/(R_m+R_s)) , R_m = impedance hp , R_s = resistance of the self\n ')
    end

%% Coefficient of the filters
if nargin<2
    Filter.order = 2;
end

if Filter.order > 4
    fprintf(' Order of the filters limited to 4');
    Filter.order = 4;
end
  
Filter.A.fm = sqrt(Filter.A.fl * Filter.fh);
Filter.B.fm = sqrt(Filter.B.fl * Filter.fh);

if Filter.order == 1
    Filter.A.C1 = 0.159 / (Filter.Rh*Filter.A.fh);
    Filter.A.C2 = 0.5540 / (Filter.Rm*Filter.A.fm);
    Filter.A.L1 = 0.0458 * Filter.Rm/Filter.A.fm;
    Filter.A.L2 = 0.1592 * Filter.Rl/Filter.A.fl;
    fprintf('\n Filter type A first order 6db/oct');
    fprintf('C1 = %g F, L1 = %g H \n',Filter.A.C1,Filter.A.L1);
    fprintf('C2 = %g F, L2 = %g H \n',Filter.A.C2,Filter.A.L2);

    Filter.B.C1 = 0.159 / (Filter.Rh*Filter.B.fh);
    Filter.B.C2 = 0.5070 / (Filter.Rm*Filter.B.fm);
    Filter.B.L1 = 0.0500 * Filter.Rm/Filter.B.fm;
    Filter.B.L2 = 0.1592 * Filter.Rl/Filter.B.fl;
    fprintf('\n Filter type B first order 6db/oct');
    fprintf('C1 = %g F, L1 = %g H \n',Filter.B.C1,Filter.B.L1);
    fprintf('C2 = %g F, L2 = %g H \n',Filter.B.C2,Filter.B.L2);
end

if Filter.order == 2
    Filter.A.C1 = 0.0791 / (Filter.Rh*Filter.A.fh);
    Filter.A.C2 = 0.3236 / (Filter.Rm*Filter.A.fm);
    Filter.A.C3 = 0.0227 / (Filter.Rm*Filter.A.fm);
    Filter.A.C4 = 0.0791 / (Filter.Rl*Filter.A.fl);

    Filter.A.L1 = 0.3202 * Filter.Rh/Filter.A.fh;
    Filter.A.L2 = 1.029 * Filter.Rm/Filter.A.fm;
    Filter.A.L3 = 0.0837 * Filter.Rm/Filter.A.fm;
    Filter.A.L4 = 0.3202 * Filter.Rl/Filter.A.fl;
    fprintf('\n Filter type A second order');
    fprintf('Gain dof the low pass section 2.08 dB /n The low pass section has an inverted polarity\n');
    fprintf('C1 = %g F, L1 = %g H \n',Filter.A.C1,Filter.A.L1);
    fprintf('C2 = %g F, L2 = %g H \n',Filter.A.C2,Filter.A.L2);
    fprintf('C3 = %g F, L3 = %g H \n',Filter.A.C3,Filter.A.L3);
    fprintf('C4 = %g F, L4 = %g H \n ',Filter.A.C4,Filter.A.L4);
    
    Filter.B.C1 = 0.0788 / (Filter.Rh*Filter.B.fh);
    Filter.B.C2 = 0.3046 / (Filter.Rm*Filter.B.fm);
    Filter.B.C3 = 0.0248 / (Filter.Rm*Filter.B.fm);
    Filter.B.C4 = 0.0788 / (Filter.Rl*Filter.B.fl);

    Filter.B.L1 = 0.3217 * Filter.Rh/Filter.B.fh;
    Filter.B.L2 = 0.932 * Filter.Rm/Filter.B.fm;
    Filter.B.L3 = 0.0913 * Filter.Rm/Filter.B.fm;
    Filter.B.L4 = 0.3217 * Filter.Rl/Filter.B.fl;
    fprintf('\n Filter type B second order');
    fprintf('Gain dof the low pass section 2.45 dB /n The low pass section has an inverted polarity\n');
    fprintf('C1 = %g F, L1 = %g H \n',Filter.B.C1,Filter.B.L1);
    fprintf('C2 = %g F, L2 = %g H \n',Filter.B.C2,Filter.B.L2);
    fprintf('C3 = %g F, L3 = %g H \n',Filter.B.C3,Filter.B.L3);
    fprintf('C4 = %g F, L4 = %g H \n ',Filter.B.C4,Filter.B.L4);
    
end

if Filter.order == 3
    Filter.A.C1 = 0.0995 / (Filter.Rh*Filter.A.fh);
    Filter.A.C2 = 0.3402 / (Filter.Rh*Filter.A.fh);
    Filter.A.C3 = 0.0683 / (Filter.Rm*Filter.A.fm);
    Filter.A.C4 = 0.3128 / (Filter.Rm*Filter.A.fm);
    Filter.A.C5 = 1.148 / (Filter.Rm*Filter.A.fm);
    Filter.A.C6 = 0.2126 / (Filter.Rl*Filter.A.fl);

    Filter.A.L1 = 0.1191 * Filter.Rh/Filter.A.fh;
    Filter.A.L2 = 0.0665* Filter.Rm/Filter.A.fm;
    Filter.A.L3 = 0.0223 * Filter.Rm/Filter.A.fm;
    Filter.A.L4 = 0.4285 * Filter.Rm/Filter.A.fm;
    Filter.A.L5 = 0.2546 * Filter.Rl/Filter.A.fl;
    Filter.A.L6 = 0.0745 * Filter.Rl/Filter.A.fl;

    fprintf('\n Filter type A second order');
    fprintf('Gain dof the low pass section 1.6 dB /n The low pass section has an inverted polarity\n');
    fprintf('C1 = %g F, L1 = %g H \n',Filter.A.C1,Filter.A.L1);
    fprintf('C2 = %g F, L2 = %g H \n',Filter.A.C2,Filter.A.L2);
    fprintf('C3 = %g F, L3 = %g H \n',Filter.A.C3,Filter.A.L3);
    fprintf('C4 = %g F, L4 = %g H \n ',Filter.A.C4,Filter.A.L4);
    fprintf('C5= %g F, L5 = %g H \n ',Filter.A.C5,Filter.A.L5);
    fprintf('C6 = %g F, L6 = %g H \n ',Filter.A.C6,Filter.A.L6);
    
    Filter.B.C1 = 0.0980 / (Filter.Rh*Filter.B.fh);
    Filter.B.C2 = 0.3459 / (Filter.Rm*Filter.B.fm);
    Filter.B.C3 = 0.0768 / (Filter.Rm*Filter.B.fm);
    Filter.B.C4 = 0.2793 / (Filter.Rl*Filter.B.fl);
    Filter.B.C5 = 1.061  / (Filter.Rm*Filter.B.fm);
    Filter.B.C6 = 0.2129 / (Filter.Rl*Filter.B.fl);

    Filter.B.L1 = 0.1190 * Filter.Rh/Filter.B.fh;
    Filter.B.L2 = 0.0711* Filter.Rm/Filter.B.fm;
    Filter.B.L3 = 0.0254 * Filter.Rm/Filter.B.fm;
    Filter.B.L4 = 0.3951 * Filter.Rm/Filter.B.fm;
    Filter.B.L5 = 0.2586 * Filter.Rl/Filter.B.fl;
    Filter.B.L6 = 0.0732 * Filter.Rl/Filter.B.fl;
    fprintf('\n Filter type B second order');
    fprintf('Gain dof the low pass section 2.1 dB /n The low pass section has an inverted polarity\n');
    fprintf('C1 = %g F, L1 = %g H \n',Filter.B.C1,Filter.B.L1);
    fprintf('C2 = %g F, L2 = %g H \n',Filter.B.C2,Filter.B.L2);
    fprintf('C3 = %g F, L3 = %g H \n',Filter.B.C3,Filter.B.L3);
    fprintf('C4 = %g F, L4 = %g H \n ',Filter.B.C4,Filter.B.L4);
   
    Filter.An.C1 = 0.1138 / (Filter.Rh*Filter.A.fh);
    Filter.An.C2 = 0.2976 / (Filter.Rh*Filter.A.fh);
    Filter.An.C3 = 0.0765 / (Filter.Rm*Filter.A.fm);
    Filter.An.C4 = 0.3475 / (Filter.Rm*Filter.A.fm);
    Filter.An.C5 = 1.068 / (Filter.Rm*Filter.A.fm);
    Filter.An.C6 = 0.2127 / (Filter.Rl*Filter.A.fl);
    Filter.An.L1 = 0.1191 * Filter.Rh/Filter.A.fh;
    Filter.An.L2 = 0.0598* Filter.Rm/Filter.A.fm;
    Filter.An.L3 = 0.0253 * Filter.Rm/Filter.A.fm;
    Filter.An.L4 = 0.3789 * Filter.Rm/Filter.A.fm;
    Filter.An.L5 = 0.2227 * Filter.Rl/Filter.A.fl;
    Filter.An.L6 = 0.0852 * Filter.Rl/Filter.A.fl;
    fprintf('\n Filter type A second order');
    fprintf('Gain dof the low pass section 0.85 dB /n The low pass section has a normal polarity\n');
    fprintf('C1 = %g F, L1 = %g H \n',Filter.An.C1,Filter.An.L1);
    fprintf('C2 = %g F, L2 = %g H \n',Filter.An.C2,Filter.An.L2);
    fprintf('C3 = %g F, L3 = %g H \n',Filter.An.C3,Filter.An.L3);
    fprintf('C4 = %g F, L4 = %g H \n ',Filter.An.C4,Filter.An.L4);
    fprintf('C5= %g F, L5 = %g H \n ',Filter.An.C5,Filter.An.L5);
    fprintf('C6 = %g F, L6 = %g H \n ',Filter.An.C6,Filter.An.L6);
    
    Filter.Bn.C1 = 0.1158 / (Filter.Rh*Filter.B.fh);
    Filter.Bn.C2 = 0.2927 / (Filter.Rm*Filter.B.fm);
    Filter.Bn.C3 = 0.0884 / (Filter.Rm*Filter.B.fm);
    Filter.Bn.C4 = 0.3112 / (Filter.Rl*Filter.B.fl);
    Filter.Bn.C5 = 0.9667  / (Filter.Rm*Filter.B.fm);
    Filter.Bn.C6 = 0.2130 / (Filter.Rl*Filter.B.fl);
    Filter.Bn.L1 = 0.1189 * Filter.Rh/Filter.B.fh;
    Filter.Bn.L2 = 0.0634* Filter.Rm/Filter.B.fm;
    Filter.Bn.L3 = 0.0284 * Filter.Rm/Filter.B.fm;
    Filter.Bn.L4 = 0.3395 * Filter.Rm/Filter.B.fm;
    Filter.Bn.L5 = 0.2187 * Filter.Rl/Filter.B.fl;
    Filter.Bn.L6 = 0.0866 * Filter.Rl/Filter.B.fl;
    fprintf('\n Filter type B second order');
    fprintf('Gain dof the low pass section 0.99 dB /n The low pass section has a normal polarity\n');
    fprintf('C1 = %g F, L1 = %g H \n',Filter.Bn.C1,Filter.Bn.L1);
    fprintf('C2 = %g F, L2 = %g H \n',Filter.Bn.C2,Filter.Bn.L2);
    fprintf('C3 = %g F, L3 = %g H \n',Filter.Bn.C3,Filter.Bn.L3);
    fprintf('C4 = %g F, L4 = %g H \n ',Filter.Bn.C4,Filter.Bn.L4);
    
end

end

