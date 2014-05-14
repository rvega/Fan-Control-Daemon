Fan-Control-Daemon
====================

Introduction
---------------------
This is an enhanced version of [Allan McRae mbpfan](http://allanmcrae.com/2010/05/simple-macbook-pro-fan-daemon/)

Fan-Control-Daemon is a daemon that uses input from coretemp module and sets the fan speed using the applesmc module. 
This enhanced version assumes any number of processors and fans (max. 10).

*  It only uses the temperatures from the processors as input.
*  It requires coretemp and applesmc kernel modules to be loaded.
*  It requires root use
*  It daemonizes or stays in foreground
*  Verbose mode for both syslog and stdout
*  Users can configure it using the file /etc/mbpfan.conf


Supported GNU/Linux Distributions
---------------------------------
We provide scripts to to load mbpfan daemon at system boot for many distros.
Please note that the support is provided by volunteers. mbpfan needs tests and bug reports.

Supported distributions:

- Ubuntu
- Debian
- Archlinux
- Fedora
- RedHat
- CentOS
- Gentoo


Tested Macbook Models
---------------------
This section reports those models where mbpfan was tested successfully. It does not necessarily mean that the daemon does not work on non-listed models. 

- MacBook Pro 9,2 13"  (Intel i5/i7 - Linux 3.10)
- Macbook Pro 8,2 15"  (Intel i7 - Linux 3.6.2)
- MacBook Pro 8,1 13"  (Intel i7 - Linux 3.2.0)
- Macbook Pro 6,2 15"  (Intel i7 - Linux 3.5.0)
- MacBook Pro 6,2 15"  (Intel i7 - Linux 3.2.0)
- MacBook Pro 2,2 15"  (Intel Core 2 Duo - Linux 3.4.4)
- Macbook Air 5,2 (unknown)


Warning
-------
Be sure to load the kernel modules **applesmc** and **coretemp**.


Arch Linux
---------
See [mbpfan-git at AUR](https://aur.archlinux.org/packages/mbpfan-git/).
Otherwise, please refer to the Generic Instructions.


Ubuntu
------

Install the ```build-essential``` package.
Then, refer to the Generic Install Instructions.


Generic Install Instructions
-------------------------
Compile with

    make

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
**Ubuntu**
For upstart based init systems (Ubuntu), an example upstart job has been
provided for use in place of the LSB-style init script. 
To use, execute:

    sudo cp mbpfan.upstart /etc/init/mbpfan.conf
    sudo start mbpfan

**Debian**
An init file suitable for /lib/lsb/init-functions (Debian) 
is located in the main folder of the source files, called mbpfan.init.debian
Rename it to mbpfan, give it execution permissions (chmod +x mbpfan)
and move it to /etc/init.d
Then, add it to the default runlevels with (as root):

    sudo update-rc.d mbpfan defaults

**Redhat, CentOS, Fedora**
An init file suitable for /etc/rc.d/init.d/functions
(RHEL/CentOS & Fedora) is also located at the same place, this file is called
mbpfan.init.redhat. Also rename it to mbpfan, give it execution permissions
and move it to /etc/init.d
To add the script to the default runlevels, run the following as root:

    chkconfig --level 2345 mbpfan on && chkconfig --level 016 mbpfan off

**Gentoo**
An init file is available for gentoo users: mbpfan.init.gentoo
To install, run as root:

    cp mbpfan.init.gentoo /etc/init.d/mbpfan

To automatically run mbpfan at boot, run as root:

    rc-update add mbpfan default


**systemd**
As a special bonus, a service file for systemd is also included. To use it,
execute the following (as root):

    sudo cp mbpfan.service /usr/lib/systemd/system
    sudo ln -s /usr/lib/systemd/system/mbpfan.service /etc/systemd/system/mbpfan.service
    sudo systemctl daemon-reload
    sudo systemctl start mbpfan.service

To start the service automatically at boot, also execute the following:

    sudo systemctl enable mbpfan.service


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
