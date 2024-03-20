
Set Up Required:
1. Need one Test machine 
2. Create a private n/w and connect device and test machine in private n/w
	Qualcomm 8295P IP :-    192.168.1.1 (subnet mask 255.255.255.0) (default GateWay 192.168.1.100)
	Test Machine IP :-      192.168.1.10
3. Connect to COM port from Test machine using Putty 
	(e.g COM6 baud rate 115200)
4. Connect One end of Aux cable (TRS) to the Laptop and other end to the MIC1 of target device.
5. Connect a speaker at Line 1 audio output port of the target device.

Build amsTest-ares app:

1. clone amsTest-ares application:
git clone https://github.com/Prashant-Jagtap-einfochips/amsTest-ares.git

2. Open Momentics IDE

3. Open Project:
	File -> Open Project from file system
	
4. right click on amsTest-ares project and select 
	Build Configurations -> set active -> aarch64le-debug
	
5. right click on amsTest-ares project and select 
	Clean project
	
6. right click on amsTest-ares project and select 
	Build project
	
7. Inside Build->aarch64le-debug directory "amsTest-ares" app executable is generated.

Signing Steps for share library:
1. Open Hexagon SDK 5.4.0.3
2. Go to <Hexagon SDK 5.4.0.3>/utils/scripts
3. Enter following command for signing:
	- signer.py sign -t <Device serialno> -d 4 -i <shared libray name> -o <output Directory name>
 	- signed library is generated in output directory. (Push this signed library to device at: /mnt/etc/images/dsp)

Verification of amsTest-ares Application:
1. Connect to COM port
2. reset device
3. Enter following commands
	- mq
	- mount -uw /mnt
4. Copy amsTest-ares application to /var/data directory
5. Provide executable permission to amsTest-ares (chmod 777 amsTest-ares)
6. Enter reset command
7. Run amsTest-ares exeutable 
8. Select Usecase
9. Create graph -> Open graph -> Start Graph 

Note: In case the test app does not work then remove both end of the Aux cable, Hard power cycle the target device and reconnect the cable.




