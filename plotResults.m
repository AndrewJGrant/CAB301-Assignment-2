% Plotting command for CAB301 Assignment 2 Semester 1 2017
% Author: Shane Havers n9477756
clear; close all; clc;
%% Read In Data
dataOps = csvread('OutputOps.csv', 1, 0);
dataTime = csvread('OutputTime.csv', 1, 0);

%% Plot Data for Basic Operations Counting
figure()
plot(dataOps(:,1), dataOps(:,2), 'b-*');
hold on
plot(dataOps(:,1), dataOps(:,3), 'b-o');
plot(dataOps(:,1), dataOps(:,1).^2 - dataOps(:,1), 'r-*', 'MarkerSize', 3)
plot(dataOps(:,1), (dataOps(:,1).^2) ./ 2 - (dataOps(:,1)./2), 'r-o', 'MarkerSize', 3);
hold off
title('Count of Basic Operation Executions')
xlabel('Input Size')
ylabel('Basic operations executed')
legend('MinDistance', 'MinDistance2', 'Expected MinDistance',...
    'Expected MinDistance2', 'Location', 'northwest')

%% Plot Data for Execution Times
figure()
plot(dataTime(:,1), dataTime(:,2), 'b-*');
hold on
plot(dataTime(:,1), dataTime(:,3), 'r-*');
hold off
title('Execution Time Trial Results')
xlabel('Input Size')
ylabel('Execution Time (ms)')
legend('MinDistance', 'MinDistance2', 'Location', 'northwest')