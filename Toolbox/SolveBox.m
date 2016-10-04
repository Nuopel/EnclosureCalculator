function [box] = SolveBox(V,d,ct,opt)
% Solve the equation for a box giving back the interior and exterior
% dimension for a ratio, ex: 1*1.6*2.6 considering the ratio as the
% exterior.
% [sol] = SolveBox(V,d,ct,opt)
% V the volume of the box
% d the thickness of the box
% ct is a structure containing the different ratio width,height,length
% Sent back the interior dimensions a b c and exterior A B C
% opt : can had a gap in the box ct.g 

if nargin<4
    opt=0;
end

if opt~=1
    syms a b c A B C positive
    sol=solve(A==ct.width/ct.length*C,B==ct.height/ct.length*C,A==a+2*d,B==b+2*d,C==c+2*d,V==a*b*c);
    % equation of the box minuscule: interior, majjuscule exterior
    
    box.widthIn=double(vpa(sol.a));
    box.heightIn=double(vpa(sol.b));
    box.lengthIn=double(vpa(sol.c));
    
    box.widthExt=double(vpa(sol.A));
    box.heightExt=double(vpa(sol.B));
    box.lengthExt=double(vpa(sol.C));
    
else % same than before but the is a gap for the heigth (interior box + space)
    syms a b c A B C positive
    sol=solve(A==ct.width/ct.length*C,B==ct.height/ct.length*C,A==a+2*d,B==b+3*d+ct.g,C==c+2*d,V==a*b*c); 
    
    box.widthIn=double(vpa(sol.a));
    box.heightIn=double(vpa(sol.b));
    box.lengthIn=double(vpa(sol.c));
    
    box.widthExt=double(vpa(sol.A));
    box.heightExt=double(vpa(sol.B));
    box.lengthExt=double(vpa(sol.C));
end

end

