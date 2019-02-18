[org 0x7c00]

mov bx, DAB
call print
call print_nl
call print_nl
mov bx, DAB2
call print

%include "print.asm"

DAB:
	db '<0/ dab on the haters', 0
DAB2:
	db '<0/', 0

; zero padding and magic bios number
times 510-($-$$) db 0
dw 0xaa55
