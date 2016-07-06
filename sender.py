import socket
from struct import pack,unpack
import numpy as np
from time import sleep

temps = np.arange(0,601,1)
print(temps)
posX = 3 * np.sin(temps/60)
posY = 3 * np.cos(temps/60)
posZ = 1 * np.cos(temps/20)

# create the UDP socket for send
sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock.setblocking(1)
addr = ("127.0.0.1",21567)

#Socket à écouter
#sock2 = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock.bind(("", 21568))

for i in temps:
# Envoie
  data = pack('ddd',  posX[i], posY[i], posZ[i])
  sock.sendto(data, addr)
  
# Reception
  data_back, host=sock.recvfrom(24)
  pos = list(unpack('ddd',data_back))
  print("pos=",pos)
  
# sleep(1/60)
