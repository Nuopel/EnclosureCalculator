#include "../Header/ClosedBoxCalculator.h"
#include "../Header/speaker.h"

closedbox::closedbox(): Enclosure()
{
    lectureFile();
    calculateEnclosureParameters();
    akabakClosedBoxScript();
}

closedbox::closedbox(speaker &speakerbass): Enclosure(speakerbass)
{
    lectureFile();
    calculateEnclosureParameters();
    akabakClosedBoxScript();

}
closedbox::closedbox(Enclosure &initEnclosure)
{
}
closedbox::~closedbox()
{
    delete m_fc ;
    delete m_f3 ;
}
void closedbox::lectureFile()
{
    //The function read the abak table and extract the value corresponding for different value of Qts
    //
    double Qts=m_speakerbass->returnQts();
    string NumbernameFile[sizeQtc]={"500","577","707","800","900","1000","1100","1200","1500"};
    double Qtc[sizeQtc]={0.500,0.577,0.707,0.800,0.900,1.000,1.100,1.200,1.500};

    string nameFile;
    vector<vector<double>  > grille;// grille de vecteur

    double qtsTemp,alphaTemp,fbTemp;//declare value for temp stock
    int line;// declare value of the line in the field
    int pos,nbrRetour(0);// pos of the smallest value, number of line in return

    for(int ii(0);ii<sizeQtc;ii++) //sizeQtc
    {
            line=0;
            nameFile="close/closeQtc0_"+NumbernameFile[ii]+".txt";//read all the file
            ifstream monFlux(nameFile.c_str());
            if(monFlux)
            {
                while(!monFlux.eof())// retreive all the data in the file and put them in grille
                {
                    grille.push_back(vector<double>(3));
                    monFlux >> qtsTemp>>alphaTemp>>fbTemp;
                    grille[line][0] = qtsTemp ;
                    grille[line][1] = alphaTemp;
                    grille[line][2] = fbTemp ;
                   // cout<< grille[line][0]<<" "<< grille[line][1]<<" "<< grille[line][2]<<" "<< endl;
                    line++;
                }
                pos=findNearestValueArray2D(grille, Qts);//find the nearest value
                if (pos>0)
                {
                     m_tabParam.push_back(vector<double>(3));// add line of the nearest value
                     m_tabParam[nbrRetour][0]=grille[pos][0];// Qts
                     m_tabParam[nbrRetour][1]=grille[pos][1];// alpha
                     m_tabParam[nbrRetour][2]=grille[pos][2];// fb
                     m_qtcPossible.push_back(Qtc[ii]);
                     nbrRetour++;
                }
                else
                    cout << "Value of Qts given too far from the abak table Qtc="<<NumbernameFile[ii]<<endl;


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



void closedbox::calculateEnclosureParameters()
{
    //calculate the enclosure parameters from extracted data

    int nbrConfig=(m_tabParam.size());
    if (nbrConfig==0)
    {
        cout<< "The table of initial parameter is empty"<< endl;
        return;
    }

    m_volume = new double [nbrConfig];
    m_fc = new double [nbrConfig];
    m_f3 = new double[nbrConfig];
    double qtc[sizeQtc] = {0.500,0.577,0.707,0.800,0.900,1.000,1.100,1.200,1.500};



    for(int ii(0);ii<nbrConfig;ii++)
    {
        m_volume[ii]=m_parameters[5]/m_tabParam[ii][1];
        m_fc[ii]=m_qtcPossible[ii]*m_parameters[0]/m_parameters[3];
        m_f3[ii]=pow((1/(m_qtcPossible[ii]*m_qtcPossible[ii])-2+sqrt(pow(1./pow(m_qtcPossible[ii],2)-2,2)+4))/2,0.5)*m_fc[ii];// -3db cut off

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
   // akabakClosedBoxScript(diffraction,volume,m_tabParam,speakerbass,m_parameters,boxDimension);

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

void closedbox::akabakClosedBoxScript()
{
    string const associedParameters(m_speakerbass->nameParameters());
    string strFileName="GeneratedScript/closed.aks";
    ofstream ofsaveSpeaker(strFileName.c_str());
    ofsaveSpeaker <<"Def_Driver  '"<< m_speakerbass->getName()<<"' \n";
   // vector<string> QtcPossible(m_speakerbass->QtcPossible());

    //cout << m_parameters[7];
    if(m_parameters[7]!=0)
    ofsaveSpeaker <<"dD="<<m_parameters[6] <<"cm  |Piston \n";
    else return;

    if(m_parameters[0]!=0 && m_parameters[11]!=0 && m_parameters[4]!=0)
    ofsaveSpeaker <<"fs="<<m_parameters[0] <<"Hz  Mms="<< m_parameters[11]<<"g  Qms="<<m_parameters[4] <<" \n";
    else return;


    if(m_parameters[8]!=0 && m_parameters[6]!=0)
    ofsaveSpeaker <<"dD1="<<m_parameters[7]<<"cm  tD1="<<m_parameters[8]<<"cm \n";

    if(m_parameters[1]!=0 && m_parameters[10]!=0 && m_parameters[12]!=0)
    ofsaveSpeaker <<"Qes="<< m_parameters[1]<< " Re="<<m_parameters[10]<<"ohm  Le="<<m_parameters[12]<<"mH  ExpoLe=0.618 \n \n";
    else return;


    for (int ii(0);ii<m_tabParam.size();ii++)
    {
        ofsaveSpeaker <<"System 'S"<<ii<<"_clos_Qtc_"<<m_qtcPossible[ii]<<"'";
        ofsaveSpeaker <<"Driver 'D1' Def='"<<m_speakerbass->getName()<<"' Node=0=1=2=21\n";
        ofsaveSpeaker <<"Enclosure    'E1'  Node=2\n ";
        ofsaveSpeaker <<" Vb="<<m_volume[ii]<<"L  Qb/fo=1 Lb="<<m_boxDimension[ii][4]<<"m Sb="<<m_boxDimension[ii][4]*m_boxDimension[ii][3]<<"m2\n";
        ofsaveSpeaker <<" Radiator  'Rad1'  Def='D1' Node=21 \n";
        ofsaveSpeaker <<"x=0  y=0  z=0cm  HAngle=0  VAngle=0 \n  \n";
        if (m_diffraction==1)
            ofsaveSpeaker <<"  HEdge="<<m_boxDimension[ii][4]<<"m WEdge="<<m_boxDimension[ii][3]<<"m\n \n \n ";
    }

ofsaveSpeaker.close();
    cout<<"Write akabak script: done"<<endl;

}
