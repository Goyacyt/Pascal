  .data
  _prompt: .asciiz "Enter an interger:"
  _ret: .asciiz "\n"
  .globl main
  .text
  read:
    li $v0, 4
    la $a0, _prompt
    syscall
    li $v0, 5
    syscall
    jr $ra
  
  write:
    li $v0, 1
    syscall
    li $v0, 4
    la $a0, _ret
    syscall
    move $v0, $0
    jr $ra
  
  main:
    move $fp, $sp
    addi $sp, $sp, -72
    li $t0, 0
    move $t1, $t0
    li $t2, 1
    move $t3, $t2
    li $t4, 0
    move $t5, $t4
    sw $t0, -4($fp)
    sw $t1, -8($fp)
    sw $t2, -12($fp)
    sw $t3, -16($fp)
    sw $t4, -20($fp)
    sw $t5, -24($fp)
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal read
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    move $t0, $v0
    sw $t0, -28($fp)
    lw $t1, -28($fp)
    move $t0, $t1
    move $t2, $t1
    sw $t0, -32($fp)
    sw $t2, -36($fp)
  label1:
    lw $t0, -32($fp)
    lw $t1, -24($fp)
    blt $t1, $t0, label2
    j label3
  label2:
    lw $t1, -16($fp)
    lw $t2, -8($fp)
    add $t0, $t2, $t1
    move $t3, $t0
    sw $t0, -40($fp)
    sw $t3, -44($fp)
    lw $t0, -16($fp)
    move $a0, $t0
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal write
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    li $t1, 0
    move $t2, $t0
    move $t3, $t0
    lw $t4, -44($fp)
    move $t0, $t4
    move $t5, $t4
    li $t6, 1
    lw $s0, -24($fp)
    add $t7, $s0, $t6
    move $s0, $t7
    move $s1, $t7
    sw $t0, -16($fp)
    sw $t1, -48($fp)
    sw $t2, -8($fp)
    sw $t3, -52($fp)
    sw $t5, -56($fp)
    sw $t6, -60($fp)
    sw $t7, -64($fp)
    sw $s0, -24($fp)
    sw $s1, -68($fp)
    j label1
  label3:
    li $t0, 0
    move $v0, $t0
    sw $t0, -72($fp)
    jr $ra
  
