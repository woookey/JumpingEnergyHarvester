function [] = maccepaHopper_visualisation(T_t, Q_t, param)
% T_t - time array
% Q_t = [theta1, theta2, xf, yf]
% param contains specifications of the robot

%theta1 = Q_t(:, 1);
%theta2 = Q_t(:, 2);
%xf = Q_t(:, 3);
%yf = Q_t(:, 4);

% Interpolate points of Q_t according to the resolution of Tres
Tres = 1e-2;
T = [0: Tres: T_t(end)];
%eps = 0.001;
%Q_t(:, 1) = cumsum(ones(size(Q_t(:, 1))))*eps + Q_t(:, 1);
theta1 = interp1(T_t, Q_t(:,1), T);
theta2 = interp1(T_t, Q_t(:,2), T);
xf = interp1(T_t, Q_t(:,3), T);
yf = interp1(T_t, Q_t(:, 4), T);


% Set parameters of the visualisation
figure(1);
hFig = figure(1);
set(gcf,'PaperPositionMode','auto')
set(hFig, 'Position', [300 300 800 1500])
axis(gca, 'equal');
xlow = -1; xhigh = 1;
axis([xlow xhigh -0.4 0.9]);
xlabel('X[m]'); ylabel('Y[m]')
title('Maccepa Hopper Visualisation');
timeS = {'[Time =', num2str(0), 's]'};
timeBox = text(0, -0.2, strjoin(timeS));


for it=1:size(T,2) % iterate through time
    % Calculate position of each link
    Link2Coordinates = [[xf(it), xf(it)+param.l2*sin(theta2(it)-theta1(it))]; [yf(it), yf(it)+param.l2*cos(theta2(it)-theta1(it))]];
    link2 = line(Link2Coordinates(1,:), Link2Coordinates(2,:), 'Color', 'black', 'LineWidth', 2);
    Link1Coordinates = [[Link2Coordinates(1,2), xf(it)+param.l2*sin(theta2(it)-theta1(it))-param.l1*sin(theta1(it))];...
                        [Link2Coordinates(2,2), yf(it)+param.l2*cos(theta2(it)-theta1(it))+param.l1*cos(theta1(it))]];
    link1 = line(Link1Coordinates(1,:), Link1Coordinates(2,:), 'Color', 'black', 'LineWidth', 2);
    
    % Add surface
    surfaceCoordinates=[[xlow, xhigh];[0, 0]];
    surfaceLine=line(surfaceCoordinates(1,:), surfaceCoordinates(2,:), 'Color', 'black', 'LineWidth', 3);
    % Add post line
    postCoordinates = [[0, 0]; [0, 0.5]];
    postLine = line(postCoordinates(1,:), postCoordinates(2,:), 'Color', 'green', 'LineWidth', 0.5, 'LineStyle', '--');
    pause(0.05);
    
    % Clear frame if not the end of visualisation
    if (it~=size(T,2))
        delete(link2)
        delete(link1)
    end
    
    % Show current time
	timeS = {'[Time =', num2str(T(it)), 's]'};
    set(timeBox, 'String', strjoin(timeS));

end