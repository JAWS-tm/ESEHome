#frame = "BA1000000002EEEEEE00A2420508CAFEDECADA"
from data_communication.UartSerial import UartSerial

uart_reader = UartSerial("/dev/tty.usbmodem14203", 115200, 3.0)
uart_reader.read_uart_frames("\n")
    

    