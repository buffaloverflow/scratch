import subprocess

class Open(object):
    def __init__(self):
        self.whitelist = ["netstat",
                          "ufw",
                          "firewall-cmd",
                          "iptables",
                          "ls",
                          "cat",
                          "nc"
                          ]

    def run(self, inp):
        for i in self.whitelist:
            if i in inp:
                return(subprocess.check_output(inp.split()))
