#include "iGraphics.h"
#define BALL_WIDTH 90
#define BALL_HEIGHT 90
#include "iSound.h"
#include "iFont.h"

// Coordinates of blocks and spikes

typedef struct{
    int x1;
    int y1;
    int x2;
    int y2;
    int n;
}coordinates;

//Prototypes

void mute_function();
void show_score(bool f);
void update_spider();
void collision_upperblock(coordinates*upblock,int n);
void collision_lowerblock(coordinates*downblock,int n);
void jumpblock();
void start_game();
void gameover();
void leaderboard();
void help();
void jump();
void Load_blocks(int n,int n1,int n2, int n3,coordinates*upblocks,coordinates*downblocks , coordinates*spikes);
void load_game();
void spike(coordinates*spikes,int n);
void healthReduce();
void Finished(int y1);
void Load_spider(int n,coordinates*ptr);
void collision_spider(int n2,coordinates*ptr);
void Load_spider_sprite();
void update_saved();
int save_to_leaderboard(const char *name, int score);
void Take_name();

//Global Variables

int soundOn=1;
int scoreIncrease=1;
bool aa = true;
int initialized=0;
int sound;
int r = 0;
int can_jump = 0,lv=0;
int touching_spike =0 ;
int freeze_frame = 0,touching_right=0,touching_left=0;
char ball_sprite[100];
int pressed =0,x=0,v=10;
int x_ball=640,s=1,c=0,block_num=0;
int floor_game =65,level =1,j=0,g=150,score =0;
int health = 100,y=floor_game;
int sp_y = 70,direction=1,sp_speed=100,touching_sp=0;
char leaderboard_lines[5][100];
int leaderboard_count = 0;
char player_name[100] = "";
int name_index = 0;
int entering_name = 0;


//coordinates

coordinates level1_upblock[]{
    {465,275,1015,625,1},
    {1920,260,2200,630,2},
    {3015,540,3200,630,3},
    {4020,282,4200,630,4},
    {6020,255,6210,630,5},
    {6750,260,6935,630,6},
    {7485,260,7670,630,7},
    {9030,260,9215,630,8},
    {10030,260,10210,630,9}
};

coordinates level2_upblock[]{
    {2420,245,2600,650,1},
    {3160,450,3340,650,2},
    {6120,245,6300,650,3},
    {8150,245,8350,650,4},
    {9170,450,9360,650,5}
};

coordinates level3_upblock[]{
    {900,445,1060,650,1},
    {3900,445,4070,650,2},
    {5820,445,6010,650,3},
    {6700,535,7160,650,4}
};

coordinates level1_downblock[]{
    {1285,76,1470,430,1},
    {2370,77,2560,340,2},
    {2560,270,2740,340,3},
    {2920,270,3020,345,4},
    {3020,270,3200,345,5},
    {3200,270,3300,345,6},
    {3480,270,3650,345,7},
    {3650,77,3860,350,8},
    {6390,77,6570,410,9},
    {7110,77,7320,410,10},
    {7860,77,8040,410,11},
    {8400,77,8580,245,12},
    {8580,77,8670,170,13},
    {8670,77,8900,345,14},
    {9400,77,9580,345,15},
    {9580,77,9675,170,16},
    {9675,77,9860,245,17}
};

coordinates level2_downblock[]{
    {1400,70,1570,420,1},
    {1570,340,2040,420,2},
    {2040,260,2220,420,3},
    {2780,70,2970,430,4},
    {3800,70,4260,430,5},
    {9170,70,9360,240,6}
};

coordinates level3_downblock[]{
    {890,70,1160,260,1},
    {1700,70,2130,160,2},
    {3800,70,3900,160,3},
    {3900,70,4070,260,4},
    {5120,270,5300,350,5},
    {5820,70,6010,260,6},
    {6710,70,6810,260,7},
    {7080,70,7160,260,8},
    {7770,70,7950,260,9},
    {8560,70,8920,260,10},
    {9270,70,9620,260,11},
    {9620,70,9870,170,12},
    {10050,270,10230,350,13},
    {10760,70,10940,148,14},
    {11200,180,11290,260,15},
    {11290,180,11380,350,16},
    {11380,270,11470,350,17}
};

coordinates level1_sprite[]{
    {1585,77,1620,170,1},
    {2760,77,2800,170,2},
    {3310,77,3350,170,3},
    {4680,77,4720,170,4},
    {4950,77,5000,170,5},
    {5310,77,5360,170,6},
    {5680,77,5730,170,7},
    {8600,167,8630,270,8},
    {9600,167,9640,260,9}
};

coordinates level2_sprite[]{
    {1190,70,1220,180,1},
    {1850,70,1890,190,2},
    {3040,70,3080,200,3},
    {3660,70,3700,200,4},
    {4370,70,4400,200,5},
    {5000,70,5050,150,6},
    {5950,70,6000,150,7},
    {6500,70,6560,220,8},
    {7040,70,7090,200,9},
    {7600,70,7650,250,10},
    {8460,70,8480,250,11}
};

coordinates level3_sprite[]{
    {360,77,410,220,1},
    {730,77,780,220,2},
    {1180,77,1210,200,3},
    {2020,165,2060,265,4},
    {2250,77,2280,200,5},
    {3810,170,3850,280,6},
    {4250,77,4300,220,7},
    {4820,77,4870,220,8},
    {5380,77,5420,180,9},
    {6310,77,6370,240,10},
    {6550,77,6590,240,11},
    {7290,77,7330,230,12},
    {7650,77,7690,220,13},
    {8720,270,8800,360,14},
    {9420,270,9470,390,15},
    {11410,77,11450,210,16}
};

coordinates level2_spider[]{
    {4530,70,4720,620,1},
    {5100,70,5290,620,2},
    {5640,70,5830,620,3},
    {8620,70,5810,620,4},
};

coordinates level3_spider[]{
    {1390,70,1580,620,1},
    {2470,70,2660,620,2},
    {2680,70,2870,620,3},
    {2890,70,3080,620,4},
    {3200,70,3390,620,5},
    {3390,70,3580,620,6},
    {4470,70,4660,620,7},
    {5430,70,5620,620,8},
    {8100,70,8290,620,9},
    {8300,70,8490,620,10}
};

//functions

void change_state(){
    if(pressed == 0){
        pressed = 1;
        iResumeTimer(0);
    }
    update_spider();
}

int main(int argc, char *argv[])
{
    iSetTimer(500,change_state);
    iSetTimer(200,jump);
    iSetTimer(300,healthReduce);
    iWindowedMode(1280, 720, "Bounce Classico");
    iStartMainLoop();
    iInitializeSound();
    return 0;
}

/*
function iDraw() is called again and again by the system.
*/
void iDraw()
{
    iClear();
    if(pressed == 0)
        iShowImage(0, 0, "assets/images/bg/loading.jpg");
    else if(pressed == 1){
        iShowImage(0, 0, "assets/images/bg/home.jpg");
        iText(100,50,"Use Your Mouse To navigate");
    }
    else if(pressed == 2){
        start_game();
    }
    else if(pressed == 3){
        load_game();
    }
    else if(pressed == 4){
        leaderboard();
   }
    else if(pressed == 5){
        help();
    }
    else if(pressed ==6 ){
        gameover();
    }
    else if(pressed == 7){
        if(entering_name){
            Take_name();
        }
}


}

/*
function iKeyPress() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyPress(unsigned char key)
{
    if (entering_name) {
        if (key == '\r') {
            if (name_index == 0) return;

            save_to_leaderboard(player_name, score);
            pressed = 1;
            entering_name = 0;
            return;
        }
        else if (key == '\b') {
            if (name_index > 0) {
                name_index--;
                player_name[name_index] = '\0';
            }
            return;
        }
        else if (name_index < 99 && (
            (key >= 'a' && key <= 'z') ||
            (key >= 'A' && key <= 'Z') ||
            key == ' ')) {
            player_name[name_index++] = key;
            player_name[name_index] = '\0';
            return;
        }
    }

    switch (key)
    {
        case 'c':
            c = 1;
            if (pressed == 4 || pressed == 6 || pressed == 7)
                pressed = 1;
            break;
        case 'f':
            freeze_frame = 0;
            break;
        case 'n':
            break;
        default:
            break;
    }
}



/*
function iSpecialKeyPress() is called whenver user hits special keys likefunction
keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11,
GLUT_KEY_F12, GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN,
GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME, GLUT_KEY_END,
GLUT_KEY_INSERT */
void iSpecialKeyPress(unsigned char key)
{
    switch (key)
    {
    case GLUT_KEY_HOME:
        pressed=1;
        break;
    case GLUT_KEY_END:
        update_saved();
        iCloseWindow();
        break;
    case GLUT_KEY_RIGHT:
        if(touching_right && freeze_frame){
            v=10;
            x+=v;
            touching_right=0;
        }
        if (!freeze_frame ) {
        v = 10;
        x += v;
        if(scoreIncrease) score++;
        s++;
        if (s > 8) s %= 8;
        }

        break;

    case GLUT_KEY_LEFT:
        if(touching_left && freeze_frame){
            v=10;
            x-=v;
            touching_left=0;
        }
        if (!freeze_frame) {
        x -= 10;
        if(scoreIncrease) score--;
        s--;
        if (s < 1) s = 8;
        }
        break;
    case GLUT_KEY_UP:
        if (can_jump) {
            g = 100;
            j = 1;
            can_jump = 0;
        }
        j=1;
        break;
    default:
        break;
    }
}

/*
function iMouseClick() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseClick(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(pressed ==1){
            if(mx> 850 && mx < 1150 && my > 595 && my <690) {
                health = 100;
                x = 0;
                pressed = 2;
                score= 0;
                iInitializeSound();
                sound = iPlaySound("assets/sounds/bgmusic.wav",true);

            }
            if(mx> 850 && mx < 1150 && my > 460 && my < 555 ){
                pressed = 3;
                sound = iPlaySound("assets/sounds/bgmusic.wav",true);
            }
            if(mx> 850 && mx < 1150 && my > 335 && my < 430){
                pressed = 4;
            }
            if(mx> 850 && mx < 1150 && my > 210 && my < 300){
                pressed = 5;
            }
            if(mx> 1160 && mx < 1275 && my > 20 && my < 70){
                exit(0);
            }
        }
        if(pressed == 2){
            if(mx> 560 && mx < 630 && my > 645 && my <715){
                if(soundOn) soundOn = 0;
                else soundOn = 1;
            }
        }

    }
}
/*
function iMouseMove() is called when the user moves the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    // place your codes here
}

void start_game(){
    // Room for the longest values plus the terminating '\0'. "Health: 100" alone is 12 bytes,
    // so the old 11-byte buffer overflowed and the score text got glued onto it.
    char hlth[32];
    char scr[32];
    snprintf(hlth, sizeof hlth, "Health: %d", health);
    snprintf(scr, sizeof scr, "Score: %d", score);
    if(health == 0){
        pressed = 6;
    }
    if(level == 1){
        scoreIncrease=1;
        iShowImage(0, 0, "assets/images/levels/Bg.jpg");
        mute_function();
        iShowText(20, 655, hlth, "assets/fonts/Game.ttf", 54);
        iShowText(890, 655, scr, "assets/fonts/Game.ttf", 54);
        Load_blocks(1,9,17,9,level1_upblock,level1_downblock,level1_sprite);
        sprintf(ball_sprite,"assets/images/sprites/tile00%d.png" , s);
        collision_upperblock(level1_upblock,9);
        collision_lowerblock(level1_downblock,17);
        if(freeze_frame==1) iShowText(10,20,"Screen has been frozen, press ' f ' to continue","assets/fonts/Mkc.ttf",49);
        spike(level1_sprite,9);
        char chp[100];
        sprintf(chp,"assets/images/sprites/finish/Fin%d.jpg" , r+1);
        r++;
        iShowText(10, 600, "Press END to save your game.", "assets/fonts/Game.ttf", 30);
        if(r > 3) r =0;
        iShowImage(1280-x+10030,77,chp);
        if(y>=550) y = 550;
        iShowImage(x_ball, y, ball_sprite);
        Finished(10030+720);
    }
    if(level == 2){
        scoreIncrease=1;
        iShowImage(0, 0, "assets/images/levels/Bg.jpg");
        mute_function();
        iShowText(20, 655, hlth, "assets/fonts/Game.ttf", 54);
        iShowText(890, 655, scr, "assets/fonts/Game.ttf", 54);
        Load_blocks(2,5,6,11,level2_upblock,level2_downblock,level2_sprite);
        Load_spider(4 , level2_spider);
        sprintf(ball_sprite,"assets/images/sprites/tile00%d.png" , s);
        collision_upperblock(level2_upblock,5);
        collision_lowerblock(level2_downblock,6);
        collision_spider(4,level2_spider);
        if(freeze_frame==1) iShowText(10,20,"Screen has been frozen, press ' f ' to continue","assets/fonts/Mkc.ttf",49);
        spike(level2_sprite,11);
        char chp[100];
        sprintf(chp,"assets/images/sprites/finish/Fin%d.jpg" , r+1);
        r++;
        iShowText(10, 600, "Press END to save your game.", "assets/fonts/Game.ttf", 30);
        if(r > 3) r =0;
        iShowImage(1280-x+9215,245,chp);
        if(y>=550) y = 550;
        iShowImage(x_ball, y, ball_sprite);
        Finished(9215+720);

    }
    if(level == 3){
        scoreIncrease=1;
        iShowImage(0, 0, "assets/images/levels/Bg.jpg");
        mute_function();
        iShowText(20, 655, hlth, "assets/fonts/Game.ttf", 54);
        iShowText(890, 655, scr, "assets/fonts/Game.ttf", 54);
        Load_blocks(3,4,17,16,level3_upblock,level3_downblock,level3_sprite);
        Load_spider(10, level3_spider);
        sprintf(ball_sprite,"assets/images/sprites/tile00%d.png" , s);
        collision_upperblock(level3_upblock,4);
        collision_lowerblock(level3_downblock,17);
        collision_spider(10,level3_spider);
        if(freeze_frame==1) iShowText(10,20,"Screen has been frozen, press ' f ' to continue","assets/fonts/Mkc.ttf",49);
        spike(level3_sprite,16);
        char chp[100];
        sprintf(chp,"assets/images/sprites/finish/Fin%d.jpg" , r+1);
        r++;
        iShowText(10, 600, "Press END to save your game.", "assets/fonts/Game.ttf", 30);
        if(r > 3) r =0;
        iShowImage(1280-x+11710,floor_game,chp);
        if(y>=550) y = 550;
        iShowImage(x_ball, y, ball_sprite);
        Finished(720+11710);

    }

}

void Load_blocks(int n,int n1,int n2,int n3,coordinates*upblocks,coordinates*downblocks , coordinates*spikes){
        for(int i = 0 ; i < n1 ; i++){
            if(x>upblocks[i].x1){
                char c[100];
                int u = upblocks[i].x1-x+1280;
                sprintf(c,"assets/images/levels/upperblock%d/%d.jpg" ,n, i+1);
                iShowImage(u,upblocks[i].y1,c);
            }

        }
        for(int i = 0 ; i < n2 ; i++){
            if(x>downblocks[i].x1){
                char c[100];
                sprintf(c,"assets/images/levels/lowerblock%d/%d.jpg" ,n, i+1);
                iShowImage(downblocks[i].x1-x+1280,downblocks[i].y1,c);
            }

        }
        for(int i = 0 ; i < n3 ; i++){
            if(x>spikes[i].x1){
                char c[100];
                sprintf(c,"assets/images/levels/spikes%d/%d.jpg" ,n, i+1);
                iShowImage(spikes[i].x1-x+1280,spikes[i].y1,c);
            }

        }

}

void gameover() {
    iStopSound(sound);
    pressed = 7;
    entering_name = 1;
    player_name[0] = '\0';
    name_index = 0;
}



void help(){
    iShowImage(0,0,"assets/images/bg/help.png");
}

void jump(){
    if (j) {
        freeze_frame = 0;
        y = y + g;
        g -= 35;
    }
    if (y <= floor_game) {
        y = floor_game;
        g = 150;
        j = 0;
        freeze_frame = 0;
    }
}

void collision_upperblock(coordinates*upblock,int n) {
    for (int i = 0; i < n; i++) {
        int blockLeft = upblock[i].x1 - x + 1280;
        int blockRight = upblock[i].x2 - x + 1280;
        int blockBottom = upblock[i].y1;
        int blockTop = upblock[i].y2;
        int ballLeft = x_ball;
        int ballRight = x_ball + BALL_WIDTH;
        int ballBottom = y;
        int ballTop = y + BALL_HEIGHT;

        if (g > 0 &&
            ballRight > blockLeft && ballLeft < blockRight &&
            ballTop >= blockBottom && ballBottom < blockBottom)
        {
            y = blockBottom - BALL_HEIGHT;
            g = -g;
            return;
        }
        if (ballRight >= blockLeft && ballLeft < blockLeft &&
            ballTop > blockBottom && ballBottom < blockTop) {
            x_ball = blockLeft - BALL_WIDTH - 1;
            freeze_frame = 1;
            return;
        }
        if (ballLeft <= blockRight && ballRight > blockRight &&
            ballTop > blockBottom && ballBottom < blockTop) {
            x_ball = blockRight + 1;
            freeze_frame = 1;
            return;
        }
    }
}

void collision_lowerblock(coordinates*downblock,int n) {
    int on_block = 0;
    for (int i = 0; i < n; i++) {
        int blockLeft   = downblock[i].x1 - x + 1280;
        int blockRight  = downblock[i].x2 - x + 1280;
        int blockTop    = downblock[i].y2;
        int blockBottom = downblock[i].y1;
        int ballLeft    = x_ball;
        int ballRight   = x_ball + BALL_WIDTH;
        int ballBottom  = y;
        int ballTop     = y + BALL_HEIGHT;

        if (ballRight > blockLeft && ballLeft < blockRight-20 &&
            ballBottom <= blockTop && ballBottom + abs(g) >= blockTop && g < 0) {
            y = blockTop;
            j = 0;
            on_block = 1;
            can_jump = 1;

        }
        if (!on_block && ballLeft <= blockRight+10 && ballRight > blockRight &&
            ballTop > blockBottom-10 && ballBottom < blockTop-25) {
            touching_right=1;
            freeze_frame = 1;

        }
        if (!on_block && ballRight >= blockLeft+10 && ballLeft < blockLeft &&
            ballTop > blockBottom-10 && ballBottom < blockTop-45) {
            touching_left=1;
            freeze_frame = 1;
        }
        if (g > 0 &&
            ballRight > blockLeft+20 && ballLeft < blockRight &&
            ballTop >= blockBottom && ballBottom < blockBottom)
        {
            if(blockBottom<80) y = blockBottom;
            else y = blockBottom - BALL_HEIGHT;
            g = -g;
            return;
        }
    }
    if (!on_block && y > floor_game) {
        j = 1;
        can_jump = 0;
    }
}

void collision_spider(int n2,coordinates*ptr){
    for(int i = 0 ; i < n2 ; i++){
        int spLeft   = ptr[i].x1 - x + 1280;
        int spRight  = ptr[i].x2 - x + 1280;
        int spTop    = sp_y + 190;
        int spBottom = sp_y;
        int ballLeft    = x_ball;
        int ballRight   = x_ball + BALL_WIDTH;
        int ballBottom  = y;
        int ballTop     = y + BALL_HEIGHT;
        if(ballRight>spLeft && ballLeft<spRight && ballBottom<spTop && ballTop>spBottom) touching_sp=1;
    }


}

void healthReduce(){
    if(touching_spike || touching_sp){
        health-=10;
        touching_spike=0;
        touching_sp=0;
    }
}

void spike(coordinates*spikes,int n){
    for (int i = 0; i < n; i++){
        int spikeLeft = spikes[i].x1-x+1280;
        int spikeRight = spikes[i].x2-x+1280;
        int spikeTop = spikes[i].y2;
        int ballLeft    = x_ball;
        int ballRight   = x_ball + BALL_WIDTH;
        int ballBottom  = y;
        if(((ballLeft>spikeLeft && ballLeft<spikeRight) || (ballRight>spikeLeft && ballRight<spikeRight) )&& ballBottom < spikeTop){
            touching_spike = 1;
        }
        else if(spikeLeft>ballLeft && spikeRight<ballRight && ballBottom < spikeTop){
            touching_spike = 1;
        }
    }

}

void Finished(int y1) {
    if (x > y1) {
        scoreIncrease=0;
        if (level < 3) {
            x = 0;
            y = floor_game;
            health = 100;
            level++;
        }
        else if (level == 3) {
            Take_name();
            show_score(aa);
        }
    }
}


void show_score(bool f){
    if(f){
        iShowImage(0,0,"assets/images/levels/Bg.jpg");
        iShowText(118,338,"Congratulations" , "assets/fonts/congo.ttf",179);
        char scored[100];
        int q = score ;
        sprintf(scored,"Your score is %d ",q);
        iShowText(238,177,scored , "assets/fonts/Mkc.ttf",99);
        iTextAdvanced(319,20,"Press c to continue....",0.5,5.0);
    }
    if(c && f){
        aa = false;
        //pressed =1;
        entering_name=1;
        c=0;
    }


}

void Load_spider(int n1,coordinates*ptr){
    for(int i = 0 ; i < n1 ; i++){
        if(x>ptr[i].x1){
            char c[100];
            int u = ptr[i].x1-x+1280;
            sprintf(c,"assets/images/sprites/spider/sp.png");
            if(i > 6) sprintf(c,"assets/images/sprites/spider/boss.png");
            iShowImage(u,sp_y,c);
        }
    }


}

void update_spider(){
    sp_y += direction * sp_speed;
    if (sp_y <= 80 || sp_y+190 >= 620) {
        direction *= -1;
    }

}

void load_game(){
    FILE * fp = fopen("saved.txt" , "r");
    fscanf(fp , "%d %d %d %d %d" , &level , &x , &y ,&health,&score);
    fclose(fp);
    pressed = 2;
}

void update_saved(){
    FILE*ofp = fopen("saved.txt" , "w");
    fprintf(ofp , "%d %d %d %d %d" , level,x,y,health,score);
    fclose(ofp);
}
int save_to_leaderboard(const char *name, int score) {
    char lines[21][100];
    int scores[21];
    int counter = 0;

    FILE *fp = fopen("leaderboard.txt", "r");
    if (fp != NULL) {
        while (counter < 20 && fgets(lines[counter], sizeof lines[counter], fp) != NULL) {
            char tempName[50];
            int tempScore;
            if (sscanf(lines[counter], "%49s %d", tempName, &tempScore) == 2) {
                scores[counter] = tempScore;
            } else {
                scores[counter] = 0;
            }
            counter++;
        }
        fclose(fp);
    }
    int highestExistingScore = -1;
    for (int i = 0; i < counter; i++) {
        char tempName[50];
        int tempScore;
        if (sscanf(lines[i], "%49s %d", tempName, &tempScore) == 2) {
            if (strcmp(tempName, (name && *name) ? name : "PLAYER") == 0) {
                highestExistingScore = tempScore;
            }
        }
    }
    if (highestExistingScore == -1 || score > highestExistingScore) {
        if (counter < 5 || score > scores[4]) {
            if (counter < 21) {
                snprintf(lines[counter], sizeof lines[counter], "%s %d\n",
                         (name && *name) ? name : "PLAYER", score);
                scores[counter] = score;
                counter++;
            }
            for (int i = 0; i < counter - 1; i++) {
                for (int j = i + 1; j < counter; j++) {
                    if (scores[j] > scores[i]) {
                        int tmpScore = scores[i];
                        scores[i] = scores[j];
                        scores[j] = tmpScore;

                        char tmpLine[100];
                        strcpy(tmpLine, lines[i]);
                        strcpy(lines[i], lines[j]);
                        strcpy(lines[j], tmpLine);
                    }
                }
            }
            fp = fopen("leaderboard.txt", "w");
            if (!fp) {
                perror("leaderboard.txt");
                return 1;
            }
            int written = 0, lastScore = -1;
            for (int i = 0; i < counter && written < 5; i++) {
                if (scores[i] != lastScore) {
                    fputs(lines[i], fp);
                    lastScore = scores[i];
                    written++;
                }
            }
            fclose(fp);
        }
    }
    return 0;
}


void load_leaderboard() {
    FILE *fp = fopen("leaderboard.txt", "r");
    leaderboard_count = 0;
    if (fp != NULL) {
        int lastScore = -1;
        while (leaderboard_count < 5 &&
               fgets(leaderboard_lines[leaderboard_count], sizeof leaderboard_lines[leaderboard_count], fp) != NULL) {
            int currentScore;
            char tempName[50];
            if (sscanf(leaderboard_lines[leaderboard_count], "%49s %d", tempName, &currentScore) == 2) {
                leaderboard_lines[leaderboard_count][strcspn(leaderboard_lines[leaderboard_count], "\r\n")] = '\0';
                if (currentScore != lastScore) {
                    lastScore = currentScore;
                    leaderboard_count++;
                }
            }
        }
        fclose(fp);
    }
}

void show_leaderboard_on_screen() {
    iShowImage(0, 0, "assets/images/bg/leaderboard.jpg");
    int display_count = (leaderboard_count < 5) ? leaderboard_count : 5;
    for (int i = 0; i < display_count; i++) {
        int scoren;
        char tempo[100];
        sscanf(leaderboard_lines[i] , "%s %d" , tempo , &scoren);
        char scre[100];
        sprintf(scre,"%d",scoren);
        iShowText(265,355 - i*65 , tempo ,"assets/fonts/Game.ttf" , 55);
        iShowText(870,355 - i*65 , scre,"assets/fonts/Game.ttf" , 55);
    }
    iShowText(238, 20, "Press  'c'  to  return  to  menu","assets/fonts/Game.ttf" , 55);
}

void leaderboard() {
    load_leaderboard();
    show_leaderboard_on_screen();
}

void Take_name(){
    iShowImage(0, 0, "assets/images/bg/inputBG.jpg");
    iTextAdvanced(330, 50, "Enter your surname only", 0.4, 2.2);
    iTextAdvanced(150, 150, "Press ENTER to submit", 0.6, 5.0);
    iShowText(200,330,player_name,"assets/fonts/starcraft.ttf",138);
}

void mute_function(){
    if(soundOn){
        iShowImage(560, 645, "assets/images/bg/green.png");
        iResumeSound(sound);
    }
    else{
        iShowImage(560, 645, "assets/images/bg/red.png");
        iPauseSound(sound);
    }
}



