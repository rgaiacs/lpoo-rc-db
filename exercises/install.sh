#!/bin/bash

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

  printatscreen "Assunto encontrado: ${subdb//-db.tex/}\n"
  printatscreen "Confirma: (S/N): "
  read sorn
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
  
  read subset
  case $subset in
    A)  subset=""
      ;;
    O)  get_origin
        subset="[origin={$origin}]"
      ;;
    *)  errorprint "Selecao nao encontrada\n"
        exit 1
      ;;
  esac
}

function generate_tmp_file() {
  tmp_file_name="${subdb//-db.tex/}$(cat /dev/urandom | tr -cd 'a-f0-9' | head -c 8).tex"
  cat core.tex > $tmp_file_name
  sed -i "s/SUBJECT/$subject - $subname/" $tmp_file_name
  sed -i "s/SUBDB/$subdb/" $tmp_file_name
  sed -i "s/SUBSET/$subset/" $tmp_file_name
  cat $tmp_file_name
}

function generate_pdf() {
  pdf_file_name="${subdb//-db.tex/.pdf}"
  latexmk -pdf $tmp_file_name
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

####

read_subject
get_origins
read_subset
generate_tmp_file
generate_pdf

exit 0

