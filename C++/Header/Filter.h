#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

#include <vector>
#include <cmath>

#include "enclosure.h"
#include "bassreflex.h"


class Filter
{
    public:
        Filter(speaker* speakerBass, speaker* speakerTweet);

        void calculateLowHighPass();
        void tweeterAntiResonant();
        void AttenuatorFilter();
        void impCompensWoofer();
        void LeScript(speaker* speakerBass, speaker* speakerTweet);



    protected:
        double m_f;
        double m_Rh;
        double m_Rl;
        double m_C1;
        double m_L1;
        double m_C2;
        double m_L2;
        //tweeter anti resonant
        double m_Lt;
        double m_Rt;
        // Filtre  attenuateur tweeter
        double m_A;
        double m_Z;
        double m_R2;
        double m_R1;
        // WOOFER COMP IMPEDANCE
        double m_Rcb;
        double m_Cb;

        const double *m_parameters;
        const double *m_parameters2;
};


#endif // FILTER_H_INCLUDED
