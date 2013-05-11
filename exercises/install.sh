#!/bin/bash

#### Variables

#debug_is_on="true"
pdfcompiler="latexmk -silent -pdf"

#### Functions 

function printatscreen() {
  echo -en "\033[0;32m"$*"\033[0m"
}

function warningprint() {
  echo -en "\033[0;33m"$*"\033[0m"
}

function errorprint() {
  echo -en "\033[0;31m"$*"\033[0m"
}

function read_subject() {
  printatscreen "Bem vindo!\n"
  printatscreen "Este script compila os exercicios de acordo com o assunto e as suas\n"
  printatscreen "especificacoes.\n"
  newline
  printatscreen "Indique o ID do assunto: "
  read subject
  if ls $subject*-db.tex &> /dev/null
  then
    subdb=$(ls ${subject}*-db.tex)
    subname=${subdb//-db.tex/}
    subname=${subname//$subject-/}
  else
    errorprint "Nao foi encontrado assunto com ID $subject\n"
    exit 1
  fi

  newline
  printatscreen "Assunto encontrado: ${subdb//-db.tex/}\n"
  printatscreen "Confirma: (S/N): "
  read sorn
  newline
  while [ $sorn != "N" -a $sorn != "S" ]
  do
    warningprint "Esperado S ou N: "
    read sorn
  done
  if [ $sorn == "N" ]; then
    errorprint "Assunto errado encontrado. Verifique ID $subject\n"
    exit 1
  fi
}

function read_subset() {
  printatscreen "Que selecao de exercicios voce quer?\n"
  printatscreen " A -  Todos\n"
  printatscreen " O -  Com assunto especifico\n"
  printatscreen " D -  Com dificuldade especifica\n"
  printatscreen " E -  IDs especificos\n"
  
  read subset
  newline
  case $subset in
    A)  subset=""
        pdf_file_name="${subdb//-db.tex/.pdf}"
      ;;
    O)  get_origin
        pdf_file_name="${subdb//-db.tex/-origin-$origin.pdf}"
        subset="[origin={$origin}]"
      ;;
    D)  get_difficulty
        pdf_file_name="${subdb//-db.tex/-diff-$difficulty.pdf}"
        subset="[difficulty={$difficulty}]"
      ;;
    E)  get_specific
        pdf_file_name="${subdb//-db.tex/-specific.pdf}"
        subset="[label={$specific}]"
      ;;
    *)  errorprint "Selecao nao encontrada\n"
        exit 1
      ;;
  esac
}

function with_answer() {
  answer="[noanswer]"
  printatscreen "Choose: \n"
  printatscreen " 0 - Just exercises (default)\n"
  printatscreen " 1 - Just answers \n"
  printatscreen " 2 - Exercises and answers \n"
  read option
  case $option in
    0)  answer="[noanswer]"
      ;;
    1)  answer="[answeronly]"
      pdf_file_name=${pdf_file_name//.pdf/-only-answers.pdf}
      ;;
    2)  answer=""
      pdf_file_name=${pdf_file_name//.pdf/-with-answers.pdf}
      ;;
    *)  answer="[noanswer]"
      answername=""
      ;;
  esac
}

function generate_tmp_file() {
  tmp_file_name="${subdb//-db.tex/}$(cat /dev/urandom | tr -cd 'a-f0-9' | head -c 8).tex"
  cat core.tex > $tmp_file_name
  sed -i "s/SUBJECT/$subject - $subname/" $tmp_file_name
  sed -i "s/SUBDB/$subdb/" $tmp_file_name
  sed -i "s/SUBSET/$subset/" $tmp_file_name
  sed -i "s/ANSWER/$answer/" $tmp_file_name
  if [ ! -z "$debug_is_on" ]; then
    cat $tmp_file_name
    rm -f ${tmp_file_name//.tex/}*
    exit 1
  fi
}

function generate_pdf() {
  ${pdfcompiler} $tmp_file_name
  cp ${tmp_file_name//.tex/.pdf} $pdf_file_name
  rm -f ${tmp_file_name//.tex/}*
}

function get_origin() {
  list_origins
}

function list_origins() {
  origins=$(awk 'BEGIN{regex="origin={.*}"}
    {if (match($0,regex)){
      tag=substr($0,RSTART+8,RLENGTH-9)
      print tag 
    }}' $subdb | sort | uniq)
  printatscreen "As possiveis origens sao: \n"
  warningprint "$origins\n"
  printatscreen "Sua escolha: "
  read origin
  if [ -z "echo $origins | grep -w $origin" ]; then
    errorprint "$origin nao foi encontrado em $origins"
    exit 1
  fi
}

function get_difficulty() {
  printatscreen "Coloque as dificuldades desejadas separadas por , sem espaco\n"
  printatscreen "1-Facil, 2-Medio, 3-Dificil, 4-Muito Dificil\n",
  printatscreen "> "
  read difficulty
}

function get_specific() {
  printatscreen "Coloque os IDs dos exercicios separados por , sem espaco\n"
  printatscreen "> "
  read specific
}

function newline() {
  echo " "
}

####

read_subject
newline
read_subset
newline
with_answer
newline
generate_tmp_file
generate_pdf

exit 0


