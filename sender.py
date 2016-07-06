import socket
from struct import pack,unpack
import numpy as np
from time import sleep

#Generate the data to send
temps = np.arange(0,601,1)
posX = 3 * np.sin(temps/60)
posY = 3 * np.cos(temps/60)
posZ = 1 * np.cos(temps/20)

# create the UDP socket
sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock.setblocking(1)

# Port to wait for the answer 21568
sock.bind(("", 21568))

# Blender IP,port
addr = ("127.0.0.1",21567)


for i in temps:
# Send
  data = pack('ddd',  posX[i], posY[i], posZ[i])
  sock.sendto(data, addr)
  
# Receive
  data_back, host=sock.recvfrom(24)
  pos = list(unpack('ddd',data_back))
  print("pos=",pos)
  
# sleep(1/60)
