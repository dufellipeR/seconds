# seconds
A simple linux kernel module that reports the number of elapsed seconds since the kernel module was loaded.

To compile: 
  ```make```
  
To load compiled module:
  ```sudo insmod seconds.ko```
  
To check kernel log buffer:
  ```dmesg```

#### read module
To read the module report:
  ```cat /proc/seconds```

To remove the kernel module:
  ```sudo rmmod seconds```
