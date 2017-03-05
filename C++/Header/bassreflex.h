#ifndef BASSREFLEX_H_INCLUDED
#define BASSREFLEX_H_INCLUDED
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#define sizeQ 3

#include "enclosure.h"
#include "speaker.h"
using namespace std;

class bassReflex : public Enclosure
{
    public:
        bassReflex();
        bassReflex(speaker &speakerbass);
        bassReflex(Enclosure &initEnclosure);

        ~bassReflex();
        void tweeteradd();
        void lectureFile();
        void calculateEnclosureParameters();
        void akabakBassReflexScript();
        void AbecBassReflexScript();



    protected:
        vector<vector<double> >  m_tabParam;
        vector<string> m_QPossible;
        double *m_f3;
        double *m_fb;
        speaker *m_speakertweet;
        const double*m_parameters2;//tweeter parameter


};



#endif // BASSREFLEX_H_INCLUDED
