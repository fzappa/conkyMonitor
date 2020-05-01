conkyMonitor
============================================
Simple monitor to use with Conky Manager.

This program uses the glibtop library.
--------------------------------------------------------------------------
To execute...
```sh
$ clang++ monitor.cpp -o monitor -I/usr/include/libgtop-2.0/ -lgtop-2.0 `pkg-config --cflags --libs gtk+-3.0`
$ ./monitor
  Usage: ./monitor <option>
  Options:
    --ram       Show total ram info
    --ramuse    Show percentual ram in use
    --swap      Show swap info
    --swapuse   Show percentual swap in use
    --extip     Show external IP address
```


| References for this project | Links |
| ------ | ------ |
| GlibTop | https://developer.gnome.org/libgtop/stable/libgtop-GlibTop.html |
| Mem | https://developer.gnome.org/libgtop/stable/libgtop-mem.html |
| Swap | https://developer.gnome.org/libgtop/stable/libgtop-swap.html |
| Conky Manager | https://teejeetech.in/conky-manager/ |
