#ifndef ENCLOSURE_H_INCLUDED
#define ENCLOSURE_H_INCLUDED
#include "NewtonMethod.h"

#include "speaker.h"

class Enclosure
{
    public:
      Enclosure();
      Enclosure(speaker &speakerbass);
      virtual  ~Enclosure();
      virtual  void initEmptyEnclosure();

      virtual  void afficheSpeakerTS();

    protected:
        double *m_volume;
        double m_thickness;
        int m_diffraction;
        speaker *m_speakerbass;
        vector<vector<double> > m_boxDimension;
        const double*m_parameters;

};

#endif // ENCLOSURE_H_INCLUDED
