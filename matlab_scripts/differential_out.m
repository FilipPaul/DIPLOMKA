close all
clear variables
clc

V_in = 3.3;
N_pins = 20;
R_NMOS = 0.2;
R_PMOS = 0.03;

R_path = 0:1:1e3;
RX = 0:20:1e3
RX = RX + R_NMOS ;

V_out = zeros(length(RX),length(R_path));
V_out_diff = zeros(length(RX),length(R_path)-1);
V_error_value = zeros(length(RX),length(R_path));
% V_dif_zero = (V_in-err_value).*RX(dRx)./( RX(dRx) -1 +R_PMOS )
for dRx = 1:length(RX)
    for dRpath = 1:length(R_path)
        err_value = V_in*R_PMOS./((RX(dRx)+ R_path(dRpath))/N_pins + R_PMOS);
        V_out(dRx,dRpath) = (V_in-err_value).*RX(dRx)./( RX(dRx) +R_path(dRpath)+R_PMOS );
        V_error_value(dRx,dRpath) = (err_value).*RX(dRx)./( RX(dRx) +R_path(dRpath));
%         disp("VOUT " + V_out(dRx,dRpath))
        if dRpath > 1   
            V_out_diff(dRx,dRpath-1) = abs(V_out(dRx,dRpath) - (V_in-err_value).*RX(dRx)./( RX(dRx) + 1 +R_path(dRpath)+R_PMOS ));
%             disp(V_out(dRx,dRpath-1) + " - " + V_out(dRx,dRpath))
%             disp("VDIFF " + V_out_diff(dRx,dRpath-1))
        else
            disp("BONDARY dRX: " + dRx + " dRpath: " + dRpath+ "\n")
        end
    end
end

[R_path2,RX2] = meshgrid(R_path(2:end),RX);
[R_path,RX] = meshgrid(R_path,RX);
figure(1)
subplot(3,1,1)
surf(R_path, RX,  V_out);
title("V_out")
xlabel("Rpath")
ylabel("Rx")
zlabel("V_out")
grid on
grid minor

subplot(3,1,2)
surf(R_path2, RX2, V_out_diff);
title("Vout")
xlabel("Rpath")
ylabel("Rx")
zlabel("$\partial V/\partial R_{path}$","Interpreter","latex")
view(90,0)
grid on
grid minor


subplot(3,1,3)
surf(R_path, RX, V_error_value);
title("Vout")
xlabel("Rpath")
ylabel("Rx")
zlabel("$\partial V/\partial R_{path}$","Interpreter","latex")
view(90,0)
grid on
grid minor
zlim([0,0.025])



(V_out(2,3) - V_out(2,4)) - V_out_diff(2,3)