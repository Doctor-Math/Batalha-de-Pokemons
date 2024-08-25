# Batalha de Pokemons
Jogo desenvolvido como objeto de trabalho prático no final do semestre da disciplina "Programação e Desenvolvimento de Software I" (PDS I), do curso de Ciência de Dados da Universidade Federal de Minas Gerais (UFMG).

# Pokémon: Eu Escolho Você!

Este repositório explora o fascinante universo dos pokémons através de um jogo desenvolvido em linguagem C. O projeto simula batalhas entre pokémons de dois jogadores, cada um com atributos específicos que influenciam na dinâmica do jogo. A seguir, serão detalhados os processos lógicos que estruturam o código, além dos desafios e erros enfrentados durante o desenvolvimento.

## 📋 Introdução

O jogo simula batalhas de pokémons utilizando um sistema de turnos. Cada jogador começa com um número específico de pokémons, e a partida continua até que todos os pokémons de um dos jogadores sejam derrotados. A força de cada pokémon é determinada pelos atributos de ataque e defesa, que variam conforme o tipo do pokémon envolvido no combate.

O jogo inicia com a leitura de um arquivo pré-definido contendo informações sobre os pokémons de cada jogador. Após o fim das rodadas, o jogo imprime o resultado das batalhas, mostrando quais pokémons venceram e quais foram derrotados, além de declarar o jogador vencedor da partida.

## 🎮 Funcionamento

1. **Inicialização**: Os jogadores 1 e 2 informam o número de pokémons que utilizarão. Esta informação é lida de um arquivo TXT, que contém na primeira linha os números de pokémons de cada jogador.
   
2. **Leitura dos Dados**: As linhas seguintes do arquivo contêm os nomes dos pokémons e seus atributos (Ataque, Defesa, Vida, e Tipo). Esses dados são armazenados em estruturas que representam os pokémons de cada jogador.

3. **Simulação de Batalhas**: A batalha é realizada por meio de um loop que alterna entre os turnos dos jogadores. Durante cada turno, um jogador ataca e o outro defende. O dano causado é calculado com base nos atributos dos pokémons e em uma função que determina a eficácia do ataque, considerando os tipos dos pokémons.

4. **Cálculo de Dano e Condições de Vitória**: A função `calculaDano` avalia a efetividade do ataque com base nos tipos dos pokémons, enquanto a função `tipoAtaque` ajusta o dano de acordo com a vantagem ou desvantagem de tipo. Se o dano exceder a defesa do pokémon, este perde pontos de vida proporcionalmente; caso contrário, o pokémon perde apenas uma unidade de vida.

5. **Finalização**: A batalha continua até que todos os pokémons de um jogador sejam derrotados. O jogo então imprime o resultado final, incluindo o vencedor e os pokémons sobreviventes e derrotados.

## 📂 Exemplo de Execução

### Input:
```
3 2
Wartortle 26 41 19 agua
Magmortar 21 16 24 fogo
Bonsly 11 19 17 pedra
Dewgong 17 26 33 gelo
Pikachu 25 15 24 eletrico
```

### Output:
```
Dewgong venceu Wartortle
Magmortar venceu Dewgong
Pikachu venceu Magmortar
Pikachu venceu Bonsly

Jogador 2 venceu

Pokémons sobreviventes:
Pikachu

Pokémons derrotados:
Wartortle
Magmortar
Bonsly
Dewgong
```


## 🛠️ Ferramentas Utilizadas

- **Linguagem C**: Para o desenvolvimento do algoritmo e simulação das batalhas.

## 🚀 Desafios e Melhorias Futuras

Durante o desenvolvimento, enfrentamos desafios relacionados à manipulação de arquivos, estruturação do código para uma melhor leitura e otimização do algoritmo de combate. Para versões futuras, planeja-se implementar novas funcionalidades, como a inclusão de habilidades especiais para os pokémons e modos de jogo adicionais.

