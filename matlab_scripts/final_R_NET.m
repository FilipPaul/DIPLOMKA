close all
clear variables
clc

V_in = 3.3;
Vref_DAC = 3.3;
R2 = linspace(0,1e3 ,1001);
% R2 = 0:Vref_DAC/2^12:50;


%Vin-> --|R1| ---- |Rpath(R2)| ---- R3 -----
%                                ^Vout

R1 = 680; %R on input
R1_tolerance = 0.01; %in %
R3 = 220; %R on ouptut
R3_tolerance = 0.01;
%Vout = Vin*R1/(R1+R2+R3)
%Vin*R1=Vout(R1+R2+R3)-> R2 = (R1*Vin)/Vout-R1-R3

v_out = V_in.*R1./(R1+R2+R3);
v_out_tolerance_min_1 = V_in.*R1*(1+R1_tolerance)./(R1*(1+R1_tolerance)+R2+R3*(1+R3_tolerance));
v_out_tolerance_max_1 = V_in.*R1*(1-R1_tolerance)./(R1*(1-R1_tolerance)+R2+R3*(1-R3_tolerance));

R1_tolerance = 0.05;
R3_tolerance = 0.05;
v_out_tolerance_min = V_in.*R1*(1-R1_tolerance)./(R1*(1-R1_tolerance)+(R2+R3*(1+R3_tolerance)));
v_out_tolerance_max = V_in.*R1*(1+R1_tolerance)./(R1*(1+R1_tolerance)+R2+R3*(1-R3_tolerance));
%REAL VALUES:
V_out_graph = round(v_out(end)*2^12/Vref_DAC)*Vref_DAC/2^12:Vref_DAC/2^12:round(v_out(1)*2^12/Vref_DAC)*Vref_DAC/2^12;
R2_graph = (V_in.*R1)./V_out_graph-R1-R3;

figure(1)
plot(R2,v_out,"xb")
hold on
plot(R2,v_out_tolerance_min_1,":r")
plot(R2,v_out_tolerance_max_1,":r")
plot(R2,v_out_tolerance_min,":k")
plot(R2,v_out_tolerance_max,":k")
plot(R2_graph,V_out_graph,"xr")
grid on
grid minor
title("Toleranční analýza")
legend("0%","-1%","+1%","-5%","+5%","real_samples")
xlabel("R2: path resistance [\Omega]")
ylabel("Vout [V]")
min_val = 1000;


%% analysis for tolerances
min_val_tolerance_max = 10000;% some big number -> will be overwriten
min_val_tolerance_min = 10000;% some big number -> will be overwriten
for i = 1:length(R2)-1
    if(  (v_out_tolerance_max(i)-v_out_tolerance_max(i+1)) < min_val_tolerance_max)
        min_val_tolerance_max = v_out_tolerance_max(i)-v_out_tolerance_max(i+1);
    end
    if ( (min_val_tolerance_max) < (Vref_DAC/2^12) )
        disp("BREAKING tolerance_max")
        disp(i)
        break;
    end
end

for i = 1:length(R2)-1
    if(  (v_out(i)-v_out(i+1)) < min_val)
        min_val = v_out(i)-v_out(i+1);
    end
    if ( (min_val) < (Vref_DAC/2^12) )
        disp("BREAKING tolerance_zero")
        disp(i)
        break;
    end
end

for i = 1:length(R2)-1
    if(  (v_out_tolerance_min(i)-v_out_tolerance_min(i+1)) < min_val_tolerance_min)
        min_val_tolerance_min = v_out_tolerance_min(i)-v_out_tolerance_min(i+1);
    end
    if ( (min_val_tolerance_min) < (Vref_DAC/2^12) )
        disp("BREAKING tolerance_min")
        disp(i)
        break;
    end
end


figure(2)
plot(R2_graph,V_out_graph,"xr")
grid on
grid minor
title("Toleranční analýza")
ylabel("V_out_graph","Interpreter","none")
xlabel("R2_graph","Interpreter","none")

