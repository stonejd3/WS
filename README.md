# WS

NODE_backup.ino is the current program installed on nodes.

BASE_backup.cpp runs on the base. main.py also must run on the base to synchronize with the web server.  To simplify things, the program can be run on rPi by the complementary bash script  (run as ./main.sh)

REPEATER_backup runs on the repeater module. 

NOTE: For compiling RF24 for raspberry pi, use make sure the driver is installed.  Programs must be added to the makefile to ensure that the correct driver is linked with the program.  Simply using the gcc compiler will not work, since the rPi uses an ARM compiler for its processor.
