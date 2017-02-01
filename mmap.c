#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BLOCKSIZE 64 * 1024       // 64 KiB
#define BLOCKNUM  1024            // BLOCKNUM * 64 KiB (block)
#define SIZE BLOCKSIZE * BLOCKNUM // in bytes

#define FIXED_ADDR 0x4000000

int main(int argc, char **argv)
{
  uint8_t *p = NULL;
 
  if (!(argc == 2 && atoi(argv[1])) > 0) {
    printf("Usage: %s <num>, where num determines the allocated size as size = 64 MiB * num\n", argv[0]);
    exit(1);
  }

  size_t size = SIZE * atoi(argv[1]);

  p = (uint8_t *)    mmap((void *) FIXED_ADDR,
                     size,
                     PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE | MAP_FIXED, 
//                   MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,
//                   MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB | MAP_FIXED,
                     
                     -1,
                      0 
                     );  

  p = (uint8_t *)    mmap((void *) FIXED_ADDR,
                     size,
                     PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED  | MAP_HUGETLB,
//                   MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,
//                   MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB | MAP_FIXED,
                     
                     -1,
                      0 
                     );  

 if (p !=  (void *) -1)
   printf("Addr: %p, size: %d\n", p, (int ) size);
 else {
   printf("mmap() failed: errno=%d, %s\n", errno, strerror(errno));
   exit(1);
 }

 int i = 0;
 while (1) {
   for(i = 0; i < size; i++) {
     p[i] = (uint8_t) rand();
   }

   printf(".\n");
  }

  // Should never reach here.
  printf("Halting...\n");
  while(1);
}
