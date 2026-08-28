1. we download the latest arch release from the arch wiki.

2. Get a installation media setup thingy, set it up on a usb.

3. Select arch from boot options, do memtest for safety first.

# optional pre startup

we can setup our keymap & fonts of our terminal

```localectl list-keymaps```, then ```loadkeys x```

Console fonts are locatedf in /usr/share/kbd/consolefonts/, and can be set with ```setfont x```

# Starting Up

First you should probably check if you have the correct boot via ```cat /sys/firmware/efi/fw_platform_size```, if it returns "No such file or directory",
you probably booted in with bios or something

Then lets ensure you have an internet connection either via ethernet or wifi.

Ethernet just go run ```ip addr list``` if u get an ip u got connection or just ```ping -c 5 8.8.8.8```

## Wifi

A lil bit more tricky, first run ```iwctl``` (internet wireless control utility), then go ```device list``` to see your active 
wifi drivers, select one for example wlan0.

Then go ```station wlan0 scan``` to scan for the active wifi connections, this wont actually show anything, we gotta go ```station wlan0 get-networks```
to enter then go  ```station wlan0 connectionName```, where then you enter your password and valla! You are conencted to wifi, you can do the steps above to check

## Optional SSH for installation

First setup a password FOR THE INSTALLER, not for the final result of our arch.```passwd```, then enter the password.

Then we can ssh into our setup via another terminal and connect to the pc.

using ```ssh root@ip_adress```

THIS SSH WILL ALSO CLOSE AFTER WE FINISH THE SETUP AND THE USB GOES DEAD

## Updating / checking system clock

```timedatectl``` Ensuring that our system clock is synced ```timedatectl status```
