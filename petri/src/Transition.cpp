#include <Transition.h>
#include <iostream>

using namespace std;

Transition::Transition(string name, vector<weak_ptr<Place>> originVec, vector<int> weightOrigin,
                       vector<weak_ptr<Place>> destinationVec, vector<int> weightDestination):
                       t_name(name)
{
    if (weightOrigin.size() < originVec.size()){
        cout << "Weight vector smaller than places vector. All origin conections will have weight = 1" << endl;
        for(int i  = 0; i < originVec.size(); ++i){
            origin.push_back(make_tuple(originVec[i],1));
        }
    } else {
        for(int i  = 0; i < originVec.size(); ++i){
            origin.push_back(make_tuple(originVec[i],weightOrigin[i]));
        }
    }
    if (weightDestination.size() < destinationVec.size()){
        cout << "Weight vector smaller than places vector. All destination conections will have weight = 1" << endl;
        for(int i  = 0; i < destinationVec.size(); ++i){
            destination.push_back(make_tuple(destinationVec[i],1));
        }
    } else {
        for(int i  = 0; i < destinationVec.size(); ++i){
            destination.push_back(make_tuple(destinationVec[i],weightDestination[i]));
        }
    }
}

Transition::~Transition(){}

bool Transition::isActive(){
    for (tuple<weak_ptr<Place>,int> &tupleOriginPlace : origin)
    {
        weak_ptr<Place> &weak_place = get<0>(tupleOriginPlace);
        int tokens = weak_place.lock()->getNumberOfTokens();
        int weight = get<1>(tupleOriginPlace);
        cout << "Tokens: " << tokens << endl << "Weight: " << weight << endl;
        if ( tokens < weight) return false;
    }
    return true;
}

void Transition::realizeTransition(){
    if(isActive()){
        exitPlace();
        enterPlace();
    }
    else{
        cout << "Transition " << t_name << " is not active" << endl;
    }
}

void Transition::exitPlace(){
    for (tuple<weak_ptr<Place>,int> &tupleOriginPlace : origin){
        weak_ptr<Place> &weak_place = get<0>(tupleOriginPlace);
        if(weak_place.lock()){
            weak_place.lock()->exitPlace(get<1>(tupleOriginPlace));
        }
    }
}


void Transition::enterPlace(){
    for (tuple<weak_ptr<Place>,int> &tupleDestinationPlace : destination){
        weak_ptr<Place> &weak_place = get<0>(tupleDestinationPlace);
        if(weak_place.lock()){
            weak_place.lock()->exitPlace(get<1>(tupleDestinationPlace));
        }
    }
}

string Transition::getTName(){
    return t_name;
}
