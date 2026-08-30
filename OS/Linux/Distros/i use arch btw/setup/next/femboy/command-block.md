```
cat /sys/firmware/efi/fw_platform_size

lsblk

fdisk `disk`  
(
g
n 
n
n
p

t
4
23

w
)

cryptsetup luksFormat p4
cryptsetup open --type luks p4 lvm

pvcreate /dev/mapper/lvm
vgcreate volgroup0 /dev/mapper/lvm

lvcreate -L 30G volgroup0 -n lv_root
lvcreate -L 800G volgroup0 -n lv_home

modprobe dm_mod
vgscan
vgchange -ay

mkfs.fat -F32 p1
mkfs.ext4 p2
mkswap p3
mkfs.ext4 /dev/volgroup0/lv_root
mkfs.ext4 /dev/volgroup0/lv_home

mount /dev/volgroup0/lv_root /mnt

mkdir /mnt/boot
mount p2 /mnt/boot

mkdir /mnt/home
mount /dev/volgroup0/lv_home /mnt/home

swapon p3
```

pacman-key --init
pacman-key --populate archlinux
pacman -Sy archlinux-keyring

```
reflector --latest 5 --sort rate --save /etc/pacman.d/mirrorlist # could also do this from the arch website

pacstrap -K -i /mnt base intel-ucode linux-firmware vi

genfstab -U -p /mnt >> /mnt/etc/fstab

arch-chroot /mnt

echo `yourname` > /etc/hostname

passwd

useradd -m -g users -G wheel username

visudo

passwd username

pacman -S base-devel dosfstools grub efibootmgr lvm2 mtools nano networkmanager os-prober sudo openssh git man-db man-pages

pacman -S pipewire pipewire-pulse pipewire-jack wireplumber

systemctl enable sshd

pacman -S linux linux-headers linux-lts linux-lts-headers

pacman -S nvidia-open nvidia-utils reflector

nano /etc/mkinitcpio.conf

mkinitcpio -p linux
mkinitcpio -p linux-lts

ln -sf /usr/share/zoneinfo/Area/Location /etc/localtime
hwclock --systohc

nano /etc/locale.gen 
locale-gen

echo "rd.luks.name=$(blkid -s UUID -o value path_to_rootpartiton)=lvm"
nano /etc/default/grub #*add the thing above to CMDLINE_LINUX root=path_to_root

mkdir /boot/EFI
mountp p1 /boot/EFI

grub-install target=x86_64-efi --bootloader-id=grub_uefi --recheck
cp /usr/share/locale/en\@quot/LC_MESSAGES/grub.mo /boot/grub/locale/en.mo
grub-mkconfig -o /boot/grub/grub.cfg

systemctl enable NetworkManager

exit
umount -a
reboot
```

```
nmcli device wifi connect name

pacman -S bluez bluez-utils bluez-deprecated-tools
modinfo btusb

systemctl start bluetooth.service
```

```
sudo pacman -S --needed git base-devel && git clone https://aur.archlinux.org/yay.git && cd yay && makepkg -si

pacman -S hyprland kitty waybar hyprpaper firefox  rofi-hyperland dunst hyprshot xdg-desktop-portal-hyprland polkit-kde-agent qt5-wayland qt6-wayland

sudo pacman -S ttf-mononoki-nerd

fc-cache -fv

fc-list | grep -i mononoki

pacman -S lv
systemctl enable lv@tty2

pacman -S zen ghostty tmux

reboot

cd ~/.config/hypr

echo "{
      "workspace": {
        "library": [
          "/usr/share/hypr/stubs"
        ]
      }
    }"
> .luarc.json

nvim hyprland.lua (

/ programs

local terminal = "ghostty"
local menu = "rofi"
local browser = "zen"
local neovim = "nvim"
local appMenu = "rofi -show drun -show-icons"
local config = "root_to_hyprland_conf"

/ bind

local secondMod = mainMod .. " + shift "
local nvimWindowMod = "CTRl + w"

hl.bind(mainMod .. " + T", hl.dsp.exec_cmd(terminal))
hl.bind(mainMod .. " + B", hl.dsp.exec_cmd(browser))
hl.bind(mainMod .. " + N", hl.dsp.exec_cmd(neovim))
hl.bind(mainMod .. " + L", hl.dsp.exec_cmd("systemctl suspend")) 
hl.bind(mainMod .. " + Space", hl.dsp.exec_cmd(appMenu)) 
hl.bind(secondMod .. " + C", hl.dsp.exec_cmd(config)) 

hl.bind(secondMod .. "Q") -- exit command
hl.bind("ALT + F4") -- exit command
)

git clone https://github.com/lr-tech/rofi-themes-collection.git
cd rofi-themes-collection

mkdir -p ~/.local/share/rofi/themes/

cp themes/centered-simple-tokyonight.rasi ~/.local/share/rofi/themes/

rofi-theme-selector

command shift c (

/ -- Move

# copy paste and create 
hl.bind(nvimViewMod .. " + h") # etc etc

# configure something for movign windows aswell
hl.bind(secondMod .. " + T") # toggle split
hl.bind(secondMod .. " + F") ({mode = "maximized"}) # toggle fullscreen

/LOOK
# just mess around here a bit seutp whats best for you
)
```

```
sudo pacman -S brightnessctl playerctl
sudo pacman -S nwg-look qt6ct
sudo pacman -S bibata-cursor-theme

# pick a theme

nwg-look

command shift c(

/ hl.env

hl.env("QT_QPA_PLATFORMTHEME", "qt6ct")
)

reboot

qt6ct
```

```
cd .config/hypr

mkdir .config/waybar
cd .config/waybar

nvim config.jsonc (
:%s/sway/hyprland
# modules left should be hyprland/submap
)

mkdir syle.css # get the default from the repo, change fonts to "monoki Nerd font"

command shift c (
    /autostart

hl.exec_cmd("hyprctl setcursor Bibata-Classic-Ice 30") # replace cursor sizes after

"/usr/lib/polkit-kde-authentication-agent-1"

)
```
