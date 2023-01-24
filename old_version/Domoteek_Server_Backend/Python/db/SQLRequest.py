
# ----- MESSAGE -----
addMessageSQLQuery = "INSERT INTO message (destinataire, emetteur, type_message_id, parametre_id, message, date, permanent) VALUES (%s,%s,%s,%s,%s,%s,%s)"
getMessageSQLQuery = "SELECT * FROM `message` WHERE `emetteur`= 'EEEEEE00'"
removeMessageSQLQuery = "DELETE FROM message WHERE id=%s"
