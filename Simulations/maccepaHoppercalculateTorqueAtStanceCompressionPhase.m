function [K, Prege, T] = maccepaHoppercalculateTorqueAtStanceCompressionPhase(Q, param)
    theta1 = Q(1); theta2 = Q(2); dtheta1=Q(3); dtheta2=Q(4);
    l2 = param.l2; lc2 = param.lc2; l1 = param.l1; lc1 = param.lc1;
    g = param.g; m1=param.m1; m2 = param.m2;
    
    T = zeros(2, 1);
    u1 = 0; % Equilibrium angle
    % Limit equilibrium angle to [-pi/2, pi/2]
    if (u1>pi/2)
        u1 = pi/2;
    elseif (u1<-pi/2)
        u1 = -pi/2;
    end
    u2 = param.preTensionAngleDuringStance_compression; % Pre-tension
    
    % Calculate regenerative power and achieved stiffness
    Prege = (param.batteryResistance*param.motor.Kt^2*param.motor.Ke^2*dtheta2^2)/(param.batteryResistance+param.motor.Rm)^2;
    K = param.k0*param.B*param.C*cos(u1-theta2)*(1+(param.r*u2+param.B-param.C)/sqrt(param.B^2+param.C^2-2*param.B*param.C*cos(u1-theta2)))...
        -(param.k0*param.B^2*param.C^2*sin(u1-theta2)^2*(param.r*u2+param.B-param.C))/(param.B^2+param.C^2-2*param.B*param.C*cos(u1-theta2))^(3/2);
    
    T(1) = 0;
    T(2)=param.k0*param.B*param.C*sin(u1-theta2)*(1+(param.r*u2+param.B-param.C)/sqrt(param.B^2+param.C^2-2*param.B*param.C*cos(u1-theta2)))-param.motor.T_friction;
end