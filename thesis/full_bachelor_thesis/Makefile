all: delete compile
	evince output/thesis.pdf

delete:
	ls -d output/* | grep -v ".pdf" | xargs rm
compile:
	pdflatex -output-directory output/ thesis.tex
	pdflatex -output-directory output/ thesis.tex


