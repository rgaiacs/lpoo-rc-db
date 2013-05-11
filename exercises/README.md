# Banco de Questões da Rede Colaborativa do LPOO

O Banco de Questões utiliza o pacote `exercise`.

De toda forma, acredita-se que você não terá dificuldades se utilizar os
arquivos `padrao.tex` e `padrao-db.tex` como templates.

# Compilação

Para compilar todas as listas de exercícios, utilize

    $ make -B

Para compilar apenas uma lista, utilize

    $ make -B LISTA=lista_desejada.pdf

onde `lista_desejada.pdf` é o arquivo que deseja.

A flag `-B` é necessária pois as dependência são verificadas pelo `latexmk`.

# Convenções

## Nomes de arquivos

Os nomes de arquivos devem ser em letras minúsculas e com `_` no lugar de
espaços.

Existem três tipos de arquivos:

1. Banco de dados das questões (por assunto).

   Para o assunto FOO de código XXX, o arquivo deve-se chamar `foo-db.tex`.

2. Lista com todas as questões de um assunto.

   Para o assunto FOO de código XXX, o arquivo deve-se chamar `foo.tex`.

3. Lista com as questões de uma dada aula.

   Sendo a aula do dia DD/MM/AAAA sobre o assunto FOO de código XXX em que foi
   abordado o tema BAR, o arquivo deve-se chamar `foo-DD-MM-AAAA-bar.tex` (ou
   `foo-DD-MM-AAAA-bar.tex`).
