from socket import *
import sys
import os
import errno 

hostt ='localhost'
port = htons(1055) #pitfall 4
HOST=(hostt,port)
s = socket(AF_INET,SOCK_DGRAM)
s.bind(HOST)
while True:
	try: 	
		#pitfall 2
#		conn,address = s.recvfrom(1055)
#		if len(conn)>0:	
#			 print "Received: \n", (conn , address)
#			 reply= raw_input("Reply : \n")
#			 s.sendto(reply,address)
#		elif len(conn) <=0:
#			eror = "ERROR: "+ str(errno.EBADMSG) + ":" + os.strerror(errno.EBADMSG)
#			s.sendto(eror,address)
###			print " ERROR " , errno.EBADMSG , " :  ", os.strerror(errno.EBADMSG)
#			s.close() // peer socket closure
#		else:
#			 print " watserong " 
#
		#pitfall 1
		byteread = s.getsockopt(SOL_SOCKET, SO_REUSEADDR )
		if byteread >0:
			print " function already set" , port, " " , s.getsockopt(SOL_SOCKET, SO_REUSEADDR) 
			break
		elif byteread < 0:
			print "ERROR  ", errno.ENODATA , " : " , os.strerror(errno.ENODATA)
			break
		else:
			print " first check " , port 
			s.setsockopt(SOL_SOCKET, SO_REUSEADDR , 7)
			#pitfall 3 , error in use
		# pitfall 5 ? noone
		
			
	except error, (value,message): #try catch all exceptions
		e = (value,message)
		print ("Error : ", e)
		break
		 
			
s.close()
