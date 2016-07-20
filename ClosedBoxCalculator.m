function [closedbox,abak] = ClosedBoxCalculator(speaker,ct)
%% calculate the constants as well to conceive a closed box loudspeaker.
% It generate the coefficients in the structure variable closedbox and
% generate an akabak program to visualise the frequency response
fprintf('\n %%%%%%%%%%%%%%%%%%%%%')
fprintf('\nClosed box calculation \n')
fprintf(' %%%%%%%%%%%%%%%%%%%%% \n')


%% Load abak
ct.Qtc=[ 500 577 707 800 900 1000 1100 1200 1500 ]; % Qtc de l'enceinte (abak)
abak.line=zeros(length(ct.Qtc),3);
for ii=1:length(ct.Qtc)
%load all the abak fron Vance Dickason cookbook
name.file=sprintf('close/closeQtc0_%i.txt',ct.Qtc(ii));
name.var=sprintf('abak.closedQtc%i',ct.Qtc(ii));
name.cmd=sprintf('abak.closedQtc%i=load(name.file);',ct.Qtc(ii));
eval(name.cmd);

% look in the abak which is the nearest value
abak.line(ii,1)=closest(speaker.Qts,eval([name.var '(:,1)']));
abak.line(ii,:)=eval([name.var '(abak.line(ii,1),:)']);
end
abak.alpha=abak.line(:,2);

%% alert msg if Qts out of abak
ct.choice=find(abs(abak.line(:,1)-speaker.Qts)<0.05==0);
if isempty(ct.choice)==0
abak.line(ct.choice,:)=[];
fprintf('Due to a Qts to far from the abak value available the following entry have been removed : \n');
fprintf('Qtc : %g\n',ct.Qtc(ct.choice)/1000);
end
if length(ct.choice)== length(ct.Qtc)
    fprintf('The value of Qts indicated are too far apart from the abak \n')
    fprintf('It''s not possible to calculate a closed box\n')
    closedbox.null=0;
    return ;
end

%% Constants definitions to for closed box design
closedbox.Vb=speaker.Vas./abak.alpha; % volume of the box
closedbox.fc=ct.Qtc*1e-3*speaker.fs/speaker.Qts;% resonance frequency of the closedbox

closedbox.f3=((1./ct.Qtc.^2-2+sqrt((1./ct.Qtc.^2-2).^2+4))/2).^(1/2).*closedbox.fc;% -3db cut off
% not working ?
%% Define ratio size of the different enclosure configuration 
ct.EnclosureClosedRatio=(closedbox.Vb/ct.width/ct.height/ct.length).^(1/3);

closedbox.height=ct.EnclosureClosedRatio*ct.height*1e1; %hauteur
closedbox.width=ct.EnclosureClosedRatio*ct.width*1e1; %largeur
closedbox.length=ct.EnclosureClosedRatio*ct.length*1e1; %profondeur

AkabakClosedBoxScript(speaker,closedbox,ct)


end

