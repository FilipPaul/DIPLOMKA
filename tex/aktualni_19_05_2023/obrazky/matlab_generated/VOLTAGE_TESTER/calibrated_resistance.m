clear all
close all
clc
format long g
%Hodnoty změřeneé referečním multimeterem
% file1 =  readmatrix("nejdelsi_mereni.txt");
file1 =  readmatrix("output_log_calibrated.txt");
calibrated_data = readmatrix("calibValues3.txt");
addvalue = 8;
tickSize = 15 + addvalue;
labelSize = 13 + addvalue;
titleSize = 14 + addvalue;
legendSize = 10 + addvalue;
ref_values = [0,16.4795,100.57,180.77,996.75,4673.19,0,0];
% voltage_reference = 3.355;
time = file1(:,1)/3600;
PIN1 = file1(:,2); %- 8;
PIN2 = file1(:,3)-3;
PIN3 = file1(:,4)-3;
PIN4 = file1(:,5)-3;
PIN5 = file1(:,6)-5;%-8;
PIN6 = file1(:,7)-3;%-8;
DVM = file1(:,10);
%measurement at PIN 7 does not make sense, becasuse is out of range (-1
%values)
PIN1 = calibrated_data(PIN1,2);
PIN2 = calibrated_data(PIN2,2);
PIN3 = calibrated_data(PIN3,2);
PIN4 = calibrated_data(PIN4,2);
PIN5 = calibrated_data(PIN5,2);
PIN6 = calibrated_data(PIN6,2);

R2 = [460,460.8,460.8,459.9,459.9,460.5,459.1,459.5,458.7];

files = {PIN1,PIN2,PIN3,PIN4,PIN5,PIN6};
titles = ["PIN1","PIN2","PIN3","PIN4","PIN5","PIN6","PIN7","PIN8"];
pin_diff = [];
figure('Units','normalized','Position',[0,0,0.6,1])
abs_chyba = zeros(1,6);
rel_chyba = zeros(1,6);
t = tiledlayout(6,2,'TileSpacing','Compact','Padding','Compact');
for i = 1:1:6
%     if i ~= 1
%         nexttile
%     end
    nexttile
%     subplot(4,2,2*i-1)
    data = cell2mat(files(i));
    measured_resistor = (PIN1.*R2(i))./data-R2(i);
    if i == 1
        measured_resistor = measured_resistor.*0;
    end
    minimum = min(measured_resistor);
    maximum = max(measured_resistor);
    average = mean(measured_resistor);
    pin_diff = [pin_diff, ref_values(i)-average];
    sigma_rel = std(measured_resistor);
    plot(time,measured_resistor)
    ax=gca;
    ax.FontSize = tickSize;
    ax.YAxis.Exponent = 0;
    grid on
    grid minor
    xlabel("Čas [hodina]","FontSize",labelSize,"FontWeight","bold")
    ylabel("Odpor [\Omega]","FontSize",labelSize,"FontWeight","bold")
    title_data = sprintf("- Reálná hodnota: %0.3fOhm",ref_values(i));
    title(titles(i) + title_data,"FontSize",titleSize,"FontWeight","bold")

    nexttile
%     subplot(4,2,2*i)
    histogram(measured_resistor ,100)
    ax=gca;
    ax.FontSize = tickSize;
    ax.YAxis.Exponent = 0;
    grid on
    grid minor
    xlabel("Odpor [\Omega]","FontSize",labelSize,"FontWeight","bold")
    ylabel("Četnost [-]","FontSize",labelSize,"FontWeight","bold")
    title_data = sprintf("- MIN:%0.5f, MAX:%0.5f, AWG:%0.5f, stdDev:%0.5f",minimum,maximum,average,sigma_rel);
    title(titles(i) + title_data,"FontSize",titleSize,"FontWeight","bold")

    abs_chyba(i) = abs(average - ref_values(i));
    rel_chyba(i) = abs(average - ref_values(i))/ref_values(i)*100;
end

    sgtitle('Zkalibrovaný Časový průběh měřených odporů - přiblížení (vlevo), Distribuce odporů (vpravo)',"FontSize",25,"FontWeight","bold") 
    exportgraphics(gcf,"calib_resistor_part1.eps")
%     saveas(gcf,"calib_resistor_part1","epsc")
