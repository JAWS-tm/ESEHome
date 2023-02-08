import Main
#This class is used to receivre a dictionary (containing the frame) from "Response" to write it inside the DataBase.
class Receive_write:
    #                       ------- INIT -------
    def __init__(self):
        self.nom = "----- Receive_write class -----"
        
    #                       ---------- Functions ----------

    def recieve_uart_tram():
        precedentDico = {}
        print(Main.tram_dico)

        while True:


            if(Main.tram_dico == precedentDico):
                # Le dictionnaire n'a pas été mis à jour, donc on ne fait rien
                print("dico pas changé")
            else:
                # le dico est différent, il a été mis à jour, on peut donc les envoyer dans la BDD
                print("dico changé")


    def write_uart_tram():
            

if __name__ == "__main__":
    write = Receive_write()
    write.recieve_uart_tram()



