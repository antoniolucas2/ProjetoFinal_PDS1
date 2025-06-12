#ifndef CONSTANTS_HEADER
#define CONSTANTS_HEADER

/* Aqui os codigos de erro para os exit's que foram executados.*/

enum ERROS_ALLEGRO{ALLEGRO_NAO_INICIOU = 1,
                   TECLADO_NAO_FOI_INSTALADO,
                   ERRO_ADDON_IMAGENS,
                   ERRO_INSTALACAO_AUDIO,
                   ACODECS_NAO_INICIOU,
                   ERRO_RESERVA_SAMPLES};

// Total de samples para o audio no Allegro. Por padrao, estou usando 16
#define TOTAL_AUDIO_SAMPLES 16

#endif
