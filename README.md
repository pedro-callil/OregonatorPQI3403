OregonatorSolve
===============

Esses são os arquivos que integram os scripts em python e o código fonte
para o programa em C utilizados no projeto final da disciplina.

Os dois arquivos em python, `python_solver.py` e `plot.py` são,
respectivamente, um script para resolver as equações diferenciais com o uso do
método BDF (imprimindo em `stdout` os resultados) e um script para representar
graficamente os resultados obtidos com o uso do método das linhas.

Vale notar que o script em python é a forma mais eficiente de se resolver o
sistema de EDOs; como o programa em C foi executado algumas poucas vezes, para
o caso reação-difusão, não se fez um esforço muito grande em sua otimização.

Entretanto, caso exista algum interesse em se utilizar o programa, basta clonar
esse repositório e compilar o programa:

```
git clone https://github.com/pedro-callil/OregonatorPQI3403
cd OregonatorPQI3403
make
```

Autores
-------

André Ferreira <afs.souza@usp.br>

Giovani Vicentim <giovanialves@usp.br>

Luiz Amorim <l.henrique@usp.br>

Pedro Callil <pedrocallil@usp.br>

