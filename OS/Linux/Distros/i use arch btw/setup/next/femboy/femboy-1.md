# If you are a chad / femboy, you can manually install.

## First WE gotta partion our disk

Type in ```lsbkl``` view the disks in the computer, and target the accurate disk to partition.

Then, you gotta go ```fdisk path_to_disk```

Then we will partition our disk into 3:

*You can go ```p``` to view partition layout* 

EFI, Boot, Root

1. EFI:

first type in ```g``` to create a partition lablel, then go ```n``` to create a new partition, pick the default number

Then we need to pick where the line of memory starts, just accept default, then we choose where the memory
ends, essentially allocing memory. go ```+1G```, which means go untill you alloc 1GB. ( 1gb is kind of an overkill but it leaves a lot of headroom)

2. Boot

Same above, also 1GB

67. Swap

4* gigs as above

3. Root

Same above but just default to use the rest of the drive.

**There you go! You sucesfully partitioned your drive! go ```p``` to view your partitions** 

Next go ```w``` to confirm and exit the fdisk process.

> [!WARNING]
> THIS WILL WIPE YOUR DRIVE

## Formatting our Partitions

Make file system ```mkfs.<filesystem_type> [args] path_to_partition```, formats a partion writing the actual filesytem onto the partion.

#### Filesystem types

    1. btrfs => Copy-on-write (when modified, the file wont be overriden instead a new version is copied to a different location, really easy snapshots)
       Slightly slower than ext4, native snapshots, subvolumes, transparent compression. Can dynamically add&remove&shrink devices, extent based
       Checksums => FS hashes the data, and checks against it at every read so if a corruption happens it can know.

    2. ext4 => Journaling (the FS journals the changes, so if a corruption happens while writing it can just read that again) extent based => "N contigious block starting at adress X"
    instead of "file uses blocks 1,2,3,4..." (A LOT less expensive), no native snapshots or checksumming. Can grow online, shrinking requires unmount. Low CPU overhead.

    3. xfs => Journaling, great at larger files, great multithreaded write, can never shrink => servers

    4. f2fs => Flash Friendly File System designed around ssd behavior.Reduces write amplification which results in better endurance and performance on flash media
        less mature, used by mobile / android mostly, not really compatible with HDD's

    5. Fat => File Allocation Table -F32

1. Partion 1 (EFI)

Go ```lsblk``` to view your partitions, then go ```mkfs.fat -F32 path_to_partition1``` which will format the partition

2. Partion 2 (Boot)

    ```mkfs.ext4 path_to_partition2```

67. Swap

    ```mkswap path_to_partition```

3. Partion 3 LVM

### Encrypting and formatting the Root

luks = linux unified key setup

```cryptsetup luksFormat path_to_root```

> [!WARNING]
> NO WAY TO RESTORE PASSPHRASE DONT FORGET IT

To use our encrypted volume, we gotta go:

   ```cryptsetup open --type luks path_to_root new_name(lvm)```

   Opens a view to the encrypted partion at dev/mapper/new_name(lvm), anything that gets written here gets encrypted before hitting the disk

give passphrase then we open that volume, we can see where its open via ```ls -l /dev/mapper```

### LVMs

Logical Volume Managers => snapshots, and easy upgrading disks.
Kinda like virtual partioning, instead of fixed they are resizable.

We mark the decrypted view as a physical volume
```pvcreate /dev/mapper/lvm```

Then we create a volume group, which is a pool of data consisting of multiple physical volumes
```vgcreate volgroup0 /dev/mapper/lvm```

Then we split 30 and 800 gigs from that pool named lv_root and lv_home respectively
```lvcreate -L 30GB volgroup0 -n lv_root```
```lvcreate -L 800GB volgroup0 -n lv_home```
We actually dont wanna alloc %100 of our space, as LV's can grow only if vg has free space, which
allows us to create snapshots etc. It gives us really nice flexability for the future.

### Activating LVM's

Loads the device-mapper kernel module
```modprobe dm_mod```

Search for volume groups in the disk
```vgscan```

Activate all volume groups activate yes, makes the LV's available
```vg change -ay```

### Formatting Logical Volumes
Same formatting, just applied to LV's instead.
```mkfs.ext4 /dev/volgroup0/lv_root```
```mkfs.ext4 /dev/volgroup0/lv_home```

### Mounting the Logical Volumes

Mounting => Before mounting a filesystem (partion, lv, vg ,usb) is just raw formatted data sitting inside of a device it isnt connected to anything, you cant navigate through it.
            Mounting attaches that filesystem to a folder  ( called a mount point ), and from that moment, anything insdie that folder is that filesystem.

Now we mount our volgroup's root into mnt itself
```mount /dev/volgroup0/lv_root /mnt```

Now we wanna mount the boot partition
```mkdir /mnt/boot```
```mount path_to_partion2 /mnt/boot```

Now we mount our home
```mount /dev/volgroup0/lv_home /mnt/home```

```swapon patH_to_swap```
