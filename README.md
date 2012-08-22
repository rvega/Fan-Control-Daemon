Fan-Control-Daemon
====================

Introduction
---------------------
This is an enhanced version of [rvega's Fan-Control-Daemon](https://github.com/rvega/Fan-Control-Daemon),
which itself is an enhanced version of [Allan McRae mbpfan](http://allanmcrae.com/2010/05/simple-macbook-pro-fan-daemon/)

Fan-Control-Daemon is a daemon that uses input from coretemp module and sets the fan speed using the applesmc module. 
This enhanced version assumes any number of processors and fans (max. 10).

*  It only uses the temperatures from the processors as input.
*  It requires coretemp and applesmc kernel modules to be loaded.
*  It requires root use
*  It daemonizes or stays in foreground
*  Verbose mode for both syslog and stdout
*  Users can configure it using the file /etc/mbpfan.conf


Compile Instructions
---------------------
Compile with
   make

Manually compile with
   gcc -o bin/mbpfan src/mbpfan.c -lm


Install Instructions
--------------------
Install with
   sudo make install

It copies mbpfan to /usr/sbin and mbpfan.conf to /etc


Run The Tests (Recommended)
---------------------------
It is recommended to run the tests after installing the program
	sudo ./bin/mbpfan -t
or
	sudo make tests


Run Instructions
----------------
If not installed, run with
sudo bin/mbpfan

If installed, manually run with
sudo mbpfan

If installed and using the init file, run with (Ubuntu example)
sudo service mbpfan start


Starting at boot
----------------
An init file suitable for /lib/lsb/init-functions (Debian & Ubuntu for sure)
is located in the main folder of the source files, called mbpfan.init.debian
Rename it to mbpfan, give it execution permissions (chmod +x mbpfan)
and move it to /etc/init.d
Then, add it to the default runlevels with sudo update-rc.d mbpfan defaults

Additionally, an init file suitable for /etc/rc.d/init.d/functions
(RHEL/CentOS & Fedora) is also located at the same place, this file is called
mbpfan.init.redhat. Also rename it to mbpfan, give it execution permissions
and move it to /etc/init.d
To add the script to the default runlevels, run the following as root:
chkconfig --level 2345 mbpfan on && chkconfig --level 016 mbpfan off

For upstart based init systems (Ubuntu), an example upstart job has been
provided for use in place of the LSB-style init script. To use, execute
as root:
cp mbpfan.upstart /etc/init/mbpfan.conf
start mbpfan
As a special bonus, a service file for systemd is also included. To use it,
execute the following as root:
cp mbpfan.service /usr/lib/systemd/system
ln -s /usr/lib/systemd/system/mbpfan.service /etc/systemd/system/mbpfan.service
systemctl daemon-reload
systemctl start mbpfan.service
To start the service automatically at boot, also execute the following:
systemctl enable mbpfan.service


Usage
-------
Usage: ./mbpfan OPTION(S)
-h Show the help screen
-f Run in foreground
-t Run the tests
-v Be (a lot) verbose


License
---------------------
GNU General Public License version 3


Based On
---------------------
* http://allanmcrae.com/2010/05/simple-macbook-pro-fan-daemon/
* http://allanmcrae.com/2011/08/mbp-fan-daemon-update/
* https://launchpad.net/macfanctld
* http://paste2.org/p/862259
* http://www.lobotomo.com/products/FanControl/
