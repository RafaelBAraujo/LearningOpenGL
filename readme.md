<h2>Instruções para a movimentação da câmera</h2>

- A tecla 'd' rotaciona a matriz ModelView no eixo y, sentido anti-horário.
- A tecla 'a' rotaciona a matriz ModelView no eixo y, sentido horário.
- A tecla 'w' escalona a matriz ModelView positivamente.
- A tecla 's' escalona a matriz ModelView negativamente.

<br/>
<h2>Instruções para a compilação do código</h2>

Em primeiro lugar, para a compilação é necessário que você tenha instalado em seu computador as seguintes livrarias:

- SDL2
- Assimp
- GLEW
- GLM

<h3>Instruções para <b>Linux</b></h3>

Para instalar as livrarias SDL2, GLEW e GLM, basta digitar na linha de comando:

> sudo apt-get install libsdl2-dev && libglew-dev && libglm-dev

A livraria Assimp pode ser baixada no seguinte link:

<a href="https://github.com/assimp/assimp/releases">https://github.com/assimp/assimp/releases</a>

Para instalá-la, descompacte a pasta com o código-fonte que você baixou, e, dentro desta, crie uma nova pasta:

> mkdir (NOME_DA_PASTA)

> cd (NOME_DA_PASTA)

e, estando no diretório da nova pasta, digite os seguintes comandos para construir a livraria e concluir a instalação:

> sudo make

> sudo make install

Instalada as livrarias, já é possível compilar o meu código. Para isso, basta digitar os seguintes comandos dentro do diretório raíz, BufferData/ :

> sudo make

Isso executará o Makefile, que compilará o código e criará um executável com o nome 'output'. Para executá-lo, digite:

> ./output


<h4>Sobre as livrarias</h4>

<h5>SDL2</h5>
O SDL2 é uma API que fornece uma abstração para a manipulação de janelas, leitura de eventos gerados por teclado, mouse, joystick, para o acesso de saída de áudio, e também para a manipulação de hardwares gráficos utilizando o prórpio OpenGL. Eu uso a SDL2 para sustituir algumas das funcionalidades da livraria GLUT que já não são compatíveis com a versão do OpenGL que procuro atingir nesse programa.


<h5>Assimp</h5>
A livraria Assimp auxilia na leitura de arquivos que descrevem mechas, como por exemplo arquivos .obj e .mtl, que são os que eu utilizo aqui. É a mais popular e provavelmente a mais completa.


<h5>GLEW - OpenGL Extension Wrangler</h5>
A livriaria GLEW possui todas as funcionlidades das livrarias do OpenGL gl.h e glu.h, e diferente dessas, carrega as funções do OpenGL não em tempo de compilação, mas em tempo de execução. Ela descarta algumas das funções que já se tornaram "descontinuadas" (cujo uso não é mais aconselhado; ou "<i>deprecated functions</i>"), e suporta funcionalidades mais recentes do OpenGL, como a criação de "Vertex Array Objects" e "Vertex Buffer Objects".


<h5>GLM - OpenGL Mathematics</h5>
A livraria GLM possui algumas definições e convenções que ajudam a tornar mais prático cálculos e manipulação de matrizes e vetores, e a transferir dados entre código C++ e GLSL, OpenGL Shading Language (no qual é baseado).
