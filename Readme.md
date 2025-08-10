```c
         _                                
        | |                                 
   ___  | |__   ___   ___  _ __ __   __ ___  
  / _ \ | '_ \ / __| / _ \| '__|\ \ /  _ \ 
 | (_) || |_) |\__ \|  __/| |    \ V /|  __/ 
  \___/ |_.__/ |___/ \___||_|     \_/  \___| 
                                            
           
```

Observe is a simple command-line tool written in C to monitor changes
  in a specified file. It continuously polls the file at a user-defined
  interval and prints the file's contents whenever it detects a change
  in the file size.
  
  ## Usage

 
 ```bash
 observe <file-to-watch> [-i interval_seconds]
 ```
 
 ## Arguments
 
 - `<file-to-watch>`  
   The path to the file you want to monitor.
 
 ## Options
 
 - `-i <seconds>`  
   Polling interval in seconds (default is 1 second).
 - `-h, --help`  
   Show this help message and exit.
 
 ## How it works
 
 1. The tool opens the specified file in read mode.
 2. It repeatedly checks the file size every `interval` seconds.
 3. When the file size changes (indicating modification), observe
    reopens the file and prints the entire contents to stdout.
 4. This continues indefinitely until the program is terminated.
 
 ## Notes
 
 - The tool uses file size changes to detect modifications.
   Changes that do not affect file size may not be detected.
 - The polling interval can be adjusted via the `-i` option,
   but a smaller interval can cause more CPU usage.
 - If the file cannot be opened or reopened, observe will
   print an error message and exit.
 
 ## Example
 
 ```bash
 observe /var/log/syslog -i 2
 ```
 
 This will monitor the syslog file every 2 seconds and print any
 changes detected.
 
 ## Compilation
 
 ```bash
 gcc observe.c -o observe
 ```
 
 ## Running
 
 ```bash
 ./observe /path/to/file.txt -i 1
 ```
 
 ## Limitations
 
 - Works by polling; no inotify or event-driven mechanisms.
 - Prints full file contents on each change (not incremental diffs).
 
 ## License
 
 Open source; free to use and modify.
 
 Enjoy using observe!
