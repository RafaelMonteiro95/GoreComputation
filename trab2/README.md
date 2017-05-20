# Integrantes
Lucas Alexandre Soares		-	9293265  
Rafael Augusto Monteiro		-	9293095  
Giovanna Oliveira Guimarães	-	9293693  

# Compilando e rodando:

Compile com Make all:

```Make all```

Rode com Make Run:

```Make run```

# Controlando a câmera

São implementadas funções de __movimentação__ e __rotação__ da câmera

## Movimentação:

|Tecla|Função|
|-----|------|
|__w__|Anda para frente
|__s__|Anda para trás
|__a__|Anda para a esquerda
|__d__|Anda para a direita

## Rotação:

|Seta|Função
|-----|------|
|__↑__|Olha para cima|
|__↓__|Olha para baixo|
|__←__|Olha para esquerda|
|__→__|Olha para direita|

# Controlando os objetos

É possível aplicar transformações de __translação__, __rotação__ e __escala__ no objeto atualmente selecionado. As tabelas abaixo definem as teclas e suas funcionalidades:

## Selecionar objeto
Tecla|Função
-----|------|
__t__|Seleciona objeto anterior|
__y__|Seleciona próximo objeto|

## Transladar objeto
|Tecla|Função
|-----|------|
|__u__|Translada objeto para esquerda|
|__i__|Translada objeto para direita|

## Rotacionar objeto em torno do eixo x
|Tecla|Função|
|-----|------|
|__j__|Rotaciona no sentido horário|
|__k__|Rotaciona no sentido anti horário|

## Escalar objeto
|Tecla|Função|
|-----|------|
|__n__|Aumenta a escala do objeto em 10%|
|__m__|Diminui a escala do objeto em 10%|


# Makefile rules

`all` compile project  
`run` run executable  
`clean` clean object files and zip/tar  
`zip/tar` compress project folder  

set `debug=1` to compile/run in debug mode   
set `IN=*filename*` to feed a file to the program 
set `OUT=*filename*` to write program output to designed file  
use `CFLAGS+=*flags*` to add *flags*
