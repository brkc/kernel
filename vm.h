#define PAGE_SIZE 4096
#define PAGE_ROUNDDOWN(x) ((x) & -(PAGE_SIZE))
#define PAGE_ROUNDUP(x) PAGE_ROUNDDOWN((x) + ((PAGE_SIZE) - 1))
