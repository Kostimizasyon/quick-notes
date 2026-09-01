# ricing waybar & hyprpaper

## Hyprpaper

Really fucking easy tbh
```
nvim .config/hypr/hyprpaper.conf (

wallpaper {
    monitor = DP-1
    path = ~/myFile.jxl
    fit_mode = cover  # can be fill cover tile 
    timout = 30       # time till image change
    order = random    # order of displaying images from dir
    recursive = false # whetehr or not to recursively search if given path is a dir
}

)
```

# firewall setup via uncomplicated firewall

```
sudo pacman -S ufw

sudo ufw status verbose# check ufw status
```

Setup our firewall first then enable it.

## Default policies

```
sudo ufw default deny incoming 
sudo ufw default allow outgoing
```

### Deny vs Reject

Reject -> informs connector that it has been rejected
Deny   -> Times out without warning

## Deny / Allowing stuff for everyone

```
sudo ufw allow ssh # enable for everyone

sudo ufw allow 80/tcp # enable acess for web server
```

## Deny / Allow for certain ips

```
sudo ufw allow from IP to any port 22 # only ssh to certain ip
```

## Removing Rules

```
sudo ufw status numbered

sudo ufw delete number
```

## Rate Limiting
```
sudo ufw limit ssh
```
