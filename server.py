from socket import *

 
HOST=''
PORT=1055
bufsize = ' '
afterset = ' '
state = ' ' 
timeoutb4 = ' '
timeoutafter =' '
s= socket(AF_INET,SOCK_STREAM)
s.bind((HOST,PORT))
s.listen(1)
conn,addr = s.accept()
print 'Connected by', addr
while True:
	data = conn.recv(1024)
	print "Received: ", repr(data) , "  " , bufsize
	reply= raw_input("Reply : ")
	conn.sendall(reply) 
	bufsize= s.getsockopt(SOL_SOCKET , SO_SNDBUF)
	timeoutb4 = s.gettimeout()
	state = s.getsockopt(SOL_SOCKET, SO_REUSEADDR )

	print " get sock buff send : " , bufsize
	print " get timeout  : " , timeoutb4
	afterset = s.setsockopt(SOL_SOCKET , SO_REUSEADDR ,1)
	timeoutafter = s.settimeout(5)
	print  " set time out : " , afterset

	
conn.close()
