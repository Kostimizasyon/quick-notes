# post install stuff!

## You dont fucking have bluetooth

```
pacman -S bluez bluez-utils bluez-deprecated-tools

lsmod
# or 
modinfo btusb
# see if the bluetooth driver is loaded (if not modprobe it) then

systemctl start bluetooth.service
```

## Now, lets setup a desktop manager 

Choose what you want, i just like hyprland
```
pacman -S hyprland kitty waybar hyprpaper firefox
```

hyprland :: actual desktop manager
waybar   :: a navigation bar for hyprland
hyprpaper:: custimization / desktop setup for hyprland

kitty    :: a default terminal fallback for hyprland
firefox  :: defualt browser fallback for hyprland


## Now lets get a little bit more personal

Next, lets add some more special / personal preference stuff, such as our browser & terminal
```
pacman -S zen ghostty
```
