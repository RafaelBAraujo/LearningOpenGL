<h3>Instruções para a compilação do código</h3>

Em primeiro lugar, para a compilação é necessário que você tenha instalado em seu computador as seguintes livrarias:

- SDL2
- Assimp
- GLEW
- glm

Se você usa <b>Linux</b>, para instalar as livrarias SDL2, GLEW e glm, basta digitar na linha de comando:

> sudo apt-get install libsdl2-dev && libglew-dev && libglm-dev

A livraria Assimp pode ser baixada no seguinte link:

<a href="https://github.com/assimp/assimp/releases">https://github.com/assimp/assimp/releases</a>

Para instalá-la, descompacte a pasta com o código fonte que você baixou, e, dentro desta, crie uma nova pasta:

> mkdir (NOME_DA_PASTA)
> cd (NOME_DA_PASTA)

e, estando no diretório da nova pasta, digite os seguintes comandos para construir a livraria e concluir a instalação:

> sudo make
> sudo make install

Instalada as livrarias, já é possível compilar o meu código. Para isso, basta digitar os seguintes comandos dentro do diretório raíz, BufferData/ :

> sudo make

Isso executará o Makefile, que compilará o código e criará um executável com o nome 'output'. Para executá-lo:

> ./output

O SDL2 é uma API que fornece uma abstração para a manipulação de janelas, leitura de eventos gerados por teclado, mouse, joystick, ..etc, para o acesso de saída de áudio, e hardwares gráficos. Eu uso a SDL2 para sustituir algumas das funcionalidades da livraria GLUT que já não são compatíveis com a versão do OpenGL que procuro atingir nesse programa .

A livraria Assimp auxilia na leitura de arquivos que descrevem mexas (ou "meshes"), como por exemplo arquivos .obj e .mtl, que são os que eu utilizo aqui. É a mais popular e mais completa.

A livriaria GLEW possui todas as funcionlidades das livrarias do OpenGL gl.h e glu.h. Ela descarta algumas das funções que já se tornaram "descontinuadas" (cujo uso não é mais aconselhado; ou "<i>deprecated</i>"), e carrega 
