#pragma once

#include <Place.h>
#include <iostream>

Place::Place(int initialTokenNumber, string name):numTokens(initialTokenNumber), placeName(name){}

Place::~Place(){}

// Função que adiciona token quando o lugar é acessado
void Place::enterPlace(int tokens){
    if(tokens == 0){
        cout << "No token added" << endl;
    } else {
        cout << "Adding " << tokens << " tokens to " << placeName;
        numTokens += tokens;
    }
}

// Função que retira token quando sair do lugar
void Place::exitPlace(int tokens){
    if(tokens == 0){
        cout << "No token removed" << endl;
    } else {
        cout << "Removing " << tokens << " tokens from " << placeName;
        numTokens -= tokens;
    }
}

// Seta o numero de tokens no lugar
void Place::setNumberOfTokens(int tokens){
    numTokens = tokens;
}

// Retorna o numero de tokens no lugar
int Place::getNumberOfTokens(){
    return numTokens;
}