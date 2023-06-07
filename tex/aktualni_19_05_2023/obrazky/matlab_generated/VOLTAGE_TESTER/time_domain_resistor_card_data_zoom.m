clear all
close all
clc
%Hodnoty změřeneé referečním multimeterem
file1 =  readmatrix("nejdelsi_mereni.txt");
addvalue = 8;
tickSize = 15 + addvalue;
labelSize = 13 + addvalue;
titleSize = 14 + addvalue;
legendSize = 10 + addvalue;

ref_values = [0,16.4795,100.57,180.77,996.75,4673.19,0,0];
time = file1(:,1)/3600;
PIN1 = file1(:,2);
PIN2 = file1(:,3);
PIN3 = file1(:,4);
PIN4 = file1(:,5);
PIN5 = file1(:,6);
PIN6 = file1(:,7);
PIN7 = file1(:,8);
PIN8 = file1(:,9);

R2 = 470;

files = {PIN1,PIN2,PIN3,PIN4,PIN5,PIN6,PIN7,PIN8};
titles = ["PIN1","PIN2","PIN3","PIN4","PIN5","PIN6","PIN7","PIN8"];
pin_diff = [];
figure('Units','normalized','Position',[0,0,0.6,1])
t = tiledlayout(6,2,'TileSpacing','Compact','Padding','Compact');
abs_chyba = zeros(1,6);
rel_chyba = zeros(1,6);
for i = 1:1:6
    nexttile
    data = cell2mat(files(i));
    measured_resistor = (PIN1.*R2)./data-R2;
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
%     title_data = sprintf("- MIN:%0.5f, MAX:%0.5f, AWG:%0.5f, stdDev:%0.5f",minimum,maximum,average,sigma_rel);
    title_data = sprintf("- Reálná hodnota: %0.3fOhm,",ref_values(i));
    title(titles(i) + title_data,"FontSize",titleSize,"FontWeight","bold")

    nexttile
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
    sgtitle('Časový průběh měřených odporů - přiblížení (vlevo), Distribuce odporů (vpravo)',"FontSize",25,"FontWeight","bold") 
  exportgraphics(gcf,"dlouhodoba_stabilita_resistor_part1.eps")

abs_chyba
rel_chyba