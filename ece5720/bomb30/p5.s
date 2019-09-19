(gdb) disas phase_5
Dump of assembler code for function phase_5:
   0x000000000040107a <+0>:     sub    $0x18,%rsp
   0x000000000040107e <+4>:     lea    0x8(%rsp),%rcx
   0x0000000000401083 <+9>:     lea    0xc(%rsp),%rdx
   0x0000000000401088 <+14>:    mov    $0x40258a,%esi
   0x000000000040108d <+19>:    mov    $0x0,%eax
   0x0000000000401092 <+24>:    callq  0x400ac8 <__isoc99_sscanf@plt>
   0x0000000000401097 <+29>:    cmp    $0x1,%eax
   0x000000000040109a <+32>:    jg     0x4010a1 <phase_5+39>
   0x000000000040109c <+34>:    callq  0x40148f <explode_bomb>
   0x00000000004010a1 <+39>:    mov    0xc(%rsp),%eax
   0x00000000004010a5 <+43>:    and    $0xf,%eax
   0x00000000004010a8 <+46>:    mov    %eax,0xc(%rsp)
   0x00000000004010ac <+50>:    cmp    $0xf,%eax
   0x00000000004010af <+53>:    je     0x4010de <phase_5+100>
   0x00000000004010b1 <+55>:    mov    $0x0,%ecx
   0x00000000004010b6 <+60>:    mov    $0x0,%edx
   0x00000000004010bb <+65>:    mov    $0x4024e0,%esi
   0x00000000004010c0 <+70>:    add    $0x1,%edx 		;while eax < 15
   0x00000000004010c3 <+73>:    cltq   
   0x00000000004010c5 <+75>:    mov    (%rsi,%rax,4),%eax
   0x00000000004010c8 <+78>:    add    %eax,%ecx
   0x00000000004010ca <+80>:    cmp    $0xf,%eax		; check that eax is 15
   0x00000000004010cd <+83>:    jne    0x4010c0 <phase_5+70>
   0x00000000004010cf <+85>:    mov    %eax,0xc(%rsp)
   0x00000000004010d3 <+89>:    cmp    $0xf,%edx		; check that edx is 15
   0x00000000004010d6 <+92>:    jne    0x4010de <phase_5+100>
   0x00000000004010d8 <+94>:    cmp    0x8(%rsp),%ecx
   0x00000000004010dc <+98>:    je     0x4010e3 <phase_5+105>
   0x00000000004010de <+100>:   callq  0x40148f <explode_bomb>
   0x00000000004010e3 <+105>:   add    $0x18,%rsp
   0x00000000004010e7 <+109>:   retq   
End of assembler dump.

