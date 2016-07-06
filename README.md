Communication UDP sous blender
==============================

Exemple de communication UDP bilatérale entre blender et l'extérieur, en python ou C, entre les port 21567 et 21568.
Blender doit démarrer en premier et il n'a pas besoin de connaitre l'IP de l'expéditeur.

Le programme sender.py envoie 3 doubles (pendant 10 secondes, toutes les 1/60 secondes) sur le port 21567.

udep_send.c est l'équivalent en C. 


Le script server dans blender reçoit ces données pour les imposer comme position du Cube.


