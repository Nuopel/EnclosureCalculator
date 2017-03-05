#include "../Header/enclosure.h"

 Enclosure::Enclosure()
{
    initEmptyEnclosure();
    m_speakerbass=new speaker();
    m_parameters=m_speakerbass->parameters();
}

Enclosure::Enclosure(speaker &speakerbass)
{
    initEmptyEnclosure();
    m_speakerbass = &speakerbass;
    m_parameters=m_speakerbass->parameters();
}

void Enclosure::initEmptyEnclosure()
{
    cout << "Welcome in a small soft which help to do simulation for speaker enclosure" << endl;
    cout << "Please take time to fill 2 small parameters." << endl;
    cout <<endl;
    cout << "What thickness do you choose for your box ? (Write in mm)" << endl;
    cin >> m_thickness;
    m_thickness*=0.001;

   // Options
    // boolean variable 1 for diffraction of the enclosure edge 0 else;
    cout <<endl << "Do you want to take into account the diffraction in the simulation ?"<< endl;
    cout << "1 Yes" << endl;
    cout << "2 No" << endl;
    while(m_diffraction != 1 && m_diffraction != 2)
    {
        cin >>  m_diffraction ;
        if (m_diffraction != 1 && m_diffraction != 2)
            {
                cout << "Choice are 1 or 2" << endl;
            }
    }
}



void Enclosure::afficheSpeakerTS()
{
    m_speakerbass->afficherValeur();
}

Enclosure::~Enclosure()
{
    delete m_speakerbass;
}


