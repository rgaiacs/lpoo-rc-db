LISTA=padrao.pdf \
      linux.pdf \
      linux-101.pdf \
      gawk-101.pdf

all: ${LISTA}

%.pdf: %.tex
	latexmk -pdf $<

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
	-rm *.pdfsync
	-rm *.ps
	-rm *.snm
	-rm *.synctex.gz
	-rm *.toc
	-rm *.vrb
	-rm *.xdy
	-rm *.tdo
