(gdb) disas phase_3
Dump of assembler code for function phase_3:
   0x0000000000401144 <+0>:     sub    $0x18,%rsp
   0x0000000000401148 <+4>:     lea    0x7(%rsp),%rcx
   0x000000000040114d <+9>:     lea    0xc(%rsp),%rdx
   0x0000000000401152 <+14>:    lea    0x8(%rsp),%r8
   0x0000000000401157 <+19>:    mov    $0x402479,%esi
   0x000000000040115c <+24>:    mov    $0x0,%eax
   0x0000000000401161 <+29>:    callq  0x400ac8 <__isoc99_sscanf@plt>
   0x0000000000401166 <+34>:    cmp    $0x2,%eax
   0x0000000000401169 <+37>:    jg     0x401170 <phase_3+44>
   0x000000000040116b <+39>:    callq  0x40148f <explode_bomb>
   0x0000000000401170 <+44>:    cmpl   $0x7,0xc(%rsp)
   0x0000000000401175 <+49>:    ja     0x40126d <phase_3+297>
   0x000000000040117b <+55>:    mov    0xc(%rsp),%eax
   0x000000000040117f <+59>:    jmpq   *0x4024a0(,%rax,8)
   0x0000000000401186 <+66>:    mov    $0x70,%eax
   0x000000000040118b <+71>:    cmpl   $0x184,0x8(%rsp)
   0x0000000000401193 <+79>:    je     0x40127e <phase_3+314>
   0x0000000000401199 <+85>:    callq  0x40148f <explode_bomb>
   0x000000000040119e <+90>:    mov    $0x70,%eax
   0x00000000004011a3 <+95>:    jmpq   0x40127e <phase_3+314>
   0x00000000004011a8 <+100>:   mov    $0x7a,%eax
   0x00000000004011ad <+105>:   cmpl   $0x2ec,0x8(%rsp)
   0x00000000004011b5 <+113>:   je     0x40127e <phase_3+314>
   0x00000000004011bb <+119>:   callq  0x40148f <explode_bomb>
   0x00000000004011c0 <+124>:   mov    $0x7a,%eax
   0x00000000004011c5 <+129>:   jmpq   0x40127e <phase_3+314>
   0x00000000004011ca <+134>:   cmpl   $0x332,0x8(%rsp)
   0x00000000004011d2 <+142>:   je     0x401279 <phase_3+309>
   0x00000000004011d8 <+148>:   callq  0x40148f <explode_bomb>
   0x00000000004011dd <+153>:   mov    $0x75,%eax
   0x00000000004011e2 <+158>:   jmpq   0x40127e <phase_3+314>
   0x00000000004011e7 <+163>:   mov    $0x78,%eax
   0x00000000004011ec <+168>:   cmpl   $0x1e7,0x8(%rsp)
   0x00000000004011f4 <+176>:   je     0x40127e <phase_3+314>
   0x00000000004011fa <+182>:   callq  0x40148f <explode_bomb>
   0x00000000004011ff <+187>:   mov    $0x78,%eax
   0x0000000000401204 <+192>:   jmp    0x40127e <phase_3+314>
   0x0000000000401206 <+194>:   mov    $0x74,%eax
   0x000000000040120b <+199>:   cmpl   $0xad,0x8(%rsp)
   0x0000000000401213 <+207>:   je     0x40127e <phase_3+314>
   0x0000000000401215 <+209>:   callq  0x40148f <explode_bomb>
   0x000000000040121a <+214>:   mov    $0x74,%eax
   0x000000000040121f <+219>:   jmp    0x40127e <phase_3+314>
   0x0000000000401221 <+221>:   cmpl   $0x25a,0x8(%rsp)
   0x0000000000401229 <+229>:   je     0x401279 <phase_3+309>
   0x000000000040122b <+231>:   callq  0x40148f <explode_bomb>
   0x0000000000401230 <+236>:   mov    $0x75,%eax
   0x0000000000401235 <+241>:   jmp    0x40127e <phase_3+314>
   0x0000000000401237 <+243>:   mov    $0x73,%eax
   0x000000000040123c <+248>:   cmpl   $0x2b9,0x8(%rsp)
   0x0000000000401244 <+256>:   je     0x40127e <phase_3+314>
   0x0000000000401246 <+258>:   callq  0x40148f <explode_bomb>
   0x000000000040124b <+263>:   mov    $0x73,%eax
   0x0000000000401250 <+268>:   jmp    0x40127e <phase_3+314>
   0x0000000000401252 <+270>:   mov    $0x6f,%eax
   0x0000000000401257 <+275>:   cmpl   $0x213,0x8(%rsp)
   0x000000000040125f <+283>:   je     0x40127e <phase_3+314>
   0x0000000000401261 <+285>:   callq  0x40148f <explode_bomb>
   0x0000000000401266 <+290>:   mov    $0x6f,%eax
   0x000000000040126b <+295>:   jmp    0x40127e <phase_3+314>
   0x000000000040126d <+297>:   callq  0x40148f <explode_bomb>
   0x0000000000401272 <+302>:   mov    $0x72,%eax
   0x0000000000401277 <+307>:   jmp    0x40127e <phase_3+314>
   0x0000000000401279 <+309>:   mov    $0x75,%eax
   0x000000000040127e <+314>:   cmp    0x7(%rsp),%al
   0x0000000000401282 <+318>:   je     0x401289 <phase_3+325>
   0x0000000000401284 <+320>:   callq  0x40148f <explode_bomb>
   0x0000000000401289 <+325>:   add    $0x18,%rsp
   0x000000000040128d <+329>:   retq   
