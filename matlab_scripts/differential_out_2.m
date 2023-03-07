% close all
clear all
clc

V_in = 3.3;
R_NMOS = 0.2;
R_PMOS = 0.03;

V_ref = 3.3;
R_path = 0:20:1e3;
RX = 0:10:1e3;
RX = RX + R_NMOS ;
[R_path,RX] = meshgrid(R_path,RX);
pass_fail_face = 0.7
pass_fail_color = [0.8,0,0]
V_diff_face = 0.7
V_diff_color = [0,0.8,0]
% dRx = [0.1,0.2,0.3,0.5,0.7,1]
dRx = [1,1,1,1,1,1]*2
% N_all_pins = [1,10,20,40,60,80]
N_all_pins = [1,1,1,1,1,1]*40
Rdson = [0.015 ,0.03,0.032, 0.035,0.05,0.06]
% Rdson = [1,1,1,1,1,1] * 0.025
fontsize = 15



% err_value = V_in*R_PMOS./((RX+ R_path)/N_pins + R_PMOS);
% V_out = (V_in-err_value).*RX./( RX +R_path+R_PMOS);
% 
% V_dif =  (V_in-err_value).*RX./( RX +R_path+R_PMOS) - (V_in-err_value).*RX./( RX +1 +R_path+R_PMOS) ;


V_out = V_in.*RX./( RX +R_path);



% 
% figure("Name","Analysis2","Units","centimeters","Position",[0,0,100,50])
% subplot(1,2,1)
% surf(R_path, RX,V_out);
% title("Vout f(Rpath,Rout) 3D view","FontSize",fontsize,"FontWeight","bold")
% xlabel("Rpath","FontSize",fontsize,"FontWeight","bold")
% ylabel("Rout","FontSize",fontsize,"FontWeight","bold")
% zlabel("V_out","FontSize",fontsize,"FontWeight","bold")
% grid on
% grid minor
% grid on
% grid minor
% subplot(1,2,2)
% surf(R_path, RX,V_out);
% view(90,0)
% title("Vout f(Rpath,Rout) XY view","FontSize",fontsize,"FontWeight","bold")
% xlabel("Rpath","FontSize",fontsize,"FontWeight","bold")
% ylabel("Rout","FontSize",fontsize,"FontWeight","bold")
% zlabel("V_out","FontSize",fontsize,"FontWeight","bold")
% grid on
% grid minor
% grid on
% grid minor



figure("Name","Analysis5","Units","normalized","Position",[0,0,0.5,1])
for i = 1:1:4
    dR = dRx(i)
    V_dif = V_in.*RX./( RX +R_path) - V_in.*RX./( RX +R_path +dR) ;
    N_pins = N_all_pins(i); 
    R_PMOS = Rdson(i)
    max_err_value = (V_in*R_PMOS./(RX/N_pins + R_PMOS) ).*RX./( RX +R_path) ; %Rpath = 0 ohm
    
    subplot(2,2,i)
    hold on;
    surf(R_path,RX, 20*log10(V_ref/2^11 + max_err_value).*RX./RX, 'FaceColor','r', 'FaceAlpha',0.7, 'EdgeColor','none')
    surf(R_path, RX,20*log10(V_dif), 'FaceColor', [0, 1,0.7], 'FaceAlpha',0.7, 'EdgeColor','none');
    
    title(sprintf("Npins = %2d, RDson = %0.3f Ohm, přesnost = %0.2f Ohm, Vref = 3.3V, Vin = 3.3V",...
        N_pins, R_PMOS, dR),...
        "FontSize",14,"FontWeight","bold")
    xlabel("Rpath","FontSize",fontsize,"FontWeight","bold")
    ylabel("Rout","FontSize",fontsize,"FontWeight","bold")
    zlabel("V_out","FontSize",fontsize,"FontWeight","bold")
    grid on
    grid minor
    view(90,90)

end

% saveas(gcf,"C:\Users\Filip\Desktop\diplomka\tex\sablona-cze\obrazky\PASS_FAIL_MERENI","epsc")
