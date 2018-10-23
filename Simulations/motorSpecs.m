%% Script to obtain the internal characteristics of the used motor from the parameters given in the datasheet
clear all; clc;
appliedVoltage = 12; % applied voltage [V]
v_noLoad = 80*2*pi/60; % no-load speed [rad/s] @12V
I_noLoad = 0.3; % no-load current [A] @12V
I_stall = 5; % stall current [A] @12V
T_stall = 1.7654; % stall torque [Nm] @12V

% Calculate the internal parameters Rm, Km, Kt and T_friction
Rm = appliedVoltage/I_stall; % internal resistance [Ohm]
Kt = T_stall/(I_stall-I_noLoad); % torque constant [Nm/A]
T_friction = Kt*I_stall-T_stall; % static friction torque[Nm]
Ke = (appliedVoltage-Rm*I_noLoad)/v_noLoad; % speed constant [Vs/rad]