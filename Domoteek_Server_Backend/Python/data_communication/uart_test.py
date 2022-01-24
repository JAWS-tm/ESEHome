#frame = "BA1000000002EEEEEE00A2420508CAFEDECADA"
from UartSerial import UartSerial

#uart_reader = UartSerial("/dev/tty.usbmodem14203", 115200, 3.0)
uart_reader = UartSerial("COM3", 115200, 3.0)
uart_reader.read_uart_frames("\n")
    

    