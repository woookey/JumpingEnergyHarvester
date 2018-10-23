function [Q_afterTD] = speedConversionAfterTouchdown(Q_beforeTD, param)
    % Q_afterTouchdown = [theta1, theta2, dtheta1, dtheta2]
    % Q_beforeTouchdown = [theta1, theta2, xf, yf, dtheta1, dtheta2, dxf, dyf]
    theta1before = Q_beforeTD(1); theta2before = Q_beforeTD(2);
    xfbefore = Q_beforeTD(3); yfbefore = Q_beforeTD(4);
    dtheta1before = Q_beforeTD(5); dtheta2before = Q_beforeTD(6);
    dxfbefore = Q_beforeTD(7); dyfbefore = Q_beforeTD(8);
    
    dQ_hx_beforeTD = dxfbefore+param.l2*cos(theta2before-theta1before)*(dtheta2before-dtheta1before)-param.l1*cos(theta1before)*dtheta1before;
    dQ_hy_beforeTD = dyfbefore-param.l2*sin(theta2before-theta1before)*(dtheta2before-dtheta1before)-param.l1*sin(theta1before)*dtheta1before;
    dQ_h_beforeTD = [dQ_hx_beforeTD; dQ_hy_beforeTD];
    
    A = [-(param.l2*cos(theta2before-theta1before)+param.l1*cos(theta1before)), param.l2*cos(theta2before-theta1before);...
        param.l2*sin(theta2before-theta1before)-param.l1*sin(theta1before), -param.l2*sin(theta2before-theta1before)];
    
    dthetaafterTD = zeros(2,1);
    dthetaafterTD = inv(A)*dQ_h_beforeTD;
    
    Q_afterTD = [theta1before, theta2before, dthetaafterTD'];
end