// Process control information is used by the OS to manage the process itself. This includes:
//
// The process scheduling state, e.g. in terms of "ready", "suspended", etc., and other scheduling information as well, like a priority value, the amount of time elapsed since the process gained control of the CPU or since it was suspended. Also, in case of a suspended process, event identification data must be recorded for the event the process is waiting for.
// Process structuring information: process's children id's, or the id's of other processes related to the current one in some functional way, which may be represented as a queue, a ring or other data structures.
// Interprocess communication information: various flags, signals and messages associated with the communication among independent processes may be stored in the PCB.
// Process privileges, in terms of allowed/disallowed access to system resources.
// Process state: State may enter into new, ready, running, waiting, dead depending on CPU scheduling.
// Process No.: a unique identification number for each process in the operating system.
// Program counter: a pointer to the address of the next instruction to be executed for this process.
// CPU registers: indicates various register set of CPU where process need to be stored for execution for running state.
// CPU scheduling information: indicates the information of a process with which it uses the CPU time through scheduling.
// Memory management information: includes the information of page table, memory limits, Segment table depending on memory used by the operating system.
// Accounting information: includes the amount of CPU used for process execution, time limits, execution ID etc.
// IO status information: includes a list of I/O devices allocated to the process.


enum processState {
    ZOMBIE = -1 , NEW, READY, WAITING, SUSPENDED, RUNNING, ENDED
}; //TODO : add swapped states

typedef struct {
    int
            millisecond,
            second,
            minute,
            hour,
            day,
            month,
            year;
} Date;

typedef struct pcb {
    int id;
    char *name;
    char *owner;
    int priority;

    enum processState state;
    Date creationDate;
    Date *limitTime; //remove ?
    int cpuCycles;
    int IONum;
    float estimatedMemorySize;  //in bytes

    struct pcb *father;

    /* TODO : add childs list
     * TODO : add input devices list
     * TODO : add files list
     * TODO : add pointers to the executable machine code of a process
    */
} PCB;

int initPcb();

int updatePcb();

int endPcb();