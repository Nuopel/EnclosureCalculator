#include "../Header/Filter.h"
#include "../Header/speaker.h"
#include <iostream>

// Filtre second ordre Linkwitz-Riley
// The Filter should be at least 2.8 * fs
Filter::Filter(speaker* speakerBass, speaker* speakerTweet)
{
    m_parameters=speakerBass->parameters();
    m_parameters2=speakerTweet->parameters();
    calculateLowHighPass();
    tweeterAntiResonant();
    impCompensWoofer();
    LeScript(speakerBass,speakerTweet);

}


void Filter::calculateLowHighPass()
{
    cout<< "It's advised to use a frequency of at least 2.8*fs = "<< 2.8*m_parameters2[0]<<"Hz for your Tweeter"<<endl;
    cout<<"Enter the choosen cut off frequency:"<<endl;
    cin>>m_f;
    cout<<"Enter the choosen Rh:"<<endl;
    cin>>m_Rh;
    cout<<"Enter the choosen Rl:"<<endl;
    cin>>m_Rl;

    m_C1=0.0796/(m_Rh*m_f);
    m_L1=0.3183*m_Rh/m_f;
    m_C2=0.0796/(m_Rl*m_f);
    m_L2=0.3183*m_Rl/m_f;

    cout<< "The corresponding Capacitor C1 is : "<< m_C1<<"F"<<endl;
    cout<< "The corresponding Capacitor C2 is : "<< m_C2<<"F"<<endl;
    cout<< "The corresponding Capacitor L1 is : "<< m_L1<<"H"<<endl;
    cout<< "The corresponding Capacitor L2 is : "<< m_L2<<"H"<<endl;
}

void Filter::tweeterAntiResonant()
{
        //Filtre  tweeter anti resonant
    if (m_parameters2[10]!=0 && m_parameters2[1]!=0 && m_parameters2[1]!=0 &&m_parameters2[4]!=0)
    {
        m_Lt=0.1592*m_parameters2[10]*m_parameters2[1]/m_parameters2[0];
        m_Rt=m_parameters2[10]+m_parameters2[1]*m_parameters2[10]/m_parameters2[4];
    }

    else
        printf("\nUnable to calculate the antiresonant Filter for the tweeter due to lack of informations\n");
}

void Filter::AttenuatorFilter()
{
        // Filtre  attenuateur tweeter
    cout<<"Enter the negative gain to apply between both speaker (ex:-2)"<<endl;
    cin>>m_A;
    m_Z=8;
    m_R2=pow(10,m_A/20)*m_Z/(1-pow(10,m_A/20));
    m_R1=m_Z-1/(1/m_R2+1/m_Z);
}

void Filter::impCompensWoofer()
{

    // Filtre compensation d'impedance boomer
    if (m_parameters[10]!=0 && m_parameters2[12]!=0 )
    {
            m_Rcb=1.25*m_parameters2[10];
            m_Cb=m_parameters2[12]*1e-3/pow(m_Rcb,2);
    }

    else
        printf("\nUnable to calculate the impedance compesation \n Filter for the tweeter due to lack of informations\n");

}

void Filter::LeScript(speaker* speakerBass, speaker* speakerTweet)
{
//// Create the Le script
//// Open the file
    FILE * pFile;
    pFile=fopen("Abec_vertices/LeScript.txt","w");

    if (pFile!=NULL)
    {
        fprintf(pFile," //*****************************************************************************\n");
        fprintf(pFile," //\n");
        fprintf(pFile," // ABEC2 Lumped Element File\n");
        fprintf(pFile," //\n");
        fprintf(pFile," //*****************************************************************************\n\n\n");

        fprintf(pFile," // Thiele-Small parameter of electro-dynamic driver\n");
        fprintf(pFile," // Note, no diaphragm dimensions to be specified in this script.\n");
        fprintf(pFile,"Def_Driver '%s'\n",(speakerBass->getName()).c_str());
        fprintf(pFile," Re=%lfohm \n",m_parameters[10]);
        fprintf(pFile," Mms=%lfg \n",m_parameters[11]);
        fprintf(pFile," Bl=%lfN/A\n",m_parameters[13]);
        fprintf(pFile," fs=%lfHz  Qms=%lf  Qes=%lf\n",m_parameters[0],m_parameters[4],m_parameters[1]);
        fprintf(pFile," Le=%lfH\n\n",m_parameters[12]);

        fprintf(pFile,"Def_Driver '%s'\n",(speakerTweet->getName()).c_str());
        fprintf(pFile,"  Mms=%lfg  \n",m_parameters2[10]);
        fprintf(pFile,"  Re=%lfohm ExpoRe=0.824\n",m_parameters2[11]);
        fprintf(pFile,"  fs=%lfHz    Qes=%lf Qms=%lf\n",m_parameters2[0],m_parameters2[4],m_parameters2[1]);
        fprintf(pFile,"  Le=%lfH\n\n",m_parameters2[12]);

        fprintf(pFile," // Driving value of LE network (here using formula to convert dB to voltage)\n");

        fprintf(pFile,"Def_Driving \"Driving\"\n");
        fprintf(pFile,"  Value={0.707*2}  \n");
        fprintf(pFile,"  IsRms\n\n");

        fprintf(pFile," // Lumped element network \n");

        fprintf(pFile,"System 'S1'\n");
        fprintf(pFile,"// filtre passe bas second ordre Linkwitz-Riley\n");
        fprintf(pFile,"  Coil 'L2'\n");
        fprintf(pFile,"   Node=2=3  L=%lfH\n",m_L2);
        fprintf(pFile,"  Capacitor 'C2'\n");
        fprintf(pFile,"   Node=3=0  C=%lfF\n\n",m_C2);

        fprintf(pFile,"// Filtre compensation impedance %s\n",(speakerBass->getName()).c_str());
        fprintf(pFile,"  Capacitor 'Cb'\n");
        fprintf(pFile,"   Node=3=8  C=%lfF\n",m_Cb);
        fprintf(pFile,"  Resistor  'Rt'\n ");
        fprintf(pFile,"   Node=8=0  R=%lf ohm\n\n",m_Rcb);

        fprintf(pFile,"// Generator resistance of wires etc\n");
        fprintf(pFile,"  Resistor 'Rg' R=0.1ohm\n");
        fprintf(pFile,"   Node=1=2\n\n");

        fprintf(pFile,"// Speaker electro-acoustic\n");
        fprintf(pFile,"  Driver  'Drv1'  Def='%s'\n",(speakerBass->getName()).c_str());
        fprintf(pFile,"   Node=3=0=10=20   DrvGroup=1001,1002  // Link to BE\n");
        fprintf(pFile,"  RadImp 'Front'                         // Radiation impedance of external domain\n");
        fprintf(pFile,"   Node=10	DrvGroup=1001            // Link to BE\n");
        fprintf(pFile,"  RadImp 'Rear'                          // Radiation impedance of enclosure\n");
        fprintf(pFile,"   Node=20  DrvGroup=1002            // Link to BE\n\n");

        fprintf(pFile,"//filtre passe haut second ordre Linkwitz-Riley\n");
        fprintf(pFile,"  Coil 'L1'\n");
        fprintf(pFile,"   Node=4=0  L=%lfH\n",m_L1);
        fprintf(pFile,"  Capacitor 'C1'\n");
        fprintf(pFile,"   Node=2=4  C=%lfF\n\n",m_C1);

        fprintf(pFile,"// attenuateur\n");
        fprintf(pFile,"// Resistor  '%lf'  Node=4=15  R=2ohm\n",m_R1);
        fprintf(pFile,"// Resistor  '%lf'  Node=15=0  R=20ohm\n",m_R2);

        fprintf(pFile,"  Driver  'Drv2'  Def='%s'\n",(speakerTweet->getName()).c_str());
        fprintf(pFile,"   Node=4=0=12=22   DrvGroup=1003,1004\n");

        fprintf(pFile,"  RadImp 'Front2'                         // Radiation impedance of external domain\n");
        fprintf(pFile,"   Node=12     DrvGroup=1003            // Link to BE\n");
        fprintf(pFile,"  RadImp 'Rear2'                          // Radiation impedance of enclosure\n");
        fprintf(pFile,"   Node=22     DrvGroup=1004 \n ");

    }
    fclose(pFile);

}
//00 m_fs
//01 m_Qes
//02 m_Qtc
//03 m_Qts
//04 m_Qms
//05 m_Vas
//06 m_r
//07 m_dD
//08 m_tD1
//09 m_hD1
//10 m_Re
//11 m_Mms
//12 m_Le
