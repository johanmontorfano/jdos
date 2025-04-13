# Johan's Dumb Operating System

**JDOS is an operating system made from scratch, its intended to have the
following features at some point:**
- Disk I/O
- Graphical User Interface
- Applications
- User Mode

### Compilation

To properly compile the system, call `make`. To run it, call `make run`.

If you are trying to use HDD-based bootloader/kernel, call `make run_hdd`
instead.

If you have trouble running the OS (loop), try removig `hdd.bin` and
recompiling. In some cases, `hdd.bin` content can be causing issues.

### OS Specifications

##### Drivers

Drivers, depending on their kind, have to operate with buffers.

##### Buffers

Buffers are objects used by the kernel to keep track of input/outputs making
possible for libc to abstract stuff like `getline`.

| Buffer name      | Buffer Description                            |
| ---------------- | --------------------------------------------- |
| **stdin**        | Stores keyboard/mouse input data              |
| **stdout**       | Stores printed data                           |
| **stderr**       | Stores printed data categorized as errors     |

Every buffer can be flushed by a program/the kernel.

### Roadmap
- [x] Bootloader
    - [x] 16-bits compile option
    - [x] 32-bits compile option
    - [x] Kernel loader
    - [x] Interrupts
- [-] Kernel
    - [x] Interrupts
    - [-] Drivers
        - [-] Keyboard
            - [x] Codes support
            - [ ] Full codes support
            - [ ] Layout support
        - [x] VGA screen
        - [ ] 2D screen
        - [-] Disk I/O
            - [x] ATA Identify
            - [x] ATA PIO 24 bits R/W
            - [ ] ATA PIO 48 bits R/W
            - [ ] DMA ATA R/W
    - [-] Features
        - [x] Memory allocation
        - [ ] Memory reallocation
        - [-] User mode
        - [x] Kernel mode
        - [ ] File system
        - [ ] APM (Advanced Power Mgmt) support
    - [-] Mini shell
- [ ] File system
    - [ ] Head table
    - [ ] Files
    - [ ] Folders
- [ ] 2D screen
    - [ ] Adaptative resolution
    - [ ] Graphics drawing
