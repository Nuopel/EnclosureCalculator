#include <speaker.h>


Speaker::Speaker() : associedParameters{"m_fs (Hz)","m_Qes","m_Qts","m_Qms","m_Vas(l)","m_dD(cm)","m_dD1 (cm)(dustcap)","m_tD1 (cm)(deep of cone)","m_hD1(cm)(height of dustcap)","m_Re(ohm)","m_Mms(g)","m_Le(mh)","m_BL"}
{
    QWidget();
    m_Save  = new QPushButton("Save", this);
    m_Save->setFont(QFont("Comic Sans MS", 14));
    m_Load = new QPushButton("Load", this);
    m_Load->setFont(QFont("Comic Sans MS", 14));
    QVBoxLayout *mainlayout =new QVBoxLayout;
    QGridLayout *gridbox = new QGridLayout;

    gridbox->addWidget(m_Save,0,1);
    gridbox->addWidget(m_Load,1,1);

    QFormLayout *layout = new QFormLayout;
    QList<QLineEdit* > *qle_list = new QList<QLineEdit* > ();

    qle_list->append(new QLineEdit());
    qle_list->at(0)->setObjectName(QString("lineEdit%1").arg(0)); // It's easier to recognize an object by name
    layout->addRow("Name",qle_list->at(0));
    mainlayout->addLayout(layout);

    for(int i = 1; i < 14; ++i)
    {
        qle_list->append(new QLineEdit());
        qle_list->at(i)->setObjectName(QString("lineEdit%1").arg(i)); // It's easier to recognize an object by name
        layout->addRow(associedParameters[i-1],qle_list->at(i));
        mainlayout->addLayout(layout);
    }
    mainlayout->addLayout(gridbox);
    this->setLayout(mainlayout);
}

void Speaker::fillparameters()
{
    QString temp;
    name = qle_list->at(0)->text();
    for(int i = 1; i < 14; ++i)
    {
        temp = qle_list->at(i)->text();
         speakerParameters[i-1] = temp.toDouble();
    }
}

double Speaker::returnQts()
{
    return speakerParameters[2];
}
QString  Speaker::nameParameters()const
{
    return *associedParameters;
}

int findNearestValueArray2D(QVector<QVector<double> >  grille, double Qts)
{
    double smallest = qAbs(grille[0][0]-Qts) ; //declare and initiate smallest value at first case 0
    //cout<< endl;
    int position=0;// position of the smallest value
    for ( int i=1;  i < grille.size();  ++i )
    {
        if ( qAbs(grille[i][0]-Qts)  < smallest )// if case value smaller replace it
        {
            smallest=qAbs(grille[i][0]-Qts);
            position = i;
        }
    }

    if  (qAbs(grille[position][0]-Qts)>0.04)// if value too far appart send back error
        return -1;

    return position;
}

QString  Speaker::getName() const
{
    return name;
}

QVector<QString> Speaker::QtcPossible()
{
    return qtcPossible;
}
