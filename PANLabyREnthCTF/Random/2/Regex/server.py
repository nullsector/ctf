import SocketServer
import re

FLAG = open('passwords.txt', 'r').read().strip()
r = re.compile(open('omglob_what_is_dis_crap.txt', 'r').read().strip())


class DoAThing(SocketServer.StreamRequestHandler):
    def handle(self):
        self.request.sendall("Enter your key:\n")
        msg = self.rfile.readline().strip()

        if not r.match(msg):
            self.request.sendall("Correct key. Here's all the passwords: %s\n" % FLAG)
        else:
            self.request.sendall("Failure...\n")


class ServInThePaint(SocketServer.ThreadingMixIn, SocketServer.TCPServer):
    pass

if __name__ == "__main__":
    addy = ("", 8003)
    server = ServInThePaint(addy, DoAThing)
    server.allow_reuse_address = True
    server.serve_forever()
