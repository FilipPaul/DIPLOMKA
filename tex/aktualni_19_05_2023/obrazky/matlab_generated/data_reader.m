clear all
close all
clc

file1 =  readmatrix("1pin_DAC_STEP_1.csv",'NumHeaderLines',3);
file2 =  readmatrix("1pin_DAC_STEP_5.csv",'NumHeaderLines',3);
file3 =  readmatrix("1pin_DAC_STEP_5_out_of_range.csv",'NumHeaderLines',3);
file4 =  readmatrix("ALL_PINS.csv",'NumHeaderLines',3);
file5 = readmatrix("out_of_range_fast.csv",'NumHeaderLines',3);
addvalue = 10;
tickSize = 15 + addvalue;
labelSize = 20 + addvalue;
titleSize = 30 + addvalue;
legendSize = 10 + addvalue;

files = {file1 , file2,file3,file4,file5};
titles = ["Měření jednoho pinu - DAC STEP 1","Měření jednoho pinu - DAC STEP 5",...
    "Měření mimo rozshat - DAC\_STEP 5","Měření všech pinů- DAC\_STEP\_1","Optimalizace měření mimo rozsah" ];

saveNames = ["pin_step1", "pin_step5", "pin_out_of_range","all_pins","pin_out_of_range_opt"];
for i = 1:1:5
    currentFile = cell2mat(files(i));
    time = currentFile(:,1).*1e3;
    channel1 = currentFile(:,2);
    channel2 = currentFile(:,3);
    channel3 = currentFile(:,4);
    
    figure('Units','normalized','Position',[0,0,0.7,0.5])
    plot(time,channel1, "-r")
    hold on
    plot(time,channel2, "-g")
    plot(time,channel3, "-b")

    ax=gca;
    ax.FontSize = tickSize;
    
    grid on
    grid minor
    title("Měření napětí","FontSize",titleSize,"FontWeight","bold")
    xlabel("čas [ms]","FontSize",labelSize,"FontWeight","bold")
    ylabel("Napětí [V]","FontSize",labelSize,"FontWeight","bold")
    legend(["DAC","D1 pin","bRC"],"Location","northwest","FontSize",legendSize,"FontWeight","bold")
    title(titles(i))

   saveas(gcf,saveNames(i),"epsc")
end



