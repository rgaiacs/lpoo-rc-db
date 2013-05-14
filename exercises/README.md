# Banco de Questões da Rede Colaborativa do LPOO

O Banco de Questões utiliza o pacote `exercise`.

Para criar exercícios, utilize o arquivo `padrao-db.tex` como template.

Não é necessário criar um outro arquivo para ver o resultado. Utilize
os comandos prontos de compilação.

# Compilação

Para compilar todas as listas de exercícios, utilize

    $ make all

Para compilar apenas uma lista, utilize

    $ make lista LISTA=<ID>

onde ID  é o id do assunto desejado.

Ex.: `make lista LISTA=101`, `make lista LISTA=103`

Para listas manuais, crie seu arquivo `meu.tex` (possivelmente uma
cópia de padrao.tex) e compile com

    $ make meu.pdf

## Listas avançadas

Para gerar uma lista com opções especiais, use o script `./install.sh`

A chamada usual é 

    $ ./install.sh -A <ID> --default

que compila o assunto ID com todos os exercícios sem respostas.

Você também pode especificar subconjuntos de exercícios. Você pode
selecionar por sub-assuntos, por dificuldade, ou problemas específicos.

Além disso, podemos selecionar se queremos apenas os exercícios,
apenas as respostas, ou ambos.

Para verificar todas opções, use

    $ ./install.sh -h

# Convenções

## Nomes de arquivos

Os nomes de arquivos devem ser `XXX-<Nome>-db.tex`. 

`XXX` deve ser o ID do assunto
e <Nome> deve ser o nome do assunto como irá aparecer no título da lista.
Preferencialmente coloque maiúscula na primeira letra e minúscula nas outras.

Ex.: `101-Linux-db.tex`, `103-C,C++-db.tex`.

## Formato dos exercícios

Cada arquivo `XXX-<Nome>-db.tex` é composto de perguntas e respostas.
As perguntas devem ter sempre um label para identificar o exercício,
uma dificuldade e uma tag.

O label é um ID que começa no 0001 e vai até 9999. Não pule nenhum número
e escreva com os 4 dígitos.

O formato dos exercícios é

    \begin{Exercise}[label={XXXX}, difficulty={Y}, origin={BAR}]
      Pergunta
      \Question Item A, se houver
      \Question Item B, se houver
    \end{Exercise}

O formato das respostas é

    \begin{Answer}[ref={XXXX}]
      Resposta.
      \Question Resposta do item A, se houver
      \Question Resposta do item B, se houver
    \end{Answer}

Não use enumerate, use \\Question.

Não use verbatim ou verb, use o pacote listings.

Verifique o arquivo `padrao-db.tex` como exemplo.
