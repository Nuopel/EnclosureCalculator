#include <enclosure.h>

Enclosure::Enclosure() : liste(new QComboBox(this))
{
 QWidget();
 setFixedSize(200, 100);
 liste->addItem("Closed Box");
 liste->addItem("Bass Reflex");
 liste->setCurrentIndex(0);
}

Enclosure::~Enclosure()
{
    delete m_volume;
    delete m_parameters;
}

int Enclosure::getchoicebox()
{
   return liste->currentIndex();
}

