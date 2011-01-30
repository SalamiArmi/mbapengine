global ArgonStrLen

len resb	4

ArgonStrLen:
	enter 0, 0
	pusha
	mov	eax, 0x0
	
_do:
	mov	cl, [ebx]
	inc	ebx
	inc	eax
	cmp	cl, 0x0
	jz	_exit
	jmp	_do
	
_exit:
	mov	[len], eax
	popa
	mov eax, [len]
	leave
	ret