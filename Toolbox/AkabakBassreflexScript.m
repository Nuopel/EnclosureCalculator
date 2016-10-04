function [] = AkabakBassreflexScript(speaker,bassreflex,ct)
%% This function allows to generate script for akabak in order to calculate bass reflex frequency response

%% Open the file
fileID = fopen('bassreflex.aks','w');
%gnclude speaker definition
fprintf(fileID,'Def_Driver  ''%s'' \n',speaker.name);
fprintf(fileID,' dD=%gcm  |Piston \n',speaker.r*2);
fprintf(fileID,' fs=%gHz  Mms=%gg  Qms=%g \n',speaker.fs,speaker.Mms,speaker.Qms);
if isfield(speaker,'dD1') && isfield(speaker,'tD1')
fprintf(fileID,' dD1=%gcm  tD1=%gcm \n ',speaker.dD1,speaker.tD1);
end
fprintf(fileID,' Qes=%g Re=%gohm  Le=%gmH  ExpoLe=0.618 \n \n',speaker.Qes,speaker.Re,speaker.Le);
%
for jj=1:length(ct.kind)
    for kk=1:length(ct.Ql)
        ii=(kk-1)*length(ct.Ql)+jj;
        
        name.system=sprintf('\n \n \n System ''S%g_BassReflex_%sQL%g'' \n \n',ii,char(ct.kind(jj)),ct.Ql(kk));
        fprintf(fileID,name.system);
        fprintf(fileID,'Driver ''D1'' Def=''%s'' Node=0=1=2=21\n',speaker.name);
        fprintf(fileID,'Enclosure    ''E1''  Node=2\n ');
        fprintf(fileID,'  Vb=%gL  Qb/fo=1 Lb=%gcm Sb=%gcm2\n', bassreflex.Vb(ii),bassreflex.height(ii),bassreflex.height(ii)*bassreflex.width(ii));
        fprintf(fileID,' fb=%gHz  dD=%gcm \n \n',bassreflex.fb(ii),bassreflex.dv);
        
        
        
        
        fprintf(fileID,'  Radiator  ''Rad1''  Def=''D1'' Node=21 \n');
        fprintf(fileID,'  x=0  y=0  z=0cm  HAngle=0  VAngle=0 \n');
        if ct.diffraction==1
            fprintf(fileID,'  HEdge=%gcm WEdge=%gcm',bassreflex.height(ii),bassreflex.width(ii));
        end
    end
end
fclose(fileID);
end