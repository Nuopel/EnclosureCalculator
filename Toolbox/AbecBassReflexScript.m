function [] = AbecBassReflexScript(speaker,speaker2,bassreflex,Filter,ct)
%% This function allows to generate script for akabak in order to calculate bass reflex frequency response

%% Open the file
name.system=sprintf('SolvingBassReflex%s.txt',char(ct.kind(ct.index,:)));
fileID = fopen(name.system,'w');

%% write control solver 
fprintf(fileID,'Control_Solver \n');
fprintf(fileID,'f1=20;  f2=500;  NumFrequencies=10;  Abscissa=log; \n');
fprintf(fileID,'ImpedanceNumFrequencies=250 \n');
fprintf(fileID,'Dim=3D \n');
fprintf(fileID,'Sym=x \n');
fprintf(fileID,'MeshFrequency=500Hz \n\n\n');


%% Define subdomain   
fprintf(fileID,'SubDomain_Properties ''Enclosure''\n');
fprintf(fileID,'SubDomain=1\n');
fprintf(fileID,'ElType=Interior \n');
fprintf(fileID,'Color=''Green''\n\n');

fprintf(fileID,'SubDomain_Properties ''Vent''\n');
fprintf(fileID,'SubDomain=2\n');
fprintf(fileID,'ElType=Interior \n');
fprintf(fileID,' Color=''blue''\n\n');

fprintf(fileID,'SubDomain_Properties ''Exterior''\n');
fprintf(fileID,'SubDomain=3 \n');
fprintf(fileID,' ElType=Exterior //Radiation to infinity\n\n\n');
      

%% Define formula value        
 
fprintf(fileID,'Formula "taille"\n');
fprintf(fileID,'{\n\n');

fprintf(fileID,'He=%g; // Hauteur exterieur\n',bassreflex.heightExt(ct.index));
fprintf(fileID,'Le=%g; //Longueur exterieur\n',bassreflex.widthExt(ct.index));
fprintf(fileID,'Pe=%g; // Profondeur exterieur\n\n',bassreflex.lengthExt(ct.index));

fprintf(fileID,'hi=%g;// Hauteur exterieur\n',bassreflex.heightIn(ct.index));
fprintf(fileID,'li=%g;// Longueur exterieur\n',bassreflex.widthIn(ct.index));
fprintf(fileID,'pin=%g;// Profondeur exterieur\n\n',bassreflex.lengthIn(ct.index));

fprintf(fileID,'d=%g;//thichness of the wood pannel\n\n',bassreflex.thickness);
if isfield(speaker,'dD')
fprintf(fileID,'dDw=%g; // Diameter of cone\n',speaker.dD*1e-2);
else
    sprintf('Abec script aborted\nMissing basic dimension dD for the woofer')
    return;
end

if isfield(speaker,'dD1')&& isfield(speaker,'tD1')&& isfield(speaker,'hD1')
fprintf(fileID,'tD1w=%g; // Inner depth of cone to base of dust cap\n',speaker.tD1*1e-2);
fprintf(fileID,'dD1w=%g; // Diameter of dust cap\n',speaker.dD1*1e-2);
fprintf(fileID,'hD1w=%g;  // Height of dust cap  \n\n',speaker.hD1*1e-2);
else
    sprintf('Abec script aborted\n Missing basic dimensions such as tD1, dD1 and hD1 for the woofer ')
    return;
end

if isfield(speaker2,'dD1')&& isfield(speaker2,'tD1')&& isfield(speaker2,'hD1')
fprintf(fileID,'dDt=%g;        // Diameter of cone\n',speaker2.dD*1e-2);
fprintf(fileID,'tD1t=%g;       // Inner depth of cone to base of dust cap\n',speaker2.tD1*1e-2);
fprintf(fileID,'dD1t=%g;    // Diameter of dust cap\n',speaker2.dD1*1e-2);
fprintf(fileID,'hD1t=%g;   // Height of dust cap \n\n',speaker2.hD1*1e-2);
else
    sprintf('Abec script aborted\n Missing basic dimensions such as dD,tD1, dD1 and hD1 for the tweeter ')
    return;
end

fprintf(fileID,'Ddv=%g; //diameter vent\n',bassreflex.dv*1e-2);
Leduct=170^2/(pi*bassreflex.Vb(ct.index)*1e-3)*(bassreflex.dv*1e-2/bassreflex.fb(ct.index))^2;
fprintf(fileID,'Lev=%g; //length vent\n\n}\n\n\n',Leduct);

fprintf(fileID,'//_________________________________________________\n// ____________Nodes definition_______________________\n//_________________________________________________\n\n');
fprintf(fileID,'Nodes   "NF"\n //--------- Interior--------------------\n//---------------------------------------\n\n');
fprintf(fileID,'Scale=1m\n');

fprintf(fileID,'1 {0} {+d} {d}\n');
fprintf(fileID,'2 {0} {hi+d} {d}\n');
fprintf(fileID,'3 {li/2} {hi+d} {d}\n');
fprintf(fileID,'4 {li/2} {+d} {d}\n');
fprintf(fileID,'5 {li/2} {+d} {pin+d}\n');
fprintf(fileID,'6 {0} {+d} {pin+d}\n');
fprintf(fileID,'7 {0} {hi+d} {pin+d}\n');
fprintf(fileID,'8 {li/2} {hi+d} {pin+d}\n\n');

fprintf(fileID,'//---------Exterior--------------------\n//--------------------------------------\n\n');
fprintf(fileID,'201 {0} {0} {0}\n');
fprintf(fileID,'202 {0} {He} {-0}\n');
fprintf(fileID,'203 {Le/2} {He} {-0}\n');
fprintf(fileID,'204 {Le/2} {-0} {-0}\n');
fprintf(fileID,'205 {Le/2} {0} {Pe+0}\n');
fprintf(fileID,'206 {0} {0} {Pe}\n');
fprintf(fileID,'207 {0} {He} {Pe}\n');
fprintf(fileID,'208 {Le/2} {He} {Pe}\n\n');

fprintf(fileID,'//_________________________________________________\n');
fprintf(fileID,'// ____________Enclosure part______________________\n');
fprintf(fileID,'//_________________________________________________\n\n');
fprintf(fileID,'Elements "Enclosure-int" \n RefNodes="NF"\n SubDomain=1\n');
fprintf(fileID,' 1003 5 6 7 8\n1006 3 4 5 8\n 1005 1 6 5 4 \n\n');
fprintf(fileID,'off  WallImpedance\n  RefElements="Enclosure-int"\n  ImpType=Damping\n  Value=0.01\n\n');
fprintf(fileID,'Infinite_Baffle  "IB Front"\n  Subdomain=3 \n  Position=y \n\n');
fprintf(fileID,'Elements "Enclosure-exterior" \n  RefNodes="NF"\n  SubDomain=3\n  SwapNormals=true\n');
fprintf(fileID,'  2003 205 206 207 208\n  2006 203 204 205 208\n\n');
fprintf(fileID,'//_______________________________________________\n// ____________vented part_______________________\n//_______________________________________________\n\n// Inner boundary of vent\n');
fprintf(fileID,' Duct "Vent-Inner"\n  DuctType=Circle\n  SubDomain=2\n  Dd={Ddv}\n  Len={Lev}\n\n');
fprintf(fileID,'// Interface between vent and cabinet \nTransition "I-Vent-Inner"\n  Subdomain=2,1\n  RefElement="Vent-Inner"\n  RefEdge=2\n\n');
fprintf(fileID,'// Interface between outside and vent \nTransition "I-Vent-Outer"\n  Subdomain=3,2\n  RefElement="Vent-Inner"\n  RefEdge=1\n\n\n');
fprintf(fileID,'//__________________________________________________\n// __________baffle+ position of elements___________\n//__________________________________________________\n// Front of cabinet, which belongs to exterior boundaries.;\n\n\n');
fprintf(fileID,'Baffle "Exterior"\n  Subdomain=3\n  Vertices=201,202,203,204  "NF"\n  105  Ref="Cone front"   y={0}  x={0.25*He}\n108  Ref="Tweeter front"   y={0}  x={0.75*He}\n\n');
fprintf(fileID,'Baffle "interior" \n  Subdomain=1 \n SwapNormals=true\n  Vertices=1,2,3,4  "NF"\n  106  Ref="Cone rear"   y={0}  x={0.25*He-d}\n  107  Ref="Tweeter rear"   y={0}  x={0.75*He-d}\n');
fprintf(fileID,'Baffle "ventbExterior"\n  Subdomain=3\n  Vertices=202,207,208,203  "NF"\n  102  Ref="Vent-Inner"   x={Pe/2}  y=0mm\n\n');
fprintf(fileID,'  Baffle "ventbinterior"\n  Subdomain=1\n  SwapNormals=true\n  Vertices=2,7,8,3  "NF"\n  109  Ref="Vent-Inner"   x={Pe/2-d} y=0mm\n\n');

fprintf(fileID,'//_________________________________________________\n');
fprintf(fileID,'// ____________speaker part________________________\n');
fprintf(fileID,'//_________________________________________________\n\n\n');


fprintf(fileID,'Diaphragm  "Cone front"\n');
fprintf(fileID,'DrvGroup=1001       // Driving group link to observation stage\n');
fprintf(fileID,'  SubDomain=3      // Front side belongs to sub-domain 2\n');
fprintf(fileID,'  NoBaffle\n');
fprintf(fileID,'  Simple=true         // Simple model\n');
fprintf(fileID,'  Side=Front          // Creates elements for the front side of the diaphragm\n');
fprintf(fileID,'   dD={dDw}            // Diameter of cone\n');
fprintf(fileID,'   tD1={tD1w}           // Inner depth of cone to base of dust cap\n');
fprintf(fileID,'  dD1={dD1w}           // Diameter of dust cap\n');
fprintf(fileID,'  hD1={hD1w}          // Height of dust cap\n\n');         
    

fprintf(fileID,'Diaphragm  "Cone rear"\n');
fprintf(fileID,' Side=Rear                    // This is the rear side of the diaphragm\n');
fprintf(fileID,'  DrvGroup=1002                // Driving group link to observation stage\n');
fprintf(fileID,'  SubDomain=1                  // This side belongs to sub-domain SubDomain=1\n');
fprintf(fileID,'  RefDiaph="Cone front"        // Inherite from "Cone front"\n');
fprintf(fileID,'  HasBaffle=false//true\n\n');

fprintf(fileID,'Diaphragm  "tweeter front"\n');
fprintf(fileID,'    DrvGroup=1003       // Driving group link to observation stage\n');
fprintf(fileID,'  SubDomain=3      // Front side belongs to sub-domain 2  \n    ');
fprintf(fileID,'  NoBaffle\n');
fprintf(fileID,'  Simple=true         // Simple model\n');
fprintf(fileID,'  Side=Front          // Creates elements for the front side of the diaphragm\n');
fprintf(fileID,'  dD={dDt}            // Diameter of cone\n');
fprintf(fileID,'   tD1={tD1t}           // Inner depth of cone to base of dust cap\n');
fprintf(fileID,'  dD1={dD1t}           // Diameter of dust cap\n');
fprintf(fileID,'  hD1={hD1t}            // Height of dust cap         \n\n');
    

fprintf(fileID,'Diaphragm  "tweeter rear"\n');
fprintf(fileID,' Side=Rear                    // This is the rear side of the diaphragm\n');
fprintf(fileID,'  DrvGroup=1004                // Driving group link to observation stage\n');
fprintf(fileID,'  SubDomain=1                  // This side belongs to sub-domain SubDomain=1\n');
fprintf(fileID,'  RefDiaph="tweeter front"        // Inherite from "Cone front"\n');
fprintf(fileID,'  HasBaffle=false//true\n\n');

fclose(fileID);

%% Create the Le script
%% Open the file
name.system=sprintf('LeScript.txt');
fileID = fopen(name.system,'w');

fprintf(fileID,' //*****************************************************************************\n');
fprintf(fileID,' //\n');
fprintf(fileID,' // ABEC2 Lumped Element File\n');
fprintf(fileID,' //\n');
fprintf(fileID,' //*****************************************************************************\n\n\n');

fprintf(fileID,' // Thiele-Small parameter of electro-dynamic driver\n');
fprintf(fileID,' // Note, no diaphragm dimensions to be specified in this script.\n');
fprintf(fileID,'Def_Driver ''%s''\n',speaker.name);
fprintf(fileID,' Re=%gohm \n',speaker.Re);
fprintf(fileID,' Mms=%gg \n',speaker.Mms);
fprintf(fileID,' Bl=%gN/A\n',speaker.Bl);
fprintf(fileID,' fs=%gHz  Qms=%g  Qes=%g\n',speaker.fs,speaker.Qms,speaker.Qes);
fprintf(fileID,' Le=%gH\n\n',speaker.Le);

fprintf(fileID,'Def_Driver ''%s''\n',speaker2.name);
fprintf(fileID,'  Mms=%gg  \n',speaker2.Mms);
fprintf(fileID,'  Re=%gohm ExpoRe=0.824\n',speaker2.Re);
fprintf(fileID,'  fs=%gHz    Qes=%g Qms=%g\n',speaker2.fs,speaker2.Qes,speaker2.Qms);
fprintf(fileID,'  Le=%gH\n\n',speaker2.Le);
  
fprintf(fileID,' // Driving value of LE network (here using formula to convert dB to voltage)\n');

fprintf(fileID,'Def_Driving "Driving"\n');
fprintf(fileID,'  Value={0.707*2}  \n');
fprintf(fileID,'  IsRms\n\n');

fprintf(fileID,' // Lumped element network \n');
  
fprintf(fileID,'System ''S1''\n');
fprintf(fileID,'// filtre passe bas second ordre Linkwitz-Riley\n');
fprintf(fileID,'  Coil ''L2''\n');
fprintf(fileID,'   Node=2=3  L=%gH\n',Filter.L2);
fprintf(fileID,'  Capacitor ''C2''\n');
fprintf(fileID,'   Node=3=0  C=%gF\n\n',Filter.C2);

fprintf(fileID,'// Filtre compensation impedance %s\n',speaker.name);
fprintf(fileID,'//  Capacitor ''Cb''\n');
fprintf(fileID,'//   Node=3=8  C=%gF\n',Filter.Cb);
fprintf(fileID,'//  Resistor  ''Rt''\n ');
fprintf(fileID,'//   Node=8=0  R=%g\n\n',Filter.Rcb);	

fprintf(fileID,'// Generator resistance of wires etc\n');	
fprintf(fileID,'  Resistor ''Rg'' R=0.1ohm\n');
fprintf(fileID,'   Node=1=2\n\n');

fprintf(fileID,'// Speaker electro-acoustic\n');
fprintf(fileID,'  Driver  ''Drv1''  Def=''%s''\n',speaker.name);
fprintf(fileID,'   Node=3=0=10=20   DrvGroup=1001,1002  // Link to BE\n');
fprintf(fileID,'  RadImp ''Front''                         // Radiation impedance of external domain\n');
fprintf(fileID,'   Node=10	DrvGroup=1001            // Link to BE\n');
fprintf(fileID,'  RadImp ''Rear''                          // Radiation impedance of enclosure\n');
fprintf(fileID,'   Node=20  DrvGroup=1002            // Link to BE\n\n');
 
fprintf(fileID,'//filtre passe haut second ordre Linkwitz-Riley\n');
fprintf(fileID,'  Coil ''L1''\n');
fprintf(fileID,'   Node=4=0  L=%gH\n',Filter.L1);
fprintf(fileID,'  Capacitor ''C1''\n');
fprintf(fileID,'   Node=2=4  C=%gF\n\n',Filter.C1);
   
fprintf(fileID,'// attenuateur\n');
fprintf(fileID,'// Resistor  ''%g''  Node=4=15  R=2ohm\n',Filter.R1);
fprintf(fileID,'// Resistor  ''%g''  Node=15=0  R=20ohm\n',Filter.R2);

fprintf(fileID,'  Driver  ''Drv2''  Def=''%s''\n',speaker2.name);
fprintf(fileID,'   Node=4=0=12=22   DrvGroup=1003,1004\n');
	
fprintf(fileID,'  RadImp ''Front2''                         // Radiation impedance of external domain\n');
fprintf(fileID,'   Node=12     DrvGroup=1003            // Link to BE\n');
fprintf(fileID,'  RadImp ''Rear2''                          // Radiation impedance of enclosure\n');
fprintf(fileID,'   Node=22     DrvGroup=1004 \n ');

fclose(fileID);

end