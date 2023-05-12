clear all
close all
clc
format long g
%Hodnoty změřeneé referečním multimeterem
file1 =  readmatrix("output_log_calibrated.txt");
calibrated_data = readmatrix("calibValues3.txt");
addvalue = 8;
tickSize = 15 + addvalue;
labelSize = 13 + addvalue;
titleSize = 14 + addvalue;
legendSize = 10 + addvalue;

ref_values = [0,16.4795,100.57,180.77,996.672,4673.19,0,0];
voltage_reference = 4095;
time = file1(:,1)/3600;
PIN1 = file1(:,2);
PIN2 = file1(:,3)-3;
PIN3 = file1(:,4)-3;
PIN4 = file1(:,5)-3;
PIN5 = file1(:,6)-7;
PIN6 = file1(:,7)-4;
%measurement at PIN 7 does not make sense, becasuse is out of range (-1
%values)
PIN7 = file1(:,8);
PIN8 = file1(:,9);
DVM = file1(:,10);

PIN1 = calibrated_data(PIN1,2);
PIN2 = calibrated_data(PIN2,2);
PIN3 = calibrated_data(PIN3,2);
PIN4 = calibrated_data(PIN4,2);
PIN5 = calibrated_data(PIN5,2);
PIN6 = calibrated_data(PIN6,2);
PIN7 = PIN7.*0;
PIN8 = calibrated_data(PIN8,2);

files = {PIN1,PIN2,PIN3,PIN4,PIN5,PIN6,PIN7,PIN8};
titles = ["PIN1","PIN2","PIN3","PIN4","PIN5","PIN6","PIN7","PIN8"];
pin_diff = [];
figure('Units','normalized','Position',[0,0,0.6,1])
t = tiledlayout(6,2,'TileSpacing','Compact','Padding','Compact');
for i = 1:1:6
    nexttile
    data = cell2mat(files(i));
    minimum = min(data);
    maximum = max(data);
    average = mean(data);
    sigma_rel = std(data);
    plot(time,data)
    ax=gca;
    ax.FontSize = tickSize;
    ax.YAxis.Exponent = 0;
    grid on
    grid minor
    xlabel("Čas [hodina]","FontSize",labelSize,"FontWeight","bold")
    ylabel("Napětí [V]","FontSize",labelSize,"FontWeight","bold")
    title_data = sprintf("- MIN:%0.5f, MAX:%0.5f, AWG:%0.5f, stdDev:%0.5f",minimum,maximum,average,sigma_rel);
    title(titles(i) + title_data,"FontSize",titleSize,"FontWeight","bold")

    nexttile
    histogram(data ,100)
    ax=gca;
    ax.FontSize = tickSize;
    ax.YAxis.Exponent = 0;
    grid on
    grid minor
    xlabel("Napětí [V]","FontSize",labelSize,"FontWeight","bold")
    ylabel("Četnost [-]","FontSize",labelSize,"FontWeight","bold")
    title_data = sprintf("- MIN:%0.5f, MAX:%0.5f, AWG:%0.5f, stdDev:%0.5f",minimum,maximum,average,sigma_rel);
    title(titles(i) + title_data,"FontSize",titleSize,"FontWeight","bold")

end
    sgtitle('Zkalibrovaný Časový průběh měřených napětí - přiblížení (vlevo), Distribuce napětí (vpravo)',"FontSize",25,"FontWeight","bold") 
  exportgraphics(gcf,"dlouhodoba_stabilita_calibrated_voltage_part1.eps")

%  figure('Units','normalized','Position',[0,0,0.6,0.4])
%  t = tiledlayout(2,2,'TileSpacing','Compact','Padding','Compact');
%   for i = 8:1:9
% 
%     nexttile
%     data = cell2mat(files(i));
%     minimum = min(data);
%     maximum = max(data);
%     average = mean(data);
%     sigma_rel = std(data);
%     plot(time,data)
%     ax=gca;
%     ax.FontSize = tickSize;
%     ax.YAxis.Exponent = 0;
%     grid on
%     grid minor
%     xlabel("Čas [hodina]","FontSize",labelSize,"FontWeight","bold")
%     ylabel("Napětí [V]","FontSize",labelSize,"FontWeight","bold")
%     title_data = sprintf("- MIN:%0.5f, MAX:%0.5f, AWG:%0.5f, stdDev:%0.5f",minimum,maximum,average,sigma_rel);
%     title(titles(i) + title_data,"FontSize",titleSize,"FontWeight","bold")
% 
%     nexttile
%     histogram(data ,100)
%     ax=gca;
%     ax.FontSize = tickSize;
%     ax.YAxis.Exponent = 0;
%     grid on
%     grid minor
%     xlabel("Napětí [V]","FontSize",labelSize,"FontWeight","bold")
%     ylabel("Četnost [-]","FontSize",labelSize,"FontWeight","bold")
%     title_data = sprintf("- MIN:%0.5f, MAX:%0.5f, AWG:%0.5f, stdDev:%0.5f",minimum,maximum,average,sigma_rel);
%     title(titles(i) + title_data,"FontSize",titleSize,"FontWeight","bold")
% 
% end
%     sgtitle('Zkalibrovaný Časový průběh měřených napětí - přiblížení (vlevo), Distribuce napětí (vpravo)',"FontSize",25,"FontWeight","bold") 
%   exportgraphics(gcf,"dlouhodoba_stabilita_calibrated_voltage_part2.eps")