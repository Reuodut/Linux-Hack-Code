Linux 下隐藏修改进程名称及参数  隐藏ps -ef 等显示

注意：

此方法并不能修改 /proc/pid/stat 以及 /proc/pid/status 下的进程信息，要修改的话需要配合另一种修改方式， 详见项目中的 利用prctl修改进程名称 或者看博文 https://reuodut.github.io/2020/09/Linux%E8%BF%9B%E7%A8%8B%E9%9A%90%E8%97%8F-%E5%88%9D%E7%BA%A7%E9%9A%90%E8%97%8F%E7%AF%87/

    
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
