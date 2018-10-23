clear all; clc
%% Initialise system
param.g = 9.81;
param.l = 1;
param.m = 1;
param.k = 100;
param.b = 5;

X0 = [param.l*2; 0];
Tmax = 40;
tspan = [0; 40];

% Phases description
% 1 - ballistic flight mode
% 2 - compression mode
% 3 - thrust mode
% 4 - decompression mode
nextPhase = 1;

T = 0;
X = X0';
while(T(end) < Tmax)
    T_currentMode = 0;
    X_currentMode = zeros(1,2);
    
    if (nextPhase == 1) % Perform ballistic mode when phase = 1
        optionsTouchdown = odeset('events', @eventTouchdown, 'MaxStep', 0.001);
        [T_currentMode, X_currentMode] = ode45(@(t, X)dynamicsBallisticFlight(t, X, param), [0; Tmax-T(end)], X(end, :)', optionsTouchdown);
        nextPhase = 2;
        
    elseif (nextPhase == 2) % Perform compression mode when phase = 2
        optionsCompression = odeset('events', @eventBottom, 'MaxStep', 0.001);
        [T_currentMode, X_currentMode] = ode45(@(t, X)dynamicsCompression(t, X, param), [0; Tmax-T(end)], X(end,:)', optionsCompression);
        nextPhase = 3;
        
    elseif (nextPhase == 3) % Perform thrust mode when phase = 3
        % Setting delta for thrust
        thrust.deltaThrust = 0.1;
        thrust.desiredThrust = 50;
        optionsThrust = odeset('MaxStep', 0.001);
        [T_currentMode, X_currentMode] = ode45(@(t, X)dynamicsThrust(t, X, param, thrust.desiredThrust), [0, thrust.deltaThrust], X(end,:)', optionsThrust);
        nextPhase = 4;
        
    elseif (nextPhase == 4) % Perform decompression mode when phase = 4
        optionsDecompression = odeset('events', @eventLiftOff, 'MaxStep', 0.001);
        [T_currentMode, X_currentMode] = ode45(@(t, X)dynamicsDecompression(t, X, param), [0; Tmax-T(end)], X(end,:)', optionsDecompression);
        nextPhase = 1;
    end
    T = [T; T(end)+T_currentMode(2:end)];
    X = [X; X_currentMode(2:end,:)];
end

%% Plotting results

figure(1);
set(gca, 'FontName', 'Ubuntu');
set(gca, 'FontSize', 24);
plot(T, X(:, 1), T, X(:, 2));
xlabel('Time'), ylabel('Amplitude');
legend('Position', 'Velocity');

set(gca, 'FontName', 'Ubuntu');
set(gca, 'FontSize', 24);
figure(2);
plot(X(:, 1), X(:, 2));
xlabel('Position'), ylabel('Velocity');
title('Poincare Map');

%% Modes definitions
function dX = dynamicsDecompression(t, X, param)
    % gravity-matched spring loaded inverted pendulum dynamics
    dX = zeros(2,1);
    dX(1) = X(2);
    dX(2) = -param.k/param.m*X(1)-param.b/param.m*X(2);
end

function dX = dynamicsThrust(t, X, param, desiredThrust)
    % Fixed thrust over delta t
    dX = zeros(2,1);
    dX(1) = X(2);
    dX(2) = -param.b/param.m*X(2)+desiredThrust/param.m;
    
end

function dX = dynamicsCompression(t, X, param)
    dX = zeros(2,1);
    dX(1) = X(2);
    dX(2) = -param.k/param.m*X(1)-param.b/param.m*X(2);
end

function dX = dynamicsBallisticFlight(t, X, param)
    % Only gravity acting on the mass during flight
    dX = zeros(2,1);
    dX(1) = X(2);
    dX(2) = -param.g;
end

function [value, isterminal, direction] = eventTouchdown(t, X)
    isterminal = 1;
    direction = 0;
    value = X(1);
end

function [value, isterminal, direction] = eventBottom(t, X)
    isterminal = 1;
    direction = 1;
    value = X(2);
end

function [value, isterminal, direction] = eventLiftOff(t, X)
    isterminal = 1;
    direction = 0;
    value = X(1);
end