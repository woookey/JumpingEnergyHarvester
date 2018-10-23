M_motor = 0.235; % mass of the motors [kg]
M_dampingMotor = M_motor;
M_preTensioningMotor = M_motor;
M_equilibriumMotor = M_motor;
M_slidingBlock = 0.24; % mass of the sliding joint [kg]
M_shin = 0.24; % mass of the shin part [kg]
M_thigh = 0.455; % mass of the thigh part [kg]

L1_thigh = 0.15; % length of the thigh [m]
L1_damper = 0.05; % distance between the second joint and the damping motor [m] 
L1_slidingBlock = 0.22; % distance from the second joint to the sliding block [m]
L1_preTensioningMotor = 0.13; % distance from the second joint to the preTensioning motor [m]
L2_motor = 0.22; % distance from the bottom to the equilibrium angle motor [m]
L2_shin = 0.2; % length of the shin


% Calculate the approximated values of the intertia for both links
I_1 = M_slidingBlock*L1_slidingBlock^2 + M_dampingMotor*L1_damper^2 + ...
    M_thigh*(L1_thigh/2)^2 + M_preTensioningMotor*L1_preTensioningMotor^2;
I_2 = M_equilibriumMotor*L2_motor^2 + M_shin*(L2_shin/2)^2;

% Calculate the approximated values of the centre of masses for both links
lc1 = (M_slidingBlock*L1_slidingBlock + M_dampingMotor*L1_damper + ...
    M_thigh*(L1_thigh/2) + M_preTensioningMotor*L1_preTensioningMotor)/(M_slidingBlock + ...
    M_dampingMotor + M_thigh + M_preTensioningMotor);
lc2 = (M_equilibriumMotor*L2_motor + M_shin*(L2_shin/2))/(M_equilibriumMotor+M_shin);