Linux 下隐藏修改进程名称及参数  隐藏ps -ef 等显示

    
    root@ubuntu# ./hide_ProcessnameAndArgv 1 2 3 4
    ========== Before the modification ============
    ProcessName: ./hide_ProcessnameAndArgv
    Argv1: 1
    Argv2: 2
    Argv3: 3
    Argv4: 4
    ========== After the modification ============
    ProcessName: 
    Argv1: 
    Argv2: 
    Argv3: 
    Argv4: 
    ========== Copy data ============
    ProcessName: ./hide_ProcessnameAndArgv
    Argv1: 1
    Argv2: 2
    Argv3: 3
    Argv4: 4
