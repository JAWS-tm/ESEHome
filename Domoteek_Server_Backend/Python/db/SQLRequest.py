#Note : compléter les ... par les champs de la BDD après qu'elle ait été rentrée sur le serveur

# ----- MESSAGE -----
addMessageSQLQuery = "INSERT INTO message (object_id, message, permanent) VALUES (%s,%s,%s)"
getMessageSQLQuery = "SELECT * FROM message"
removeMessageSQLQuery = "DELETE FROM message WHERE id=%s"