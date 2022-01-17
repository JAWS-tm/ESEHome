from config.app_config import logger
from data_communication.FrameParser import *
from BDD.BDDRequest import BDDRequest

def main():
    logger.debug("-------------------Starting application-------------------")
    bdd = BDDRequest()


    dummy_message = "BA1000000002EEEEEE00A2420508CAFEDECADA"#String
    #parsed_message = FrameParser()

main()


# bdd.sendData("INSERT INTO pipo (data) VALUES (%s)", (test,))
# bdd.sendData("UPDATE pipo SET data=%s WHERE id=%s", (test,7))
# bdd.sendData("DELETE FROM pipo WHERE id=%s", (8,))

# bdd.recieveData("SELECT * FROM pipo")
# for (id, data) in bdd.getCursor():
#     print("ID : {}, Data : {}".format(id, data))

