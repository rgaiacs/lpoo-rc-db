RM = rm -f

.PHONY: default
default: error

.PHONY: error
error:
	@echo "ERRO Selecione uma opção para o make\n"
	@grep "^[a-z_]*:" Makefile | awk '{print " - "$$1}' | tr -d :

.PHONY: all
all:
	@for id in $$(ls [0-9][0-9][0-9]*-db.tex); do \
		id=$$(echo $$id | head -c 3); \
		./install.sh --default -A $$id; \
	done

.PHONY: lista
lista:
	@if [ -z "$(LISTA)" ]; then echo "Defina a variável LISTA"; exit 1; fi
	./install.sh --default -A $(LISTA)

.PHONY: linux
linux:
	./install.sh --default -A 101

.PHONY: ccpp
ccpp:
	./install.sh --default -A 103

.PHONY: test
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

.PHONY: clean
clean:
	$(RM) *.acn
	$(RM) *.acr
	$(RM) *.alg
	$(RM) *.aux
	$(RM) *.bbl
	$(RM) *.blg
	$(RM) *.dvi
	$(RM) *.fdb_latexmk
	$(RM) *.fls
	$(RM) *.glg
	$(RM) *.glo
	$(RM) *.gls
	$(RM) *.idx
	$(RM) *.ilg
	$(RM) *.ind
	$(RM) *.ist
	$(RM) *.lof
	$(RM) *.log
	$(RM) *.lot
	$(RM) *.maf
	$(RM) *.mtc
	$(RM) *.mtc0
	$(RM) *.nav
	$(RM) *.nlo
	$(RM) *.out
	$(RM) *.pdf
	$(RM) *.pdfsync
	$(RM) *.ps
	$(RM) *.snm
	$(RM) *.synctex.gz
	$(RM) *.tar
	$(RM) *.toc
	$(RM) *.tdo
	$(RM) *.vrb
	$(RM) *.xdy

.PHONY: purge
purge: clean
	
