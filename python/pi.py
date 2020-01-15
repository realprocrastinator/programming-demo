#pi ip address 
https://www.raspberrypi.org/documentation/remote-access/ip-address.md

#ssh pi ethernet and power line connect to pi and share internet to pi thorugh mac
ssh pi@raspberry_local
username:pi
password:raspberry

#convert .mov to .mp4
ffmpeg -i input.mov output.mp4

#to auto run command on start up 
cd /etc/init.d


#camera command
raspistill -o cam.jpg #take static photo


#pi to control arduino
cp -avr nanpy-firmware/ ~/sketchbook/libraries/


#pi camera API
https://picamera.readthedocs.io/en/release-0.6/api.html
https://picamera.readthedocs.io/en/release-1.12/fov.html
#example of using pi camera with open cv
https://www.pyimagesearch.com/2015/03/30/accessing-the-raspberry-pi-camera-with-opencv-and-python/
#capture video with pi cameara
https://docs.opencv.org/3.1.0/dd/d43/tutorial_py_video_display.html
sudo modprobe bcm2835-v4l2 #enable the pi camear for video capture for cv2


#clone a image from the sd card
diskutil list #find which disk is the pi
sudo dd if=/dev/disk2 of=~/Desktop/raspberrypi.dmg

#restore a image to an empty sd card
diskutil list #find the empty sd card
diskutil unmountDisk /dev/disk2
sudo newfs_msdos -F 16 /dev/disk2 #formate the sd card
sudo dd if=~/Desktop/raspberrypi.dmg of=/dev/disk2 #restore a image to the sd card



#berry conda 
https://github.com/jjhelmus/berryconda



#virtualenvwrapper=========================================================
https://realpython.com/python-virtual-environments-a-primer/
https://www.bogotobogo.com/python/python_virtualenv_virtualenvwrapper.php

sudo pip install virtualenvwrapper
vi ~/.bashrc
export WORKON_HOME=~/Envs #setup the environment dir
source ~/.bashrc

mkdir -p $WORKON_HOME

#run the virutal wrapper script
source /usr/local/bin/virtualenvwrapper.sh
echo "source /usr/local/bin/virtualenvwrapper.sh" >> ~/.bashrc #add this the bash

#create an evn
mkvirtualenv env1

#show the current working dir
ls $WORKON_HOME




#check ram
htoo
free -h
dd -h
#==========================================================================================
#NFS access mac from pi
#set up the pi client NFS side
#https://www.aymerick.com/2013/09/20/nfs_client_on_raspberrypi.html
sudo apt-get install rpcbind
sudo update-rc.d rpcbind enable
sudo /etc/init.d/rpcbind start
sudo mount ip_of_nfs_host:/path/ofshareing /mnting/point/on_pi
showmount -e ip_of_nfs_host #to veryfy the fs has been mounted

#set up the mac NFS hosting side
#https://community.spiceworks.com/how_to/61136-how-to-create-an-nfs-share-on-mac-os-x-snow-leopard-and-mount-automatically-during-startup-from-another-mac
sudo nfsd enable #This starts the nfs server and sets it to startup on reboot.
sudo vim /etc/exports  #put the path of file wish to share on NFS e.g.:/Volumes/Macintosh HD -mapall=501
#mapall id could be found by command id
showmount -e #verify the mount



#share a folder from mac os through NFS
#https://knowledge.autodesk.com/search-result/caas/sfdcarticles/sfdcarticles/Enabling-network-NFS-shares-in-Mac-OS-X.html
#using samba to share a folder from mac with raspi
#https://www.raspberrypi.org/documentation/remote-access/samba.md



#==========================================================================================
#nettalk for mac to get access to raspi
#https://www.raspberrypi.org/forums/viewtopic.php?t=26826
sudo apt-get update
sudo apt-get install netatalk
sudo /etc/init.d/netatalk stop
sudo nano /etc/netatalk/AppleVolumes.default
#add in the path you wish to share
sudo /etc/init.d/netatalk start

#==========================================================================================
#my alias should be unique and it will forward the local host to this address
#http://serveo.net/
ssh -R myalias:22:localhost:22 serveo.net
#output:Forwarding HTTP traffic from https://xzho2604.serveo.net


#==========================================================================================
#pi configure wifi
sudo nano /etc/wpa_supplicant/wpa_supplicant.conf

network={
ssid="YOUR_NETWORK_NAME"
psk="YOUR_NETWORK_PASSWORD"
proto=RSN
key_mgmt=WPA-PSK
pairwise=CCMP
auth_alg=OPEN
id_str = "home"
}

network={
ssid="YOUR_NETWORK_NAME"
psk="YOUR_NETWORK_PASSWORD"
proto=RSN
key_mgmt=WPA-PSK
pairwise=CCMP
auth_alg=OPEN
id_str = "school"
}

#==========================================================================================





