import numpy as np
from numpy.ma.core import asarray

A_input = np.matrix('0 0 0 0 0 1 0 0 0 0; 1 1 0 0 1 0 0 0 0 0; 1 1 1 5 0 0 0 0 0 0; 1 1 0 0 0 0 1 0 0 0; 0 0 0 0 0 0 0 1 0 0; 0 0 0 0 0 0 0 0 0 1; 0 0 0 0 0 0 0 0 1 0')

#           Motor  Sensor  LED  Contador  Cont_max  PWM  L&PWM_on  LED_Emg  Mot_h  Mot_ant
# A_input =   0      0      0      0         0       1       0        0       0       0     Na
#             1      1      0      0         1       0       0        0       0       0     Peça_detectada
#             1      1      1      5         0       0       0        0       0       0     Cont_é_5
#             1      1      0      0         0       0       1        0       0       0     Nf_on
#             0      0      0      0         0       0       0        1       0       0     Nf_off
#             0      0      0      0         0       0       0        0       0       1     Motor_anti-horario
#             0      0      0      0         0       0       0        0       1       0     Motor_horario

A_output = np.matrix('1 1 1 0 0 0 1 0 0 0; 1 1 0 1 0 0 0 0 0 0; 0 0 0 0 5 1 0 0 0 0; 0 0 0 0 0 0 0 1 0 0; 1 1 0 0 0 0 1 0 0 0; 0 0 0 0 0 0 0 0 1 0; 0 0 0 0 0 0 0 0 0 1')

#           Motor  Sensor  LED  Contador  Cont_max  PWM  L&PWM_on  LED_Emg  Mot_h  Mot_ant
# A_output =  1      1      1      0         0       0       1        0       0       0     Na
#             1      1      0      1         0       0       0        0       0       0     Peça_detectada
#             0      0      0      0         5       1       0        0       0       0     Cont_é_5
#             0      0      0      0         0       0       0        1       0       0     Nf_on
#             1      1      0      0         0       0       1        0       0       0     Nf_off
#             0      0      0      0         0       0       0        0       1       0     Motor_anti-horario
#             0      0      0      0         0       0       0        0       0       1     Motor_horario


A = A_output - A_input

# Estado inicial

x0 = np.array([0, 0, 0, 0, 5, 1, 0, 0, 0, 1])

# Definindo as transições

Na = (np.array([1, 0, 0, 0, 0, 0, 0]), "Na")
S_activate = (np.array([0, 1, 0, 0, 0, 0, 0]), "S_activate")
Count_5 = (np.array([0, 0, 1, 0, 0, 0, 0]), "Count_5")
Nf_on = (np.array([0, 0, 0, 1, 0, 0, 0]), "Nf_on")
Nf_off = (np.array([0, 0, 0, 0, 1, 0, 0]), "Nf_off")
Motor_antiH = (np.array([0, 0, 0, 0, 0, 1, 0]), "Motor_antiH")
Motor_H = (np.array([0, 0, 0, 0, 0, 0, 1]), "Motor_H")

all_transactions = [Na, S_activate, Count_5, Nf_on, Nf_off, Motor_antiH, Motor_H]
trigger =[Na, S_activate, Motor_antiH, S_activate, Nf_on, Nf_off, S_activate, S_activate, S_activate, Count_5, Na]
error_trigger = [Na, S_activate, Na, Nf_off]

def isTransitionActive(transition, state):
    result = np.squeeze(np.asarray(state - (transition[0] * A_input)))
    for temp in result:
        if temp < 0:
            print()
            print("The transition", end =" ")
            print(transition[1], end =" ")
            print("is not active for the state", end = " ")
            print(x0)
            return False
    return True

def runTransitions(transitionsVec, initialState):
    actualState = initialState
    for transition in transitionsVec:
        if(isTransitionActive(transition, actualState)):
            actualState = np.squeeze(np.asarray(actualState + transition[0] * A))
            print("Actual state:", end = " ")
            print(actualState)
        else:
            print("Stoping execution...")
            break
        
print("Beginning in ")
print(x0)
runTransitions(trigger, x0)

print()
print("Testing non-active transacion")
runTransitions(error_trigger, x0)