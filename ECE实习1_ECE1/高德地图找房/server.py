# server.py
from http.server import HTTPServer, CGIHTTPRequestHandler
PORT = 8080		# can be edited
httpd = HTTPServer(("", PORT), CGIHTTPRequestHandler)
print("Service start at port: ", PORT)
httpd.serve_forever()