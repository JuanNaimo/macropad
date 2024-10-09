#include "oled_driver.h"

enum layers {
    BASE,    // Capa base
    FN,      // Capa de funciones
    PAD      // Capa numérica 
};

// Define las teclas personalizadas
enum custom_keycodes {
   OPEN_CHROME = SAFE_RANGE, // Asegura que el código de la tecla sea únicO
   OPEN_SPOTIFY = SAFE_RANGE,
   OPEN_VSCODE = SAFE_RANGE,
};

uint8_t current_layer = BASE;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base Layer: Default Layer
     * ,-------------------------------------------------------.
     * | CTRLC | CTRLV | OPEN VC | OPEN CHROME | OPEN SPOTIFY |
     * |------------------------------------------------------|
     * | MUTE | PREVIOUS | PLAY | NEXT | DORMIR |
     * `-------------------------------------------------------'
     */
    [BASE] = LAYOUT(
        LCTL(KC_C), LCTL(KC_V), OPEN_VSCODE, OPEN_CHROME, OPEN_SPOTIFY
        KC_AUDIO_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, KC_SYSTEM_SLEEP
    ),

    /* Function Layer: Media/Function Keys
     * ,------------------------------.
     * | F13 | F14 | F15 | F16 | F17 | 
     * |-----------------------------|
     * | F18 | F19 | F20 | F21 | F22 |
     * `------------------------------'
     */
    [FN] = LAYOUT(
        KC_F13, KC_F14, KC_F15, KC_F16, KC_F17,
        KC_F18, KC_F19, KC_F20, KC_F21, KC_F22
    ),

    /* Numeric Layer: Numeric Pad
     * ,--------------------------------.
     * | K_0 |  K_1 | K_2 | K_3  | K_4 |
     * |-------------------------------|
     * | K_5 |  K_6 | K_7 | K_8  | K_9 |
     * `--------------------------------'
     */
    [PAD] = LAYOUT(
        KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_4,
        KC_KP_5, KC_KP_6, KC_KP_7, KC_KP_8, KC_KP_9
    )
};

// Encoder rotation
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { // Primer encoder
        if (clockwise) {
            tap_code(KC_VOLU); // Volumen arriba
        } else {
            tap_code(KC_VOLD); // Volumen abajo
        }
    } else if (index == 1) { // Segundo encoder
        if (clockwise) {
            tap_code(KC_F23); // F23
        } else {
            tap_code(KC_F24); // F24
        }
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case OPEN_CHROME:
            if (record->event.pressed) {
                // El código aquí se ejecuta cuando la tecla es presionada
                SEND_STRING(SS_LGUI("r") "chrome\n"); // Esto es específico para Windows
            }
            return false; // No ejecutar más funciones
        case OPEN_SPOTIFY:
            if (record->event.pressed) {
                // Esto es específico para Windows
                SEND_STRING(SS_LGUI("r") "spotify\n");
            }
            return false; // No ejecutar más funciones
        case OPEN_VSCODE:
            if (record->event.pressed) {
                // Esto es específico para Windows
                SEND_STRING(SS_LGUI("r") "code\n");
            }
            return false;    
            
    }
    return true;
}
void matrix_scan_user(void) {
    // Lee el estado del botón del encoder
    uint8_t pin_state = readPin(ENCODER_BUTTON_PIN_A); // Sustituir con el pin real del botón del encoder
    static uint8_t old_state = 1;

    if (old_state != pin_state) {
        old_state = pin_state;
        if (pin_state == 0) { // Si el botón está presionado (ajusta esto según tu botón)
            // Alterna entre las capas
            current_layer = (current_layer + 1) % 3; // Avanza y vuelve a BASE después de FN2
            layer_move(current_layer); // Cambia a la capa seleccionada
            oled_update_layer(current_layer); // Actualiza la pantalla OLED con la capa actual
        }
    }
}

void oled_update_layer(uint8_t layer) {
    // Limpia la pantalla
    oled_clear();
    oled_set_cursor(0, 1);
    // Muestra el número de capa
    oled_write_P(PSTR("Capa: "), false);
    switch (layer) {
        case BASE:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case FN:
            oled_write_P(PSTR("FN\n"), false);
            break;
        case PAD:
            oled_write_P(PSTR("NumPad\n"), false);
            break;
        default:
            oled_write_P(PSTR("\n"), false);
    }
}

// Función que se llama cada vez que cambia una capa
layer_state_t layer_state_set_user(layer_state_t state) {
    // Actualiza la pantalla OLED con el número de capa actual
    oled_update_layer(get_highest_layer(state));
    return state;
}



