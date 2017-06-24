#ifndef SECONDFENETRESPEAKER_H
#define SECONDFENETRESPEAKER_H

#define numParam 13
#include <QFormLayout>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QList>
#include <QGridLayout>
#include <QVector>
#include <QString>
using namespace std;

class Speaker : public QWidget // On hérite de QWidget (IMPORTANT)
{
   // Q_OBJECT
public:

    Speaker();
    void afficherValeur() const;// print value of T/S parameters
    void saveSpeak();// modify the T/S parmeters of a speaker
    void loadSpeaker(const std::string &fname);
    void ebpCalculation();
    void fillparameters();
    double returnQts();
    QString nameParameters()const;
<<<<<<< HEAD
    QString getName() const;
    QVector<QString> QtcPossible();
=======
    QString getName()const;
    const std::vector<std::string> QtcPossible() const;
>>>>>>> 4d94345087e03439eb3b4da0e0006b9a2d760490


public slots://homade slot


signals: //homemade signal


private:
    QPushButton *m_Save;
    QPushButton *m_Load;
    QVBoxLayout *mainlayout;
    QFormLayout *layout;

    QString name;
    QString associedParameters[numParam];
    double speakerParameters[numParam];
    double ebp;
    QVector<QString> qtcPossible;
    QList<QLineEdit *> *qle_list;
};

int findNearestValueArray2D(QVector<QVector<double> >  grille, double Qts);

std::string selectSpeaker();

#endif // SECONDFENETRESPEAKER_H

