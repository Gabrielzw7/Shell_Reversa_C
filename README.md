<h2>Shell Reversa C</h2>
<p>Shell reversa simples criada em C.</p>

<p>O Objetivo deste código é aprimorar os conhecimentos em C, especificamente em Windows API e Socket.</p>

<p><i><b>Até o momento (08/24) não detectada pelo Windows Defender.</b></i></p>

<h2>Compilação:</h2>
No Linux para Windows:</br>
x86_64-w64-mingw32-gcc shell.c -o shell.exe -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc -lWs2_32 -mwindows</p>

<p>No Windows:</br>
gcc shell.c -o shell.exe -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc -lWs2_32 -mwindows</p>

<h2>Próximos passos:</h2>
[  ] - Implementar conexão criptografada utilizando OpenSSL;</br>
[  ] - Função de upload/download de arquivos;</br>
[  ] - Ofuscar o código;</br>
[  ] - Migração de processo via Process injection;</br>
[  ] - Persistência.</br>
