if __name__ == '__main__':
    import socket,time
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
    sock.bind(('',3389))
    sock.listen(5)
    while True:
        connection,address = sock.accept()
        #buf = connection.recv(1024)
    	while True:
        	#connection,address = sock.accept()
        	try:
            	#connection.settimeout(5)
            		buf = connection.recv(1024)
	    		#if not buf: break
            		if buf == '1':
                		connection.send('welcome to server! hahaha')
            		else:
                		connection.send('please go out! %s' % (time.strftime("%Y-%m-%d %H:%M:%S")))
        	except socket.timeout:
            		print 'time out'
            	print ' run ip ' + address[0] +':' + str(address[1])
    connection.close()
