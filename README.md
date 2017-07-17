# commpage-routine
This PoC does three things:

1. Add a new routine (32-bit and 64-bit compatible) to the comm page <b>text section</b>.
2. Add a new string to the comm page <b>data section</b>.
3. Call (after mapped into the process's address space) the newly added routine from a user space program.

### Preparations
The following files needs to be patched/added in order to work:

- osfmk/i386/cpu_capabilities.h (address definitions (text and data))
- osfmk/i386/commpage/hello_commpage.s (contains 32-bit and 64-bit versions of the new routine)
- osfmk/i386/commpage/commpage_asm.s (to populate the new routine)
- osfmk/i386/commpage/commpage/commpage.c (to populate the new string)
- osfmk/conf/files.x86_64 (to build hello_commpage.s)

### Sample Session
```
$ uname -a
Darwin NOPs-Mac.local 16.5.0 Darwin Kernel Version 16.5.0: Do 13 Jul 2017 19:29:54 CEST; adfontes:xnu-3789.51.2/BUILD/obj/DEBUG_X86_64 x86_64
```

Get the beginning of the comm page text area:

```
$ vmmap $$ | grep "shared memory.*r-x"
shared memory          00007fffffe14000-00007fffffe15000 [    4K     4K     4K     0K] r-x/r-x SM=SHM
```

Run user space program:

```
./commpage-routine 0x7fffffe14000
[*] Found hello commpage routine at address 0x00007fffffe14580
[*] Routine returns 'Hello, Commpage!'
```
