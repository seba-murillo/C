char_device simulator module for linux

use 'make' to build


Que hace:
	El modulo simula un char device con una encriptacion simple: +10 al valor del char.
	
	Tiene 2 modos:
		PLAIN_TEXT - escribe y lee sin cambiar los mensajes (no encrypt)
		CYHPER_TEXT - aplica la "encriptacion" al leer y escribir (+/- 10)

	El programa de testeo realiza lo siguiente:
	1) escribe una cadena en modo PLAIN: 							[ABCDEF]
	2) lee la misma cadena en modo PLAIN:							[ABCDEF]
	3) escribe la misma cadena en modo CYHPER						[ABCDEF]
	4) lee esa cade en modo PLAIN, que como fue encriptada, queda:  [KLMNOP]
	5) lee la cadena en modo CYHPER, desencriptandola:				[ABCDEF]

Procedimiento:
	1) abrir terminal
	2) [make]. Esto compile el modulo (chardevso1.ko) y el programa de testeo (test_char_device)
	3) insertar el modulo: [sudo insmod chardevso1.ko]
	4) ejecutar programa de testo (requiere permisos): [sudo ./test_char_device]
	5) ver el log del kernel: [sudo dmesg]
	
	*recordar remover modulo: sudo rmmod chardevso1.ko

	-Sebastian Murillo
