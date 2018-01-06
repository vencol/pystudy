import socket, SocketServer, time, traceback
class MyThreadingTCPServer(SocketServer.ThreadingTCPServer):
	def server_bind(self):
		self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)
		self.socket.bind(self.server_address)
		self.server_address = self.socket.getsockname()

class MyThreadingUDPServer(SocketServer.ThreadingUDPServer):
	def server_bind(self):
		self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)
		self.socket.bind(self.server_address)
		self.server_address = self.socket.getsockname()

class MySockServer(SocketServer.BaseRequestHandler):
	def setup(self):
		print 'new ok'

	def finish(self):
		print 'close' + str(self.client_address)
	
	def server_bind(self):
		self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)
		self.socket.bind(self.server_address)
		self.server_address = self.socket.getsockname()
				

	def handle(self):
		while True:
			print str(self.client_address) + time.strftime("%Y-%m-%d %H:%M:%S")
			data = self.request.recv(1024)
			if not data:break
			print 'receive: ' + str(data)
            		if data == '1':
                		self.request.send('welcome to server! hahaha')
				self.request.close()
				break
			elif data == 'c':
				traceback.print_exc()
			elif len(data) == 1:
                		self.request.send(data)
            		else:
                		self.request.send('hex:123\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10456 ip:%s at %s data [%s]\r\n' % ( str(self.client_address), time.strftime("%Y-%m-%d %H:%M:%S"), data))

if __name__ == '__main__':
	s = SocketServer.ThreadingTCPServer(('',3389),MySockServer)
	#us = MyThreadingUDPServer(('',3389),MySockServer)
	#s = MyThreadingTCPServer(('',3389),MySockServer)
	s.serve_forever()
	#us.serve_forever()
