#include "fenetre.h"

MainFenetre::MainFenetre() : QWidget()
{
    setFixedSize(500, 700);

    //Layout bouton vertical
    QGridLayout *Vmainbox = new QGridLayout;
    QGridLayout *VboxSpeaker = new QGridLayout;
    QHBoxLayout *Hboxselect = new QHBoxLayout;


    // Construction des boutons
    m_BoutonSpeaker1 = new QPushButton("Add Woofer ", this);
    m_BoutonSpeaker1->setFont(QFont("Comic Sans MS", 14));

    m_BoutonSpeaker2 = new QPushButton("Add Midrange ", this);
    m_BoutonSpeaker2->setFont(QFont("Comic Sans MS", 14));

    m_BoutonSpeaker3 = new QPushButton("Add Tweeter ", this);
    m_BoutonSpeaker3->setFont(QFont("Comic Sans MS", 14));

    m_BoutonEnceinteSelect = new QPushButton("Filter", this);
    m_BoutonEnceinteSelect->setFont(QFont("Comic Sans MS", 14));

    m_BoutonFilterSelect = new QPushButton("Enclosure kind", this);
    m_BoutonFilterSelect->setFont(QFont("Comic Sans MS", 14));

    m_BoutonGenerate = new QPushButton("Generate", this);
    m_BoutonGenerate->setFont(QFont("Comic Sans MS", 14));

    m_woofer_tick = new QCheckBox(this);
    m_mid_tick = new QCheckBox(this);
    m_tweet_tick = new QCheckBox(this);




    // link boutons vbox
    VboxSpeaker->addWidget(m_BoutonSpeaker1,0,0);
    VboxSpeaker->addWidget(m_BoutonSpeaker2,1,0);
    VboxSpeaker->addWidget(m_BoutonSpeaker3,2,0);
    VboxSpeaker->addWidget(m_woofer_tick,0,1);
    VboxSpeaker->addWidget(m_mid_tick,1,1);
    VboxSpeaker->addWidget(m_tweet_tick,2,1);


    Hboxselect->addWidget(m_BoutonEnceinteSelect);
    Hboxselect->addWidget(m_BoutonFilterSelect);

    Vmainbox->addWidget(m_BoutonGenerate,0,0);

    // set layouts in mother layout
    Vmainbox->addLayout((VboxSpeaker),1,0);
    Vmainbox->addLayout((Hboxselect),2,0);
    this->setLayout(Vmainbox);

    // Enclosure selection
    Enclosure *enclo1 = new Enclosure();
    enclo1->show();


    // Open new windows
    TSWooferBox = new AddSpeaker() ;
    TSMidrangeBox = new AddSpeaker() ;
    TSTweeterBox = new AddSpeaker() ;
    QLabel *labelt = new QLabel("Tweeter ",TSTweeterBox);   // titre du layout
    QLabel *labelm = new QLabel("Midrange ",TSMidrangeBox); // titre du layout
    QLabel *labelw = new QLabel("Woofer ",TSWooferBox);     // titre du layout

    Vmainbox->addWidget(TSWooferBox,1,1);
    Vmainbox->addWidget(TSMidrangeBox,1,2);
    Vmainbox->addWidget(TSTweeterBox,1,3);
    TSTweeterBox->hide();  // hide fenetre tweeter
    TSMidrangeBox->hide(); //hide fenetre mid
    TSWooferBox->hide();   //hide fenetre woofer

    QWidget::connect(m_BoutonSpeaker1, SIGNAL(clicked()),this , SLOT(checkedW()) ); // connect bouton woofer to tick
    QWidget::connect(m_BoutonSpeaker2, SIGNAL(clicked()),this , SLOT(checkedM()) ); // connect bouton mid to tick
    QWidget::connect(m_BoutonSpeaker3, SIGNAL(clicked()),this , SLOT(checkedT()) );// connect bouton tweeter to tick

    // Obtenir les signaux des boites
    QWidget::connect(m_BoutonGenerate, SIGNAL(clicked()),this , SLOT(GetValueSpeaker()) ); // connect bouton
  }

void MainFenetre::addSize()
{
     setFixedSize(width()+300,height());

}

void MainFenetre::reduceSize()
{
    setFixedSize(width()-300,height());

}

void MainFenetre::checkedW()
{
    if(m_woofer_tick->checkState() == false)
    {
        m_woofer_tick->setChecked(true);
        TSWooferBox->show();
       addSize();

    }
    else
    {
        m_woofer_tick->setChecked(false);
        TSWooferBox->hide();
        reduceSize();
    }
}

void MainFenetre::checkedM()
{
    if(m_mid_tick->checkState() == false)
    {
        m_mid_tick->setChecked(true);
        TSMidrangeBox->show();
        addSize();
    }
    else
    {
        m_mid_tick->setChecked(false);
        TSMidrangeBox->hide();
        reduceSize();
    }
}

void MainFenetre::checkedT()
{
    if(m_tweet_tick->checkState() == false)
    {
        m_tweet_tick->setChecked(true);
        TSTweeterBox->show();
        addSize();

    }
    else
    {
        m_tweet_tick->setChecked(false);
        TSTweeterBox->hide();
        reduceSize();
    }
}

// get values from speakers form if the box is checked
void MainFenetre::GetValueSpeaker()
{
    if(m_woofer_tick->checkState() == true)
    {
        TSWooferBox->fillparameters();
    }
    if(m_mid_tick->checkState() == true)
    {
        TSMidrangeBox->fillparameters();
    }
    if(m_tweet_tick->checkState() == true)
    {
        TSTweeterBox->fillparameters();
    }

}


