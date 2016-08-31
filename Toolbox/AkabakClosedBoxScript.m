function [] = AkabakClosedBoxScript(speaker,closedbox,ct)
%% This function allows to generate script for akabak in order to calculate closed box frequency response

%% Open the file
fileID = fopen('closed.aks','w');
%gnclude speaker definition
fprintf(fileID,'Def_Driver  ''%s'' \n',speaker.name);
fprintf(fileID,' dD=%gcm  |Piston \n',speaker.r*2);
fprintf(fileID,' fs=%gHz  Mms=%gg  Qms=%g \n',speaker.fs,speaker.Mms,speaker.Qms);
if isfield(speaker,'dD1') && isfield(speaker,'tD1')
fprintf(fileID,' dD1=%gcm  tD1=%gcm \n ',speaker.dD1,speaker.tD1);
end
fprintf(fileID,' Qes=%g Re=%gohm  Le=%gmH  ExpoLe=0.618 \n \n',speaker.Qes,speaker.Re,speaker.Le);


for ii = 1:length(ct.Qtc) 
name.system=sprintf('System ''S%g_clos_Qtc_%g'' \n \n',ii,ct.Qtc(ii));
fprintf(fileID,name.system);
fprintf(fileID,'Driver ''D1'' Def=''%s'' Node=0=1=2=21\n',speaker.name);
fprintf(fileID,'Enclosure    ''E1''  Node=2\n ');
fprintf(fileID,'  Vb=%gL  Qb/fo=1 Lb=%gcm Sb=%gcm2\n',closedbox.Vb(ii),closedbox.height(ii),closedbox.height(ii)*closedbox.width(ii));
fprintf(fileID,'  Radiator  ''Rad1''  Def=''D1'' Node=21 \n');
fprintf(fileID,'  x=0  y=0  z=0cm  HAngle=0  VAngle=0 \n');
    if ct.diffraction==1
    fprintf(fileID,'  HEdge=%gcm WEdge=%gcm\n \n \n',closedbox.height(ii),closedbox.width(ii));
    end
end
fclose(fileID);

end

