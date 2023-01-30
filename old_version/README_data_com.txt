Ce dossier doit contenir tous les modules n\351cessaires \340 l'interpretation des trames arrivant depuis l'UART.
On peut \351galement y renseigner des informations utiles comme l'architecture des modules. 

Objet<-RF->StationDeBase(C)<-UART->StationDeBase(Python)<-localhost->BDD

UART --> Create FrameParser message --> Create specific object ? --> Create SQL query from object --> Send data to database