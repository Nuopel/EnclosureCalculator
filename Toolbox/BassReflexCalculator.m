function [bassreflex] = BassReflexCalculator( speaker,ct,bassreflex )
%% Calculate the constants as well to conceive a Bass reflex loudspeaker.
% It generate the coefficients in the structure variable bassreflex and
% generate an akabak program to visualise the frequency response
fprintf('\n %%%%%%%%%%%%%%%%%%%%%')
fprintf('\nBass Reflex calculation \n')
fprintf(' %%%%%%%%%%%%%%%%%%%%% \n')
%% Load abak
ct.Ql=7; % QL de l'enceinte, indicating the leak (abak)
ct.kind=['BB4';'QB3';'C4 '];
ct.kind=cellstr(ct.kind);
bassreflex.line=zeros(length(ct.Ql)*length(ct.kind),5);
for jj=1:length(ct.kind)
for ii=1:length(ct.Ql)
    ct.var=(ii-1)*length(ct.Ql)+jj;
%load all the abak fron Vance Dickason cookbook
name.file=sprintf('bassreflex/%sQL%i.txt',char(ct.kind(jj)),ct.Ql(ii));
name.var=sprintf('bassreflex.Breflex%sQL%i',char(ct.kind(jj)),ct.Ql(ii));
name.cmd=sprintf('bassreflex.Breflex%sQL%i=load(name.file);',char(ct.kind(jj)),ct.Ql(ii));
eval(name.cmd);

% look in the abak which is the nearest value
bassreflex.line(ct.var,1)=closest(speaker.Qts,eval([name.var '(:,1)']));
bassreflex.line(ct.var,:)=eval([name.var '(bassreflex.line(ct.var,1),:)']);
end
end
bassreflex.alpha=bassreflex.line(:,3);

ct.choice=find(abs(bassreflex.line(:,1)-speaker.Qts)<0.05==0);
if isempty(ct.choice)==0
bassreflex.line(ct.choice,:)=[];
fprintf('Due to a Qts to far from the abak value available, the following entry have been removed : \n');
for ii=1:length(ct.choice)
fprintf('%s \n',char(ct.kind(ct.choice(ii))));
end
end
if length(ct.choice)== length(ct.Ql)*length(ct.kind)
    fprintf('The value of Qts indicated are too far apart from the abak \n')
    fprintf('It''s not possible to calculate a bass reflex\n')
    return;
end

%% Constants definitions to for closed box design
bassreflex.Vb=speaker.Vas./bassreflex.alpha; % volume of the box
bassreflex.fb=speaker.fs*bassreflex.line(:,2);% resonance frequency of the closedbox

bassreflex.f3=bassreflex.line(:,4)*speaker.fs;% -3db cut off
% not working ?
%% Define ratio size of the different enclosure configuration 
ct.BassReflexRatio=(bassreflex.Vb/ct.width/ct.height/ct.length).^(1/3);

bassreflex.height=ct.BassReflexRatio*ct.height*1e1; %hauteur
bassreflex.width=ct.BassReflexRatio*ct.width*1e1; %largeur
bassreflex.length=ct.BassReflexRatio*ct.length*1e1; %profondeur
AkabakBassreflexScript(speaker,bassreflex,ct)

end

