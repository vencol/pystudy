from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer  
import io,shutil    
import urllib  
import os, sys  
  
class MyRequestHandler(BaseHTTPRequestHandler):  
    def do_GET(self):  
        mpath,margs=urllib.splitquery(self.path)   
        self.do_action(mpath, margs)  
  
    def do_POST(self):  
        mpath,margs=urllib.splitquery(self.path)  
        datas = self.rfile.read(int(self.headers['content-length']))  
        self.do_action(mpath, datas)  
  
    def do_action(self, path, args):  
            self.outputtxt(path + args )  
  
    def outputtxt(self, content):  
        enc = "UTF-8"  
        content = content.encode(enc)            
        f = io.BytesIO()  
        f.write(content)  
        f.seek(0)    
        self.send_response(200)    
        self.send_header("Content-type", "text/html; charset=%s" % enc)    
        self.send_header("Content-Length", str(len(content)))    
        self.end_headers()    
        shutil.copyfileobj(f,self.wfile)  

 
if __name__ == '__main__': 
	from BaseHTTPServer import HTTPServer  
	sever = HTTPServer(("",8002),MyRequestHandler)   
	#server = BaseHTTPServer.HTTPServer(('0.0.0.0',8103), MyRequestHandler)    
	sever.serve_forever()  
   # server = ThreadingHttpServer(('0.0.0.0',18460), WebRequestHandler)    
   # ip, port = server.server_address  
    # Start a thread with the server -- that thread will then start one  
    # more thread for each request  
    #server_thread = threading.Thread(target=server.serve_forever)  
    # Exit the server thread when the main thread terminates  
   # server_thread.setDaemon(True)  
    #server_thread.start()  
    #print "Server loop running in thread:", server_thread.getName()  
    #while True:  
    #    pass  
