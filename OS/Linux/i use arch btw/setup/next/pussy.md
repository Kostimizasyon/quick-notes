# If you are a pussy, you can just go archinstall

... go ```archinstall```. Youll get a GUI with steps on what to do like a fucking baby you goo goo gaga motherfucker.

## Language

Default depends on what you installed, you can change here.

## Locales

Setting up your keyboard locals and encodings

## Mirrors and Repos

Where arch gets its software from, select a region for your mirror.

## Disk Partioning

Here we get 3 options: 

1. Best Effort Layout
2. Manual
3. Saved

Just pick 1 you little fucking baby and select ur disk.

### filesystem

1. btrfs => copy on write ::: good for backups
2. ext4  => journaling, most reliable ::: best usage for general
3. xsf   => journaling, can only grow, never shrink really good multithreaded perf ::: used by servers mostly
4. f2fs  => less mature, SSD behaviour ::: used in embeded and phones etc (android uses it)

### seperate split for home 
Basically the windows user thing jsut do it

### Optional Disk Encryption

## Swap

Swap => Disk space used as overflow when RAM fills up. Pages of RAM that arent actively usedf get moved here, freeing up ram.

zram => creates a compressed block device in ram itself and uses that as swap rather than diskspace

Why zram?

Faster than disk, 2 to 3x compression, less disk writing ( better ssd lifetime )

## Bootloader

### Bootloader
The software responsible for loading the kernel + passing boot parameters. (GRUB etc)

### Unified Kernel Images

Normal boot = Seperate pieces : kernel, initramfs, cmdline params, bootlaoder config which are all stitched together at boot time

UKI = bunndles all of these info a .efi executable that UEFI can boot directly.

## Kernel

Select linux and lts for a backup

1. linux – Standard/mainline kernel, latest stable release. 

2. linux-lts – "Long Term Support" kernel. Older, but maintained longer with security patches. More stable/conservative.

3. linux-hardened – Security-focused fork with extra hardening patches (memory protections, restricted access to kernel info, etc.). Slight performance trade-off for better resistance against exploits. 

4. linux-zen – Tuned for desktop/responsiveness — different scheduler tweaks, aimed at lower latency. Community-maintained, less "vanilla" than mainline.

## Hostname

Profile name

## Authentication

Root Password
User Account

## Profile

Desktop, pick an enviroment, then graphic driver

Minimasilts => jsut a cmd and u go fam

Open kernel module for nvidia

## Application

Do what u need (pipewire)
Firefall ufw ( optional )

## Network Config

Network manager.

## Pacman

Leave as is

## Additional Packages

Do what u want jsut apps essentially

> then just press install.

Vala there you go pussy
