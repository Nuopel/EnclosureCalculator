#ifndef SECONDFENETRESPEAKER_H
#define SECONDFENETRESPEAKER_H

#define numParam 13
#include <QFormLayout>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QList>
#include <QGridLayout>

class AddSpeaker : public QWidget // On hérite de QWidget (IMPORTANT)
{
    Q_OBJECT
public:

    AddSpeaker();
    void afficherValeur() const;// print value of T/S parameters
    void saveSpeak();// modify the T/S parmeters of a speaker
    void loadSpeaker(const std::string &fname);
    void ebpCalculation();
    void fillparameters();

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
    std::vector<std::string> qtcPossible;
    QList<QLineEdit *> *qle_list;
};

int findNearestValueArray2D(std::vector<std::vector<double> >  grille, double Qts);

std::string selectSpeaker();

#endif // SECONDFENETRESPEAKER_H

