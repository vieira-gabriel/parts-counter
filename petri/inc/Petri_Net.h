#pragma once

#include <Transition.h>
#include <Place.h>

using namespace std;

typedef enum
{
   P_OFF,
   P_MOTOR,
   P_SENSOR,
   P_LED,
   P_COUNTER,
   P_MAX_COUNT,
   P_LED_PWM,
   P_LED_EMERGENCY
} place_id;

typedef enum
{
    T_NA_PRESS,
    T_DETECT,
    T_COUNT_5,
    T_NF_ON,
    T_NF_OFF
} transition_id;

typedef enum
{
    MOTOR_CLOCKWISE,
    MOTOR_ANTICLOCKWISE
} motor_direction;

class Petri_Net
{
private:
    vector<Transition> transitions;
	vector<weak_ptr<Place>> places;

    vector<weak_ptr<Place>> getPlacesFromNames(vector<string> names);
    void createTransition(vector<string> &originPlaces,
                            vector<int> &originWeights,
                            vector<string> &destinationPlaces,
                            vector<int> &destinationWeights);
    void createPlace(string name,
						int initialNumberOfTokens);

public:
    Petri_Net(/* args */);
    ~Petri_Net();

    void printState();
    int getNumberOfTokens(string place);
    void run(vector<string> transitionsOrder);
    int generatePN(vector<string> places,
                    vector<string> transitions,
                    vector<vector<int>> originMatrix,
                    vector<vector<int>> destinationMatrix);

};
