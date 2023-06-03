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
  
  fact:
    move $fp, $sp
    addi $sp, $sp, -24
    li $t0, 1
    sw $a0, -4($fp)
    sw $t0, -8($fp)
    lw $t0, -8($fp)
    lw $t1, -4($fp)
    beq $t1, $t0, label1
    j label2
  label1:
    lw $t0, -4($fp)
    move $v0, $t0
    jr $ra
  
    j label3
  label2:
    li $t0, 1
    lw $t2, -4($fp)
    sub $t1, $t2, $t0
    move $a0, $t1
    sw $t0, -12($fp)
    sw $t1, -16($fp)
    addi $sp, $sp, -8
    sw $ra, 4($sp)
    sw $fp, 0($sp)
    jal fact
    move $sp, $fp
    lw $fp, 0($sp)
    lw $ra, 4($sp)
    addi $sp, $sp, 8
    move $t0, $v0
    lw $t2, -4($fp)
    mul $t1, $t2, $t0
    move $v0, $t1
    sw $t0, -20($fp)
    sw $t1, -24($fp)
    jr $ra
  
  label3:
  main:
    move $fp, $sp
    addi $sp, $sp, -44
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal read
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    move $t0, $v0
    sw $t0, -4($fp)
    lw $t1, -4($fp)
    move $t0, $t1
    move $t2, $t1
    li $t3, 1
    sw $t0, -8($fp)
    sw $t2, -12($fp)
    sw $t3, -16($fp)
    lw $t0, -16($fp)
    lw $t1, -8($fp)
    bgt $t1, $t0, label4
    j label5
  label4:
    lw $a0, -8($fp)
    addi $sp, $sp, -8
    sw $ra, 4($sp)
    sw $fp, 0($sp)
    jal fact
    move $sp, $fp
    lw $fp, 0($sp)
    lw $ra, 4($sp)
    addi $sp, $sp, 8
    move $t0, $v0
    move $t1, $t0
    move $t2, $t0
    sw $t0, -20($fp)
    sw $t1, -24($fp)
    sw $t2, -28($fp)
    j label6
  label5:
    li $t0, 1
    move $t1, $t0
    move $t2, $t0
    sw $t0, -32($fp)
    sw $t1, -24($fp)
    sw $t2, -36($fp)
  label6:
    lw $t0, -24($fp)
    move $a0, $t0
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal write
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    li $t1, 0
    li $t2, 0
    move $v0, $t2
    sw $t1, -40($fp)
    sw $t2, -44($fp)
    jr $ra
  
