
[![Build Status](https://travis-ci.com/TralahM/linux_kernel_module.svg?branch=master)](https://travis-ci.com/TralahM/linux_kernel_module)
[![Build status](https://ci.appveyor.com/api/projects/status/yvvmq5hyf7hj743a/branch/master?svg=true)](https://ci.appveyor.com/project/TralahM/linux_kernel_module/branch/master)
[![Documentation Status](https://readthedocs.org/projects/linux_kernel_module/badge/?version=latest)](https://linux_kernel_module.readthedocs.io/en/latest/?badge=latest)
[![License: GPLv3](https://img.shields.io/badge/License-GPLV2-green.svg)](https://opensource.org/licenses/GPLV2)
[![Organization](https://img.shields.io/badge/Org-TralahTek-blue.svg)](https://github.com/TralahTek)
[![PRs Welcome](https://img.shields.io/badge/PRs-Welcome-brightgreen.svg?style=flat-square)](https://github.com/TralahM/linux_kernel_module/pull/)
[![GitHub pull-requests](https://img.shields.io/badge/Issues-pr-red.svg?style=flat-square)](https://github.com/TralahM/linux_kernel_module/pull/)
[![Language](https://img.shields.io/badge/Language-C-555555.svg)](https://github.com/TralahM)
<noscript><a href="https://liberapay.com/TralahM/donate"><img alt="Donate using Liberapay" src="https://liberapay.com/assets/widgets/donate.svg"></a></noscript>

# linux_kernel_module.


[![TralahTek](https://img.shields.io/badge/Organization-TralahTek-black.svg?style=for-the-badge&logo=github)](https://github.com/TralahTek)
[![TralahM](https://img.shields.io/badge/Engineer-TralahM-blue.svg?style=for-the-badge&logo=github)](https://github.com/TralahM)
[![TralahM](https://img.shields.io/badge/Maintainer-TralahM-green.svg?style=for-the-badge&logo=github)](https://github.com/TralahM)

# Documentation

[![Documentation](https://img.shields.io/badge/Docs-linux_kernel_module-blue.svg?style=for-the-badge)](https://github.com/TralahM/linux_kernel_module)


## Building from Source for Developers
Ensure that the `linux-headers` are installed for your current kernel as
indicated by `uname -r`.

```console
$ git clone https://github.com/TralahM/linux_kernel_module.git
$ cd linux_kernel_module
$ make
```


### output should be

![filetree.png](filetree.png)


```console
$ sudo insmod pa2_char_driver.ko
$ sudo dmesg
```
Find the command to create a supported character device with major and minor
numbers using `dmesg` or `cat /var/log/syslog`.

The Output is Similar to this:

```
[ 2745.881449] INIT Function Called.
[ 2745.881453] Device Number 535822336 MAJ:511 MIN:0
[ 2745.881454] I was assigned major number 511. To talk to
[ 2745.881454] the driver, create a dev file with
[ 2745.881454] 'mknod /dev/simple_char_device -m 777 c 511 0'.
[ 2745.881455] Try various minor numbers. Try to cat and echo to
[ 2745.881455] the device file.
[ 2745.881456] Remove the device file and module when done.

```

After running `insmod` the appropriate device will be created automatically for
you and removed when you call `rmmod`.

if for som reason however it is not created,
Then Run the command `sudo mknod /dev/simple_char_device -m 777 c 511 0`


# Testing.

Run
```
$ make test
$ make runtest
$ cat /dev/simple_char_device
$ sudo dmesg
```

Should show the number of times the device was opened and closed.



# Contributing
[See the Contributing File](CONTRIBUTING.rst)


[See the Pull Request File](PULL_REQUEST_TEMPLATE.md)


# Support

# LICENCE

[Read the license here](LICENSE)


# Self-Promotion

[![](https://img.shields.io/badge/Github-TralahM-green?style=for-the-badge&logo=github)](https://github.com/TralahM)
[![](https://img.shields.io/badge/Twitter-%40tralahtek-blue?style=for-the-badge&logo=twitter)](https://twitter.com/TralahM)
[![TralahM](https://img.shields.io/badge/Kaggle-TralahM-purple.svg?style=for-the-badge&logo=kaggle)](https://kaggle.com/TralahM)
[![TralahM](https://img.shields.io/badge/LinkedIn-TralahM-white.svg?style=for-the-badge&logo=linkedin)](https://linkedin.com/in/TralahM)


[![Blog](https://img.shields.io/badge/Blog-tralahm.tralahtek.com-blue.svg?style=for-the-badge&logo=rss)](https://tralahm.tralahtek.com)

[![TralahTek](https://img.shields.io/badge/Organization-TralahTek-cyan.svg?style=for-the-badge)](https://org.tralahtek.com)


