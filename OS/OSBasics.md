_http://faculty.salina.k-state.edu/tim/ossg/Introduction/OSworking.html_
# ***Operating Systems - Basics***

---

### **Interrupts**
- Interrupts are signals sent to the CPU by external devices (usually I/O devices). They make the CPU stop what it's currently doing to immediatly perform the requested action. Interrupts have three types:
    - **Hardware interrupt:** Generated by *hardware devices* to signal that they need attention from the OS. The device may have received data or completed some task requested to it by the OS, like transfering data between drives.
    - **Software interrupt:** Generated by programs when they want to request a system call to be performed by the operating system.
    - **Traps**: Generated by the CPU itself to indicate that some error or condition occured for which assistance from the OS is needed.

---

### **CPU Execution Mode**
A system call (syscall) will switch the *mode bit* to kernel mode, as well as traps and interrupts, but not application programs.

#### **User mode:** 
Restricted mode. Cannot execute certain instructions, access certain registers and I/O devices.

#### **Kernel mode:**
Also called Supervisor mode, has none of the above mentioned restrictions. Being able to execute and reference every instruction and memory locations.

### **CPU response to interrupts**
***Context Switching:*** Switch of running processes to execute OS kernel code.  
To perform an interrupt, the CPU relies on two registers:  
- One which stores a pointer to the current process's [Process Control Block (PCB)](#5-pcb).
- The other one stores a pointer to a *table of pointers* to the instructions in the kernel for the interrupt handlers and syscalls.

<h5 id='5-pcb'>Process Control Blocks</h5>
A data structure in the OS kernel’s memory holding all data that the OS needs about a process. All of the process control blocks are kept in an array indexed by the PID for each process.