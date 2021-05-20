#pragma once

#include <vector>
#include <tuple>
#include <memory>
#include <Place.h>

class Transition
{
private:
    vector<tuple<weak_ptr<Place>,int>> origin;
    vector<tuple<weak_ptr<Place>,int>> destination;

    string t_name;

    // Remove tokens dos lugares de partida
    void exitPlace();

    // Adiciona tokens nos lugares de chegada
    void enterPlace();

public:
    Transition(string name, vector<weak_ptr<Place>> originVec, vector<int> weightOrigin, vector<weak_ptr<Place>> destinationVec, vector<int> weightDestination);
    ~Transition();

    bool isActive();
    string getTName();

    void realizeTransition();
};