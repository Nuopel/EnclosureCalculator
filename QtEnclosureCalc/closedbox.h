#ifndef CLOSEDBOX
#define CLOSEDBOX
#include <iostream>
#include <fstream>
#include <enclosure.h>
#include <speaker.h>
<<<<<<< HEAD
 #include <QGenericMatrix>
=======
#include <QString>
>>>>>>> 4d94345087e03439eb3b4da0e0006b9a2d760490

using namespace std;

class Closedbox : public Enclosure
{
    public:
        Closedbox(Speaker &speakerbass2copy, Speaker &speakermid2copy);
        Closedbox(Speaker &speakerbass2copy);
        Closedbox(Speaker &speakerbass2copy, Speaker &speakermid2copy, Speaker &speakertw2copy);
        ~Closedbox();
        void lectureFile();
        void calculateEnclosureParameters();
        void akabakClosedboxScript();


    protected:
        QVector<QVector<double> >  m_tabParam;
        QVector<double> m_qtcPossible;
        double *m_fc;
        double *m_f3;



};

#endif // CLOSEDBOX

