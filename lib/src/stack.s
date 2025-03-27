	.cpu arm7tdmi
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"stack.c"
	.global	sp
	.bss
	.align	2
	.type	sp, %object
	.size	sp, 4
sp:
	.space	4
	.global	sbase
	.align	2
	.type	sbase, %object
	.size	sbase, 4
sbase:
	.space	4
	.global	size
	.data
	.align	2
	.type	size, %object
	.size	size, 4
size:
	.word	5
	.section	.rodata
	.align	2
.LC0:
	.ascii	"overflow, realloc\000"
	.align	2
.LC1:
	.ascii	"realloc fail\000"
	.text
	.align	2
	.global	push
	.type	push, %function
push:
	@ Function supports interworking.
	@ args = 20, pretend = 16, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	sub	sp, sp, #16
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	add	ip, fp, #4
	stmia	ip, {r0, r1, r2, r3}
	mov	r3, #0
	str	r3, [fp, #-8]
	mov	r3, #0
	str	r3, [fp, #-12]
	ldr	r3, .L7
	ldr	r3, [r3]
	cmp	r3, #0
	beq	.L2
	ldr	r3, .L7
	ldr	r3, [r3]
	mov	r2, r3
	ldr	r3, .L7+4
	ldr	r3, [r3]
	rsb	r3, r3, r2
	mov	r2, r3, asr #2
	mov	r3, r2
	mov	r3, r3, asl #1
	add	r3, r3, r2
	mov	r1, r3, asl #4
	add	r3, r3, r1
	mov	r1, r3, asl #8
	add	r3, r3, r1
	mov	r1, r3, asl #16
	add	r3, r3, r1
	mov	r3, r3, asl #2
	add	r3, r3, r2
	mov	r2, r3
	ldr	r3, .L7+8
	umull	r1, r3, r2, r3
	mov	r3, r3, lsr #4
	str	r3, [fp, #-12]
	ldr	r3, .L7+12
	ldr	r3, [r3]
	ldr	r2, [fp, #-12]
	cmp	r2, r3
	bne	.L3
	ldr	r0, .L7+16
	bl	puts
	ldr	r3, .L7+12
	ldr	r3, [r3]
	add	r2, r3, #5
	ldr	r3, .L7+12
	str	r2, [r3]
	ldr	r3, .L7+4
	ldr	r2, [r3]
	ldr	r3, .L7+12
	ldr	r3, [r3]
	mov	r0, r2
	mov	r1, r3
	bl	realloc
	mov	r2, r0
	ldr	r3, .L7+4
	str	r2, [r3]
	ldr	r3, .L7+4
	ldr	r3, [r3]
	cmp	r3, #0
	bne	.L4
	ldr	r0, .L7+20
	bl	puts
	mvn	r3, #0
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-8]
	b	.L5
.L4:
	ldr	r3, .L7+4
	ldr	r1, [r3]
	ldr	r2, [fp, #-12]
	mov	r3, r2
	mov	r3, r3, asl #2
	add	r3, r3, r2
	mov	r3, r3, asl #2
	add	r2, r1, r3
	ldr	r3, .L7
	str	r2, [r3]
.L3:
	ldr	r3, .L7
	ldr	r3, [r3]
	add	r2, r3, #20
	ldr	r3, .L7
	str	r2, [r3]
	ldr	r3, .L7
	ldr	r3, [r3]
	ldr	r2, [fp, #4]
	str	r2, [r3]
	ldr	r3, .L7
	ldr	r3, [r3]
	add	r2, r3, #4
	add	r3, fp, #8
	mov	r0, r2
	mov	r1, r3
	bl	strcpy
	b	.L6
.L2:
	ldr	r3, .L7+4
	ldr	r2, [r3]
	ldr	r3, .L7
	str	r2, [r3]
	ldr	r3, .L7
	ldr	r3, [r3]
	ldr	r2, [fp, #4]
	str	r2, [r3]
	ldr	r3, .L7
	ldr	r3, [r3]
	add	r2, r3, #4
	add	r3, fp, #8
	mov	r0, r2
	mov	r1, r3
	bl	strcpy
.L6:
	ldr	r3, [fp, #-8]
.L5:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	ldmfd	sp!, {fp, lr}
	add	sp, sp, #16
	bx	lr
.L8:
	.align	2
.L7:
	.word	sp
	.word	sbase
	.word	-858993459
	.word	size
	.word	.LC0
	.word	.LC1
	.size	push, .-push
	.align	2
	.global	pop
	.type	pop, %function
pop:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	stmfd	sp!, {r4, fp}
	add	fp, sp, #4
	sub	sp, sp, #32
	str	r0, [fp, #-32]
	ldr	r3, .L13
	ldr	r3, [r3]
	sub	ip, fp, #24
	mov	r4, r3
	ldmia	r4!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldr	r3, [r4]
	str	r3, [ip]
	ldr	r3, .L13
	ldr	r2, [r3]
	ldr	r3, .L13+4
	ldr	r3, [r3]
	cmp	r2, r3
	bne	.L10
	ldr	r3, .L13
	mov	r2, #0
	str	r2, [r3]
	b	.L11
.L10:
	ldr	r3, .L13
	ldr	r3, [r3]
	sub	r2, r3, #20
	ldr	r3, .L13
	str	r2, [r3]
.L11:
	ldr	r3, [fp, #-32]
	mov	ip, r3
	sub	r4, fp, #24
	ldmia	r4!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldr	r3, [r4]
	str	r3, [ip]
	ldr	r0, [fp, #-32]
	sub	sp, fp, #4
	@ sp needed
	ldmfd	sp!, {r4, fp}
	bx	lr
.L14:
	.align	2
.L13:
	.word	sp
	.word	sbase
	.size	pop, .-pop
	.align	2
	.global	isempty
	.type	isempty, %function
isempty:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	ldr	r3, .L18
	ldr	r3, [r3]
	cmp	r3, #0
	bne	.L16
	mov	r3, #1
	b	.L17
.L16:
	mov	r3, #0
.L17:
	mov	r0, r3
	sub	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L19:
	.align	2
.L18:
	.word	sp
	.size	isempty, .-isempty
	.section	.rodata
	.align	2
.LC2:
	.ascii	"malloc fail\000"
	.align	2
.LC3:
	.ascii	"push data i :\000"
	.align	2
.LC4:
	.ascii	"%d\000"
	.align	2
.LC5:
	.ascii	"push data name :\000"
	.align	2
.LC6:
	.ascii	"%s\000"
	.align	2
.LC7:
	.ascii	"pop data : %d, %s\012\000"
	.align	2
.LC8:
	.ascii	"stack empty\000"
	.align	2
.LC9:
	.ascii	"empty\000"
	.align	2
.LC10:
	.ascii	"not empty\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #56
	ldr	r3, .L37
	ldr	r3, [r3]
	mov	r2, r3
	mov	r3, r2
	mov	r3, r3, asl #2
	add	r3, r3, r2
	mov	r3, r3, asl #2
	mov	r0, r3
	bl	malloc
	mov	r3, r0
	mov	r2, r3
	ldr	r3, .L37+4
	str	r2, [r3]
	ldr	r3, .L37+4
	ldr	r3, [r3]
	cmp	r3, #0
	bne	.L21
	ldr	r0, .L37+8
	bl	puts
	mvn	r3, #0
	b	.L36
.L21:
	ldr	r3, .L37+12
	ldr	r3, [r3]
	ldr	r3, [r3, #4]
	ldr	r2, [r3, #4]
	sub	r2, r2, #1
	str	r2, [r3, #4]
	ldr	r3, [r3, #4]
	cmp	r3, #0
	bge	.L23
	ldr	r3, .L37+12
	ldr	r2, [r3]
	ldr	r3, .L37+12
	ldr	r3, [r3]
	ldr	r3, [r3, #4]
	mov	r0, r2
	mov	r1, r3
	bl	__srget_r
	mov	r3, r0
	b	.L24
.L23:
	ldr	r3, .L37+12
	ldr	r3, [r3]
	ldr	r2, [r3, #4]
	ldr	r3, [r2]
	add	r1, r3, #1
	str	r1, [r2]
	ldrb	r3, [r3]	@ zero_extendqisi2
.L24:
	str	r3, [fp, #-8]
	b	.L25
.L35:
	ldr	r3, [fp, #-8]
	cmp	r3, #112
	bne	.L26
	ldr	r0, .L37+16
	bl	printf
	sub	r3, fp, #28
	ldr	r0, .L37+20
	mov	r1, r3
	bl	scanf
	ldr	r0, .L37+24
	bl	printf
	sub	r3, fp, #28
	add	r3, r3, #4
	ldr	r0, .L37+28
	mov	r1, r3
	bl	scanf
	ldr	r3, [fp, #-12]
	str	r3, [sp]
	sub	r3, fp, #28
	ldmia	r3, {r0, r1, r2, r3}
	bl	push
	b	.L27
.L26:
	ldr	r3, [fp, #-8]
	cmp	r3, #111
	bne	.L28
	bl	isempty
	mov	r3, r0
	cmp	r3, #0
	bne	.L29
	sub	r3, fp, #52
	mov	r0, r3
	bl	pop
	sub	ip, fp, #28
	sub	lr, fp, #52
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldr	r3, [lr]
	str	r3, [ip]
	ldr	r2, [fp, #-28]
	sub	r3, fp, #28
	add	r3, r3, #4
	ldr	r0, .L37+32
	mov	r1, r2
	mov	r2, r3
	bl	printf
	b	.L27
.L29:
	ldr	r0, .L37+36
	bl	puts
	b	.L27
.L28:
	ldr	r3, [fp, #-8]
	cmp	r3, #101
	bne	.L27
	bl	isempty
	mov	r3, r0
	cmp	r3, #0
	bne	.L31
	ldr	r3, .L37+40
	ldr	r3, [r3]
	cmp	r3, #0
	bne	.L32
.L31:
	ldr	r0, .L37+44
	bl	puts
	b	.L27
.L32:
	ldr	r0, .L37+48
	bl	puts
.L27:
	ldr	r3, .L37+12
	ldr	r3, [r3]
	ldr	r3, [r3, #4]
	ldr	r2, [r3, #4]
	sub	r2, r2, #1
	str	r2, [r3, #4]
	ldr	r3, [r3, #4]
	cmp	r3, #0
	bge	.L33
	ldr	r3, .L37+12
	ldr	r2, [r3]
	ldr	r3, .L37+12
	ldr	r3, [r3]
	ldr	r3, [r3, #4]
	mov	r0, r2
	mov	r1, r3
	bl	__srget_r
	mov	r3, r0
	b	.L34
.L33:
	ldr	r3, .L37+12
	ldr	r3, [r3]
	ldr	r2, [r3, #4]
	ldr	r3, [r2]
	add	r1, r3, #1
	str	r1, [r2]
	ldrb	r3, [r3]	@ zero_extendqisi2
.L34:
	str	r3, [fp, #-8]
.L25:
	ldr	r3, [fp, #-8]
	cmp	r3, #113
	bne	.L35
	ldr	r3, .L37+4
	ldr	r3, [r3]
	mov	r0, r3
	bl	free
	mov	r3, #0
.L36:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	ldmfd	sp!, {fp, lr}
	bx	lr
.L38:
	.align	2
.L37:
	.word	size
	.word	sbase
	.word	.LC2
	.word	_impure_ptr
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC8
	.word	sp
	.word	.LC9
	.word	.LC10
	.size	main, .-main
	.ident	"GCC: (Sourcery CodeBench Lite 2014.05-28) 4.8.3 20140320 (prerelease)"
