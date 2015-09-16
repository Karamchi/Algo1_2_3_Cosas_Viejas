#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/vmalloc.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
//#include <math.h>

// Variables globales
int acum_lecturas = 0;
static unsigned long prev_prim;
static char* input;
struct proc_dir_entry* create_proc_entry(const char *name, mode_t mode,struct proc_dir_entry *parent);

bool esPrimo(unsigned long n) {
	int lim=n;
	int i;
	if (!n%2) return false;
	for (i=3;i<=lim;i+=2) {
		if (!n%i) return false;
	} return true;
}

//Funciones de lectura y escritura invocadas por /proc fs.
int cant_lecturas(char* page, char** start, off_t off, int count, int* eof, void* data) {
    int len = sprintf(page, "Lecturas/Escrituras realizadas: %d\n", acum_lecturas);
    return len;
}

static ssize_t primos_write(struct file* file, const char __user* buf, size_t len, loff_t* ppos) {
    int cant=0;

    if ((len < 2)||(len>=PAGE_SIZE)) return -EINVAL;
    cant = copy_from_user(&input, buf, len);
    if (cant != 0)
          return -EFAULT;
    cant=sscanf(input, "%lu", &prev_prim);
    if (cant!=1) {
        printk(KERN_INFO "primo: Error al cambiar valores iniciales\n");
        return -EINVAL;
    } else
        printk(KERN_INFO "primo: Cambio de variable a %lu \n", prev_prim);

    *ppos = len;
    acum_lecturas++;
    return len;
}

//Funciones de lectura invocada por /dev fs
static ssize_t primos_read(struct file* file, char* buf, size_t count, loff_t* ppos) {
    //unsigned long primo;
    char buffer[20];
    int res, len;

    if (count < 1) return -EINVAL;
    if (*ppos !=0) return 0;

    printk(KERN_INFO "primo: variables %d %lu \n", (int)count, prev_prim);
    res = esPrimo(prev_prim);
    len = sprintf(buffer, "%d", res);

    if (copy_to_user(buf, buffer,len))
        return -EINVAL;
    *ppos = len;
    acum_lecturas++;
    return len;
}

// Estructuras utililizadas por la funcion de registro de dispositivos
static const struct file_operations primos_fops = {
    .owner = THIS_MODULE,
    .read = primos_read,
    .write = primos_write
};

static struct miscdevice primos_dev = {
    MISC_DYNAMIC_MINOR,
    "primos",
    &primos_fops
};

// Funciones utilizadas por la creacion y destruccion del modulo
static int __init primos_init(void) {
    struct proc_dir_entry* proc_entry;
    int ret;
    // Registración del device
    ret = misc_register(&primos_dev);
    if (ret) {
        printk(KERN_ERR "No se puede registrar el dispositivo PRIMO\n");
    } else {
        // Inicializacion de la semilla del random
        prev_prim=0;
        input= (char*)vmalloc(PAGE_SIZE);
        memset(input,0,PAGE_SIZE);

        // Definicion de la entrada en /proc con la asociacion de funciones de lectura y escritura
        proc_entry = create_proc_entry("primocant",0644,NULL);
        if (proc_entry == NULL)
            printk(KERN_INFO "primo: No se pudo crear la entrada en /proc\n");
        else
            (*(proc_dir_entry*)proc_entry).read_proc=cant_lecturas; //cant?
    }
    return ret;
}

static void __exit primos_exit(void) {
    remove_proc_entry("primocant", NULL);
    vfree(input);
    misc_deregister(&primos_dev);
}

// Definicion de constructor y destructor del modulo.
module_init(primos_init);
module_exit(primos_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MCH");
MODULE_DESCRIPTION("tester primos");
