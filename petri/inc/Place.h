#pragma once

#include <string>

using namespace std;

class Place
{
private:
    int numTokens;

    string placeName;
public:
    Place(int initialTokenNumber, string name = "");
    ~Place();

    // Função que adiciona token quando o lugar é acessado
    void enterPlace(int tokens = 1);

    // Função que retira token quando sair do lugar
    void exitPlace(int tokens = 1);

    // Seta o numero de tokens no lugar
    void setNumberOfTokens(int tokens);

    // Retorna o numero de tokens no lugar
    int getNumberOfTokens();

};
