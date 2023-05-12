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

time = file1(:,1)/3600;
PIN1 = file1(:,2);
PIN2 = file1(:,3);
PIN3 = file1(:,4);
PIN4 = file1(:,5);
PIN5 = file1(:,6);
PIN6 = file1(:,7);
PIN7 = file1(:,8);
PIN8 = file1(:,9);

files = {PIN1,PIN2,PIN3,PIN4,PIN5,PIN6,PIN7,PIN8};
titles = ["PIN1","PIN2","PIN3","PIN4","PIN5","PIN6","PIN7","PIN8"];
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
    sgtitle('Časový průběh měřených napětí - přiblížení (vlevo), Distribuce napětí (vpravo)',"FontSize",25,"FontWeight","bold") 
  exportgraphics(gcf,"dlouhodoba_stabilita_voltage_part1.eps")

 figure('Units','normalized','Position',[0,0,0.6,0.4])
 t = tiledlayout(2,2,'TileSpacing','Compact','Padding','Compact');
  for i = 7:1:8
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
    sgtitle('Časový průběh měřených napětí - přiblížení (vlevo), Distribuce napětí (vpravo)',"FontSize",25,"FontWeight","bold") 
  exportgraphics(gcf,"dlouhodoba_stabilita_voltage_part2.eps")