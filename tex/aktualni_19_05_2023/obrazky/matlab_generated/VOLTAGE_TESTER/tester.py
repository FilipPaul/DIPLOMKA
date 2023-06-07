import pyvisa
import time

#output_log = open("output_log.txt", "a"):
rm = pyvisa.ResourceManager()
BOARD = rm.open_resource('TCPIP0::192.168.0.2::7::SOCKET')
print(BOARD)
BOARD.read_termination = '\n'
BOARD.write_termination = '\n'
print(BOARD.query('*IDN?'))
print(BOARD.query('80_IO_CARD SET SHIFT_REGISTER IO1TO40_OUTPUTS VALUE 549755813887'))
print(BOARD.query('80_IO_CARD SET SHIFT_REGISTER IO41TO80_OUTPUTS VALUE 1099511627775'))
print(BOARD.query('80_IO_CARD SET SHIFT_REGISTER IO1TO40_IMPEDANCES VALUE 1095216660479'))
print(BOARD.query('80_IO_CARD SET SHIFT_REGISTER IO41TO80_IMPEDANCES VALUE 1099511627775'))
print(BOARD.query('80_IO_CARD SET CONFIGURATION VOLTAGE_REFERENCE 4095'))
print(BOARD.query('80_IO_CARD SET CONFIGURATION DAC_RAMP_STEP 1'))
print(BOARD.query('80_IO_CARD SET CONFIGURATION VOLTAGE_READ_AVERAGES 2'))

DVM = rm.open_resource('TCPIP0::192.168.0.52::3001::SOCKET')

print(DVM)
DVM.read_termination = '\n'
DVM.write_termination = '\n'
print(DVM.query('*IDN?'))

now = time.time()
with open('output_log_calibratedXX.txt', 'w') as output_log:
    try:
        while True:
            PIN1 = BOARD.query('80_IO_CARD MEASURE VOLTAGE 0').split(':')[-1]
            PIN2 = BOARD.query('80_IO_CARD MEASURE VOLTAGE 1').split(':')[-1]
            PIN3 = BOARD.query('80_IO_CARD MEASURE VOLTAGE 2').split(':')[-1]
            PIN4 = BOARD.query('80_IO_CARD MEASURE VOLTAGE 3').split(':')[-1]
            PIN5 = BOARD.query('80_IO_CARD MEASURE VOLTAGE 4').split(':')[-1]
            PIN6 = BOARD.query('80_IO_CARD MEASURE VOLTAGE 5').split(':')[-1]
            PIN7 = BOARD.query('80_IO_CARD MEASURE VOLTAGE 6').split(':')[-1]
            print(PIN7)
            PIN8 = BOARD.query('80_IO_CARD MEASURE VOLTAGE 7').split(':')[-1]
            DVM_voltage = float(DVM.query('MEAS:VOlTage?'))

            timestamp = time.time() - now
            output_log.write(f"{timestamp},{PIN1},{PIN2},{PIN3},{PIN4},{PIN5},{PIN6},{PIN7},{PIN8},{DVM_voltage}\n")
            print(f"{timestamp},{PIN1},{PIN2},{PIN3},{PIN4},{PIN5},{PIN6},{PIN7},{PIN8},{DVM_voltage}\n")
            #time.sleep(0.5)
    except KeyboardInterrupt:
        print('interrupted!')

    rm.close()