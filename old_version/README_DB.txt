Ce dossier doit contenir tous les modules n\351cessaires \340 la communication entre la base de donn\351es et la station de base.
On peut \351galement y renseigner des informations utiles comme l'architecture des modules. 

Objet<-RF->StationDeBase(C)<-UART->StationDeBase(Python)<-localhost->BDD

# bdd.sendData("INSERT INTO pipo (data) VALUES (%s)", (test,))
# bdd.sendData("UPDATE pipo SET data=%s WHERE id=%s", (test,7))
# bdd.sendData("DELETE FROM pipo WHERE id=%s", (8,))

# bdd.recieveData("SELECT * FROM pipo")
# for (id, data) in bdd.getCursor():
#     print("ID : {}, Data : {}".format(id, data))