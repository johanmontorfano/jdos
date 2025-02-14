# Johan's Dumb Operating System

**JDOS is an operating system made from scratch, its intended to have the
following features at some point:**
- Disk I/O
- Graphical User Interface
- Applications
- User Mode

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
        - [ ] User mode
        - [ ] Kernel mode
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
