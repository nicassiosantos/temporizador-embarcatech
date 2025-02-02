#include <stdio.h> // Biblioteca padrão do C.
#include "pico/stdlib.h" // Biblioteca padrão do Raspberry Pi Pico para controle de GPIO, temporização e comunicação serial.
#include "pico/time.h"   // Biblioteca para gerenciamento de temporizadores e alarmes.

#define LED_R 13 //Definição da GPIO de saída
#define LED_B 12 //Definição da GPIO de saída
#define LED_G 11 //Definição da GPIO de saída    
#define BUTTON_PIN 5  // Define o pino GPIO 5 para ler o estado do botão.

bool volatile executando = false;       

// Função de callback para desligar o LED após o tempo programado.
int64_t turn_on_callback_1(alarm_id_t id, void *user_data) {

    gpio_put(LED_R, true);
    gpio_put(LED_G, true);
    gpio_put(LED_B, true);
    executando = true;

    return 0;
}

int64_t turn_off_callback_1(alarm_id_t id, void *user_data) {
    gpio_put(LED_G, false);

    return 0;
}

int64_t turn_off_callback_2(alarm_id_t id, void *user_data) {
    gpio_put(LED_B, false);
    return 0;
}

int64_t turn_off_callback_3(alarm_id_t id, void *user_data) {
    gpio_put(LED_R, false);
    executando = false;
    return 0;
}

int main() {
    // Inicializa a comunicação serial para permitir o uso de printf.
    // Isso é útil para depuração, embora não seja usado neste exemplo.
    stdio_init_all();

    gpio_init(LED_R);              
    gpio_set_dir(LED_R, GPIO_OUT); 
    gpio_put(LED_R, false);       

    gpio_init(LED_B);              
    gpio_set_dir(LED_B, GPIO_OUT); 
    gpio_put(LED_B, false); 

    gpio_init(LED_G);              
    gpio_set_dir(LED_G, GPIO_OUT); 
    gpio_put(LED_G, false); 


    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // Loop principal do programa que verifica continuamente o estado do botão.
    while (true) {
        if (gpio_get(BUTTON_PIN) == 0 && !executando) {
            // Adiciona um pequeno atraso para debounce
            sleep_ms(20);

            // Verifica novamente o estado do botão após o debounce.
            if (gpio_get(BUTTON_PIN) == 0) {
                
                add_alarm_in_ms(20, turn_on_callback_1, NULL, false);

                add_alarm_in_ms(3000, turn_off_callback_1, NULL, false);

                add_alarm_in_ms(6000, turn_off_callback_2, NULL, false);

                add_alarm_in_ms(9000, turn_off_callback_3, NULL, false);
            }
        }

        sleep_ms(10);
    }

    // Retorno de 0, que nunca será alcançado devido ao loop infinito.
    // Isso é apenas uma boa prática em programas com um ponto de entrada main().
    return 0;
}
