# Comment reprendre le projet
 
 Pour chaque dossier, il y a un document txt qui explique chaque document en python (fonctions, ...)
 Vous trouverez ici toutes les informations nécessaires à la bonne installation du projet

## Lancement application
### Version de l'interpréteur Python

Avant de commencer, assurez vous d'avoir installer l'interpréteur Python en **version 3.10** minimum

### Création environement virtuel, dans le dossier Domoteek_Server_Backend/Python
Dans votre Powershell ou cmd:
```
cd /path/to/Domoteek_Server_Backend/Python
python -m venv env
```

### Activation env
Dans votre Powershell ou cmd:
```
unix : source env/bin/activate
windows : env/Scripts/activate
```

### Installation des packages, library...
Dans votre Powershell ou cmd:
```
pip install -r requirements.txt
```
Voici la liste des élements présent dans requirements.txt

*  **schedule version 1.1.0**
*  **mysql-connector-python version 8.0.31**
*  **pyserial version 3.5**
*  **cryptography version 39.0.0**
*  **asyncio version 3.4.3**