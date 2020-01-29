# Pattern for Bachelor/ Master -thesis

## Questions and reports to
<s0559122@htw-berlin.de>

### Description of the project

This repository should be a pattern for your Bachelor / Master thesis. It is originally designed by **fbroemer** (<https://github.com/fbroemer>)
The project supports 

- Creating your own Cover page easily
- Table of contents
- Table of figures
- List of tables
- List of acronyms
- Bibliography
- ...


### Structure:
- thesis.tex  --> Contains the Cover page and all settings for the whole thesis
- images/     --> Contains all used images. Name must be unique
- output/     --> Contains the created files from Makefile
- text/       --> Contains the text of your thesis. It is recommend to use for every chapter a new file
- full_bachelor_thesis/   --> My complete Bachelorthesis. Everthing is free to use so don't be shy to copy stuff and knowledge
- Makefile

For some examples and special effects look at full_bachelor_thesis/
There are some germans comments, so this is a good start for learning a new language


### Getting started:
**Note: Linux only; Tested on Ubuntu 16.04 xenial; And all required Latex packages installed**
```bash
~$  git clone ...
~$  cd bachelor_project/
~$  cd thesis/
~$  make
```
In folder output/ are the created files with the pdf-file. The pdf-file is automatically executed from the Makefile.
To disable this remove line 2 in the Makefile.


### How to insert text to chapter "Introduction" ?
```bash
~/bachelor_project/$  cd text/
~/bachelor_project/$  vi introduction.tex //Create a new file or open the existing

Insert your text
Save with ":wq" //vi specific

~/bachelor_project/$  cd ../
~/bachelor_project/$  vi thesis.tex

Add "\input{text/introduction}" between \begin - \end{document}
Save with ":wq" //vi specific

~/bachelor_project/$  make
```
Have fun

