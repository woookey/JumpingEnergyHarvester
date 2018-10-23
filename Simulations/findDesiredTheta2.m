function th2 = findDesiredTheta2(theta1, l1, l2, l)
    %th2 = theta1-acos((l-l1*cos(theta1))/l2);
    % or
    th2 = theta1+acos((l-l1*cos(theta1))/l2);
end