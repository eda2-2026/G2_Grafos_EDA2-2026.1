# Campo Minado com Grafos

Conteúdo da Disciplina: Grafos

## 👥 Equipe - Grupo 2

Dupla responsável pela implementação do projeto de Campo Minado utilizando conceitos de grafos.

| Foto | Nome | Matrícula |
|---:|---|---|
| <img src="https://github.com/giovannafg.png" alt="Giovanna" width="80" style="border-radius:8px" /> | **[Giovanna Felipe](https://github.com/giovannafg)** | 241038998 |
| <img src="https://github.com/andrehsb.png" alt="Andrei" width="80" style="border-radius:8px" /> | **[André Henrique](https://github.com/andrehsb)** | 241025149 |

## Sobre

Projeto de Campo Minado desenvolvido com uma abordagem baseada em grafos, combinando uma interface web em HTML/CSS/JavaScript com um motor de jogo implementado em C. A lógica do tabuleiro representa cada casa como um vértice e as posições vizinhas como arestas, permitindo o cálculo das bombas ao redor e a abertura automática das casas vazias.

## Link do vídeo

- Link para vídeo explicativo: Em breve

## Screenshots

- Interface do jogo com seleção de níveis e tabuleiro interativo.
- Em breve serão adicionadas capturas da aplicação.

## Estruturas de dados e conceitos de grafos implementados

O projeto utiliza uma representação baseada em grafos para modelar o tabuleiro do Campo Minado:

- Cada casa do tabuleiro é tratada como um vértice.
- As casas adjacentes formam arestas, representando os 8 vizinhos possíveis.
- A função de obtenção de arestas do vértice permite identificar os vizinhos de cada célula.
- O contador de bombas ao redor de cada posição utiliza a vizinhança do vértice correspondente.

### Porta 3000

1. Interface web local: http://localhost:3000

## 🚀 Instalação Rápida

```bash
# clonar o repositório
git clone <URL_DO_REPOSITORIO>
cd G2_Grafos_EDA2-2026.1
```

### Pré-requisitos

- Node.js instalado
- GCC instalado para compilar o motor em C

### Executar localmente

No Windows:

```bat
iniciar-local.bat
```

No Linux/macOS:

```bash
bash iniciar-local.sh
```

Ou diretamente com Node:

```bash
node server.cjs
```

## ▶️ Scripts Úteis

```bash
node server.cjs
bash iniciar-local.sh
iniciar-local.bat
```

## Uso

Ao abrir a aplicação localmente, o usuário pode escolher um nível de dificuldade, abrir casas do tabuleiro e marcar bandeiras em possíveis bombas. O motor em C atualiza o estado do jogo e a interface web exibe se o jogador venceu, perdeu ou continua jogando.