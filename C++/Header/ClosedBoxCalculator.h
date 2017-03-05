#ifndef CLOSEDBOXCALCULATOR_H_INCLUDED
#define CLOSEDBOXCALCULATOR_H_INCLUDED
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "enclosure.h"
#include "speaker.h"
#define sizeQtc 9

using namespace std;

class closedbox : public Enclosure
{
    public:
        closedbox();
        closedbox(speaker &speakerbass);
        closedbox(Enclosure &initEnclosure);

        ~closedbox();
        void lectureFile();
        void calculateEnclosureParameters();
        void akabakClosedBoxScript();


    protected:
        vector<vector<double> >  m_tabParam;
        vector<double> m_qtcPossible;
        double *m_fc;
        double *m_f3;


};



#endif // CLOSEDBOXCALCULATOR_H_INCLUDED
