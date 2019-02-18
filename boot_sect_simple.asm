; Infinite loop (e9 fd ff)
start:
	mov ah,  0x0e
	mov al, '<'
	int 0x10
	mov al, '0'
	int 0x10
	mov al, '/'
	int 0x10
	mov al, ' '
	int 0x10
	mov al, 'D'
	int 0x10
	mov al, 'a'
	int 0x10
	mov al, 'b'
	int 0x10
	mov al, ' '
	int 0x10
	mov al, 'o'
	int 0x10
	mov al, 'n'
	int 0x10
	mov al, ' '
	int 0x10
	mov al, 't'
	int 0x10
	mov al, 'h'
	int 0x10
	mov al, 'e'
	int 0x10
	mov al, ' '
	int 0x10
	mov al, 'h'
	int 0x10
	mov al, 'a'
	int 0x10
	mov al, 't'
	int 0x10
	mov al, 'e'
	int 0x10
	mov al, 'r'
	int 0x10
	mov al, 's'
	int 0x10
jmp $

; Fill with 510 zeros minus the size of the previous code
times 510-($-$$) db 0
; Magic number
dw 0xaa55

