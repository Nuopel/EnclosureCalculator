#ifndef FILTER
#define FILTER

#include <QDialog>
#include <QHBoxLayout>
#include <QFormLayout>


class Filter : public QWidget // On hérite de QWidget (IMPORTANT)
{
    Q_OBJECT
public:
        Filter();

public slots://homade slot


signals: //homemade signal


private:
        QFormLayout *layout;


};


#endif // FILTER

