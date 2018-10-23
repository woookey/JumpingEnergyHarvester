clear all; clc
%% Results of resulting torques on the built MACCEPA
B = 0.035; % [m]
C = 0.110; % [m]
r = 0.009; % [m]
k0 = 4830; % [N/m]
alpha = -pi/2:0.01:pi/2; % difference between equilibrium angle and joint angle [rad]


u2 = 0:pi/5:2*pi; % pre-tension angle [rad]
for i_u2 = 1:size(u2, 2)
    T(i_u2, :) = k0*B*C*sin(alpha).*(1+(r*u2(i_u2)+B-C)./sqrt(B^2+C^2-2*B*C*cos(alpha)));
end

% Plot resulting torques
figure(1)
plot(alpha, T);
set(gca, 'FontSize', 15);
xlabel('alpha(u_1-q) [rad]', 'FontSize', 20), ylabel('Torque [N*m]', 'FontSize', 20);
title('Torques exerted by spring on MACCEPA', 'FontSize', 20);
grid
legend({'u_2 = 0', 'u_2 = pi/5', 'u_2 = 2/5*pi', 'u_2 = 3/5*pi', 'u_2 = 4/5*pi', 'u_2 = pi', ...
    'u_2 = 6/5*pi', 'u_2 = 7/5*pi', 'u_2 = 8/5*pi', 'u_2 = 9/5*pi', 'u_2 = 2*pi'}, 'FontSize', 14, ...
    'Location', 'northwest');