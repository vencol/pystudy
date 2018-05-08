import SimpleHTTPServer  
import SocketServer  
import re  
import urllib 
import io,shutil 
  
def htc(m):  
    return chr(int(m.group(1),16))  
  
def urldecode(url):  
    rex=re.compile('%([0-9a-hA-H][0-9a-hA-H])',re.M)  
    return rex.sub(htc,url)  
  
class SETHandler(SimpleHTTPServer.SimpleHTTPRequestHandler):  
    def createHTML(self):  
        html = file("index.html", "r")  
        for line in html:  
            self.wfile.write(line)  
              
    def do_GET(self):  
        print "GET"  
        print self.headers;  
       # self.createHTML()  
#	mpath,margs=urllib.splitquery(self.path)   
        self.do_action("Get test ", "adsgas")  
          
    def do_POST(self):  
        print "POST"  
        print self.headers;  
        length = int(self.headers.getheader('content-length'))  
        qs = self.rfile.read(length)  
        url=urldecode(qs)  
        print "url="  
        print url  
        #self.createHTML() 
#	mpath,margs=urllib.splitquery(self.path)  
 #       datas = self.rfile.read(int(self.headers['content-length']))  
        self.do_action("Post test data: ", qs)   


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
          
Handler = SETHandler  
PORT = 8103  
httpd = SocketServer.TCPServer(("", PORT), Handler)  
print "serving at port", PORT  
httpd.serve_forever()  
