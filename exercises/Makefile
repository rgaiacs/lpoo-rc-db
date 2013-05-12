linux:
	./install.sh --default -A 101

ccpp:
	./install.sh --default -A 103

test:
	@for answer in noanswer answeronly withanswers; do \
		./install.sh --debug --$$answer -a -A 101; \
		for origin in bash git gawk; do \
			./install.sh --debug --$$answer -o $$origin -A 101; \
		done; \
		for dif in 0 1 2 3; do \
			./install.sh --debug --$$answer -d $$dif -A 101; \
		done; \
		for sp in 0002 0005 0008; do \
			./install.sh --debug --$$answer -s $$sp -A 101; \
		done; \
	done

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
