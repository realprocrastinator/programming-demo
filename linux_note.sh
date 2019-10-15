
#==================================================================
#Convert pic to different format
magick mogrify -monitor -format jpg *.HEIC #for batch processing
magick convert my.HEIC my.jpeg #convert signle pic



#=================================================================
#terminal
ctrl + shift + t #open up a new  terminal 
ctrl + T  #open a new tab
opt + left #swtich to previous tab
opt + right #switch the next tab
cmd + shift + left #move tab to the left
cmd + shift + right #move the tab to the right

#system control
alt + tab  #switch applications
ctrl + alt + d #close all app and show desktop
ctrl + alt + arrow #change work space
opt + w #close tab
ctrl + shift + w #close window
ctrl + Q #close the current window

ctrl +   #zoom in 
ctrl -   #zomm out
ctrl 0   #original size

cmd #the super key will show activities

#window control
ctrl + m #toggle max window

#=================================================================
#Fs
parted -l #view system's partition table
gparted #graphic interface of parted

mkfs -t ext4 /dev/sdf2 #create a ext4 partition on /dev/sdf2
mount -t ext4 /dev/sdf2 /home/extra #mount -t type device mountpoint
unmount mountpoint
#device name could change since the name depends on the order the kernel find them
#so could mount fs by their Universally Unique Identifier(UUID)
blkid #show the list of devices and the corresponding fs UUIDs
mount UUID="dfjd" /home/extra #perferred way when auto mount at boot time
#conv auto tells kernel to automatically covert certain text file from DOS newline to Unix style 
mount -t vfat /dev/hda1 /dos -o ro,conv=auto 

#mount filesystem at boot time at /etc/fstab
#1.UUID/device
#2.Mount Point
#3.Fs type
#4.Options
#5.Back up info should be always 1
#6. fs integrity test order:1 for root fs, 2 for anyother fs on a hard disk 
#0 to disable the bootup check for everything else
UUID="jdfjj" mountingpiont fstype options 0 0
UUID="fjdjf" / ext4 errors=remount -ro 0 1
/dev/sr0 /cdrom iso9660 ro,user,nosuid,noauto 0 0
#could mount short cut if device has been specified in the file
mount /cdrom
#mount all entries at onece that do not contains noauto option
mount -a
# options entry
errors=:the action to be done when there is error mounting
defaults:set all the entry as defaults
noauto:tell mount -a to ignore this mount
user: allows unpriviledge users to run mount
#to check the untilisation of the currently mounted fs
df
du #print out the disk usage of all dir start from the curr dir
du -s * #-s will print out the summary the grand total

#repaire fs
#will recognise the fs and start its utility accordingly
#should not run fsck on a mounted fs,exception: mount root fs read only in single user moe
fsck /dev/sdb1 #give either the device or mount point(as listed in /etc/fstab) as arg to fsck
fsck -p #automatically fixes ordinary problems without asking and abort when serious error
fsck -b num #replace the currupted superblock with a back up super block number
fsck -n #if there is serious error check the fs without modifying anyting
mkfs -n device #will tell you the back up super block number
fsck -y #answer yes to all the question

#kernel will not mount ext3 or 4 with an nonempty journal
#need to enter in ext2 mode to flush the journel in ext3 or 4 to the regular fs database
e2fsk -fy /dev/disk_device
debugfs device # look through the files on a fs and can copy them elsewhere by default is read only

#special fs
#size in bytes the upper limits of tmpfs or nr_blocks size of PAGE_CACHE_SIZE
#it can consume ram and swap space only as musch as is requried to the current content
#in the fs
#unmount will delete all the current data in the fs
sudo mount -t tmpfs -o size=10M tmpfs /mnt/mytmpfs

#show current swap space
free -h
#use a partition for swap space
#make sure partition is empty
mkswap dev #put a swap signiture on the partition
swapon dev #to register the space with the kernel
#can create a swap entry in /etc/fstab to enable swap upon boot up
/dev/sda5 none swap sw 0 0 

#dd example :https://www.linuxnix.com/what-you-should-know-about-linux-dd-command/
dd if=/dev/sda2 | bzip2 hdadisk.img.bz2 #if image is too big compress when creating image
dd if=/dev/zero of=/dev/sdb #wipe disk
dd if=/dev/random of=/dev/sdb #make data not recoverable write random data to the disk
for i in {1..10};do dd if=/dev/random of=/dev/sdb;done #do multiple times to make it really random
dd if=/dev/dvd of=/opt/my_linux_image.iso #create iso file form cd rom

#use a file as swap
#create an empty file , initialise it as swap and add it to the swap pool
#/dev/zero is a special file that provides as  many null as to read from it
#bs is the block size
dd if=/dev/zero of=swap_file bs=1024k count=num_mb
mkswap swap_file
swapon swap_file
swapoff #remove the swap from swap pool

#===================================================================================
#Device
Block Device:access data in blocks
Char Device:no size no storage ,read and write operation , e.g. printer

dmseg # print out the message by the device driver

#https://opensource.com/article/18/11/udev
udev: is a user/device management system supplies your computer with device events
#you can write udev script to do certain task when a udev event happens e.g. usb plugged in
udevadm monitor:the event udevs send out after rule processing the kernel uevent
udevadm monitor --kernel --subsystem-match=scsi #--udev to see the whole incomming uevent
#view udev info about the device
udevadm info -a -n /dev/sdb | less
# file called 80-local.rules in /etc/udev/rules.d
SUBSYSTEM=="block", ACTION=="add", RUN+="/usr/local/bin/trigger.sh"

#check scsi device
lsscsi
#check usb connected
lsusb








