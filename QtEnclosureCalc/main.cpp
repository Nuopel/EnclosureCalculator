//#include <QApplication>
//#include <QPushButton>
//#include <QWidget>
//#include <QFont>
//#include <QIcon>
#include <QMessageBox>
#include <QApplication>
#include "fenetre.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainFenetre mainFenetre;
   mainFenetre.show();

    return app.exec();
}
