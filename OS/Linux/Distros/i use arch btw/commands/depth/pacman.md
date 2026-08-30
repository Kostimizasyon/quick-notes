# Pacman

Pacman is the package manager for archlinux distros. it fetches repos from official arch packages from mirrors

Firstly every few weeks we should probably update the repos that pacman can acess via ```pacman -Syy```.

```
-S stands for Synchronise
-y refresh the local package db
-y force the local package db cache update
```

Pacman synchronises with /etc/pacman.d/mirorlist, it will go through this list fron the top down.

## Installation & Deletion via Name

```pacman -S htop``` to install the htop package.
```pacman -R htop``` to remove the htop package.

## Installation & Deletion w/o explicit names

Search for the package in the internet then find its explicit name.

or

```pacman -Ss pygame```, then find the corresponding one.

## Finding and deleting orphans

```pacman -Qdt``` ( no need for sudo ), find all orphan packages.

```
-Q query
-d skip dependency checks
-t limit results to orphaned packages
```

## System upgrade via pacman

```pacman -Syu``` do it atleast every month

```
-u update every package that is updatable
```

## Updating mirrorlist (if installs takes too long)

Go to the arch website and generate a list.
