# post install stuff!

if you rebooted go ```nmcli device wifi connect name```

## You dont fucking have bluetooth

```
pacman -S bluez bluez-utils bluez-deprecated-tools

lsmod
# or 
modinfo btusb
# see if the bluetooth driver is loaded (if not modprobe it) then

systemctl start bluetooth.service
```

## Setting up a nerdfont

Install a nerd font then go:

```
fc-cache -fv # refresh cache

fc-list | grep -i fontname # check for that font
```

Then configure them in the apps for custimizaton like nwg-look and qt6cl

Then update usages for the terminals you use

## Now, lets setup a desktop manager 

Choose what you want, i just like hyprland
```
pacman -S hyprland kitty waybar hyprpaper firefox rofi-hyperland dunst hyprshot xdg-desktop-portal-hyprland polkit-kde-agetnt qt5-wayland qt6-wayland
```

hyprland :: actual desktop manager
waybar   :: a navigation bar for hyprland
hyprpaper:: custimization / desktop setup for hyprland
rofi     :: app launcher
dunst    :: notification daemon
hyprshot :: screenshots
xdg      :: screen sharing / file pickers
polkit   :: sudo privlages for apps / guis
qt5 & qt6:: support for qt built apps on wayland

kitty    :: a default terminal fallback for hyprland
firefox  :: defualt browser fallback for hyprland

```sudo pacman -S brightnessctl playerctl```

brightnessctl :: controlling brightness for wayland via keys
playerctl     :: controlling player for wayland via keys

Then let us create our default config file, copy paste the default from the github into ~/.config/hypr/hyprland.lua

then reboot hyperland

## Now lets get a little bit more personal

Next, lets add some more special / personal preference stuff, such as our browser & terminal
```
pacman -S zen ghostty tmux
```

### Modifying hyrpland

The docs are quite well made fyi

```hyperctl monitors all``` to view all display options.
Then go into hyperland.lua and 

```
hl.monitor({
output = "DP-1",
mode = "1920x1080@144",
position = "0x0"
scale = 1,

})
```

setup your monitors like this.

### Setting up keybinds

You should also create a new file called .luarc.json from the docs to setup lsp

Nvim into your config, then find programs to set your defaults aswell.

You can create new globals they are just names of the programs you want for example 
```lua
local browser = "zen"
local terminal = "ghostty"
local appMenu = "rofi -show drun -show-icons"
local commandMenu = "rofi -show run"
```

Now search for bindings, then set it up to your hearts content!

### Customizing rofi UI

get your themes!

```
git clone https://github.com/lr-tech/rofi-themes-collection.git
cd rofi-themes-collection

mkdir -p ~/.local/share/rofi/themes/

cp themes/<your-selected-theme> ~/.local/share/rofi/themes/
```

## Setting up Darkmode

```
pacman -S nwg-look qtct
```
nwg-look :: configuring themes for gtk apps
qt6ct    :: configuring theme for qt applications

For our GTK apps, we should be using a theme:

```
sudo pacman -S catpuccing-gtk-theme-mocha nordic-theme gruvbox-gtk-theme

nwg-look # select your theme
```

### Setting up defaults for QT

nvim into hyperland conf file

Find the enviroment variables
```lua
hl.env("QT_QPA_PLATFORMTHEME", "qt6ct")
```

then reboot then run ```qt6ct```

## Cursor Setup

```
yay -S bibata-cursor-theme

nvim conf
hl.exec_cmd("hyprctl setcursor Bibata-Classic-Ice 30") # replace cursor sizes after
```

## Waybar Setup

First we need to create a conf for it, lets use the defualt boring one off the repo for starting

```
cd .config/hypr

mkdir .config/waybar
cd .config/waybar

nvim config.jsonc (

:%s/sway/hyprland

modules left should be hyprland/submap

)
```
then paste in the config

Now we want sytles
```
mkdir syle.css # get the default from the repo

waybar # startit up
killall waybar # reboot
waybar
```

### Hyprland autocmds

```
nvim hyperland.lua

/auto

setup waybar also

"/usr/lib/polkit-kde-authentication-agent-1"
```
