
;TEST TEST TEST

global _GetMemSize ; does not work correctly

_GetMemSize:
	push 	ebp 	
	mov 	ebp, esp 	
	push 	eax 	
	push 	edx 	
	mov 	eax, 0 	;EAX ist Z�hler f�r die MBs
	mov 	edx, 0x1EFFFC 	;EDX auf 3 Bytes vor die 2 MB Grenze setzen
.1:
	inc 	eax 	
	mov 	DWORD [edx], 0xAAAAAAAA 	;0xAAAAAAAA an die Speicherstelle schreiben
	mov 	ebx, [edx] 	;Speicherstelle wieder lesen
	add 	edx, 0x100000 	;Adresse um 1 MB erh�hen
	cmp 	ebx, 0xAAAAAAAA 	;Stimmt gelesener Wert mit dem geschriebenen �berein?
	je 	.1 	
	pop 	edx 	
	;pop 	eax 	
	mov 	esp, ebp 	
	pop 	ebp 	
	ret 
