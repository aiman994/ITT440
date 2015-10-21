from socket import *
import sys
import os
import errno 
HOST=('localhost',1055)
status = ' '
s= socket(AF_INET,SOCK_DGRAM)
s.bind(HOST)

while True:
	try:
#		conn,address = s.recvfrom(1055) 
		status = s.connect(HOST)
		if status < 0:
			s
			print " error " ,os.strerror(errno.EFAULT), ": " , errno.EFAULT
			break
		elif status == 0:
			print " stat : ", status	
			print "Received: ", (conn , address)
			reply= raw_input("Reply : ")
			s.sendto(reply,address)
		else:
			print "May the force be with you"
	except error, (value,message): #try catch all exceptions
		e = (value,message)
		print ("Error : ", e) 
			
 	
s.close()
