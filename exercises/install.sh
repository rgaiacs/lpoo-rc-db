#!/bin/bash

#### Variables

#debug_is_on="true"
#dont_process="true"
pdfcompiler="latexmk -silent -pdf"
#pdfcompiler="latexmk -pdf"

#### Functions 

function printatscreen() {
  echo -en "\033[0;32m$*\033[0m"
}

function warningprint() {
  echo -en "\033[0;33m$*\033[0m"
}

function errorprint() {
  echo -en "\033[0;31m$*\033[0m"
}

function print_help() {
  printatscreen "Gerador de pdf dos exercicios\n"
  printatscreen "Uso:\n"
  printatscreen "  ./install.sh [opcoes]\n\n"
  printatscreen "Possiveis opcoes:\n"
  printatscreen "  -h|--help|--ajuda\n"
  printatscreen "    Imprime esta ajuda\n\n"
  printatscreen "  --debug\n"
  printatscreen "    Liga o debug\n\n"
  printatscreen "  --dont_process\n"
  printatscreen "    Nao processa o pdf, imprime o nome do arquivo ao inves\n\n"
  printatscreen "  -A|--assunto|--subject <ID>\n"
  printatscreen "    Define o assunto\n\n"
  printatscreen "  -a|--all|--tudo\n"
  printatscreen "    Seleciona todos os problema (default)\n\n"
  printatscreen "  -o|--origin|--origem <ORI>\n"
  printatscreen "    Seleciona a origem <ORI>\n\n"
  printatscreen "  -d|--dificuldade|--difficulty <D>\n"
  printatscreen "    Seleciona as dificuldades <D>, separadas por virgula\n\n"
  printatscreen "  -s|--id <IDS>\n"
  printatscreen "    Seleciona problema com ids IDS que devem estar separadas\n"
  printatscreen "    por vírgula, sem espaço\n\n"
  printatscreen "  --noanswer|--semrespostas\n"
  printatscreen "    Imprime apenas as perguntas (padrao)\n\n"
  printatscreen "  --answeronly|--sorespostas\n"
  printatscreen "    Imprime apenas as respostas\n\n"
  printatscreen "  --withanswers|--comrespostas\n"
  printatscreen "    Imprime perguntas e respostas\n\n"
  printatscreen "  --default|--padrao\n"
  printatscreen "    Seleciona os parametros padroes:\n"
  printatscreen "    Todos os problemas, sem respostas. Necessita do assunto.\n"
  printatscreen "    Equivale a ./install.sh -A <ID> -a --noanswer\n"
}

function parse_arguments() {
  while [ $# -gt 0 ]
  do
    case "$1" in
      -h|--help|--ajuda)
        print_help
        exit 0
        ;;
      --debug)
        debug_is_on="true"
        ;;
      -A|--assunto|--subject) 
        subject="$2"
        if ls $subject*-db.tex &> /dev/null; then
          subdb=$(ls ${subject}*-db.tex)
          subname=${subdb//-db.tex/}
          subname=${subname//$subject-/}
        else
          errorprint "Nao for encontrado assunto com ID $subject\n"
          exit 1
        fi
        shift
        ;;
      -a|--all|--tudo)
        subset="all"
        ;;
      -o|--option|--origem)
        origin="$2"
        subset="[origin={$origin}]"
        shift
        ;;
      -d|--difficulty|--dificuldade)
        difficulty="$2"
        subset="[difficulty={$difficulty}]"
        shift
        ;;
      -s|--id)
        specific="$2"
        subset="[label={$specific}]"
        shift
        ;;
      --noanswer|--semrespostas)
        answer="[noanswer]"
        ;;
      --answeronly|--sorespotas)
        answer="[answeronly]"
        ;;
      --withanswers|--comrespotas)
        answer="[with-answers]"
        ;;
      --default|--padrao)
        subset="all"
        answer="[noanswer]"
        ;;
    esac
    shift
  done

  if [ "$subset" == "all" ]; then
    if [ -z "$subdb" ]; then
      errorprint "Assunto nao foi definido, flag -a/--all ignorada.\n"
      exit 1
    fi
  fi
  if [ ! -z "$origin" ]; then
    if [ -z "$subdb" ]; then
      errorprint "Assunto nao foi definido, mas origem $origin eh pedido.\n"
      exit 1
    fi
    origins=$(awk 'BEGIN{regex="origin={.*}"}
      {if (match($0,regex)){
        tag=substr($0,RSTART+8,RLENGTH-9)
        print tag 
      }}' $subdb | sort | uniq)
    if [ -z "$(echo $origins | grep -w $origin)" ]; then
      errorprint "'$origin' nao foi encontrado\n"
      exit 1
    fi
  fi
  if [ ! -z "$difficulty" ]; then
    if [ -z "$subdb" ]; then
      errorprint "Assunto nao foi definido, mas dificuldade eh pedida.\n"
      exit 1
    fi
  fi
  if [ ! -z "$specific" ]; then
    if [ -z "$subdb" ]; then
      errorprint "Assunto nao foi definido, mas problemas sao pedidos.\n"
      exit 1
    fi
  fi
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
      ;;
    O)  get_origin
        subset="[origin={$origin}]"
      ;;
    D)  get_difficulty
        subset="[difficulty={$difficulty}]"
      ;;
    E)  get_specific
        subset="[label={$specific}]"
      ;;
    *)  errorprint "Selecao nao encontrada\n"
        exit 1
      ;;
  esac
}

function set_file_name() {
  if [ -z "$subset" ]; then
    pdf_file_name="${subdb//-db.tex/.pdf}"
  elif [ ! -z "$origin" ]; then
    pdf_file_name="${subdb//-db.tex/-origin-$origin.pdf}"
  elif [ ! -z "$difficulty" ]; then
    pdf_file_name="${subdb//-db.tex/-diff-$difficulty.pdf}"
  elif [ ! -z "$specific" ]; then
    pdf_file_name="${subdb//-db.tex/-specific.pdf}"
  else
    errorprint "Alguma coisa errada aconteceu. Reporte esse bug.\n" 
    exit 1
  fi
  if [ "$answer" == "[answeronly]" ]; then
    pdf_file_name=${pdf_file_name//.pdf/-only-answers.pdf}
  elif [ "$answer" == "" ]; then
    pdf_file_name=${pdf_file_name//.pdf/-with-answers.pdf}
  elif [ "$answer" != "[noanswer]" ]; then
    errorprintif "Alguma coisa errada aconteceu. Reporte esse bug.\n"
    exit 1
  fi
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
      ;;
    2)  answer=""
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
  if [ -z "$(echo $origins | grep -w $origin)" ]; then
    errorprint "'$origin' nao foi encontrado\n"
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

parse_arguments "$@"
if [ -z "$subject" ]; then
  read_subject
  newline
fi
if [ -z "$subset" ]; then
  read_subset
  newline
elif [ $subset == "all" ]; then
  subset=""
fi
if [ -z "$answer" ]; then
  with_answer
  newline
elif [ "$answer" == "[with-answers]" ]; then
  answer=""
fi
generate_tmp_file
set_file_name
if [ ! -z "$dont_process" ]; then
  cat $tmp_file_name
  rm -f ${tmp_file_name//.tex/}*
  exit 1
fi
if [ ! -z "$debug_is_on" ]; then
  echo $pdf_file_name
  rm -f ${tmp_file_name//.tex/}*
  exit 0
fi
generate_pdf

exit 0


