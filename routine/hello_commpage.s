// Move this file to osfmk/i386/commpage

#include <sys/appleapiopts.h>
#include <machine/cpu_capabilities.h>
#include <machine/commpage.h>

COMMPAGE_FUNCTION_START(hello, 32, 4)
  movl $0xffff00D0, %eax
  ret
COMMPAGE_DESCRIPTOR(hello,_COMM_PAGE_HELLO)

COMMPAGE_FUNCTION_START(hello_64, 64, 4)
  movq $0x7fffffe000D0, %rax
  ret
COMMPAGE_DESCRIPTOR(hello_64,_COMM_PAGE_HELLO)
