#include "../Header/bassreflex.h"
#include "../Header/speaker.h"
#include "../Header/Filter.h"

bassReflex::bassReflex(): Enclosure()
{
    lectureFile();
    calculateEnclosureParameters();
    akabakBassReflexScript();
    tweeteradd();

}

bassReflex::bassReflex(speaker &speakerbass): Enclosure(speakerbass)
{
    lectureFile();
    calculateEnclosureParameters();
    akabakBassReflexScript();
    tweeteradd();

}


bassReflex::~bassReflex()
{
    delete m_f3 ;
    delete m_fb ;

}

void bassReflex::tweeteradd()
{
    cout <<endl<< "Do you want to add a tweeter, calculate filters and produce an Abec Script? " << endl;
    cout << "1 Yes" << endl;
    cout << "2 No" << endl;
    int choice2;
    while(choice2 != 1 && choice2 != 2)
    {
        cin >>  choice2;
        if (choice2==1)
            {
                m_speakertweet= new speaker();
                m_parameters2=m_speakertweet->parameters();
                AbecBassReflexScript();
                Filter filtre(m_speakerbass, m_speakertweet);
                delete m_speakertweet;
            }
        else if (choice2==2)
            {

            }
        else
            {
                cout << "Choice are 1 or 2" << endl;
            }
    }
}
void bassReflex::lectureFile()
{
    //The function read the abak table and extract the value corresponding for different value of Qts
    //
    double Qts=m_speakerbass->returnQts();
    string NumbernameFile[sizeQ]={"BB4","QB3","C4"};
    //double Qtc[sizeQtc]={0.500,0.577,0.707,0.800,0.900,1.000,1.100,1.200,1.500};
    string nameFile;
    vector<vector<double>  > grille;// grille de vecteur

    double qtsTemp,alphaTemp,fbTemp,f3Temp,peakdBTemp;//declare value for temp stock
    int line;// declare value of the line in the field
    int pos,nbrRetour(0);// pos of the smallest value, number of line in return

    for(int ii(0);ii<sizeQ;ii++) //sizeQtc
    {
            line=0;
            nameFile="bassreflex/"+NumbernameFile[ii]+"QL7.txt";//read all the file
            ifstream monFlux(nameFile.c_str());
            if(monFlux)
            {
                while(!monFlux.eof())// retreive all the data in the file and put them in grille
                {
                    grille.push_back(vector<double>(5));
                    monFlux >> qtsTemp>>fbTemp>>alphaTemp>>f3Temp>>peakdBTemp;
                    grille[line][0] = qtsTemp ;
                    grille[line][1] = fbTemp;
                    grille[line][2] = alphaTemp;
                    grille[line][3] = f3Temp ;
                    grille[line][4] = peakdBTemp ;
                   // cout<< grille[line][0]<<" "<< grille[line][1]<<" "<< grille[line][2]<<" "<< endl;
                    line++;
                }
                pos=findNearestValueArray2D(grille, Qts);//find the nearest value
                if (pos>0)
                {
                     m_tabParam.push_back(vector<double>(5));// add line of the nearest value
                     m_tabParam[nbrRetour][0]=grille[pos][0];// Qts
                     m_tabParam[nbrRetour][1]=grille[pos][1];// fb/fs frequency of the resonator
                     m_tabParam[nbrRetour][2]=grille[pos][2];// alpha
                     m_tabParam[nbrRetour][3]=grille[pos][3];// f3
                     m_tabParam[nbrRetour][4]=grille[pos][4];// surpeak db


                     m_QPossible.push_back(NumbernameFile[ii]);
                     nbrRetour++;
                }
                else
                    cout << "Value of Qts given too far from the abak table Q ="<<NumbernameFile[ii]<<endl;


            }
            else
                cout << "Unable to open file of the abak" << endl;
            monFlux.close();
            grille.clear();
    }
        if (m_tabParam.size()==0)
        {
            cout<< "Value of Qts given too far from the abak table of all Qtc, there is no available closed box configuration"<< endl;
        }

}



void bassReflex::calculateEnclosureParameters()
{
    //calculate the enclosure parameters from extracted data

    int nbrConfig=(m_tabParam.size());
    if (nbrConfig==0)
    {
        cout<< "The table of initial parameter is empty"<< endl;
        return;
    }

    m_volume = new double [nbrConfig];
    m_f3 = new double[nbrConfig];
    m_fb = new double[nbrConfig];

    for(int ii(0);ii<nbrConfig;ii++)
    {
        m_volume[ii]=m_parameters[5]/m_tabParam[ii][2];//Vas/alpha
        m_fb[ii]=m_parameters[0]*m_tabParam[ii][1];// value of the box resonance
        m_f3[ii]=m_tabParam[ii][2]*m_parameters[0];// -3db cut off f3 tab* fs

        //define the different dimension of the box
            Eigen::MatrixXd sol(6,1);
            sol= newtonMethodSolver(m_thickness,m_volume[ii]);
            m_boxDimension.push_back(vector<double>(6));
           // afficherBoxDimension(sol);
            for (int j=0;j<6;j++)
            {
                m_boxDimension[ii][j]=sol(j,0);
            }
    }
   // akabakbassReflexScript(diffraction,volume,m_tabParam,speakerbass,m_parameters,boxDimension);

//00 m_fs
//01 m_Qes
//02 m_Qtc
//03 m_Qts
//04 m_Qms
//05 m_Vas
//06 m_dD
//07 m_dD1
//08 m_tD1
//09 m_hD1
//10 m_Re
//11 m_Mms
//12 m_Le



}

void bassReflex::akabakBassReflexScript()
{
    string const associedParameters(m_speakerbass->nameParameters());
    string strFileName="GeneratedScript/bassreflex.aks";
    ofstream ofsaveSpeaker(strFileName.c_str());
    ofsaveSpeaker <<"Def_Driver  '"<< m_speakerbass->getName()<<"' \n";


    //cout << m_parameters[7];
    if(m_parameters[7]!=0)
    ofsaveSpeaker <<"dD="<<m_parameters[6] <<"cm  |Piston \n";
    else return;

    if(m_parameters[0]!=0 && m_parameters[11]!=0 && m_parameters[4]!=0)
    ofsaveSpeaker <<"fs="<<m_parameters[0] <<"Hz  Mms="<< m_parameters[11]<<"g  Qms="<<m_parameters[4] <<" \n";
    else return;


    if(m_parameters[8]!=0 && m_parameters[7]!=0)
    ofsaveSpeaker <<"dD1="<<m_parameters[7]<<"cm  tD1="<<m_parameters[8]<<"cm \n";

    if(m_parameters[1]!=0 && m_parameters[10]!=0 && m_parameters[12]!=0)
    ofsaveSpeaker <<"Qes="<< m_parameters[1]<< " Re="<<m_parameters[10]<<"ohm  Le="<<m_parameters[12]<<"mH  ExpoLe=0.618 \n \n";
    else return;


    for (int ii(0);ii<m_tabParam.size();ii++)
    {
        ofsaveSpeaker <<"System 'S"<<ii<<"_BR_QL7_"<<m_QPossible[ii]<<"' \n \n";
        ofsaveSpeaker <<"Driver 'D1' Def='"<<m_speakerbass->getName()<<"' Node=0=1=2=21\n";
        ofsaveSpeaker <<"Enclosure    'E1'  Node=2\n ";
        ofsaveSpeaker <<" Vb="<<m_volume[ii]<<"L  Qb/fo=1 Lb="<<m_boxDimension[ii][4]<<"m Sb="<<m_boxDimension[ii][4]*m_boxDimension[ii][3]<<"m2\n";
        ofsaveSpeaker << "fb="<<m_fb[ii]<<"Hz  dD="<<m_parameters[06]/3<<"cm \n \n";
        ofsaveSpeaker <<" Radiator  'Rad1'  Def='D1' Node=21 \n";
        ofsaveSpeaker <<"x=0  y=0  z=0cm  HAngle=0  VAngle=0 \n";
        if (m_diffraction==1)
            ofsaveSpeaker <<"  HEdge="<<m_boxDimension[ii][4]<<"m WEdge="<<m_boxDimension[ii][3]<<"m\n \n \n ";
    }

ofsaveSpeaker.close();
    cout<<"Write akabak script for bass reflex: done"<<endl;

}


void bassReflex::AbecBassReflexScript()
{
// This function allows to generate script for akabak in order to calculate bass reflex frequency response
//
//// Open the file
string const associedParameters(m_speakerbass->nameParameters());
int nbrConfig=(m_tabParam.size());
    if (nbrConfig==0)
    {
        cout<< "The table of initial parameter is empty"<< endl;
        return;
    }

    FILE * pFile;
    char strFileName[0x100];

    for(int ii(0);ii<nbrConfig;ii++)
    {
        snprintf(strFileName,sizeof(strFileName),"Abec_vertices/SolvingBassReflex_%s.txt",m_QPossible[ii].c_str());
        pFile=fopen(strFileName,"w");

        if (pFile!=NULL)
        {
                 // write control solver
            fprintf(pFile,"Control_Solver \n");
            fprintf(pFile,"f1=20;  f2=500;  NumFrequencies=10;  Abscissa=log; \n");
            fprintf(pFile,"ImpedanceNumFrequencies=250 \n");
            fprintf(pFile,"Dim=3D \n");
            fprintf(pFile,"Sym=x \n");
            fprintf(pFile,"MeshFrequency=500Hz \n\n\n");



        // Define subdomain
        fprintf(pFile,"SubDomain_Properties 'Enclosure'\n");
        fprintf(pFile,"SubDomain=1\n");
        fprintf(pFile,"ElType=Interior \n");
        fprintf(pFile,"Color='Green'\n\n");

        fprintf(pFile,"SubDomain_Properties 'Vent'\n");
        fprintf(pFile,"SubDomain=2\n");
        fprintf(pFile,"ElType=Interior \n");
        fprintf(pFile," Color='blue'\n\n");

        fprintf(pFile,"SubDomain_Properties 'Exterior'\n");
        fprintf(pFile,"SubDomain=3 \n");
        fprintf(pFile," ElType=Exterior //Radiation to infinity\n\n\n");


        // Define formula value

        fprintf(pFile,"Formula \"taille\"\n");
        fprintf(pFile,"{\n\n");
//m_boxDimension[ii][j]
        fprintf(pFile,"He=%lf; // Hauteur exterieur\n",m_boxDimension[ii][1]);
        fprintf(pFile,"Le=%lf; //Longueur exterieur\n",m_boxDimension[ii][0]);
        fprintf(pFile,"Pe=%lf; // Profondeur exterieur\n\n",m_boxDimension[ii][2]);

        fprintf(pFile,"hi=%lf;// Hauteur exterieur\n",m_boxDimension[ii][4]);
        fprintf(pFile,"li=%lf;// Longueur exterieur\n",m_boxDimension[ii][3]);
        fprintf(pFile,"pin=%lf;// Profondeur exterieur\n\n",m_boxDimension[ii][5]);

        fprintf(pFile,"d=%lf;//thichness of the wood pannel\n\n",m_thickness);
        if (m_parameters[6]!=0)
        fprintf(pFile,"dDw=%lf; // Diameter of cone\n",m_parameters[6]*1e-2);
        else
            {
                printf("Abec script aborted\nMissing basic dimension dD for the woofer");
                return;
            }

        if (m_parameters[7]!=0&& m_parameters[8]!=0&& m_parameters[9]!=0)
        {
            fprintf(pFile,"tD1w=%lf; // Inner depth of cone to base of dust cap\n",m_parameters[7]*1e-2);
            fprintf(pFile,"dD1w=%lf; // Diameter of dust cap\n",m_parameters[8]*1e-2);
            fprintf(pFile,"hD1w=%lf;  // Height of dust cap  \n\n",m_parameters[9]*1e-2);
        }

        else
       {
            printf("Abec script aborted\n Missing basic dimensions such as tD1, dD1 and hD1 for the woofer ");
            return;
       }


        if (m_parameters2[7]!=0&& m_parameters2[8]!=0&& m_parameters2[9]!=0)
        {
            fprintf(pFile,"dDt=%lf;        // Diameter of cone\n",m_parameters2[6]*1e-2);
            fprintf(pFile,"tD1t=%lf;       // Inner depth of cone to base of dust cap\n",m_parameters2[7]*1e-2);
            fprintf(pFile,"dD1t=%lf;    // Diameter of dust cap\n",m_parameters2[8]*1e-2);
            fprintf(pFile,"hD1t=%lf;   // Height of dust cap \n\n",m_parameters2[9]*1e-2);
        }

        else
        {
            printf("Abec script aborted\n Missing basic dimensions such as dD,tD1, dD1 and hD1 for the tweeter ");
            return;
        }


        fprintf(pFile,"Ddv=%lf; //diameter vent\n",m_parameters2[6]/3*0.01);
        double Leduct(23562.5*pow(m_parameters2[6]/3,2)/(m_volume[ii]*pow(m_fb[ii],2)-0.632*m_parameters2[6]/3)*0.01);
        fprintf(pFile,"Lev=%lf; //length vent\n\n}\n\n\n",Leduct);

        fprintf(pFile,"//_________________________________________________\n// ____________Nodes definition_______________________\n//_________________________________________________\n\n");
        fprintf(pFile,"Nodes   \"NF\"\n //--------- Interior--------------------\n//---------------------------------------\n\n");
        fprintf(pFile,"Scale=1m\n");

        fprintf(pFile,"1 {0} {+d} {d}\n");
        fprintf(pFile,"2 {0} {hi+d} {d}\n");
        fprintf(pFile,"3 {li/2} {hi+d} {d}\n");
        fprintf(pFile,"4 {li/2} {+d} {d}\n");
        fprintf(pFile,"5 {li/2} {+d} {pin+d}\n");
        fprintf(pFile,"6 {0} {+d} {pin+d}\n");
        fprintf(pFile,"7 {0} {hi+d} {pin+d}\n");
        fprintf(pFile,"8 {li/2} {hi+d} {pin+d}\n\n");

        fprintf(pFile,"//---------Exterior--------------------\n//--------------------------------------\n\n");
        fprintf(pFile,"201 {0} {0} {0}\n");
        fprintf(pFile,"202 {0} {He} {-0}\n");
        fprintf(pFile,"203 {Le/2} {He} {-0}\n");
        fprintf(pFile,"204 {Le/2} {-0} {-0}\n");
        fprintf(pFile,"205 {Le/2} {0} {Pe+0}\n");
        fprintf(pFile,"206 {0} {0} {Pe}\n");
        fprintf(pFile,"207 {0} {He} {Pe}\n");
        fprintf(pFile,"208 {Le/2} {He} {Pe}\n\n");

        fprintf(pFile,"//_________________________________________________\n");
        fprintf(pFile,"// ____________Enclosure part______________________\n");
        fprintf(pFile,"//_________________________________________________\n\n");
        fprintf(pFile,"Elements \"Enclosure-int\" \n RefNodes=\"NF\"\n SubDomain=1\n");
        fprintf(pFile," 1003 5 6 7 8\n1006 3 4 5 8\n 1005 1 6 5 4 \n\n");
        fprintf(pFile,"off  WallImpedance\n  RefElements=\"Enclosure-int\"\n  ImpType=Damping\n  Value=0.01\n\n");
        fprintf(pFile,"Infinite_Baffle  \"IB Front\"\n  Subdomain=3 \n  Position=y \n\n");
        fprintf(pFile,"Elements \"Enclosure-exterior\" \n  RefNodes=\"NF\"\n  SubDomain=3\n  SwapNormals=true\n");
        fprintf(pFile,"  2003 205 206 207 208\n  2006 203 204 205 208\n\n");
        fprintf(pFile,"//_______________________________________________\n// ____________vented part_______________________\n//_______________________________________________\n\n// Inner boundary of vent\n");
        fprintf(pFile," Duct \"Vent-Inner\"\n  DuctType=Circle\n  SubDomain=2\n  Dd={Ddv}\n  Len={Lev}\n\n");
        fprintf(pFile,"// Interface between vent and cabinet \nTransition \"I-Vent-Inner\"\n  Subdomain=2,1\n  RefElement=\"Vent-Inner\"\n  RefEdge=2\n\n");
        fprintf(pFile,"// Interface between outside and vent \nTransition \"I-Vent-Outer\"\n  Subdomain=3,2\n  RefElement=\"Vent-Inner\"\n  RefEdge=1\n\n\n");
        fprintf(pFile,"//__________________________________________________\n// __________baffle+ position of elements___________\n//__________________________________________________\n// Front of cabinet, which belongs to exterior boundaries.;\n\n\n");
        fprintf(pFile,"Baffle \"Exterior\"\n  Subdomain=3\n  Vertices=201,202,203,204  \"NF\"\n  105  Ref=\"Cone front\"   y={0}  x={0.25*He}\n108  Ref=\"Tweeter front\"   y={0}  x={0.75*He}\n\n");
        fprintf(pFile,"Baffle \"interior\" \n  Subdomain=1 \n SwapNormals=true\n  Vertices=1,2,3,4  \"NF\"\n  106  Ref=\"Cone rear\"   y={0}  x={0.25*He-d}\n  107  Ref=\"Tweeter rear\"   y={0}  x={0.75*He-d}\n");
        fprintf(pFile,"Baffle \"ventbExterior\"\n  Subdomain=3\n  Vertices=202,207,208,203  \"NF\"\n  102  Ref=\"Vent-Inner\"   x={Pe/2}  y=0mm\n\n");
        fprintf(pFile,"  Baffle \"ventbinterior\"\n  Subdomain=1\n  SwapNormals=true\n  Vertices=2,7,8,3  \"NF\"\n  109  Ref=\"Vent-Inner\"   x={Pe/2-d} y=0mm\n\n");

        fprintf(pFile,"//_________________________________________________\n");
        fprintf(pFile,"// ____________speaker part________________________\n");
        fprintf(pFile,"//_________________________________________________\n\n\n");


        fprintf(pFile,"Diaphragm  \"Cone front\"\n");
        fprintf(pFile,"DrvGroup=1001       // Driving group link to observation stage\n");
        fprintf(pFile,"  SubDomain=3      // Front side belongs to sub-domain 2\n");
        fprintf(pFile,"  NoBaffle\n");
        fprintf(pFile,"  Simple=true         // Simple model\n");
        fprintf(pFile,"  Side=Front          // Creates elements for the front side of the diaphragm\n");
        fprintf(pFile,"   dD={dDw}            // Diameter of cone\n");
        fprintf(pFile,"   tD1={tD1w}           // Inner depth of cone to base of dust cap\n");
        fprintf(pFile,"  dD1={dD1w}           // Diameter of dust cap\n");
        fprintf(pFile,"  hD1={hD1w}          // Height of dust cap\n\n");


        fprintf(pFile,"Diaphragm  \"Cone rear\"\n");
        fprintf(pFile," Side=Rear                    // This is the rear side of the diaphragm\n");
        fprintf(pFile,"  DrvGroup=1002                // Driving group link to observation stage\n");
        fprintf(pFile,"  SubDomain=1                  // This side belongs to sub-domain SubDomain=1\n");
        fprintf(pFile,"  RefDiaph=\"Cone front\"        // Inherite from \"Cone front\"\n");
        fprintf(pFile,"  HasBaffle=false//true\n\n");

        fprintf(pFile,"Diaphragm  \"tweeter front\"\n");
        fprintf(pFile,"    DrvGroup=1003       // Driving group link to observation stage\n");
        fprintf(pFile,"  SubDomain=3      // Front side belongs to sub-domain 2  \n    ");
        fprintf(pFile,"  NoBaffle\n");
        fprintf(pFile,"  Simple=true         // Simple model\n");
        fprintf(pFile,"  Side=Front          // Creates elements for the front side of the diaphragm\n");
        fprintf(pFile,"  dD={dDt}            // Diameter of cone\n");
        fprintf(pFile,"   tD1={tD1t}           // Inner depth of cone to base of dust cap\n");
        fprintf(pFile,"  dD1={dD1t}           // Diameter of dust cap\n");
        fprintf(pFile,"  hD1={hD1t}            // Height of dust cap         \n\n");


        fprintf(pFile,"Diaphragm  \"tweeter rear\"\n");
        fprintf(pFile," Side=Rear                    // This is the rear side of the diaphragm\n");
        fprintf(pFile,"  DrvGroup=1004                // Driving group link to observation stage\n");
        fprintf(pFile,"  SubDomain=1                  // This side belongs to sub-domain SubDomain=1\n");
        fprintf(pFile,"  RefDiaph=\"tweeter front\"        // Inherite from \"Cone front\"\n");
        fprintf(pFile,"  HasBaffle=false//true\n\n");
        printf("Solving file for %s configuration written \n",m_QPossible[ii].c_str());

        }
        fclose(pFile);
    }
}
