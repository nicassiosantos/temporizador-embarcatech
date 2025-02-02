#include <stdio.h> // Biblioteca padrão do C para entrada e saída.
#include "pico/stdlib.h" // Biblioteca padrão do Raspberry Pi Pico para controle de GPIO, temporização e comunicação serial.
#include "pico/time.h"   // Biblioteca para gerenciamento de temporizadores e alarmes.

// Definição dos pinos GPIO para os LEDs
#define LED_R 13 // LED vermelho
#define LED_B 12 // LED azul
#define LED_G 11 // LED verde
#define BUTTON_PIN 5  // Define o pino GPIO 5 para ler o estado do botão.

// Variável global volátil para controlar a execução do programa
bool volatile executando = false;       

// Função de callback para ligar todos os LEDs após um tempo programado
int64_t turn_on_callback_1(alarm_id_t id, void *user_data) {
    gpio_put(LED_R, true); // Liga o LED vermelho
    gpio_put(LED_G, true); // Liga o LED verde
    gpio_put(LED_B, true); // Liga o LED azul
    executando = true; // Indica que o processo está em execução
    return 0;
}

// Função de callback para desligar o LED verde após um tempo programado
int64_t turn_off_callback_1(alarm_id_t id, void *user_data) {
    gpio_put(LED_G, false); // Desliga o LED verde
    return 0;
}

// Função de callback para desligar o LED azul após um tempo programado
int64_t turn_off_callback_2(alarm_id_t id, void *user_data) {
    gpio_put(LED_B, false); // Desliga o LED azul
    return 0;
}

// Função de callback para desligar o LED vermelho e finalizar a execução
int64_t turn_off_callback_3(alarm_id_t id, void *user_data) {
    gpio_put(LED_R, false); // Desliga o LED vermelho
    executando = false; // Indica que o processo foi concluído
    return 0;
}

int main() {
    // Inicializa a comunicação serial para permitir debug com printf
    stdio_init_all();

    // Configuração dos pinos dos LEDs como saída e desligados inicialmente
    gpio_init(LED_R);              
    gpio_set_dir(LED_R, GPIO_OUT); 
    gpio_put(LED_R, false);       

    gpio_init(LED_B);              
    gpio_set_dir(LED_B, GPIO_OUT); 
    gpio_put(LED_B, false); 

    gpio_init(LED_G);              
    gpio_set_dir(LED_G, GPIO_OUT); 
    gpio_put(LED_G, false); 

    // Configuração do botão como entrada com pull-up ativado
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // Loop principal do programa
    while (true) {
        // Verifica se o botão foi pressionado e se o processo não está em execução
        if (gpio_get(BUTTON_PIN) == 0 && !executando) {
            sleep_ms(20); // Pequeno atraso para debounce

            // Verifica novamente o estado do botão após debounce
            if (gpio_get(BUTTON_PIN) == 0) {
                // Aciona os LEDs em sequência usando alarmes com tempos programados
                add_alarm_in_ms(20, turn_on_callback_1, NULL, false);  // Liga todos os LEDs
                add_alarm_in_ms(3000, turn_off_callback_1, NULL, false); // Desliga o LED verde após 3 segundos
                add_alarm_in_ms(6000, turn_off_callback_2, NULL, false); // Desliga o LED azul após 6 segundos
                add_alarm_in_ms(9000, turn_off_callback_3, NULL, false); // Desliga o LED vermelho após 9 segundos
            }
        }

        sleep_ms(10); // Pequeno atraso para evitar polling excessivo
    }

    return 0; // Nunca será alcançado devido ao loop infinito
}
