clear; clc; close all;
% Robot specification parameters
param.m1 = 1.165; % mass of the first link [kg] 
param.m2 = 0.475; % mass of the second link [kg]
param.l1 = 0.22; % length of the first link [m]
param.l2 = 0.27; % length of the second link [m]
param.r = 0.009; % radius of the pre-tensioning spool [m]
param.g = 9.81; % gravity [m/s^2]
param.B = 0.035; % MACCEPA lever length [m]
param.C = 0.085; % MACCEPA distance between second joint and the pivot point [m]
param.lc2 = 0.1594; % centre of mass of the second link (measured from second foot) [m]
param.lc1 =  0.1109; % centre of mass of the first link (measured from second joint) [m]
param.J1 = 0.0187; % Inertia of the first link [kg*m^2]
param.J2 = 0.0138; % Inertia of the second link [kg*m^2]
param.k0 = 4830; % Spring rate [N/m]

% Motors specification parameters
param.motor.Rm = 2.4; % internal resistance [Ohm]
param.motor.Kt = 0.3756; % torque constant [Nm/A]
param.motor.T_friction = 0.1127; % friction of the motor [Nm]
param.motor.Ke = 1.3465; % speed constant [Vs/rad]
param.batteryResistance = 10; % resistance of the battery to be charged [Ohm]

% Control specification parameters
param.preTensionAngleDuringFlight = 0;
param.preTensionAngleDuringStance_compression = 2;
param.preTensionAngleDuringStance_decompression = 2.5*pi;

% Initial and temporary data for tracking
param.xf0 = 0;
param.yf0 = 0.05;
param.lastTouchdownHip_y = 0;
Tmax = 1.5;
param.noOfJumps = 0;
param.noOfJumpsToBePerformed = 3;

% Initialise array for visualisation
Ttotal = [];
Qtotal = [];
dQtotal = [];
Tcurrent = 0;

% Variables for estimating total energy consumption and regeneration
E_total = 0;
E_regenerated = 0;

% Calculate theta1 so that the hip is on the slider
theta2_0 = pi/3;
l = sqrt(param.l1^2+param.l2^2+2*param.l1*param.l2*cos(theta2_0));
param.theta1_0 = theta2_0+asin(param.xf0/l)-asin(param.l1/l*sin(theta2_0));

tspan = [Tcurrent Tmax];
Qcurrent = [param.theta1_0, theta2_0, param.xf0, param.yf0, 0, 0, 0, 0];

% Modes description
% Ballistic Flight Phase = 1
% Compression Phase = 2
% Decompression Phase = 3
% Stopping Phase = 4
Phase = 1; 
delete data;
while (Tcurrent < Tmax)
    if (Phase == 1) 
        
        %% Perform Ballistic Flight Phase
        tspan = [Tcurrent, Tmax];
        optionsFlight = odeset('Events', @(t, Q)EventTouchdown(t, Q, param, Tcurrent), 'MaxStep', 1e-3, 'AbsTol', 1e-4, 'RelTol', 1e-4);
        %if (noOfJumps == 1)
        %    optionsFlight = odeset('MaxStep', 1e-3, 'AbsTol', 1e-4, 'RelTol', 1e-4);
        %end
        [TFlight, QFlight] = ode45(@(t, Q)BallisticFlightPhase(t, Q, param), tspan, Qcurrent, optionsFlight);
        
        % Read the file with K, Prege and t from the above ode
        fid = fopen('data', 'r');
        D = textscan(fid, '%f %f %f %f');
        Kvalues = D{:, 1}; Pregevalues = D{:, 2}; T = D{:, 3}; dTheta2 = D{:, 4};
        fclose(fid);
        delete data;
        
        %Integrate energy consumption and regeneration
        E_total = E_total + trapz(T, Kvalues.*abs(dTheta2));
        E_regenerated = E_regenerated + trapz(T, Pregevalues);
        
        % Calculate y at touchdown
        param.lastTouchdownHip_y = QFlight(end, 4)+param.l2*cos(QFlight(end, 2)-QFlight(end, 1))+param.l1*cos(QFlight(end, 1));
        % Update array for visualisation
        Ttotal = [Ttotal; TFlight(1:end-1)];
        Qtotal = [Qtotal; QFlight(1:end-1, 1:4)];
        dQtotal = [dQtotal; QFlight(1:end-1, 5:8)];
        Tcurrent = TFlight(end);
        Qcurrent = speedConversionAfterTouchdown(QFlight(end, :), param);
        if (param.noOfJumps == param.noOfJumpsToBePerformed)
            Phase = 4; % next phase is stopping
        else
            Phase = 2; % next phase is compression
        end
        
    elseif (Phase == 2) 
        
        %% Peform Compression Phase
        tspan = [Tcurrent, Tmax];
        optionsCompression = odeset('Events', @(t, Q)EventBottom(t, Q, param), 'MaxStep', 1e-4, 'AbsTol', 1e-4, 'RelTol', 1e-4);
        [TComp, QComp] = ode45(@(t, Q)CompressionPhase(t, Q, param), tspan, Qcurrent, optionsCompression);

        % Read the file with K, Prege and t from the above ode
        fid = fopen('data', 'r');
        D = textscan(fid, '%f %f %f %f');
        Kvalues = D{:, 1}; Pregevalues = D{:, 2}; T = D{:, 3}; dTheta2 = D{:, 4};
        fclose(fid);
        delete data;
        
        %Integrate energy consumption and regeneration
        E_total = E_total + trapz(T, Kvalues.*abs(dTheta2));
        E_regenerated = E_regenerated + trapz(T, Pregevalues);
        
        % Update array for visualisation and conditions for the next phase
        Ttotal = [Ttotal; TComp(1:end-1)];
        Qtotal = [Qtotal; [QComp(1:end-1, 1), QComp(1:end-1, 2), QFlight(end, 3)*ones(size(QComp, 1)-1, 1), QFlight(end, 4)*ones(size(QComp, 1)-1, 1)]]; 
        dQtotal = [dQtotal; [QComp(1:end-1, 3:4), zeros(size(QComp, 1)-1, 1), zeros(size(QComp, 1)-1, 1)]];
        Tcurrent = TComp(end);
        Qcurrent = QComp(end, :);
        Phase = 3; % next phase is the decompression
        
    elseif (Phase == 3) 
        
        %% Perform Decompression Phase
        tspan = [TComp(end), Tmax];
        optionsDecompression = odeset('Events', @(t, Q)EventLiftOff(t, Q, param), 'MaxStep', 1e-4, 'AbsTol', 1e-4, 'RelTol', 1e-4);
        [TDecomp, QDecomp] = ode45(@(t, Q)DecompressionPhase(t, Q, param), tspan, Qcurrent, optionsDecompression);

        % Read the file with K, Prege and t from the above ode
        fid = fopen('data', 'r');
        D = textscan(fid, '%f %f %f %f');
        Kvalues = D{:, 1}; Pregevalues = D{:, 2}; T = D{:, 3}; dTheta2 = D{:, 4};
        fclose(fid);
        delete data;
        
        %Integrate energy consumption and regeneration
        E_total = E_total + trapz(T, Kvalues.*abs(dTheta2));
        E_regenerated = E_regenerated + trapz(T, Pregevalues);
        
        % Update array for visualisation and conditions for the next phase
        Ttotal = [Ttotal; TDecomp(1:end-1)];
        Qtotal = [Qtotal; [QDecomp(1:end-1, 1), QDecomp(1:end-1, 2), Qtotal(end, 3)*ones(size(QDecomp, 1)-1, 1), Qtotal(end, 4)*ones(size(QDecomp, 1)-1, 1)]]; 
        dQtotal = [dQtotal; [QDecomp(1:end-1, 3:4), zeros(size(QDecomp, 1)-1, 1), zeros(size(QDecomp, 1)-1, 1)]];
        Tcurrent = TDecomp(end);
        Qcurrent = [QDecomp(end, 1:2), Qtotal(end, 3:4), QDecomp(end, 3:4), 0, 0];
        Phase = 1; % next phase is the flight
        param.noOfJumps = param.noOfJumps+1;
    elseif (Phase == 4) % Perform stopping phase
        %% Peform Stopping Phase
        tspan = [Tcurrent, Tmax];
        optionsStopping = odeset('Events', @(t, Q)EventFullStop(t, Q, param), 'MaxStep', 1e-4, 'AbsTol', 1e-4, 'RelTol', 1e-4);
        [TStopping, QStopping] = ode45(@(t, Q)StoppingPhase(t, Q, param), tspan, Qcurrent, optionsStopping);

        % Read the file with K, Prege and t from the above ode
        fid = fopen('data', 'r');
        D = textscan(fid, '%f %f %f %f');
        Kvalues = D{:, 1}; Pregevalues = D{:, 2}; T = D{:, 3}; dTheta2 = D{:, 4};
        fclose(fid);
        delete data;
        
        %Integrate energy consumption and regeneration
        E_total = E_total + trapz(T, Kvalues.*abs(dTheta2));
        E_regenerated = E_regenerated + trapz(T, Pregevalues);
        
        % Update array for visualisation and conditions for the next phase
        Ttotal = [Ttotal; TStopping(1:end-1)];
        Qtotal = [Qtotal; [QStopping(1:end-1, 1), QStopping(1:end-1, 2), QFlight(end, 3)*ones(size(QStopping, 1)-1, 1), QFlight(end, 4)*ones(size(QStopping, 1)-1, 1)]]; 
        dQtotal = [dQtotal; [QStopping(1:end-1, 3:4), zeros(size(QStopping, 1)-1, 1), zeros(size(QStopping, 1)-1, 1)]];
        Tcurrent = Tmax; % stop the simulation when the robot stops completely
        Qcurrent = QStopping(end, :);
        break; % stop simulation
    end
end

% Plot the results
figure(5)
plot(Ttotal, Qtotal(:, 1), Ttotal, Qtotal(:, 2), Ttotal, Qtotal(:, 3), Ttotal, Qtotal(:, 4));
xlabel('Time[s]'), ylabel('Amplitude');
title('MACCEPA Simulation (1)'),
legend('theta1', 'theta2', 'xf', 'yf');

figure(6)
plot(Ttotal, dQtotal(:, 1), Ttotal, dQtotal(:, 2), Ttotal, dQtotal(:, 3), Ttotal, dQtotal(:, 4));
xlabel('Time[s]'), ylabel('Amplitude');
title('MACCEPA Simulation (2)'),
legend('dtheta1', 'dtheta2', 'dxf', 'dyf');

HipData = calculatePositionAndVelocityOfTheHip(Qtotal, dQtotal, param);
figure(7)
plot(HipData(:, 1), HipData(:, 2));
xlabel('Hip position[m]'), ylabel('Hip velocity[m/s]')

%Calculate the energy efficiency
E_net = E_total - E_regenerated;
efficiency = E_regenerated/E_total;
%Visualise the hopping
maccepaHoppervisualisation(Ttotal, Qtotal, param);



function dQ = DecompressionPhase(t, Q, param)
    % param is the specification of the robot
    % Q = [theta1, theta2, dtheta1, dtheta2]
    % dQ = [dtheta1, dtheta2, ddtheta1, ddtheta2]
    % Compute torque to be applied as T = [tau1; tau2], where tau1 = 0
    [K, Prege, appliedTorque] = maccepaHoppercalculateTorqueAtStanceDecompressionPhase(Q, param);
    
    % Save data into a file
    fid = fopen('data', 'a');
    fprintf(fid, '%f %f %f %f\n', K, Prege, t, Q(4));
    fclose(fid);
    
    % Obtain natural dynamics of the modelled maccepa
    dQ = maccepaHoppermaccepaModelDynamicsAtStance(Q, param, appliedTorque);
    
end 

function dQ = CompressionPhase(t, Q, param)
    % param is the specification of the robot
    % Q = [theta1, theta2, dtheta1, dtheta2]
    % dQ = [dtheta1, dtheta2, ddtheta1, ddtheta2]
    
    % Compute torque to be applied as T = [tau1; tau2], where tau1 = 0
    [K, Prege, appliedTorque] = maccepaHoppercalculateTorqueAtStanceCompressionPhase(Q, param);
    
    % Save data into a file
    fid = fopen('data', 'a');
    fprintf(fid, '%f %f %f %f\n', K, Prege, t, Q(4));
    fclose(fid);
    
    % Obtain natural dynamics of the modelled maccepa
    dQ = maccepaHoppermaccepaModelDynamicsAtStance(Q, param, appliedTorque);
    
end

function dQ = BallisticFlightPhase(t, Q, param)
    % Q = [theta1, theta2, xf, yf, dtheta1, dtheta2, dxf, dyf]
    % dQ = [dtheta1, dtheta2, dxf, dyf, ddtheta1, ddtheta2, ddxf, ddyf]
    
    [K, Prege, appliedTorqueAtFlight] = maccepaHoppercalculateTorqueAtFlight(Q, param);

    % Save data into a file
    fid = fopen('data', 'a');
    fprintf(fid, '%f %f %f %f\n', K, Prege, t, Q(6));
    fclose(fid);
    
    dQ = maccepaHoppermaccepaModelDynamicsAtFlight(Q, param, appliedTorqueAtFlight);
end

function dQ = StoppingPhase(t, Q, param)
    % Q = [theta1, theta2, dtheta1, dtheta2]
    % dQ = [dtheta1, dtheta2, ddtheta1, ddtheta2]
    
    % Compute torque to be applied as T = [tau1; tau2], where tau1 = 0
    [K, Prege, appliedTorque] = maccepaHoppercalculateTorqueAtStanceStoppingPhase(Q, param);
    
    % Save data into a file
    fid = fopen('data', 'a');
    fprintf(fid, '%f %f %f %f\n', K, Prege, t, Q(4));
    fclose(fid);
    
    % Obtain natural dynamics of the modelled maccepa
    dQ = maccepaHoppermaccepaModelDynamicsAtStance(Q, param, appliedTorque);
end

function [value, isterminal, direction] = EventFullStop(t, Q, param)
    % Stop integration when the vertical velocity of the hip reaches zero
    % the tolerance set is equal to 0.001 [rad/s]
    % Q = [theta1, theta2, dtheta1, dtheta2]
    y_hipdot = -param.l2*sin(Q(2)-Q(1))*(Q(4)-Q(3))-param.l1*sin(Q(1))*Q(3);
    delta = 0.001;
    if (Q(3)+Q(4) >= 0.0001)
        value = 1;
    else
        value = -1;
    end
    direction = 0;
    isterminal = 1;
end

function [value, isterminal, direction] = EventBottom(t, Q, param)
    % Stop integration when the vertical velocity of the hip changes 
    % sign from negative to positive
    % Q = [theta1, theta2, dtheta1, dtheta2]
    value = -param.l2*sin(Q(2)-Q(1))*(Q(4)-Q(3))-param.l1*sin(Q(1))*Q(3);
    direction = 1;
    isterminal = 1;
end

function [value, isterminal, direction] = EventTouchdown(t, Q, param, tStartFlight)
    % Stop integration when the y coordinate of the foot is at 0
    % deltaT is to give simulation some time before the robot goes up in
    % the air
    deltaT = 0.1;
    if (t-tStartFlight <= deltaT)
        value = 1;
    else
        value = Q(4);
    end
    direction = 0;
    isterminal = 1;
end

function [value, isterminal, direction] = EventLiftOff(t, Q, param)
    % Stop integration when the y coordinate of the hip reaches 
    % the position at the last touchdown
    value = param.lastTouchdownHip_y-(param.l2*cos(Q(2)-Q(1))+param.l1*cos(Q(1)));
    direction = 0;
    isterminal = 1;
end