#ifndef SPEAKER_H_INCLUDED
#define SPEAKER_H_INCLUDED
#include <iostream>
#define numParam 14
#include <string>
#include <fstream>
#include <vector>
#include <cmath>


using namespace std;

class speaker
{
    public:
        speaker();
        speaker(double *speakerParametersValues);
        void afficherValeur() const;// print value of T/S parameters
        void modifier();// modify the T/S parmeters of a speaker
        void ebpCalculation();
        void fillSpeaker();
        void savedSpeakerName();

        std::string nameParameters() const;
        const  double* parameters() const;
        std::string  getName()const;
        const std::vector<std::string> QtcPossible() const;
        const double returnQts()const;

        void loadSpeaker(const std::string &fname);
        void saveSpeaker();
        void addQtcPossible(std::string qtc2add);


    private:
        std::string name;
        std::string associedParameters[numParam];
        double speakerParameters[numParam];
        double ebp;
        std::vector<std::string> qtcPossible;


};

int findNearestValueArray2D(vector<vector<double> >  grille, double Qts);

std::string selectSpeaker();


#endif // SPEAKER_H_INCLUDED

