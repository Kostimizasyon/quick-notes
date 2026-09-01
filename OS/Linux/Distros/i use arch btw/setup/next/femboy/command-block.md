```
cat /sys/firmware/efi/fw_platform_size

lsblk

fdisk `disk`  
(
g
n EFI  
n 
n SWAP
n x86_64
p

w
)

cryptsetup luksFormat p4
cryptsetup open --type luks p4 lvm

pvcreate /dev/mapper/lvm
vgcreate vg0 /dev/mapper/lvm

lvcreate -L 30G vg0 -n lv_root
lvcreate -L 800G vg0 -n lv_home

modprobe dm_mod
vgscan
vgchange -ay

mkfs.fat -F32 p1
mkfs.ext4 p2
mkswap p3
mkfs.ext4 /dev/vg0/lv_root
mkfs.ext4 /dev/vg0/lv_home

mount /dev/vg0/lv_root /mnt

mkdir /mnt/boot
mount p2 /mnt/boot

mkdir /mnt/home
mount /dev/vg0/lv_home /mnt/home

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

passwd username

pacman -S base-devel dosfstools grub efibootmgr lvm2 mtools nano networkmanager os-prober sudo openssh git man-db man-pages

systemctl enable sshd

visudo

pacman -S pipewire pipewire-pulse pipewire-jack wireplumber pipewire-alsa

pacman -S linux linux-headers linux-lts linux-lts-headers

pacman -S nvidia-open nvidia-utils reflector

nano /etc/mkinitcpio.conf # find first uncommmented hooks, sd-encrypt lvm2 between block and file

mkinitcpio -p linux
mkinitcpio -p linux-lts

timedatectl set-timezone Europe/Istanbul
hwclock --systohc

nano /etc/locale.gen 
locale-gen

echo "rd.luks.name=$(blkid -s UUID -o value path_to_rootpartiton)=lvm"
nano /etc/default/grub #*add the thing above to CMDLINE_LINUX root=path_to_lv_root

mkdir /boot/EFI
mountp p1 /boot/EFI

grub-install target=x86_64-efi --bootloader-id=grub_uefi --recheck
cp /usr/share/locale/en\@quot/LC_MESSAGES/grub.mo /boot/grub/locale/en.mo
grub-mkconfig -o /boot/grub/grub.cfg

systemctl enable NetworkManager

pacman -S ly
systemctl enable ly@tty2

exit
umount -a

# you can unplug usb

reboot
```

ssh-keygen -R 192.168.1.116

```
nmcli device wifi connect "name" password "password"

sudo pacman -S vlc vlc-plugins-extra

sudo pacman -S bluez bluez-utils bluez-deprecated-tools blueman

modinfo btusb

sudo systemctl start bluetooth.service

# check lsblk --discard
sudo systemctl enable --now fstrim.timer

timedatectl set-ntp true
```

```
sudo pacman -S flatpak

sudo flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo

# sudo pacman -S --needed git base-devel && git clone https://aur.archlinux.org/yay.git && cd yay && makepkg -si

sudo pacman -S hyprland kitty waybar hyprpaper firefox dunst hyprshot xdg-desktop-portal-hyprland polkit-kde-agent qt5-wayland qt6-wayland rofi

sudo pacman -S ttf-mononoki-nerd

fc-cache -fv

fc-list | grep -i mononoki

sudo pacman -S ghostty tmux fastfetch
yay -S zen-browser

sudo reboot

cd ~/.config/hypr

echo "{
      "workspace": {
        "library": [
          "/usr/share/hypr/stubs"
        ]
      }
    }"
> .luarc.json

sudo pacman -S ripgrep fd unzip gcc make

sudo pacman -S rust pnpm npm go nodejs python python-pip typescript

cargo install --locked tree-sitter-cli

# setup env variable via ~/.bashrc # export PATH=$PATH:path

sudo pacman -S nvim # clone from git aswell
# need to setup treesitter etc all the defaults for fuckin kickstarter

nvim hyprland.lua (

/ programs

local terminal = "ghostty"
local menu = "rofi"
local browser = "zen"
local neovim = "nvim"
local appMenu = "rofi -show drun -show-icons"
local runner  = "rofie -show run"
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

command shift c (

    /autostart

hl.exec_cmd("hyprctl setcursor Bibata-Classic-Ice 30") # replace cursor sizes after

"/usr/lib/polkit-kde-authentication-agent-1"

)
```

```

nvim .config/hypr/hyprpaper.conf (

wallpaper {
    monitor = DP-1
    path =  # find a wallpaper   
    fit_mode = cover  # can be fill cover tile 
    timout = 30       # time till image change
    order = random    # order of displaying images from dir
    recursive = false # whetehr or not to recursively search if given path is a dir
}


wallpaper {
    monitor = DP-2
    path = # find a wallpaper
    fit_mode = cover  # can be fill cover tile 
    timout = 30       # time till image change
    order = random    # order of displaying images from dir
    recursive = false # whetehr or not to recursively search if given path is a dir
}

)

cd .config/hypr

mkdir .config/waybar
cd .config/waybar

nvim config.jsonc (
:%s/sway/hyprland
# modules left should be hyprland/submap
)

mkdir syle.css # get the default from the repo, change fonts to "monoki Nerd font"

command shift c => add hyperpaper to auto boot

```

