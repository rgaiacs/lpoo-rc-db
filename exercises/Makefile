LISTA=padrao.pdf \
      linux.pdf \
      linux-03-05-2013-bash.pdf \
      linux-10-05-2013-gawk.pdf \
      linux-17-05-2013-git.pdf \
      c.pdf \
      c-17-05-2013-io.pdf

all: ${LISTA}

%.pdf: %.tex
	latexmk -pdf $<
	-tar -cf $(subst .tex,.tar,$<) `grep 'aux/' $(subst .tex,.fls,$<) | uniq | sed 's/INPUT //'`

clean:
	-rm *.acn
	-rm *.acr
	-rm *.alg
	-rm *.aux
	-rm *.bbl
	-rm *.blg
	-rm *.dvi
	-rm *.fdb_latexmk
	-rm *.fls
	-rm *.glg
	-rm *.glo
	-rm *.gls
	-rm *.idx
	-rm *.ilg
	-rm *.ind
	-rm *.ist
	-rm *.lof
	-rm *.log
	-rm *.lot
	-rm *.maf
	-rm *.mtc
	-rm *.mtc0
	-rm *.nav
	-rm *.nlo
	-rm *.out
	-rm *.pdf
	-rm *.pdfsync
	-rm *.ps
	-rm *.snm
	-rm *.synctex.gz
	-rm *.tar
	-rm *.toc
	-rm *.tdo
	-rm *.vrb
	-rm *.xdy
