// Virulent AllKeys
/*
     * All Keys Active:
     *
     *                       ,-----------------------------------------------------------. 
     *                       |Esc|PrS|F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| 
     *                       `-----------------------------------------------------------' 
     * ,-------------------. ,-----------------------------------------------------------. 
     * |Del|Pls|Div|Ply|Mns| |~  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  Backs| 
     * |-------------------| |-----------------------------------------------------------| 
     * |PgU|Hom|  7|  8|  9| |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  
     * |-------------------| |-----------------------------------------------------------| 
     * |PgD|End|  4|  5|  6| |Cap   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|     Ret| 
     * |-------------------| |-----------------------------------------------------------| 
     * |Ins|Up |  1|  2|  3| |Fn0|Shif|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /| Up| Shift| 
     * |-------------------| |-----------------------------------------------------------| 
     * |Lef|Dow|Rig|  0|  .| |Ctrl |Gui|Alt  |Shf||Ctrl|Bsp|Spc |Del|Gui  Lef|Dow|Rig|
     * `-------------------' `-----------------------------------------------------------' 
     */
static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty + a few media keys */
    KEYMAP(\
                                   ESC, PSCR,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,  \
        DEL, PPLS,PSLS,PAST,PMNS,  GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, \
        5,   6,   7,   8,   9,     TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
        Q,   W,   E,   R,   T,     Y,   A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,  \
        A,   S,   D,   F,   G,     H,   QUOT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,UP,  RSFT, \
        Z,   X,   C,   V,   B,     N,   1,        3,   4,   5,   6,   7,   8,        0,   LEFT,DOWN,RGHT),
    /* 1: media keys */
    KEYMAP(\
                                   TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        1,   2,   3,   4,   5,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        Q,   W,   E,   R,   T,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        A,   S,   D,   F,   G,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS, \
        Z,   X,   C,   V,   B,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        LCTL,F11, F10, N,   LSFT,  TRNS,TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,TRNS)
};
static const action_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_TOGGLE(1)
};
