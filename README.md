# Fun-with-fileio

Fun with file I/O, of course.

## Motivation

TL;DR - Need some C code to read three values from a disk file and write three new values back.

Shaggy dog version - A program that runs on a Raspberry Pi (Linux environment) reads stuff from a BME280 sensor and publishes using MQTT. Occasionally the values are wonky. Some times wildly different from what they should be. The program runs 1/minute and the values (temperature, humidity and pressure) won't change too much from one run to another. One strategy to deal with this is to compare values from a minute previous and if they differ too much, discard the readings and bail. It will be easier to develop and test outside the context of the original application.

## Plan

Write `C` functions to

* Open a file if it exists and read and transform three space separated values to floats.
* Write three new values back to the file and close it.

## Testing

Instructions for creating a loop filesystem for testing at <https://www.reddit.com/r/linuxquestions/comments/e8t1yk/create_loop_filesystem_without_root/
> (Something I asked years ago for similar reasons.)

```text
loopdev=$(losetup -f)                           # Identify next avilable loop device
image=fs1.img                                   # image filename
dd if=/dev/zero of=$image bs=1024 count=128    # Create file for FS
mke2fs -b 1024 $image -L test1                 # create fs
udisksctl loop-setup -f $image                 # create loop device backed by fs1.img
udisksctl mount -b $loopdev                     # Mount (should be /media/hbarta/test1)
sudo chmod a+rwx /media/hbarta/test1/           # make writable
dd if=/dev/zero of=/media/hbarta/test1/filler \
        bs=1024 count=99                        # fill that baby up. use count=97 for space

# do testing stuff
udisksctl unmount -b $loopdev                   # unmount
udisksctl loop-delete -b $loopdev               # unwind loop device
rm $image
```

TIL that `fprintf()` on a full filesystem will succeed and return the number of characters that sould have been written had there been space. The subsequent `fclose()` reports the `No space left on device` error.
