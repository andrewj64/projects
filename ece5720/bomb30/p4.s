(gdb) disas phase_4
Dump of assembler code for function phase_4:
   0x00000000004010e8 <+0>:     sub    $0x18,%rsp
   0x00000000004010ec <+4>:     lea    0x8(%rsp),%rcx
   0x00000000004010f1 <+9>:     lea    0xc(%rsp),%rdx
   0x00000000004010f6 <+14>:    mov    $0x40258a,%esi
   0x00000000004010fb <+19>:    mov    $0x0,%eax
   0x0000000000401100 <+24>:    callq  0x400ac8 <__isoc99_sscanf@plt>
   0x0000000000401105 <+29>:    cmp    $0x2,%eax
   0x0000000000401108 <+32>:    jne    0x401117 <phase_4+47>
   0x000000000040110a <+34>:    mov    0xc(%rsp),%eax
   0x000000000040110e <+38>:    test   %eax,%eax
   0x0000000000401110 <+40>:    js     0x401117 <phase_4+47>
   0x0000000000401112 <+42>:    cmp    $0xe,%eax
   0x0000000000401115 <+45>:    jle    0x40111c <phase_4+52>
   0x0000000000401117 <+47>:    callq  0x40148f <explode_bomb>
   0x000000000040111c <+52>:    mov    $0xe,%edx
   0x0000000000401121 <+57>:    mov    $0x0,%esi
   0x0000000000401126 <+62>:    mov    0xc(%rsp),%edi
   0x000000000040112a <+66>:    callq  0x400e70 <func4>
   0x000000000040112f <+71>:    test   %eax,%eax
   0x0000000000401131 <+73>:    jne    0x40113a <phase_4+82>
   0x0000000000401133 <+75>:    cmpl   $0x0,0x8(%rsp)
   0x0000000000401138 <+80>:    je     0x40113f <phase_4+87>
   0x000000000040113a <+82>:    callq  0x40148f <explode_bomb>
   0x000000000040113f <+87>:    add    $0x18,%rsp
   0x0000000000401143 <+91>:    retq   
End of assembler dump.
(gdb) disas func4
Dump of assembler code for function func4:
   0x0000000000400e70 <+0>:     sub    $0x8,%rsp
   0x0000000000400e74 <+4>:     mov    %edx,%eax
   0x0000000000400e76 <+6>:     sub    %esi,%eax
   0x0000000000400e78 <+8>:     mov    %eax,%ecx
   0x0000000000400e7a <+10>:    shr    $0x1f,%ecx
   0x0000000000400e7d <+13>:    lea    (%rcx,%rax,1),%eax
   0x0000000000400e80 <+16>:    sar    %eax
   0x0000000000400e82 <+18>:    lea    (%rax,%rsi,1),%ecx
   0x0000000000400e85 <+21>:    cmp    %edi,%ecx
   0x0000000000400e87 <+23>:    jle    0x400e95 <func4+37>
   0x0000000000400e89 <+25>:    lea    -0x1(%rcx),%edx
   0x0000000000400e8c <+28>:    callq  0x400e70 <func4>
   0x0000000000400e91 <+33>:    add    %eax,%eax
   0x0000000000400e93 <+35>:    jmp    0x400eaa <func4+58>
   0x0000000000400e95 <+37>:    mov    $0x0,%eax
   0x0000000000400e9a <+42>:    cmp    %edi,%ecx
   0x0000000000400e9c <+44>:    jge    0x400eaa <func4+58>
   0x0000000000400e9e <+46>:    lea    0x1(%rcx),%esi
   0x0000000000400ea1 <+49>:    callq  0x400e70 <func4>
   0x0000000000400ea6 <+54>:    lea    0x1(%rax,%rax,1),%eax
   0x0000000000400eaa <+58>:    add    $0x8,%rsp
   0x0000000000400eae <+62>:    retq   
End of assembler dump.

7 0 "string" to activate secret phase
