#ifndef ENCLOSURE_H
#define ENCLOSURE_H

#include <QDialog>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QList>
#include <QPushButton>
#include <QTableWidget>
#include <QVector>
#include <QComboBox>

#include <speaker.h>
#include <iostream>
#include <fstream>
class Enclosure : public QWidget // On hérite de QWidget (IMPORTANT)
{
//Q_OBJECT
public:
        Enclosure();

        ~Enclosure();

        int getchoicebox();

public slots://homade slot


signals: //homemade signal


protected:
 QComboBox *liste ;
 QPushButton *m_BoutonSpeaker1;
 double *m_volume;
 double m_thickness;
 int m_diffraction;
 QVector<QVector<double> > m_boxDimension;
 const double*m_parameters;
 Speaker *speakerbass ;
 Speaker *speakermid ;
 Speaker *speakertw ;
};


#endif // ENCLOSURE_H

