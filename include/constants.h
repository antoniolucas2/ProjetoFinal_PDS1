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
                   ERRO_CRIACAO_FILA,
                   ERRO_CRIACAO_TIMER,
                   ERRO_CRIACAO_DISPLAY,
                   ERRO_CRIACAO_LINHA_INIMIGOS,
                   ERRO_CRIACAO_MATRIZ_INIMIGOS,
                   ERRO_VETOR_TOTAL_INIMIGOS,
                   NAO_CONSEGUI_CRIAR_A_FONTE,
                   NAO_CONSEGUI_INICIAR_TTF_ADDON,
                   ERRO_ABERTURA_SAVE,
                   ERRO_ABERTURA_IMAGEM,
                   TOTAL_ERROS};

enum CURRENT_SCREEN{MENU = 1, GAME, HOW_TO_PLAY_SCREEN, SAVE_DELETED};

// Total de samples para o audio no Allegro. Por padrao, estou usando 16
#define TOTAL_AUDIO_SAMPLES 16

// FPS para o jogo
#define FPS 60.0

// Resolucao do jogo
#define WIDTH_RES  1280
#define HEIGHT_RES  960

// Constantes para serem utilizadas na manipulacao do input
#define KEY_NOT_SEEN 1
#define KEY_DOWN 2

// Constante para a velocidade padrao
#define DEFAULT_SPEED 12

// Constantes para a quantidade de inimigos
#define TOTAL_ENEMIES_PER_LINE 11
#define TOTAL_LINES 5

// Constantes dos tamanhos do player e inimigos
#define PLAYER_ENEMY_WIDTH 60
#define PLAYER_ENEMY_HEIGHT 50

// Distancia que o inimigo anda
#define ENEMY_HORIZONTAL_TRAVEL_DISTANCE 20
#define ENEMY_VERTICAL_TRAVEL_DISTANCE 30

//Distancia inicial que os inimigos devem ter para a parede
#define WALL_DISTANCE 90

//Distancia inicial que os inimigos devem ter para o teto
#define CEIL_DISTANCE 100

//Calculo quantos frames quero para poder mover os inimigos
#define TOTAL_FRAMES_TO_MOVE 5

//Dimensoes para a bala
#define BULLET_WIDTH 5
#define BULLET_HEIGHT 20
#define BULLET_SPEED 15

//Cores para o background, quando usado no formato retangular
#define BG_R 118
#define BG_G 171
#define BG_B 250

//Total de frames que o aviso dos pontos fica na tela
#define FRAME_POINTS 30

// Velocidade vertical dos pontos
#define POINTS_VERTICAL_SPEED 1

// Total de FPS para o fade da logo
#define FPS_FADE_LOGO 120

// Opcoes da tela de menu
#define GAME_OPTION 0
#define HOW_TO_PLAY 1
#define DELETE_SAVE 2

#endif
