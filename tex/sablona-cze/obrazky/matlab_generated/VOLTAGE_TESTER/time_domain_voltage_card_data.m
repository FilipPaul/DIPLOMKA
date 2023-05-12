clear all
close all
clc
%Hodnoty změřeneé referečním multimeterem
file1 =  readmatrix("nejdelsi_mereni.txt");
addvalue = 10;
tickSize = 15 + addvalue;
labelSize = 20 + addvalue;
titleSize = 30 + addvalue;
legendSize = 10 + addvalue;

files = {file1};
titles = ["Dlouhodobá stabilita měření"];
saveNames = ["dlouhodoba_stabilita_cas_prehled.eps"];
for i = 1:1:1
    currentFile = cell2mat(files(i));
    time = currentFile(:,1)/3600;
    PIN1 = currentFile(:,2); 
    PIN2 = currentFile(:,3);
    PIN3 = currentFile(:,4);
    PIN4 = currentFile(:,5);
    PIN5 = currentFile(:,6);
    PIN6 = currentFile(:,7);
    PIN7 = currentFile(:,8);
    PIN8 = currentFile(:,9);

    
    figure('Units','normalized','Position',[0,0,0.6,0.4])
    t = tiledlayout(1,1,'TileSpacing','Compact','Padding','Compact');
    plot(time,PIN1,"Color",[0.7 0.7 0])
    hold on
    plot(time,PIN2,'-r')
    plot(time,PIN3,'-b')
    plot(time,PIN4,'-g')
    plot(time,PIN5,'-k')
    plot(time,PIN6,"Color",[0.2 0.7 0.2])
    plot(time,PIN7,'-m')
    plot(time,PIN8,"Color",[0.5 0.2 1])

    ylim([-1.1,3.1])
    ax=gca;
    ax.FontSize = tickSize;
    
    grid on
    grid minor
    title("Měření napětí","FontSize",titleSize,"FontWeight","bold")
    xlabel("čas [hodina]","FontSize",labelSize,"FontWeight","bold")
    ylabel("Napětí [V]","FontSize",labelSize,"FontWeight","bold")
    legend(["PIN1","PIN2","PIN3","PIN4","PIN5","PIN6","PIN7","PIN8",],"Location","northeast","FontSize",legendSize,"FontWeight","bold")
    title(titles(i))

%    saveas(gcf,saveNames(i),"epsc")
 exportgraphics(gcf,saveNames(i))
end



