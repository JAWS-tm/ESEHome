## Main URC : Uart, Read, Cryptage

from Data_comm.UartController import UartController

class mainURC():
    '''Attributes'''

    '''Constructor'''
    def __init__(self, config):
        uart_read(config)


def init(dico, rLock):
    ## multi-processing
    print("init")


def uart_read(config):
    # Lancement thread de l'uart, qui va lire les infos en continue, tant qu'il est true(def uart_process_main_thread in UartSerial.py)
    uart_controller = UartController(config)

    uart = True
    while uart:

        ## On récupère le message recu par l'uart. Le chiffrement sera fait avant que le message soit dans la queue.
        ## Donc quand un message arrivera ici, on pourra directement l'envoyer vers la BDD 
        try:
            last_message = uart_controller.get_last_message()
            if (last_message != 0): # 
                print("reception du message dans le main.py : ",last_message)   
                ## A voir ensuite comment on envoie le message dans la BDD    
        
        except Exception as e :
            config.logger.error("ERROR : There was an error processing the incoming data. The message has been ignored")
            config.logger.error(str(e))
            uart = False