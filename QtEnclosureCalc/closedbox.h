#ifndef CLOSEDBOX
#define CLOSEDBOX
#include <enclosure.h>
#include <speaker.h>

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

