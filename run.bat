cd gen
python main.py
xelatex -shell-escape template.tex
xelatex -shell-escape template.tex
cd ..
copy .\gen\template.pdf template.pdf
cd gen
del template.pdf content.tex *.log *.toc *.aux *.pyg