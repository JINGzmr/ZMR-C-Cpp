#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

static int pid = 1;
module_param(pid, int, 0644); // 模块参数，表示目标进程的PID

// 打印目标进程的虚拟空间字段
static int print_vm_areas(void) {
    struct task_struct *task;
    struct mm_struct *mm;
    struct vm_area_struct *vma;

    printk(KERN_INFO "print_vm_areas: begin.\n");

    // 通过进程 PID 找到对应的进程的 task_struct 结构
    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (!task) {
        printk(KERN_ERR "print_vm_areas: cannot find process with PID %d\n", pid);
        return -EINVAL;
    }

    // 找到进程的 mm_struct 结构，即内存描述符
    mm = task->mm;
    if (!mm) {
        printk(KERN_ERR "print_vm_areas: failed to get mm_struct of process with PID %d\n", pid);
        return -EINVAL;
    }

    // 打印进程的名称和 PID
    printk(KERN_INFO "Executable name: %s, PID: %d\n", task->comm, pid);

    // 打印进程的代码段、数据段和堆栈地址范围
    printk(KERN_INFO "Code: 0x%lx - 0x%lx\n", mm->start_code, mm->end_code);
    printk(KERN_INFO "Data: 0x%lx - 0x%lx\n", mm->start_data, mm->end_data);
    printk(KERN_INFO "Heap: 0x%lx-0x%lx\n", mm->start_brk, mm->brk);
    printk(KERN_INFO "Stack: 0x%lx\n", mm->start_stack);

    // 遍历进程的内存映射区间并打印
    printk(KERN_INFO "Virtual memory areas:\n");
    for (vma = mm->mmap; vma; vma = vma->vm_next) {
        printk(KERN_INFO "%16lx-%16lx %c%c%c%c\n",
            vma->vm_start,
            vma->vm_end,
            (vma->vm_flags & VM_READ) ? 'r' : '-',
            (vma->vm_flags & VM_WRITE) ? 'w' : '-',
            (vma->vm_flags & VM_EXEC) ? 'x' : '-',
            (vma->vm_flags & VM_SHARED) ? 's' : 'p');
    }

    printk(KERN_INFO "print_vm_areas: end.\n");
    return 0;
}

// 模块初始化函数，在加载模块时调用
static int __init print_init(void) {
    printk(KERN_INFO "print_vm_areas: module loaded.\n");
    print_vm_areas(); // 打印目标进程的虚拟空间字段
    return 0;
}

// 模块退出函数，在卸载模块时调用
static void __exit print_exit(void) {
    printk(KERN_INFO "print_vm_areas: module unloaded.\n");
}

module_init(print_init);
module_exit(print_exit);
MODULE_LICENSE("GPL");
MODULE_INFO(intree, "Y");

