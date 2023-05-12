clear all
close all
clc
%Hodnoty změřeneé referečním multimeterem
file1 =  readmatrix("mereni_2_hod.txt");
addvalue = 3;
tickSize = 15 + addvalue;
labelSize = 13 + addvalue;
titleSize = 14 + addvalue;
legendSize = 10 + addvalue;

time = file1(:,1);
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
for i = 1:1:8
    subplot(4,2,i)
    data = cell2mat(files(i));
    minimum = min(data);
    maximum = max(data);
    average = mean(data);
    sigma_rel = std(data);
    histogram(data ,100)
    ax=gca;
    ax.FontSize = tickSize;
    grid on
    grid minor
    xlabel("Napětí [V]","FontSize",labelSize,"FontWeight","bold")
    ylabel("Četnost [-]","FontSize",labelSize,"FontWeight","bold")
    title_data = sprintf("- MIN:%0.5f, MAX:%0.5f, AWG:%0.5f, stdDev:%0.5f",minimum,maximum,average,sigma_rel);
    title(titles(i) + title_data,"FontSize",titleSize,"FontWeight","bold")


end
    sgtitle('Distrubuce změřeného napětí pomocí ovládací karty',"FontSize",25,"FontWeight","bold") 
  saveas(gcf,"dlouhodoba_stabilita_histogram","epsc")



