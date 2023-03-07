close all
clear all
clc
V_in = 3.3;

N_pins = 10;
R_NMOS = 0;
R_PMOS = 1;

R_path = linspace(1,1e3,30);
RX = linspace(1,1e3,30);
RX = RX + R_NMOS ;
[R_path,RX] = meshgrid(R_path,RX);
V_out = V_in.*RX./(RX+R_path+R_PMOS);

figure(1)
subplot(3,2,1)
surf(R_path, RX, V_out);
title("Výstupní napětí ideálního  děliče: RX = 0 - 1 kOhm, Rpath = 0 - 1 kOhm, Vin = 3.3V")
xlabel("Rpath")
ylabel("Rx")
zlabel("V_out")
grid on
grid minor

subplot(3,2,2)
surf(R_path, RX, V_out);
title("Výstupní napětí ideálního děliče: pohled na YZ, RX = 0 - 1 kOhm, Rpath = 0 - 1 kOhm, Vin = 3.3V")
xlabel("Rpath")
ylabel("Rx")
zlabel("V_out")
grid on
grid minor
view(90,0)



err_value = V_in*R_PMOS./(RX/N_pins + R_PMOS);
V_out_err = (V_in - err_value).*RX./(RX+R_path);

subplot(3,2,3)
surf(R_path, RX, V_out_err);
title("Výstupní napětí děliče R^P_{Dson}= 0.02, R^N_{Dson} = 0.2: 80 pinů paralelne")
xlabel("Rpath")
ylabel("Rx")
zlabel("V_out")
grid on
grid minor


subplot(3,2,4)
surf(R_path, RX, V_out_err);
title("Výstupní napětí děliče R^P_{Dson}= 0.02, R^N_{Dson} = 0.2: 80 pinů paralelne")
xlabel("Rpath")
ylabel("Rx")
zlabel("V_out")
view(90,0)
grid on
grid minor



R_PMOS = 10;
err_value = V_in*R_PMOS./(RX/N_pins + R_PMOS);
V_out_err = (V_in - err_value).*RX./(RX+R_path);

subplot(3,2,5)
surf(R_path, RX, V_out_err);
title("Výstupní napětí děliče R^P_{Dson}= 0.02, R^N_{Dson} = 0.2: 80 pinů paralelne")
xlabel("Rpath")
ylabel("Rx")
zlabel("V_out")
grid on
grid minor


subplot(3,2,6)
surf(R_path, RX, V_out_err);
title("Výstupní napětí děliče R^P_{Dson}= 0.02, R^N_{Dson} = 0.2: 80 pinů paralelne")
xlabel("Rpath")
ylabel("Rx")
zlabel("V_out")
view(90,0)
grid on
grid minor