				----- DB -----

	----- Document DbController -----
DbController.py : grâce au infos passée dans le constructeur il renvoie le dernier message dans la bdd ou stock un nouveau à la fin de cette dernière
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
GET_LAST_MESSAGE : renvoie à l'utilisaateur le dernier meessage stocker dans la queue  
PUT_MESSAGE_IN_BDD_SENDING_QUEUE : permet à l'utilisateur de stocker un message à la fin de la queue


	----- Document README_DB.txt -----
README_DB.txt : explique les différentes liaison de la BDD aux objets
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


	----- Document SQLRequest.py -----
SQLRequest.py : commandes SQL qui permettent d'interagir avec la BDD
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
addMessageSQLQuery : insert la trame d'un message à l'adresse selectionner
getMessageSQLQuery : selectiionne le message à l'adresse selectionner
removeMessageSQLQuery : supprime le message stocker à l'adresse selectionnée


	----- Document dbRequest.py -----
dbRequest.py : comprend toutes les commandes nécesaires pour interagir avec la BDD
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
sendData : stocke les information dans la BDD à la location du curseur
receiveData : récupère toutes les information en fonction de la position du curseur
getCursor : return la position du curseur
endConn : fin de connection, on ferme le curseur puis la connection
checkForNewMessage : si il y a un nouveau message, appel la fonction : "put_message_in_queue"
put_message_in_queue : place le message du paramètre dans la queue
get_next_message : return le dernier message
db_process_main_thread : verrifie toute les 15s si il y a un nouveau message, si il y en a un, envoie ce dernier à la BDD ou la stock dans la queue
