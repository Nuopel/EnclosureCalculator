#include "fenetre.h"

MainFenetre::MainFenetre() : QWidget()
{
    setFixedSize(500, 700);

    //Layout bouton vertical
    QGridLayout *vmainbox =    new QGridLayout;
    QGridLayout *vboxSpeaker = new QGridLayout;
    QHBoxLayout *hboxselect =  new QHBoxLayout;


    // Construction des boutons
    m_BoutonSpeaker1 = new QPushButton("Add Woofer ", this);
    m_BoutonSpeaker1->setFont(QFont("Comic Sans MS", 14));

    m_BoutonSpeaker2 = new QPushButton("Add Midrange ", this);
    m_BoutonSpeaker2->setFont(QFont("Comic Sans MS", 14));

    m_BoutonSpeaker3 = new QPushButton("Add Tweeter ", this);
    m_BoutonSpeaker3->setFont(QFont("Comic Sans MS", 14));

    m_BoutonEnceinteSelect = new QPushButton("Enclosure kind", this);
    m_BoutonEnceinteSelect->setFont(QFont("Comic Sans MS", 14));

    m_BoutonFilterSelect = new QPushButton("Filter", this);
    m_BoutonFilterSelect->setFont(QFont("Comic Sans MS", 14));

    m_BoutonGenerate = new QPushButton("Generate", this);
    m_BoutonGenerate->setFont(QFont("Comic Sans MS", 14));

    m_woofer_tick = new QCheckBox(this);
    m_mid_tick = new QCheckBox(this);
    m_tweet_tick = new QCheckBox(this);




    // link boutons vbox
    vboxSpeaker->addWidget(m_BoutonSpeaker1,0,0);
    vboxSpeaker->addWidget(m_BoutonSpeaker2,1,0);
    vboxSpeaker->addWidget(m_BoutonSpeaker3,2,0);
    vboxSpeaker->addWidget(m_woofer_tick,0,1);
    vboxSpeaker->addWidget(m_mid_tick,1,1);
    vboxSpeaker->addWidget(m_tweet_tick,2,1);


    hboxselect->addWidget(m_BoutonEnceinteSelect);
    hboxselect->addWidget(m_BoutonFilterSelect);

    vmainbox->addWidget(m_BoutonGenerate,0,0);

    // set layouts in mother layout
    vmainbox->addLayout((vboxSpeaker),1,0);
    vmainbox->addLayout((hboxselect),2,0);
    this->setLayout(vmainbox);

    // Enclosure selection
    enclo1 = new Enclosure();

    // Open new windows
    tsWooferBox = new Speaker() ;
    tsMidrangeBox = new Speaker() ;
    tsTweeterBox = new Speaker() ;
    QLabel *labelt = new QLabel("Tweeter ",tsTweeterBox);   // titre du layout
    QLabel *labelm = new QLabel("Midrange ",tsMidrangeBox); // titre du layout
    QLabel *labelw = new QLabel("Woofer ",tsWooferBox);     // titre du layout

    vmainbox->addWidget(tsWooferBox,1,1);
    vmainbox->addWidget(tsMidrangeBox,1,2);
    vmainbox->addWidget(tsTweeterBox,1,3);
    tsTweeterBox->hide();  // hide fenetre tweeter
    tsMidrangeBox->hide(); //hide fenetre mid
    tsWooferBox->hide();   //hide fenetre woofer

    QWidget::connect(m_BoutonSpeaker1, SIGNAL(clicked()),this , SLOT(checkedW()) ); // connect bouton woofer to tick
    QWidget::connect(m_BoutonSpeaker2, SIGNAL(clicked()),this , SLOT(checkedM()) ); // connect bouton mid to tick
    QWidget::connect(m_BoutonSpeaker3, SIGNAL(clicked()),this , SLOT(checkedT()) );// connect bouton tweeter to tick

    // Obtenir les signaux des boites
    QWidget::connect(m_BoutonGenerate, SIGNAL(clicked()),this , SLOT(InitGeneration()) ); // connect bouton

    QWidget::connect(m_BoutonEnceinteSelect, SIGNAL(clicked()),this , SLOT(ShowEnceinteselect()) ); // connect bouton

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
        tsWooferBox->show();
        addSize();

    }
    else
    {
        m_woofer_tick->setChecked(false);
        tsWooferBox->hide();
        reduceSize();
    }
}

void MainFenetre::checkedM()
{
    if(m_mid_tick->checkState() == false)
    {
        m_mid_tick->setChecked(true);
        tsMidrangeBox->show();
        addSize();
    }
    else
    {
        m_mid_tick->setChecked(false);
        tsMidrangeBox->hide();
        reduceSize();
    }
}

void MainFenetre::checkedT()
{
    if(m_tweet_tick->checkState() == false)
    {
        m_tweet_tick->setChecked(true);
        tsTweeterBox->show();
        addSize();

    }
    else
    {
        m_tweet_tick->setChecked(false);
        tsTweeterBox->hide();
        reduceSize();
    }
}

void MainFenetre::ShowEnceinteselect()
{
    enclo1->show();
}

// get values from speakers form if the box is checked
void MainFenetre::InitGeneration()
{
    choix = 0;
    //Get value of the filled form in variable for calculation
    if(m_woofer_tick->checkState() == true)
    {
        tsWooferBox->fillparameters();
        choix+=1;
    }
    if(m_mid_tick->checkState() == true)
    {
        tsMidrangeBox->fillparameters();
        choix+=2;
    }
    if(m_tweet_tick->checkState() == true)
    {
        tsTweeterBox->fillparameters();
        choix+=4;
    }

    //Select configuration based on the checkedbox
    choixenclosure = enclo1->getchoicebox();
    Closedbox * generated = NULL;
    switch (choix)
    {
        case 0:
            //code to say nothing
            break;
        case 1:
            generated = new Closedbox(*tsTweeterBox);
            break;
        case 2:
            generated = new Closedbox(*tsMidrangeBox);
            break;
        case 3:
            generated = new Closedbox(*tsMidrangeBox, *tsTweeterBox);
            break;
        case 4:
            generated = new Closedbox(*tsWooferBox);
            break;
        case 5:
            //code nothing
            break;
        case 6:
            generated = new Closedbox(*tsWooferBox,*tsMidrangeBox);
            break;
        case 7:
            generated = new Closedbox(*tsWooferBox,*tsMidrangeBox,*tsTweeterBox);
            break;
    }

}


