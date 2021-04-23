Repositório do Projeto Final da Disciplina PQI-3403
===================================================

Esses são os arquivos que integram os scripts em python e o código fonte
para o programa em C utilizados no projeto final da disciplina.

Os dois arquivos em python, `OregonatorPython` e `2DPlotOregonator` são,
respectivamente, um script para resolver as equações diferenciais com o uso do
método BDF (imprimindo em `stdout` os resultados) e um script para representar
graficamente os resultados obtidos com o uso do método das linhas.

Vale notar que o script em python é a forma mais eficiente de se resolver o
sistema de EDOs; como o programa em C foi executado algumas poucas vezes, para
o caso reação-difusão, não se fez um esforço muito grande em sua otimização.

Para utilizar o script em python, basta executá-lo com as opções desejadas. Por
exemplo, para resolver o sistema com k₁ diferente e concentração de A duas vezes
maior, basta:

```
./OregonatorPython --k1 2.45 --conc_A 0.12
```
O uso completo está disponível com a execução de `./OregonatorPython --help`.

Como já mencionado, o programa para o sistema reação-difusão é lento; entretanto,
caso exista algum interesse em se utilizar o programa, basta clonar esse
repositório e compilá-lo:

```
git clone https://github.com/pedro-callil/OregonatorPQI3403
cd OregonatorPQI3403
make
```

O programa, denominado `OregonatorSolve`, pode então ser executado, como
exemplificado abaixo para os dados fornecidos. A título de exemplo variamos o
valor de k₃ e armazenamos os resultados em `results_reaction_diffusion.csv`,
ocultando as mensagens impressas pelo programa:

```
./OregonatorSolve -k 15.23 -S results_reaction_diffusion.csv -q
```

O uso completo do programa é acessível através de `./OregonatorSolve -h`.


Autores
-------

André Ferreira <afs.souza@usp.br>

Giovani Vicentim <giovanialves@usp.br>

Luiz Amorim <l.henrique@usp.br>

Pedro Callil <pedrocallil@usp.br>

