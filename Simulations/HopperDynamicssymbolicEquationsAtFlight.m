clear; clc
syms g l1 l2 m1 m2 lc1 lc2 J1 J2 theta1 theta2 dtheta1 dtheta2 ddtheta1 ddtheta2 tau1 tau2 xf dxf ddxf yf dyf ddyf

% Q = [theta1, theta2, xf, yf]

M11 = m1*l2^2 + 2*m1*cos(theta2)*l2*lc1 + m1*lc1^2 + m2*lc2^2 + J1 + J2;
M12 = - m1*l2^2 - lc1*m1*cos(theta2)*l2 - m2*lc2^2 - J2;
M13 = - l2*m1*cos(theta1 - theta2) - lc2*m2*cos(theta1 - theta2) - lc1*m1*cos(theta1);
M14 = - l2*m1*sin(theta1 - theta2) - lc2*m2*sin(theta1 - theta2) - lc1*m1*sin(theta1);

M21 = - m1*l2^2 - lc1*m1*cos(theta2)*l2 - m2*lc2^2 - J2;
M22 = m1*l2^2 + m2*lc2^2 + J2;
M23 = cos(theta1 - theta2)*(l2*m1 + lc2*m2);
M24 = sin(theta1 - theta2)*(l2*m1 + lc2*m2);

M31 = - l2*m1*cos(theta1 - theta2) - lc2*m2*cos(theta1 - theta2) - lc1*m1*cos(theta1);
M32 = cos(theta1 - theta2)*(l2*m1 + lc2*m2);
M33 = m1 + m2;
M34 = 0;

M41 = - l2*m1*sin(theta1 - theta2) - lc2*m2*sin(theta1 - theta2) - lc1*m1*sin(theta1);
M42 = sin(theta1 - theta2)*(l2*m1 + lc2*m2);
M43 = 0;
M44 = m1 + m2;

C11 = -2*l2*lc1*m1*sin(theta2)*dtheta2;
C12 = l2*lc1*m1*sin(theta2)*dtheta2;
C13 = 0;
C14 = 0;

C21 = l2*lc1*m1*sin(theta2)*dtheta1;
C22 = 0;
C23 = 0;
C24 = 0;

C31 = (l2*m1*sin(theta1 - theta2) + lc2*m2*sin(theta1 - theta2) + lc1*m1*sin(theta1))*dtheta1;
C32 = sin(theta1 - theta2)*(l2*m1 + lc2*m2)*dtheta2 + (-2*sin(theta1 - theta2)*dtheta1*(l2*m1 + lc2*m2));
C33 = 0;
C34 = 0;

C41 = (- l2*m1*cos(theta1 - theta2) - lc2*m2*cos(theta1 - theta2) - lc1*m1*cos(theta1))*dtheta1 + dtheta2*(2*l2*m1*cos(theta1 - theta2) + 2*lc2*m2*cos(theta1 - theta2));
C42 = - dtheta2*(l2*m1*cos(theta1 - theta2) + lc2*m2*cos(theta1 - theta2));
C43 = 0;
C44 = 0;

G1 = -g*(l2*m1*sin(theta1 - theta2) + lc2*m2*sin(theta1 - theta2) + lc1*m1*sin(theta1));
G2 = g*sin(theta1 - theta2)*(l2*m1 + lc2*m2);
G3 = 0;
G4 = (m1 + m2)*g;

M = [M11, M12, M13, M14; M21, M22, M23, M24; M31, M32, M33, M34; M41, M42, M43, M44];
C = [C11, C12, C13, C14; C21, C22, C23, C24; C31, C32, C33, C34; C41, C42, C43, C44];
G = [G1; G2; G3; G4];
T = [0; tau2; 0; 0];

% A
A_1 = - l1*cos(theta1) - l2*cos(theta1 - theta2);
A_2 = l2*cos(theta1 - theta2);
A_3 = 1;
A_4 = 0;
A = [A_1, A_2, A_3, A_4];
% dA
dA_1 = l2*sin(theta1 - theta2)*(dtheta1 - dtheta2) + l1*sin(theta1)*dtheta1;
dA_2 = -l2*sin(theta1 - theta2)*(dtheta1 - dtheta2);
dA_3 = 0;
dA_4 = 0;
dA = [dA_1, dA_2, dA_3, dA_4];

ddtheta = simplify(inv(M)*(-C*[dtheta1; dtheta2; dxf; dyf] - G + T));
