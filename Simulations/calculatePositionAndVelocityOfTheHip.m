function HipData = calculatePositionAndVelocityOfTheHip(Q, dQ, param)
    % Obtain the position and velocity of the hip during the whole movement
    % Q = [theta1, theta2, xf, yf]
    % dQ = [dtheta1, dtheta2, dxf, dyf]
    
    HipData_position = Q(:, 4) + param.l2*cos(Q(:, 2)-Q(:, 1))-param.l1*cos(Q(:, 1));
    HipData_velocity = dQ(:, 4) - param.l2*sin(Q(:, 2)-Q(:, 1)).*(dQ(:, 2)-dQ(:, 1)) - param.l1*sin(Q(:, 1)).*dQ(:, 1);
    HipData = [HipData_position, HipData_velocity];
end