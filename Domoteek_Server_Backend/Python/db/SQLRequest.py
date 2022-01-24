
# ----- MESSAGE -----
addMessageSQLQuery = "INSERT INTO message (destinataire, emetteur, type_message_id, parametre_id, message, date, permanent) VALUES (%s,%s,%s,%s,%s,%s,%s)"
getMessageSQLQuery = "SELECT * FROM message"
removeMessageSQLQuery = "DELETE FROM message WHERE id=%s"