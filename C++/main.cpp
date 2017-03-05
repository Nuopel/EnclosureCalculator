#include <iostream>
#include "Header/enclosure.h"
#include "Header/ClosedBoxCalculator.h"
#include "Header/bassreflex.h"
using namespace std;



int main()
{

    speaker *speakerbass=new speaker;

    cout <<endl<< "Please choose in the available enclore proposal" << endl;
    cout << "1 Closed box enclosure" << endl;
    cout << "2 Bass reflex enclosure" << endl;
    cout << "3 Nothing" << endl;
    int choice;
    cin>>choice;
          switch (choice)
      {
         case 1:
            closedbox * ClBox2Simu;
            ClBox2Simu= new closedbox(*speakerbass);
            //ClBox2Simu->afficheSpeakerTS();

            //delete speakerbass; //segment fault as speakerbass is take in enclosure and removed by his destructor
            delete ClBox2Simu;
            break;

         case 2:
            bassReflex * BassRBox2Simu;
            BassRBox2Simu= new bassReflex(*speakerbass);
            //ClBox2Simu->afficheSpeakerTS();

            //delete speakerbass; //segment fault as speakerbass is take in enclosure and removed by his destructor
            //delete BassRBox2Simu;
            break;

         default:
            cout<<"Then good bye";
            return 0;

      }
    return 0;
}
