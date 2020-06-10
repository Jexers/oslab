#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/kernel.h>

static int clock_proc_show(struct seq_file *m, void *v)
{
	struct timeval xtime;
 	do_gettimeofday(&xtime);
	seq_printf(m, "%d %d\n", xtime.tv_sec, xtime.tv_usec);
	return 0;
}

static int clock_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, clock_proc_show, NULL);
}

static const struct file_operations clock_proc_fops = {
	.owner=THIS_MODULE,
	.open=clock_proc_open,
	.read=seq_read,
	.release=single_release,
};

static int __init clock_proc_init(void)
{
	proc_create("my_clock", 0, NULL, &clock_proc_fops);
	return 0;
}

static void __exit clock_proc_exit(void)
{
	remove_proc_entry("my_clock", NULL);
}
MODULE_LICENSE("GPL");

module_init(clock_proc_init);
module_exit(clock_proc_exit);
