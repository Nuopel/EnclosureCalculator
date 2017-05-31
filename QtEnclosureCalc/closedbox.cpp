#include <closedbox.h>
#include <newtonsolver.h>
#define sizeQtc 9

Closedbox::Closedbox(Speaker &speakerbass2copy)//: Enclosure()
{
  speakerbass = &speakerbass2copy;
}
Closedbox::Closedbox(Speaker &speakerbass2copy,Speaker &speakermid2copy)
{
  speakerbass = &speakerbass2copy;
  speakermid = &speakermid2copy;
}

Closedbox::Closedbox(Speaker &speakerbass2copy, Speaker &speakermid2copy, Speaker &speakertw2copy)
{
    speakerbass = &speakerbass2copy;
    speakermid  = &speakermid2copy;
    speakertw   = &speakertw2copy;

}

Closedbox::~Closedbox()
{
    delete m_fc ;
    delete m_f3 ;
}
void Closedbox::lectureFile()
{
    //The function read the abak table and extract the value corresponding for different value of Qts
    //
    double qts = speakerbass->returnQts();
    string NumbernameFile[sizeQtc]={"500","577","707","800","900","1000","1100","1200","1500"};
    double qtc[sizeQtc]={0.500,0.577,0.707,0.800,0.900,1.000,1.100,1.200,1.500};

    string nameFile;
    QVector<QVector<double>  > grille;// grille de vecteur

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
                    grille.push_back(QVector<double>(3));
                    monFlux >> qtsTemp>>alphaTemp>>fbTemp;
                    grille[line][0] = qtsTemp;
                    grille[line][1] = alphaTemp;
                    grille[line][2] = fbTemp;
                   // cout<< grille[line][0]<<" "<< grille[line][1]<<" "<< grille[line][2]<<" "<< endl;
                    line++;
                }
                pos=findNearestValueArray2D(grille, qts);//find the nearest value
                if (pos>0)
                {
                     m_tabParam.push_back(QVector<double>(3));// add line of the nearest value
                     m_tabParam[nbrRetour][0]=grille[pos][0];// Qts
                     m_tabParam[nbrRetour][1]=grille[pos][1];// alpha
                     m_tabParam[nbrRetour][2]=grille[pos][2];// fb
                     m_qtcPossible.push_back(qtc[ii]);
                     nbrRetour++;
                }
                //else
                    //---> make a qdialog
                    //cout << "Value of Qts given too far from the abak table Qtc="<<NumbernameFile[ii]<<endl;
            }
            else
                //---> make a qdialog
                //cout << "Unable to open file of the abak" << endl;
            monFlux.close();
            grille.clear();
    }
        if (m_tabParam.size()==0)
        {
           //Qdialog
            //cout<< "Value of Qts given too far from the abak table of all Qtc, there is no available closed box configuration"<< endl;
        }

}

void Closedbox::calculateEnclosureParameters()
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
        m_volume[ii]=m_parameters[4]/m_tabParam[ii][1];
        m_fc[ii]=m_qtcPossible[ii]*m_parameters[0]/m_parameters[2];
        m_f3[ii]=pow((1/(m_qtcPossible[ii]*m_qtcPossible[ii])-2+sqrt(pow(1./pow(m_qtcPossible[ii],2)-2,2)+4))/2,0.5)*m_fc[ii];// -3db cut off

        //define the different dimension of the box
            Eigen::MatrixXd sol(6,1);
            sol= newtonMethodSolver(m_thickness,m_volume[ii]);
            m_boxDimension.push_back(QVector<double>(6));
           // afficherBoxDimension(sol);
            for (int j=0;j<6;j++)
            {
                m_boxDimension[ii][j]=sol(j,0);
            }
    }
   // akabakClosedboxScript(diffraction,volume,m_tabParam,speakerbass,m_parameters,boxDimension);

//00 m_fs
//01 m_Qes
//02 m_Qts 3
//03 m_Qms 4
//04 m_Vas 5
//05 m_dD 6
//06 m_dD1 7
//07 m_tD1 8
//08 m_hD1 9
//09 m_Re 10
//10 m_Mms 11
//11 m_Le 12



}

void Closedbox::akabakClosedboxScript()
{
    QString const associedParameters(speakerbass->nameParameters());
    QString strFileName="GeneratedScript/closed.aks";
    ofstream ofsaveSpeaker((strFileName.toStdString()).c_str());
    ofsaveSpeaker <<"Def_Driver  '"<< ((speakerbass->getName()).toStdString()).c_str()<<"' \n";

    if(m_parameters[6]!=0)
    ofsaveSpeaker <<"dD="<<m_parameters[5] <<"cm  |Piston \n";
    else return;

    if(m_parameters[0]!=0 && m_parameters[10]!=0 && m_parameters[3]!=0)
    ofsaveSpeaker <<"fs="<<m_parameters[0] <<"Hz  Mms="<< m_parameters[10]<<"g  Qms="<<m_parameters[3] <<" \n";
    else return;


    if(m_parameters[7]!=0 && m_parameters[5]!=0)
    ofsaveSpeaker <<"dD1="<<m_parameters[6]<<"cm  tD1="<<m_parameters[7]<<"cm \n";

    if(m_parameters[1]!=0 && m_parameters[9]!=0 && m_parameters[11]!=0)
    ofsaveSpeaker <<"Qes="<< m_parameters[1]<< " Re="<<m_parameters[9]<<"ohm  Le="<<m_parameters[11]<<"mH  ExpoLe=0.618 \n \n";
    else return;


    for (int ii(0);ii<m_tabParam.size();ii++)
    {
        ofsaveSpeaker <<"System 'S"<<ii<<"_clos_Qtc_"<<m_qtcPossible[ii]<<"'";
        ofsaveSpeaker <<"Driver 'D1' Def='"<<(speakerbass->getName()).toStdString()<<"' Node=0=1=2=21\n";
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
