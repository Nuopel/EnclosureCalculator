#ifndef ENCLOSURE_H
#define ENCLOSURE_H

#include <QDialog>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QList>
#include <QPushButton>
#include <QTableWidget>

class Enclosure : public QWidget // On hérite de QWidget (IMPORTANT)
{

public:
        Enclosure();

public slots://homade slot


signals: //homemade signal


private:
 QPushButton *m_BoutonSpeaker1;
};


#endif // ENCLOSURE_H

