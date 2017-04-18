#ifndef FENETRE_H
#define FENETRE_H


#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <QProgressBar>
#include <QSlider>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>

#include <speaker.h>
#include <enclosure.h>
#include <closedbox.h>
#include <filter.h>


class MainFenetre : public QWidget // On hérite de QWidget (IMPORTANT)
{
    Q_OBJECT
public:
    MainFenetre();

public slots://homemade slot
    void checkedW();
    void checkedM();
    void checkedT();
    void addSize();
    void reduceSize();

    void InitGeneration();// get value from form if tick checked
    void ShowEnceinteselect(); //show value


signals: //homemade signal

private:
    QPushButton *m_BoutonSpeaker1;
    QPushButton *m_BoutonSpeaker2;
    QPushButton *m_BoutonSpeaker3;

    QPushButton *m_BoutonEnceinteSelect;
    QPushButton *m_BoutonFilterSelect;

    QPushButton *m_BoutonGenerate;

    QCheckBox *m_woofer_tick;
    QCheckBox *m_mid_tick;
    QCheckBox *m_tweet_tick;
    int choix ;
    int choixenclosure ;

    //QGridLayout *VboxSpeaker;
   // QHBoxLayout *Hboxselect;
    //QVBoxLayout *Vmainbox;

   // QVBoxLayout *layout2;
     Speaker* tsWooferBox;
     Speaker* tsMidrangeBox;
     Speaker* tsTweeterBox;
     Enclosure* enclo1;
};




#endif // FENETRE_H

