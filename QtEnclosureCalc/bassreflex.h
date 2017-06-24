#ifndef BASSREFLEX_H
#define BASSREFLEX_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#define sizeQ 3
#include <eigen3/Eigen/LU>
#include "newtonsolver.h"

#include "enclosure.h"
#include "speaker.h"
using namespace std;

class bassReflex : public Enclosure
{
    public:
        bassReflex();
        bassReflex(Speaker &speakerbass);
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
        Speaker *m_speakertweet;
        const double*m_parameters2;//tweeter parameter


};
#endif // BASSREFLEX_H
