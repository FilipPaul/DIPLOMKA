clear all
close all
clc
addvalue = 8;
tickSize = 15 + addvalue;
labelSize = 13 + addvalue;
titleSize = 16 + addvalue;
legendSize = 10 + addvalue;
bit_values = linspace(0,4095,4096);
ref_voltage = 3.29994;
slope = ref_voltage/ 4095;
%Hodnoty změřeneé referečním multimeterem
% file1 =  readmatrix("output_log_calibrated.txt");
figure('Units','normalized','Position',[0,0,0.6,1])
t = tiledlayout(3,1,'TileSpacing','Compact','Padding','Compact');
nexttile
calibrated_data = readmatrix("calibValues3.txt");
plot(calibrated_data(:,2),"-r")
hold on
plot(bit_values,slope.*bit_values,"-b")
ax=gca;
ax.FontSize = tickSize;
ax.YAxis.Exponent = 0;
grid on
grid minor
xlabel("DOR registr převodníku (bit)","FontSize",labelSize,"FontWeight","bold")
ylabel("Napětí [V]","FontSize",labelSize,"FontWeight","bold")
title("Charakteristika D/A převodníku","FontSize",titleSize,"FontWeight","bold")
legend(["Zkalibrovaná hodnota", "Hodnota odvozená od referenčního napětí"],"Location","northwest")
grid on
grid minor

nexttile

plot(calibrated_data(:,2),"-r")
hold on
plot(bit_values,slope.*bit_values,"-b")
ax=gca;
ax.FontSize = tickSize;
ax.YAxis.Exponent = 0;
xlim([4020,4100])
ylim([3.23,3.305])
grid on
grid minor
xlabel("DOR registr převodníku (bit)","FontSize",labelSize,"FontWeight","bold")
ylabel("Napětí [V]","FontSize",labelSize,"FontWeight","bold")
title("Charakteristika D/A převodníku - zoom","FontSize",titleSize,"FontWeight","bold")
grid on
grid minor
legend(["Zkalibrovaná hodnota", "Hodnota odvozená od referenčního napětí"],"Location","northwest")

nexttile

plot((calibrated_data(:,2) - transpose(slope.*bit_values)).*1e3,"-r")
% hold on
% plot(bit_values,slope.*bit_values,"-b")
ax=gca;
ax.FontSize = tickSize;
ax.YAxis.Exponent = 0;
grid on
grid minor
xlabel("DOR registr převodníku (bit)","FontSize",labelSize,"FontWeight","bold")
ylabel("Chyba napětí [mV]","FontSize",labelSize,"FontWeight","bold")
title("Charakteristika D/A převodníku - Chyba měření napětí","FontSize",titleSize,"FontWeight","bold")
grid on
grid minor
% legend(["Zkalibrovaná hodnota", "Hodnota odvozená od referenčního napětí"],"Location","northwest")



exportgraphics(gcf,"calib_DAC.eps")
