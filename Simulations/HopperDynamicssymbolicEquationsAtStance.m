clear; clc
syms g l1 l2 m1 m2 lc1 lc2 J1 J2 theta1 theta2 dtheta1 dtheta2 ddtheta1 ddtheta2 tau1 tau2 L1

M11 = (m1*l2^2 + 2*m1*cos(theta2)*l2*lc1 + m1*lc1^2 + m2*lc2^2 + J1 + J2);
M12 = (- m1*l2^2 - lc1*m1*cos(theta2)*l2 - m2*lc2^2 - J2);
M21 = (- m1*l2^2 - lc1*m1*cos(theta2)*l2 - m2*lc2^2 - J2);
M22 = (m1*l2^2 + m2*lc2^2 + J2);

C11 = - 2*l2*lc1*m1*sin(theta2)*dtheta2;
C12 = l2*lc1*m1*sin(theta2)*dtheta2;
C21 = lc1*m1*sin(theta2)*l2*dtheta1;
C22 = 0;

G1 = (- l2*m1*sin(theta1 - theta2) - lc2*m2*sin(theta1 - theta2) - lc1*m1*sin(theta1))*g;
G2 = (l2*m1*sin(theta1 - theta2) + lc2*m2*sin(theta1 - theta2))*g;

M = [M11, M12; M21, M22];
C = [C11, C12; C21, C22];
G = [G1; G2];
T = [0; tau2];

% A
A_1 = - l1*cos(theta1) - l2*cos(theta1 - theta2);
A_2 = l2*cos(theta1 - theta2);
A = [A_1, A_2;];
% dA
dA_1 = l2*sin(theta1 - theta2)*(dtheta1 - dtheta2) + l1*sin(theta1)*dtheta1;
dA_2 = -l2*sin(theta1 - theta2)*(dtheta1 - dtheta2);
dA = [dA_1, dA_2];

% Calculate Lagrangian multipliers
L = simplify(inv(A*inv(M)*A')*(A*inv(M)*(T-C*[dtheta1; dtheta2]-G)+dA*[dtheta1; dtheta2]));
% Obtain symbolic ODE
ddtheta = simplify(inv(M)*(-C*[dtheta1; dtheta2] - G - A'*L + T));