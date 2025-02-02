# Controle de LEDs com Botão no Raspberry Pi Pico

## Descrição
Este projeto implementa um sistema de controle de LEDs no Raspberry Pi Pico acionado por um botão. Quando o botão é pressionado, os LEDs vermelho, azul e verde acendem e depois desligam em sequência após tempos programados.

## Funcionalidade
O programa monitora o estado do botão e, ao detectar um pressionamento, ativa um conjunto de temporizadores que controlam o acendimento e apagamento dos LEDs em diferentes momentos.

## 🛠️ Tecnologias Utilizadas

- *Linguagem de Programação*: C.
- *Placas Microcontroladoras*:
  - BitDogLab.
  - Pico w.
- *Ferramentas*:
  - Wokwi.
 
## 🗂️ Estrutura do Repositório

- `timer.c`: Código-fonte.
- `README.md`/: Tutoriais e explicações sobre a Documentação do projeto.
- `diagram.jso`n/: Diagramas de conexão e esquemas de hardware.

## Esquemático de Conexão
| Componente | GPIO |
|------------|------|
| LED Vermelho | 13 |
| LED Azul | 12 |
| LED Verde | 11 |
| Botão | 5 |

Cada LED deve estar em série com um resistor e conectado ao respectivo pino GPIO do Raspberry Pi Pico. O botão deve ser conectado ao GPIO 5 com um pull-up.

## Como Funciona
1. O programa inicializa os pinos GPIO e define seus estados iniciais.
2. O loop principal verifica continuamente o estado do botão.
3. Quando o botão é pressionado, o programa agenda a execução de temporizadores:
   - Após 20ms: Todos os LEDs acendem.
   - Após 3 segundos: O LED verde apaga.
   - Após 6 segundos: O LED azul apaga.
   - Após 9 segundos: O LED vermelho apaga.
4. O sistema aguarda uma nova interação do botão.


## Saída Esperada
- Quando o botão for pressionado, os LEDs acenderão simultaneamente e apagarão em sequência após os tempos programados.

## Autor
- **[Nicassio Santos.](https://github.com/nicassiosantos)**


