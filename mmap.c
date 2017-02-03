#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifdef __x86_64__
#define PAGE_SIZE     4096           // 4 KiB
#define HUGEPAGE_SIZE 2097152        // 2 MiB
#define FIXED_ADDR    0x100000000    // Aligned to PAGE_SIZE
#elif __PPC64__
#define PAGE_SIZE     65536          // 64 KiB
#define HUGEPAGE_SIZE 16777216       // 16 MiB
#define FIXED_ADDR    0x4000000      // Aligned to PAGE_SIZE
#else
// Not supported.
#endif

int main(int argc, char **argv)
{
  uint8_t *p = NULL;
 
  if (!(argc == 2 && atoi(argv[1])) > 0) {
    printf("Usage: %s <nr_hugepages>, where nr_hugepages determines"
             "the number of huge pages to be allocated\n", argv[0]);
    exit(1);
  }

  size_t total_alloc_size = HUGEPAGE_SIZE * atoi(argv[1]);

  p = (uint8_t *)    mmap((void *) FIXED_ADDR,
                     total_alloc_size,
                     PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED | MAP_NORESERVE,
//                   MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,
//                   MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB | MAP_FIXED,
                     
                     -1,
                      0 
                     );  

  p = (uint8_t *)    mmap((void *) FIXED_ADDR,
                     total_alloc_size,
                     PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED | MAP_HUGETLB,
//                   MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,
//                   MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB | MAP_FIXED,
                     
                     -1,
                      0 
                     );  

 if (p !=  (void *) -1)
   printf("Addr: %p, total_alloc_size: %d\n", p, (int ) total_alloc_size);
 else {
   printf("mmap() failed: errno=%d, %s\n", errno, strerror(errno));
   exit(1);
 }

 int i = 0;
 while (1) {
   for(i = 0; i < total_alloc_size; i++) {
     p[i] = (uint8_t) rand();
   }

   // printf(".\n");
  }

  // Should never reach here.
  printf("Halting...\n");
  while(1);
}
