# Setting up mirrors

```less /etc/pacman.d/mirrorlist``` to view the list of mirrors
```reflector --help```

Only the mirror list gets carried over

# now that we actually partioned our disk and mounted our LVM's and Bios, we can install some packages

## In this step, we actually dont use pacman and we use pacstrap, which is designed for fresh unbooted systems, we use it here and never again

Installs base packages
```
pacstrap -K -i /mnt base intel-ucode linux-firmware # -i for interactive mode, it asks for confirmation to install packages 
```

Base, a package group for arch's installation:

- bash      :: just good old bash
- coreutils :: basic linux utils, (ls, cp, mv, cat etc.)
- glibc     :: C std lib
- systemd   :: init system, boots and manages services
- pacman    :: package manager
- file-system & filesystem :: standard dir structure /etc, /var, /usr
- gawk, grep, sed, gzip, tar etc :: core text/file utils
- iproute2  :: basic networking toosl
- licenses  :: license files for the packages
- vi

- intel-ucode:: microcode updates & drivers for intel cpu's
- linux-firmware :: hardware drivers for linux

## Next, we need the fstabfile for our system

A fstab file is basically indexes for our mounted drives for the kernel

We just use ```genfstab -U -p /mnt >> /mnt/etc/fstab```

We can see its usage via ```cat /mnt/etc/fstab```

## Now we can continue from the root to installation

```arch-chroot /mnt```

Now, we are logged into the root, so we should run ```passwd``` to create a root password.

Now, we need to create a sudo user, as using root is not great practice.
```

useradd -m -g users -G wheel user_name
-m => create a home dir for the new user == home/username
-g users=> primary group, users    (main identifier)
-G wheel=> secondary groups, wheel (additional group)

Wheel => unix standard for power users

```
```cat /etc/passwd``` to view the user, now we want a password for this account: ```passwd user_name```

## Now we need some more basic packages

```pacman -S base-devel dosfstools grub efibootmgr lvm2 mtools nano networkmanager os-prober sudo openssh git man-db man-pages```

- base-devel :: package group with compilers/build tools gcc, make etc
- dosfstools :: tools for FAT filesystems
- grub       :: bootloader
- os-prober  :: scans for other os (so grub can add it to its boot menu)
- efibootmgr :: tool to manage UEFI boot entries in NVRAM, (used by grub to reigster itself as aboot option)
- mtool      :: utils for accessing FAT fs without mounting them  (used by grub)
- lvm2       :: actual LVM tooling, also required inside the installed system, without it we cannot reboot
- nano       :: a little text edior, just use nvim ngl
- networkmanager :: handles wifi&ethernet connections provides nmcli&nmtui, needed for internet after reboot
- sudo       :: regular user commands
- openssh    :: SSH client + server
- git        :: you already know
- man-db     :: acess to linux manuals
- man-pages  :: acess to linux manuals
- reflactor  :: relfactor for mirror setups

( unsure if included or not )

```pacman -S pipewire pipewire-pulse pipewire-jack pipewire-alsa wireplumber```

- pipewire   :: core audio & video server
- pipewire-pulse :: pulse audio compatability layer
- pipewire-jack / pipewire-alsa  :: compatability shims for jack/alsa apps
- wireplumber:: session manager for pipewire

### Enabling Remote Management via OpenSHH

```systemctl enable sshd```

## Installing Kernels

Kernels

- Linux (mainline)
        Tracks the latest stable releases, best support.
- Linux Lts
        Long term support version, stable as fuck
- Linux Hardened
        Applies hardened patchset, extra kernel protection at the result of some performance head, and sometimes software incompatability
- Linux Zen
        Aimed for desktop responsiveness, different CPU scheduler behaviors more focused on like gaming and shit

We get linux + lts for a stable as fuck fallback
```pacman -S linux linux-headers linux-lts linux-lts-headers```

## Installing Graphics Drivers

```lspci``` to view PCI devices

*   **NVIDIA**
    *   Open Kernel: `sudo pacman -S nvidia-open nvidia-utils`
*   **AMD**
    *   Open-source: `sudo pacman -S mesa`
    *   Vulkan: `sudo pacman -S vulkan-radeon lib32-vulkan-radeon`
*   **Intel**
    *   Modern (Gen4+): `sudo pacman -S mesa vulkan-intel`
    *   Legacy DDX: `sudo pacman -S xf86-video-intel mesa`
*   **VM / Generic**
    *   VirtualBox: `sudo pacman -S virtualbox-guest-utils`
    *   VMware: `sudo pacman -S open-vm-tools`
    *   QEMU / KVM: `sudo pacman -S spice-vdagent xf86-video-qxl`

## Updating mkinitcpio.conf
Controls what goes into our initramfs, open /etc/mkinitcpio.conf in a text editor

Find first occurance of non commented hooks, between block and filesystems write ```sd-encrpyt, lvm2```

We add these so that the initramfs knows how to acess the root through our encryption aswell as being able to activate LVMs
They are executed in order so the initramfs knows to decrypt before trying to open a LVM

## Generating kernel ram disks (initramfs) (required for boot)

Run ```mkinitcpio -p linux``` and ```mkinitcpio -p linux-lts``` there ya go

-p = Preset

## Timezones

Study more

```
ln -sf /usr/share/zoneinfo/

ln -sf /usr/share/zoneinfo/Area/location /etc/localtime

hwclock --systohc
```

## Setting up locales

open /etc/locale.gen in a text editor. Then find your locale and uncomment it
then generate it via ```locale-gen```

Afterward, we set our system defualt in /etc/locale.conf

## Setting up Grub

Grub is a bootloader for our system

    ```echo "rd.luks.name=$(blkid -s UUID -o value path_to_rootpartiton)=lvm"```

Copy this info, we need it to upgrade the boot config file for grub

Open the file /etc/default/grub in a text editor

Then we find GRUB_CMDLINE_LINUX and paste in our value, then add ``` root=/dev/valgroup0/lv_root```

Now that we setup grub's config, we need a place for its files ```mkdir /boot/EFI```
```mount /dev/nvme0n1p1 /boot/EFI```

Now we will install grub itself, (required to be bootable)
```grub-install target=x86_64-efi --bootloader-id=grub_uefi --recheck```
```cp /usr/share/locale/en\@quot/LC_MESSAGES/grub.mo /boot/grub/locale/en.mo```
```grub-mkconfig -o /boot/grub/grub.cfg```

## A few things to enable to make sure it works
```systemctl enable NetworkManager```

## Now we actually are basically done

Go ```exit``` to go back to our iso root
Then go ```umount -a``` errors is fine
Remove usb
Then we go ```reboot```

There you go! You can now boot out!
