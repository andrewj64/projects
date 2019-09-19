Dump of assembler code for function phase_6:
   0x0000000000400f3b <+0>:     push   %r12
   0x0000000000400f3d <+2>:     push   %rbp
   0x0000000000400f3e <+3>:     push   %rbx
   0x0000000000400f3f <+4>:     sub    $0x50,%rsp
   0x0000000000400f43 <+8>:     lea    0x30(%rsp),%rbp
   0x0000000000400f48 <+13>:    mov    %rbp,%rsi
   0x0000000000400f4b <+16>:    callq  0x4014c5 <read_six_numbers>
   0x0000000000400f50 <+21>:    mov    $0x0,%r12d
   0x0000000000400f56 <+27>:    mov    0x0(%rbp),%eax			# eax = arg1  Make sure that none of the numbers are the same
   0x0000000000400f59 <+30>:    sub    $0x1,%eax			# eax -= 1
   0x0000000000400f5c <+33>:    cmp    $0x5,%eax			# eax <= 5 (arg1 <=6) 
   0x0000000000400f5f <+36>:    jbe    0x400f66 <phase_6+43>
   0x0000000000400f61 <+38>:    callq  0x40148f <explode_bomb>
   0x0000000000400f66 <+43>:    add    $0x1,%r12d			#r12++
   0x0000000000400f6a <+47>:    cmp    $0x6,%r12d
   0x0000000000400f6e <+51>:    je     0x400f92 <phase_6+87>		# r12 == 6
   0x0000000000400f70 <+53>:    mov    %r12d,%ebx			# ebx = r12 (1)
   0x0000000000400f73 <+56>:    movslq %ebx,%rax			
   0x0000000000400f76 <+59>:    mov    0x0(%rbp),%edx			#edx = arg1
   0x0000000000400f79 <+62>:    cmp    0x30(%rsp,%rax,4),%edx		#cmp arg1 and arg2 (arg3?)
   0x0000000000400f7d <+66>:    jne    0x400f84 <phase_6+73>
   0x0000000000400f7f <+68>:    callq  0x40148f <explode_bomb>
   0x0000000000400f84 <+73>:    add    $0x1,%ebx			#exb += 1
   0x0000000000400f87 <+76>:    cmp    $0x5,%ebx
   0x0000000000400f8a <+79>:    jle    0x400f73 <phase_6+56>
   0x0000000000400f8c <+81>:    add    $0x4,%rbp			# p++ (move to next arg)
   0x0000000000400f90 <+85>:    jmp    0x400f56 <phase_6+27>		#============================
   0x0000000000400f92 <+87>:    mov    $0x0,%ebx			#ebx = 0
   0x0000000000400f97 <+92>:    lea    0x30(%rsp),%r8			#r8 = arg1
   0x0000000000400f9c <+97>:    mov    $0x1,%ebp			#ebp = 1
   0x0000000000400fa1 <+102>:   mov    $0x6033b0,%esi
   0x0000000000400fa6 <+107>:   mov    %rsp,%rdi			#rdi = rsp
   0x0000000000400fa9 <+110>:   jmp    0x400fc4 <phase_6+137>
   0x0000000000400fab <+112>:   mov    0x8(%rdx),%rdx
   0x0000000000400faf <+116>:   add    $0x1,%eax			# eax += 1
   0x0000000000400fb2 <+119>:   cmp    %ecx,%eax
   0x0000000000400fb4 <+121>:   jne    0x400fab <phase_6+112>
   0x0000000000400fb6 <+123>:   mov    %rdx,(%rdi,%rbx,2)		#increment addr by 8 every time
   0x0000000000400fba <+127>:   add    $0x4,%rbx			#rbx += 4
   0x0000000000400fbe <+131>:   cmp    $0x18,%rbx			#loop 5 times?
   0x0000000000400fc2 <+135>:   je     0x400fd4 <phase_6+153>
   0x0000000000400fc4 <+137>:   mov    (%r8,%rbx,1),%ecx
   0x0000000000400fc8 <+141>:   mov    %ebp,%eax
   0x0000000000400fca <+143>:   mov    %rsi,%rdx
   0x0000000000400fcd <+146>:   cmp    $0x1,%ecx			#arg > 1 ? maybe
   0x0000000000400fd0 <+149>:   jg     0x400fab <phase_6+112>
   0x0000000000400fd2 <+151>:   jmp    0x400fb6 <phase_6+123>
   0x0000000000400fd4 <+153>:   mov    (%rsp),%rbx
   0x0000000000400fd8 <+157>:   mov    0x8(%rsp),%rax
   0x0000000000400fdd <+162>:   mov    %rax,0x8(%rbx)
   0x0000000000400fe1 <+166>:   mov    0x10(%rsp),%rdx
   0x0000000000400fe6 <+171>:   mov    %rdx,0x8(%rax)
   0x0000000000400fea <+175>:   mov    0x18(%rsp),%rax
   0x0000000000400fef <+180>:   mov    %rax,0x8(%rdx)
   0x0000000000400ff3 <+184>:   mov    0x20(%rsp),%rdx
   0x0000000000400ff8 <+189>:   mov    %rdx,0x8(%rax)
   0x0000000000400ffc <+193>:   mov    0x28(%rsp),%rax
   0x0000000000401001 <+198>:   mov    %rax,0x8(%rdx)
   0x0000000000401005 <+202>:   movq   $0x0,0x8(%rax)
   0x000000000040100d <+210>:   mov    $0x0,%ebp
   0x0000000000401012 <+215>:   mov    0x8(%rbx),%rax
   0x0000000000401016 <+219>:   mov    (%rbx),%edx
   0x0000000000401018 <+221>:   cmp    (%rax),%edx
   0x000000000040101a <+223>:   jge    0x401021 <phase_6+230>
   0x000000000040101c <+225>:   callq  0x40148f <explode_bomb>
   0x0000000000401021 <+230>:   mov    0x8(%rbx),%rbx
   0x0000000000401025 <+234>:   add    $0x1,%ebp
   0x0000000000401028 <+237>:   cmp    $0x5,%ebp
   0x000000000040102b <+240>:   jne    0x401012 <phase_6+215>
   0x000000000040102d <+242>:   add    $0x50,%rsp
   0x0000000000401031 <+246>:   pop    %rbx
   0x0000000000401032 <+247>:   pop    %rbp
   0x0000000000401033 <+248>:   pop    %r12
   0x0000000000401035 <+250>:   retq   
End of assembler dump.


(gdb) x/24dw $rdx-64
0x603360 <node6>:       256     6       0       0
0x603370 <node5>:       130     5       6304608 0
0x603380 <node4>:       109     4       6304624 0
0x603390 <node3>:       982     3       6304640 0
0x6033a0 <node2>:       544     2       6304656 0
0x6033b0 <node1>:       803     1       6304672 0
(gdb) x/24dw $rdx-128
0x603300 <fprintf@got.plt>:     4197406 0       -139469632      32767
0x603310 <fflush@got.plt>:      4197438 0       0       0
0x603320:       0       0       0       0
0x603330 <bomb_id>:     30      808595521       892418356       48
0x603340 <user_password>:       1313634418      1415138145      1785362794      1330925686
0x603350 <user_password+16>:    1129791863      0       0       0

