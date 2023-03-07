close all
clear variables
clc
R_P_DSon = 0.02;
R_N_DSon = 0.2;
Vin = 3.3;
Rx = 0:1:800;
N_paralel_pins = 80;

R_out = Rx + R_N_DSon;
Rpath = 0:1:800;

V_out = zeros(length(R_out),1);

fault_flag = 1;
fault_precision = 1;
list_of_RPass = [];
list_of_RPass_precision = [];
for y = 1:1:length(R_out)
    if fault_flag == 0
        list_of_RPass = [list_of_RPass R_out(y-1)];
    end
    if fault_precision == 0
        list_of_RPass_precision = [list_of_RPass_precision R_out(y-1)];
    end
    fault_flag = 0;
    fault_precision = 0;
    for x = 1:1:length(Rpath)
        V_out(x) = (R_out(y)*Vin)/(Rpath(x)+R_out(y)+R_P_DSon);
%       
        if x > 1
            if (abs(V_out(x) - V_out(x-1)) < (3.3/(2^12)))
                fault_flag = 1;
%                 disp(abs(V_out(x) - V_out(x-1)))
            end
%             else
%               disp("Rpath :" + Rpath(x)+ " Rout: " + R_out(y) +  " PASS, Vdif = " + abs(V_out(y) - V_out(y-1)) )
            if abs(V_out(x) - V_out(x-1)) < ( R_P_DSon * V_out(x)/(R_out(y)/N_paralel_pins + Rpath(x))  )
                fault_precision = 1;
            end
           
        end
    end
end

list_of_RPass
list_of_RPass_precision