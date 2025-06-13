#ifndef CONSTANTS_HEADER
#define CONSTANTS_HEADER

/* Aqui os codigos de erro para os exit's que foram executados.*/

enum ERROS_ALLEGRO{ALLEGRO_NAO_INICIOU = 1,
                   TECLADO_NAO_FOI_INSTALADO,
                   ERRO_ADDON_IMAGENS,
                   ERRO_INSTALACAO_AUDIO,
                   ACODECS_NAO_INICIOU,
                   ERRO_RESERVA_SAMPLES,
                   PRIMITIVES_NAO_INICIARAM,
                   ERRO_CRIACAO_PLAYER,
                   ERRO_CRIACAO_FILA,
                   ERRO_CRIACAO_TIMER,
                   ERRO_CRIACAO_DISPLAY,
                   TOTAL_ERROS};

// Total de samples para o audio no Allegro. Por padrao, estou usando 16
#define TOTAL_AUDIO_SAMPLES 16

// FPS para o jogo
#define FPS 30.0

// Resolucao do jogo
#define WIDTH_RES  1280
#define HEIGHT_RES  960

// Constantes para serem utilizadas na manipulacao do input
#define KEY_NOT_SEEN 1
#define KEY_DOWN 2

// Constante para a velocidade padrao
#define DEFAULT_SPEED 8

#endif
