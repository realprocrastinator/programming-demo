# passwordless ssh
https://help.dreamhost.com/hc/en-us/articles/216499537-How-to-configure-passwordless-login-in-Mac-OS-X-and-Linux

# genearate RSA key pairs on the local host
ssh-keygen -t rsa 
# add the publick key to the remote host
ssh-copy-id -i ~/.ssh/id_rsa.pub username@server.dreamhost.com 
