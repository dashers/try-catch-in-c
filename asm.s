#
# These are all Intel 64 assembly language function
#
# Debajyoti Dash
#
#
	.text
	.globl	getR15
getR15:
	movq	%r15, %rax
	ret
#
#
	.text
	.globl	getR14
getR14:
	movq	%r14, %rax
	ret
#
#
	.text
	.globl	getR13
getR13:
	movq	%r13, %rax
	ret
#
#
	.text
	.globl	getR12
getR12:
	movq	%r12, %rax
	ret
#
#
	.text
	.globl	getRbx
getRbx:
	movq	%rbx, %rax
	ret
#
#
	.text
	.globl	getRbp
getRbp:
	movq	%rbp, %rax
	ret
#
#
	.text
	.globl	setR15
setR15:
	movq	%rdi, %r15
	ret
#
#
	.text
	.globl	setR14
setR14:
	movq	%rdi, %r14
	ret
#
#
	.text
	.globl	setR13
setR13:
	movq	%rdi, %r13
	ret
#
#
	.text
	.globl	setR12
setR12:
	movq	%rdi, %r12
	ret
#
#
	.text
	.globl	setRbx
setRbx:
	movq	%rdi, %rbx
	ret
#
#
	.text
	.globl	setcurrRbp
setcurrRbp:
	movq	%rdi, %rbp
	ret
#
#
	.text
	.globl	setRip
setRip:
	movq	%rdi, 8(%rbp)
	ret
#
#
	.text
	.globl	setRsp
setRsp:
	movq	%rdi, %rsp
	movq	%rsi, %rax
	popq	%rbp
	ret
#
#
#	NOT USED
#
#
	.text
	.globl	setsavedRbp
setsavedRbp:
	movq	%rdi, (%rbp)
	ret
#
#
	.text
	.globl	getRsp
getRsp:
	movq	%rsp, %rax
	ret
