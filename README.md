# 🎅 Deu a Louca no Papai Noel

Jogo de plataforma **2D**, desenvolvido em **C com Allegro 5** como trabalho da disciplina **Programação II** da **Universidade Federal do Paraná (UFPR)**.

Depois de uma briga com as renas, o Papai Noel precisa fugir do Polo Norte! Para escapar, ele deve atravessar uma fase cheia de obstáculos, plataformas e perigos.

## 🎮 Sobre o jogo

O jogador controla o Papai Noel em uma fase de plataforma com movimentação lateral, pulos e deslizes. Ao longo do percurso, é preciso desviar de espinhos, superar obstáculos e chegar ao objetivo.

### Funcionalidades

- **Uma fase** com mapa construído a partir de uma matriz de tiles;
- **Movimentação lateral**, pulo e deslize;
- **Pulo duplo** desbloqueável por item;
- **Sistema de vida**, dano e invencibilidade temporária;
- **Coletáveis**, como recuperação de vida;
- **Animações** para diferentes estados do personagem;
- **Câmera horizontal** que acompanha o Papai Noel;
- **Menu inicial** e telas de vitória e derrota.

## ⌨️ Controles

| Tecla | Ação |
|---|---|
| `A` | Mover para a esquerda |
| `D` | Mover para a direita |
| `Espaço` | Pular |
| `S` | Deslizar |
| `Enter` | Selecionar opções do menu |
| `Esc` | Sair ou voltar, conforme a tela |

O pulo duplo fica disponível após obter o item correspondente.

## 🛠️ Tecnologias e conceitos

- **Linguagem C (C11)**;
- **Allegro 5**, para gráficos, entrada de teclado, imagens e fontes;
- **Matrizes**, utilizadas na representação do mapa;
- **Estruturas (`struct`) e enumerações**, para estados do jogo e do personagem;
- **Detecção de colisões** e física básica de plataforma;
- **Máquina de estados**, para menu, partida, vitória e derrota;
- **Organização modular**, separando lógica, mapa, personagem e interface.

## 📁 Estrutura do projeto

| Arquivo ou pasta | Responsabilidade |
|---|---|
| `main.c` | Ponto de entrada do programa |
| `jogo.c/.h` | Ciclo principal, eventos e estados do jogo |
| `personagem.c/.h` | Movimentação, colisões e animações do Papai Noel |
| `mapa.c/.h` | Construção e renderização da fase |
| `interface.c/.h` | Elementos visuais da interface |
| `constantes.h` | Parâmetros e configurações do jogo |
| `assets/` | Recursos gráficos utilizados |
| `makefile` | Compilação do projeto |

## 🚀 Como compilar e executar

O projeto foi preparado para compilação com **GCC**, **Make**, **pkg-config** e as bibliotecas **Allegro 5**:

- `allegro-5`
- `allegro_font-5`
- `allegro_ttf-5`
- `allegro_image-5`
- `allegro_primitives-5`

Em um ambiente Linux com essas dependências instaladas:

```bash
git clone https://github.com/PedroStahel/Deu-a-Louca-no-Papai-Noel.git
cd Deu-a-Louca-no-Papai-Noel
make
./jogo
```

Para remover os arquivos gerados na compilação:

```bash
make clean
```

> O jogo depende dos arquivos da pasta `assets/` e deve ser executado a partir da pasta do projeto para localizar os recursos.

## 👨‍💻 Autor

**Pedro Stahel de Azevedo**  
Ciência da Computação — Universidade Federal do Paraná (UFPR)

[GitHub](https://github.com/PedroStahel) · [LinkedIn](https://www.linkedin.com/in/pedro-stahel-86a44b349)

---

*Projeto acadêmico desenvolvido para a disciplina de Programação II — UFPR.*
