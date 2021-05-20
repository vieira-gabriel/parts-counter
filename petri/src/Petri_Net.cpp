#include <Petri_Net.h>
#include <iostream>

using namespace std;

Petri_Net::Petri_Net(){}

Petri_Net::~Petri_Net(){}

void Petri_Net::printState(){}
int Petri_Net::getNumberOfTokens(string place){}
void Petri_Net::run(vector<string> transitionsOrder){}

int Petri_Net::generatePN(vector<string> places,
                vector<string> transitions,
                vector<vector<int>> originMatrix,
                vector<vector<int>> destinationMatrix)
{
    if(originMatrix.size() != places.size() || destinationMatrix.size() != places.size() ||
       originMatrix[0].size() != transitions.size() || destinationMatrix[0].size() != transitions.size()){
           cout << "Transition and place vectors have diferent size in the matrix" << endl;
           return -1;
    }

    for(int i = 0; i < places.size(); i++){
        for (int j = 0; j < transitions.size(); j++){
            
        }
    }

    return 0;
}

vector<weak_ptr<Place>> Petri_Net::getPlacesFromNames(vector<string> names){}
void Petri_Net::createTransition(vector<string> &originPlaces,
                        vector<int> &originWeights,
                        vector<string> &destinationPlaces,
                        vector<int> &destinationWeights){}
void Petri_Net::createPlace(string name,
                    int initialNumberOfTokens){}