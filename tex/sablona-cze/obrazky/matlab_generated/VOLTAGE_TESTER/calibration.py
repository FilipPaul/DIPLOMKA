import pyvisa
import time

#output_log = open("output_log.txt", "a"):
rm = pyvisa.ResourceManager()
DVM = rm.open_resource('TCPIP0::192.168.0.52::3001::SOCKET')

print(DVM)
DVM.read_termination = '\n'
DVM.write_termination = '\n'
print(DVM.query('*IDN?'))


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

with open('calibValues3XX.txt', 'w') as output_log:
    for i in range (4096):
        print(BOARD.query(f"80_IO_CARD SET DAC {i}"), end = ' ') 
        DVM_voltage = float(DVM.query('MEAS:VOlTage?'))
        print(DVM_voltage)
        output_log.write(f"{i},{DVM_voltage}\n")
        



#print(BOARD.query('80_IO_CARD SET SHIFT_REGISTER IO1TO40_OUTPUTS VALUE 549755813887'))
#print(BOARD.query('80_IO_CARD SET SHIFT_REGISTER IO41TO80_OUTPUTS VALUE 1099511627775'))
#print(BOARD.query('80_IO_CARD SET SHIFT_REGISTER IO1TO40_IMPEDANCES VALUE 1095216660479'))
#print(BOARD.query('80_IO_CARD SET SHIFT_REGISTER IO41TO80_IMPEDANCES VALUE 1099511627775'))
#print(BOARD.query('80_IO_CARD SET CONFIGURATION VOLTAGE_REFERENCE 4095'))
#print(BOARD.query('80_IO_CARD SET CONFIGURATION DAC_RAMP_STEP 1'))
#
#now = time.time()
#with open('output_log2.txt', 'a') as output_log:
#    try:
#        while True:
#            data = BOARD.query('80_IO_CARD MEASURE VOLTAGE ALL')
#            voltages = data.split(';')[1:9]
#            timestamp = time.time() - now
#            output_log.write(f"{timestamp},{','.join(voltages)}\n")
#            print(f"{timestamp},{','.join(voltages)}")
#            time.sleep(0.5)
#    except KeyboardInterrupt:
#        print('interrupted!')
#
rm.close()