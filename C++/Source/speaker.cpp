#include "../Header/speaker.h"
#include <string>
#include "math.h"
using namespace std;
speaker::speaker():  associedParameters{"m_fs (Hz)","m_Qes","m_Qtc","m_Qts","m_Qms","m_Vas(l)","m_dD(cm)","m_dD1 (cm)(dustcap)","m_tD1 (cm)(deep of cone)","m_hD1(cm)(height of dustcap)","m_Re(ohm)","m_Mms(g)","m_Le(mh)","m_BL"}
{
int choice(0);
    cout << endl<<"You will need to pick the  speaker of your enclosure " << endl;
    cout << "Do you want to add a new speaker or choose a already added one ?" << endl;
    cout << "1 Add a speaker" << endl;
    cout << "2 Choose a existant one " << endl;


    while(choice != 1 && choice != 2)
    {
        cin >>  choice ;
        if (choice==1)
            {
                fillSpeaker();
                saveSpeaker();
            }
        else if (choice==2)
            {
              string speakername;
              speakername=selectSpeaker();
              loadSpeaker(speakername);
              ebpCalculation();
              afficherValeur();
            }
        else
            {
                cout << "Choice are 1 or 2" << endl;
            }
    }
    ebpCalculation();

}


void speaker::fillSpeaker()
{
    cout << "Enter the name of the speaker"<< endl;
    cin >> name;

         for(int ii=0;ii<numParam;ii++)
    {

        cout << "Enter the value of "<< associedParameters[ii] << ", if empty put 0"<< endl;
        cin >> speakerParameters[ii];
                if (speakerParameters[ii]==0)
            speakerParameters[ii]=NULL;
    }
    ebpCalculation();
    afficherValeur();
    modifier();
}

speaker::speaker(double *speakerParametersValues)
{
    for(int ii=0;ii<numParam;ii++)
        {
            speakerParameters[ii]=speakerParametersValues[ii];

        }
    ebpCalculation();
}

void speaker::afficherValeur()const
{
    cout << "The Ts parameters of "<<name<<endl;
         for(int ii=0;ii<numParam;ii++)
    {

        cout << "The value of "<< associedParameters[ii] << " is " << speakerParameters[ii]<< endl;

    }

}

void speaker::modifier()
{
    cout << "Do you want to modify these values ?"<< endl;
    cout << "1 Yes" << endl;
    cout << "2 No" << endl;

    int choice(0);
    while(choice != 1 && choice != 2)
    {
        cin >>  choice ;
        if (choice==1)
        {
             int choiceModif;
             for(int ii=0;ii< numParam;ii++)
            {

                cout << "Enter the new value of  "<< associedParameters[ii] << ", if no put 0"<< endl;
                cin >> choiceModif;
                        if (choiceModif!=0)
                        {
                            speakerParameters[ii]=choiceModif;
                        }

            }
        }

        else if (choice==2)
        {

        }
        else
            cout << "Choice are 1 or 2" << endl;
    }
}

void speaker::ebpCalculation()
{
    if (speakerParameters[1]!=0 )
    {
            ebp=speakerParameters[0]/speakerParameters[1];
            cout << "The EBP value is : "<< ebp << endl;
            if (ebp<50)
            cout << "It''s advised to do a closed enclosure" << endl;
            else
            cout << "It's could be possible to do a closed enclosure or a bass reflex "<< endl<< endl;
    }
    else
        cout << "Missing Qes to calculate EBP "<< endl<< endl;


}

std::string  speaker::nameParameters()const
{
    return *associedParameters;
}

const double *speaker::parameters() const
{
    return speakerParameters;
}
string  speaker::getName() const
{
    return name;
}
const vector<std::string> speaker::QtcPossible() const
{
    return qtcPossible;
}
const double speaker::returnQts()const
{
    return speakerParameters[3];
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


void speaker::saveSpeaker()
{
    savedSpeakerName();

    string strFileName="speaker/"+name+".txt";
    ofstream ofsaveSpeaker(strFileName.c_str());
    ofsaveSpeaker <<name;
        for(int ii=0;ii< numParam;ii++)
                {
                    ofsaveSpeaker<<endl<<speakerParameters[ii];
                }
    ofsaveSpeaker.close();
}

void speaker::loadSpeaker(const string &fname)
{
    string strFileName="speaker/"+fname+".txt";
    ifstream ifloadSpeaker(strFileName.c_str());

    if(ifloadSpeaker)
    {

        getline(ifloadSpeaker,name);
        for(int ii=0;ii< numParam;ii++)
                {
                    ifloadSpeaker>>speakerParameters[ii];

                }
    }
    else
        cout << "Unable to open file of the speaker parameters" << endl;

}

void speaker::savedSpeakerName()
{
    string strFileName="speaker/savedSpeakerNames.txt";
    ofstream ofsaveSpeaker(strFileName.c_str(),fstream::app);
    ofsaveSpeaker <<endl<<name;
    ofsaveSpeaker.close();
}

std::string selectSpeaker()
{
            vector<string> speakerlist;
            int line(0),choice;
            string nameFile("speaker/savedSpeakerNames.txt");
            ifstream monFlux(nameFile.c_str());
            if(monFlux)
            {
                cout<<endl;

                while(!monFlux.eof())
                {
                    speakerlist.push_back("");
                    monFlux>>speakerlist[line];
                    cout<<line<<" "<<speakerlist[line]<<endl;
                    line++;
                }
                monFlux.close();
                cin>>choice;
                return speakerlist[choice];

            }
            else
            {
                cout<<"Unable to open the file of the speaker names";
                return speakerlist[choice];

            }



}
int findNearestValueArray2D(vector<vector<double> >  grille, double Qts)
{
    double smallest = abs(grille[0][0]-Qts) ; //declare and initiate smallest value at first case 0
    cout<< endl;
    int position=0;// position of the smallest value
    for ( int i=1;  i < grille.size();  ++i )
    {
        if ( abs(grille[i][0]-Qts)  < smallest )// if case value smaller replace it
        {
            smallest=abs(grille[i][0]-Qts);
            position = i;
        }
    }

    if  (abs(grille[position][0]-Qts)>0.04)// if value too far appart send back error
        return -1;

    return position;
}


void speaker::addQtcPossible(string string2add)
{
    qtcPossible.push_back(string2add);
}
