Realtime bilateral UDP Communication in Blender Game, python and C
==================================================================


 Blender Game listens on port 21567  for 3 doubles then replies with 3 doubles upon receipt. 
 
 sender.py (or udp_send.c) sends 3 doubles then wait for an answer. 
 
 "listen" is unblocking in blender and "Wait" is blocking in python/C so both programs are synchronized.
 
 Blender Game has to start first and do not need to know in advance sender's IP:port. 


Communication UDP sous blender
==============================

Exemple de communication UDP bilatérale entre blender et l'extérieur, en python ou C, entre les port 21567 et 21568.
Blender doit démarrer en premier et il n'a pas besoin de connaitre l'IP de l'expéditeur.

Le programme sender.py envoie 3 doubles (pendant 10 secondes, toutes les 1/60 secondes) sur le port 21567.

udp_send.c est l'équivalent en C. 


Le script server dans blender reçoit ces données pour les imposer comme position du Cube.


