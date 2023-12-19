!============================================================
! CS 2200 Homework 2 Part 2: Tower of Hanoi
!
! Apart from initializing the stack,
! please do not edit mains functionality. You do not need to
! save the return address before jumping to hanoi in
! main.
!============================================================

main:
    lea     $sp, stack              ! load the label address into $sp and in the next instruction,
    lw      $sp, 0($sp)             ! use $sp as base register to load the value (0xFFFF) into $sp.

    lea     $at, hanoi              ! loads address of hanoi label into $at

    lea     $a0, testNumDisks2      ! loads address of number into $a0
    lw      $a0, 0($a0)             ! loads value of number into $a0

    jalr    $at, $ra                ! jump to hanoi, set $ra to return address
    halt                            ! when we return, just halt

hanoi:
    addi    $sp, $sp, -1           ! space for fp
    sw      $fp, 0($sp)            ! fp saved in current sp
    addi    $fp, $sp, 0             ! store sp into fp
    
    addi    $t0, $zero, 1           ! initialize t0 as 1
    beq     $a0, $t0, base          ! check if a0 = 1

else:
    addi    $a0, $a0, -1            ! n -= 1
    lea     $at, hanoi              ! load the target address
    addi    $sp, $sp, -1            ! push 1 spot on stack
    sw      $ra, 0($sp)             ! store return address on stack
    jalr    $at, $ra                ! call hanoi
    lw      $ra, 0($sp)             ! load return address from the stack
    addi    $sp, $sp, 1             ! pop 1 element from the stack
    add     $v0, $v0, $v0           ! v0 *= 2
    addi    $v0, $v0, 1             ! v0 += 1
    beq     $t0, $t0, teardown      ! branch to teardown
base:
    addi    $v0, $zero, 1               !return 1 by storing it to v0

teardown:
    lw      $fp, 0($sp)             ! put back the old fp
    addi    $sp, $sp, 1             ! pop 
    jalr    $ra, $zero              ! return to caller



stack: .word 0xFFFF                 ! the stack begins here


! Words for testing \/

! 1
testNumDisks1:
    .word 0x0001

! 10
testNumDisks2:
    .word 0x000a

! 20
testNumDisks3:
    .word 0x0014
