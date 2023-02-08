#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//https://fr.wikipedia.org/wiki/Liste_des_pays_du_monde


enum Continent{EUROPE, ASIE, AFRIQUE, AMERIQUE, OCEANIE};
enum Variable{name, population, surface, pib, littoral, continent};


typedef struct {
    char name[30];
    int isRel;
    enum Variable variable;
    int isBigger;
    enum Continent continent;
    int value;
    char letter;
} Condition;


typedef struct {
    char name[30];
    int population, surface, pib, littoral;
    enum Continent continent;
    int possible, potential;
    char not_cond[12];
    int numeric_reason;
} Country;

const int NB_COUNTRY = 196;
const int NB_CONDITION;
void set_data();
Country data[196] = {0};
int count_possible = NB_COUNTRY;
int right_answer;
int num_reason = 1;

int main(void) {
    srand(time(NULL));
    set_data();
    int nb_error = 0;
    char previous_answer[30];
    int rand_country = 0;
    int count_potential;
    char answer[30];
    while (count_possible > 1) {
        right_answer = 0;
        do {
            rand_country = floor((float)rand()/RAND_MAX * NB_COUNTRY);
        } while (data[rand_country].possible != 1);

        Condition cond;
        do {
            cond.isRel = 0;
            for (int i = 0; i < NB_COUNTRY; i++) {
                data[i].potential = data[i].possible;
            }
            int rand_cond = floor((float)rand()/RAND_MAX * 6);
            count_potential = 0;
            int rand_rel;
            rand_rel = floor((float)rand()/RAND_MAX * 10);
            switch (rand_cond) {
                case 0:
                    cond.variable = name;
                    int rand_idx = floor((float)rand()/RAND_MAX * strlen(data[rand_country].name));
                    cond.letter = data[rand_country].name[rand_idx];
                    for (int i = 0; i < NB_COUNTRY; i++) {
                        if (data[i].possible == 1) {
                            for (int j = 0; j < (int)strlen(data[i].name); j++) {
                                if (data[i].name[j] == cond.letter) {
                                    data[i].potential = 1;
                                    count_potential++;
                                    break;
                                }
                                data[i].potential = 0;
                                strcpy(data[i].not_cond, "nom");
                            }
                        }
                    }
                    break;
                case 1:
                    cond.variable = population;
                    if (rand_rel < 6) {
                        cond.isRel = 0;
                        if (data[rand_country].population > 30000000) {
                            cond.isBigger = 1;
                            cond.value = 30000000;
                        } else {
                            if (data[rand_country].population > 10000000) {
                                cond.isBigger = 1;
                                cond.value = 10000000;
                            } else {
                                if (data[rand_country].population < 1500000) {
                                    cond.isBigger = 0;
                                    cond.value = 1500000;
                                } else {
                                    cond.isBigger = 0;
                                    cond.value = 10000000;
                                }
                            }
                        }
                    } else {
                        cond.isRel = 1;
                        do{
                            rand_rel = floor((float)rand()/RAND_MAX * NB_COUNTRY);
                        } while (rand_rel == rand_country); 
                        if (data[rand_rel].population > data[rand_country].population) {
                            cond.isBigger = 0;
                            cond.value = data[rand_rel].population;
                        } else {
                            cond.isBigger = 1;
                            cond.value = data[rand_rel].population;
                        }
                        strcpy(cond.name, data[rand_rel].name);                        
                    }
                    for (int i = 0; i < NB_COUNTRY; i++) {
                        if (data[i].possible == 1) {
                            if (cond.isBigger == 1) {
                                if (data[i].population >= cond.value) {
                                    count_potential++;
                                    data[i].potential = 1;
                                } else {
                                    data[i].potential = 0;
                                    strcpy(data[i].not_cond, "population");
                                    data[i].numeric_reason = data[i].population;
                                }
                            } else {
                                if (data[i].population <= cond.value) {
                                    count_potential++;
                                    data[i].potential = 1;
                                } else {
                                    data[i].potential = 0;
                                    strcpy(data[i].not_cond, "population");
                                    data[i].numeric_reason = data[i].population;
                                }
                            }
                        }
                    }
                    break;
                case 2:
                    cond.variable = surface;
                    if (rand_rel < 6) {
                        cond.isRel = 0;
                        if (data[rand_country].surface > 500000) {
                            cond.isBigger = 1;
                            cond.value = 500000;
                        } else {
                            if (data[rand_country].surface > 100000) {
                                cond.isBigger = 1;
                                cond.value = 100000;
                            } else {
                                if (data[rand_country].surface < 20000) {
                                    cond.isBigger = 0;
                                    cond.value = 20000;
                                } else {
                                    cond.isBigger = 0;
                                    cond.value = 100000;
                                }
                            }
                        }
                    } else {
                        cond.isRel = 1;
                        do{
                            rand_rel = floor((float)rand()/RAND_MAX * NB_COUNTRY);
                        } while (rand_rel == rand_country); 
                        if (data[rand_rel].surface > data[rand_country].surface) {
                            cond.isBigger = 0;
                            cond.value = data[rand_rel].surface;
                        } else {
                            cond.isBigger = 1;
                            cond.value = data[rand_rel].surface;
                        }
                        strcpy(cond.name, data[rand_rel].name);                        
                    }
                    for (int i = 0; i < NB_COUNTRY; i++) {
                        if (data[i].possible == 1) {
                            if (cond.isBigger == 1) {
                                if (data[i].surface >= cond.value) {
                                    count_potential++;
                                    data[i].potential = 1;
                                } else {
                                    data[i].potential = 0;
                                    strcpy(data[i].not_cond, "superficie");
                                    data[i].numeric_reason = data[i].surface;
                                }
                            } else {
                                if (data[i].surface <= cond.value) {
                                    count_potential++;
                                    data[i].potential = 1;
                                } else {
                                    data[i].potential = 0;
                                    strcpy(data[i].not_cond, "superficie");
                                    data[i].numeric_reason = data[i].surface;
                                }
                            }
                        }
                    }
                    break;
                case 3:
                    cond.variable = pib;
                    if (rand_rel < 6) {
                        if (data[rand_country].pib > 1000) {
                            cond.isBigger = 1;
                            cond.value = 1000;
                        } else {
                            if (data[rand_country].pib > 100) {
                                cond.isBigger = 1;
                                cond.value = 100;
                            } else {
                                if (data[rand_country].pib < 10) {
                                    cond.isBigger = 0;
                                    cond.value = 10;
                                } else {
                                    cond.isBigger = 0;
                                    cond.value = 100;
                                }
                            }
                        }
                    } else {
                        cond.isRel = 1;
                        do{
                            rand_rel = floor((float)rand()/RAND_MAX * NB_COUNTRY);
                        } while (rand_rel == rand_country); 
                        if (data[rand_rel].pib > data[rand_country].pib) {
                            cond.isBigger = 0;
                            cond.value = data[rand_rel].pib;
                        } else {
                            cond.isBigger = 1;
                            cond.value = data[rand_rel].pib;
                        }
                        strcpy(cond.name, data[rand_rel].name);                        
                    }
                    for (int i = 0; i < NB_COUNTRY; i++) {
                        if (data[i].possible == 1) {
                            if (cond.isBigger == 1) {
                                if (data[i].pib >= cond.value) {
                                    count_potential++;
                                    data[i].potential = 1;
                                } else {
                                    data[i].potential = 0;
                                    strcpy(data[i].not_cond, "pib");
                                    data[i].numeric_reason = data[i].pib;
                                }
                            } else {
                                if (data[i].pib <= cond.value) {
                                    count_potential++;
                                    data[i].potential = 1;
                                } else {
                                    data[i].potential = 0;
                                    strcpy(data[i].not_cond, "pib");
                                    data[i].numeric_reason = data[i].pib;
                                }
                            }
                        }
                    }
                    break;
                case 4:
                    cond.variable = littoral;
                    cond.value = data[rand_country].littoral;
                    for (int i = 0; i < NB_COUNTRY; i++) {
                        if (data[i].possible == 1) {
                            if (data[i].littoral == cond.value) {
                                count_potential++;
                                data[i].potential = 1;
                            } else {
                                data[i].potential = 0;
                                strcpy(data[i].not_cond, "littoral");
                            }
                        }
                    }
                    break;
                case 5:
                    cond.variable = continent;
                    cond.continent = data[rand_country].continent;
                    for (int i = 0; i < NB_COUNTRY; i++) {
                        if (data[i].possible == 1) {
                            if (data[i].continent == cond.continent) {
                                count_potential++;
                                data[i].potential = 1;
                            } else {
                                data[i].potential = 0;
                                strcpy(data[i].not_cond, "continent");
                            }
                        }
                    }
                    break;
            }
        } while (count_potential >= count_possible);
        switch (cond.variable) {
            case continent:
                switch (cond.continent) {
                    case EUROPE:
                        printf("Ce pays se situe en EUROPE");
                        break;
                    case AFRIQUE:
                        printf("Ce pays se situe en AFRIQUE");
                        break;
                    case ASIE:
                        printf("Ce pays se situe en ASIE");
                        break;
                    case AMERIQUE:
                        printf("Ce pays se situe en AMERIQUE");
                        break;
                    case OCEANIE:
                        printf("Ce pays se situe en OCEANIE");
                        break;
                }
                break;
            case littoral:
                if (cond.value == 1) {
                    printf("Ce pays possede un littoral");
                } else {
                    printf("Ce pays est enclave");
                }
                break;
            case pib:
                if (cond.isRel == 0) {
                    if (cond.isBigger == 1) {
                        printf("Ce pays a un pib de plus de %d milliards", cond.value);
                    } else {
                        printf("Ce pays a un pib de moins de %d milliards", cond.value);
                    }
                } else {
                    if (cond.isBigger == 1) {
                        printf("Ce pays est plus riche que '%s'", cond.name);
                    } else {
                        printf("Ce pays est moins riche que '%s'", cond.name);
                    }
                }
                break;
            case surface:
                if (cond.isRel == 0) {
                    if (cond.isBigger == 1) {
                        printf("Ce pays a une superficie de plus de %d %d%d%d %d%d%d km carre", cond.value / 1000000, (cond.value / 100000)%10, (cond.value / 10000)%10, (cond.value / 1000)%10, (cond.value / 100)%10, (cond.value / 10)%10, cond.value % 10);
                    } else {
                        printf("Ce pays a une superficie de moins de %d %d%d%d %d%d%d km carre", cond.value / 1000000, (cond.value / 100000)%10, (cond.value / 10000)%10, (cond.value / 1000)%10, (cond.value / 100)%10, (cond.value / 10)%10, cond.value % 10);
                    }
                } else {
                    if (cond.isBigger == 1) {
                        printf("Ce pays est plus grand que '%s'", cond.name);
                    } else {
                        printf("Ce pays est moins grand que '%s'", cond.name);
                    }
                }
                break;
            case population:
                if (cond.isRel == 0) {
                    if (cond.isBigger == 1) {
                        printf("Ce pays a plus de %d %d%d%d %d%d%d habitants", cond.value / 1000000, (cond.value / 100000)%10, (cond.value / 10000)%10, (cond.value / 1000)%10, (cond.value / 100)%10, (cond.value / 10)%10, cond.value % 10);
                    } else {
                        printf("Ce pays a moins de %d %d%d%d %d%d%d habitants", cond.value / 1000000, (cond.value / 100000)%10, (cond.value / 10000)%10, (cond.value / 1000)%10, (cond.value / 100)%10, (cond.value / 10)%10, cond.value % 10);
                    }
                } else {
                    if (cond.isBigger == 1) {
                        printf("Ce pays est plus peuple que '%s'", cond.name);
                    } else {
                        printf("Ce pays est moins peuple que '%s'", cond.name);
                    }
                }
                break;
            case name:
                printf("Ce pays contient un %c", cond.letter);
                break;
        }
        count_possible = count_potential;
        printf(" (%d)", count_possible);
        printf("\n");
        for (int i = 0; i < NB_COUNTRY; i++) {
            data[i].possible = data[i].potential;
        }
        
        do {
            int error = scanf("%s", answer);
            if (error != 1) return 1;
            if (strcmp(answer, ".") == 0) {
                strcpy(answer, previous_answer);
            }
            for (int i = 0; i < NB_COUNTRY; i++) {
                if (strcmp(data[i].name, answer) == 0) {
                    if (data[i].possible) {
                        right_answer = 1;
                        break;
                    } else {
                        printf("Ce pays n'est pas dans la bonne categorie '%s'", data[i].not_cond);
                        if (strcmp(data[i].not_cond, "pib") * strcmp(data[i].not_cond, "population") * strcmp(data[i].not_cond, "superficie") == 0 && num_reason == 1) {
                            printf(", sa valeur est %d", data[i].numeric_reason);
                        }
                        printf(", reessaye\n");
                        nb_error++;
                    }
                }
            }
        } while (right_answer == 0 && strcmp("abandon", answer) != 0);
        if (strcmp("abandon", answer) != 0) {
            printf("juste\n");
            strcpy(previous_answer, answer);
        } else {
            count_possible = 0;
        }
    }
    if (strcmp("abandon", answer) == 0) {
        printf("\nLe pays etait '%s'\n", data[rand_country].name);
    } else {
        printf("T'as gagne avec %d erreursw!\n", nb_error);
    }
    return 0;
}

void set_data() {
    Country c;
    int counter = 0;

    strcpy(c.name, "afghanistan");
    c.population = 37466414;
    c.surface = 652230;
    c.pib = 19;
    c.littoral = 0;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "afriquedusud");
    c.population = 56978635;
    c.surface = 1219912;
    c.pib = 419;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "albanie");
    c.population = 3088385;
    c.surface = 28748;
    c.pib = 17;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "algerie");
    c.population = 44487616;
    c.surface = 2381741;
    c.pib = 193;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "allemagne");
    c.population = 84079811;
    c.surface = 357588;
    c.pib = 4256;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "andorre");
    c.population = 79535;
    c.surface = 468;
    c.pib = 3;
    c.littoral = 0;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "angola");
    c.population = 33642646;
    c.surface = 1246700;
    c.pib = 175;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "antiguaetbarbuda");
    c.population = 99337;
    c.surface = 442;
    c.pib = 1;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "arabiesaoudite");
    c.population = 34173498;
    c.surface = 2149690;
    c.pib = 1040;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "argentine");
    c.population = 47327407;
    c.surface = 2791810;
    c.pib = 564;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "armenie");
    c.population = 3021324;
    c.surface = 29743;
    c.pib = 14;
    c.littoral = 0;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "australie");
    c.population = 26499819;
    c.surface = 7741200;
    c.pib = 1444;
    c.littoral = 1;
    c.continent = OCEANIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "autriche");
    c.population = 8859449;
    c.surface = 83871;
    c.pib = 479;
    c.littoral = 0;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "azerbaidjan");
    c.population = 10205810;
    c.surface = 86600;
    c.pib = 73;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "bahamas");
    c.population = 337721;
    c.surface = 13943;
    c.pib = 12;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "bahrein");
    c.population = 1442659;
    c.surface = 765;
    c.pib = 44;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "bangladesh");
    c.population = 162650853;
    c.surface = 147570;
    c.pib = 396;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "barbade");
    c.population = 294560;
    c.surface = 430;
    c.pib = 5;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "belgique");
    c.population = 11507163;
    c.surface = 30688;
    c.pib = 609;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "belize");
    c.population = 399598;
    c.surface = 22966;
    c.pib = 2;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "benin");
    c.population = 13301694;
    c.surface = 114763;
    c.pib = 10;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "bhoutan");
    c.population = 782318;
    c.surface = 38394;
    c.pib = 2;
    c.littoral = 0;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "bielorussie");
    c.population = 9477918;
    c.surface = 207600;
    c.pib = 59;
    c.littoral = 0;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "birmanie");
    c.population = 56590071;
    c.surface = 676578;
    c.pib = 69;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "bolivie");
    c.population = 11639909;
    c.surface = 1098581;
    c.pib = 41;
    c.littoral = 0;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "bosnieherzegovine");
    c.population = 3824782;
    c.surface = 51197;
    c.pib = 23;
    c.littoral = 0;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "botswana");
    c.population = 2317233;
    c.surface = 581726;
    c.pib = 15;
    c.littoral = 0;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "bresil");
    c.population = 215002523;
    c.surface = 8547404;
    c.pib = 1833;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "brunei");
    c.population = 464478;
    c.surface = 5765;
    c.pib = 35;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "bulgarie");
    c.population = 6838937;
    c.surface = 110944;
    c.pib = 89;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "burkinafaso");
    c.population = 20835401;
    c.surface = 274400;
    c.pib = 16;
    c.littoral = 0;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "burundi");
    c.population = 11865821;
    c.surface = 27834;
    c.pib = 3;
    c.littoral = 0;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "cambodge");
    c.population = 17227142;
    c.surface = 181035;
    c.pib = 28;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "cameroun");
    c.population = 27744989;
    c.surface = 475442;
    c.pib = 40;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "canada");
    c.population = 38654738;
    c.surface = 9984670;
    c.pib = 2221;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "capvert");
    c.population = 583255;
    c.surface = 4033;
    c.pib = 1;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "centreafrique");
    c.population = 5990855;
    c.surface = 622984;
    c.pib = 2;
    c.littoral = 0;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "chili");
    c.population = 19212000;
    c.surface = 755276;
    c.pib = 317;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "chine");
    c.population = 1411780000;
    c.surface = 9596960;
    c.pib = 17458;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "chypre");
    c.population = 1266676;
    c.surface = 9251;
    c.pib = 27;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "colombie");
    c.population = 51266000;
    c.surface = 1141748;
    c.pib = 351;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "comores");
    c.population = 1071229;
    c.surface = 2236;
    c.pib = 1;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "congo");
    c.population = 5400000;
    c.surface = 342000;
    c.pib = 14;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "republiquedemocratiqueducongo");
    c.population = 108407721;
    c.surface = 2345410;
    c.pib = 47;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "coreedunord");
    c.population = 25831360;
    c.surface = 120540;
    c.pib = 29;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "coreedusud");
    c.population = 51709098;
    c.surface = 100210;
    c.pib = 1804;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "costarica");
    c.population = 5111238;
    c.surface = 51100;
    c.pib = 65;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "cotedivoire");
    c.population = 29389150;
    c.surface = 322462;
    c.pib = 61;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "croatie");
    c.population = 3888529;
    c.surface = 56594;
    c.pib = 69;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "cuba");
    c.population = 11032343;
    c.surface = 110860;
    c.pib = 103;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "danemark");
    c.population = 5873420;
    c.surface = 2210579;
    c.pib = 399;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "djibouti");
    c.population = 1020333;
    c.surface = 23200;
    c.pib = 3;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "republiquedominicaine");
    c.population = 10499707;
    c.surface = 48670;
    c.pib = 109;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "dominique");
    c.population = 74243;
    c.surface = 754;
    c.pib = 1;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "egypte");
    c.population = 102334000;
    c.surface = 1001450;
    c.pib = 350;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "emiratsarabesunis");
    c.population = 9992083;
    c.surface = 82880;
    c.pib = 501;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "equateur");
    c.population = 17668000;
    c.surface = 256370;
    c.pib = 115;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "erythree");
    c.population = 3546000;
    c.surface = 117600;
    c.pib = 3;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "espagne");
    c.population = 46934632;
    c.surface = 505911;
    c.pib = 1435;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "estonie");
    c.population = 1228624;
    c.surface = 45339;
    c.pib = 37;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "eswatini");
    c.population = 1104479;
    c.surface = 17363;
    c.pib = 5;
    c.littoral = 0;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "etatsunis");
    c.population = 331449281;
    c.surface = 9833517;
    c.pib = 25346;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "ethiopie");
    c.population = 110871031;
    c.surface = 1127127;
    c.pib = 80;
    c.littoral = 0;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "fidji");
    c.population = 935974;
    c.surface = 18270;
    c.pib = 5;
    c.littoral = 1;
    c.continent = OCEANIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "finlande");
    c.population = 5527000;
    c.surface = 338145;
    c.pib = 297;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "france");
    c.population = 68014000;
    c.surface = 672051;
    c.pib = 2936;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "gabon");
    c.population = 2284912;
    c.surface = 267667;
    c.pib = 16;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "gambie");
    c.population = 2173999;
    c.surface = 11300;
    c.pib = 2;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "georgie");
    c.population = 3997000;
    c.surface = 69700;
    c.pib = 20;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "ghana");
    c.population = 32340248;
    c.surface = 238540;
    c.pib = 77;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "grece");
    c.population = 10432481;
    c.surface = 131957;
    c.pib = 222;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "grenade");
    c.population = 108890;
    c.surface = 344;
    c.pib = 1;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "guatemala");
    c.population = 17153288;
    c.surface = 344;
    c.pib = 91;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "guinee");
    c.population = 13885724;
    c.surface = 245857;
    c.pib = 17;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "guineebissau");
    c.population = 1833247;
    c.surface = 36120;
    c.pib = 1;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "guineeequatoriale");
    c.population = 1403000;
    c.surface = 28051;
    c.pib = 10;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "guyana");
    c.population = 750204;
    c.surface = 214970;
    c.pib = 13;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "haiti");
    c.population = 11067777;
    c.surface = 27750;
    c.pib = 20;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "honduras");
    c.population = 9182766;
    c.surface = 112090;
    c.pib = 30;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "hongrie");
    c.population = 9771827;
    c.surface = 93028;
    c.pib = 197;
    c.littoral = 0;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "inde");
    c.population = 1326093247;
    c.surface = 3287263;
    c.pib = 3534;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "indonesie");
    c.population = 270203917;
    c.surface = 1904569;
    c.pib = 1289;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "irak");
    c.population = 38872655;
    c.surface = 435052;
    c.pib = 297;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "iran");
    c.population = 84923314;
    c.surface = 1648195;
    c.pib = 427;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "irlande");
    c.population = 5011500;
    c.surface = 70273;
    c.pib = 516;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "islande");
    c.population = 376248;
    c.surface = 102775;
    c.pib = 27;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "israel");
    c.population = 9585000;
    c.surface = 20770;
    c.pib = 527;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "italie");
    c.population = 60359546;
    c.surface = 301336;
    c.pib = 2058;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "jamaique");
    c.population = 2808570;
    c.surface = 11425;
    c.pib = 15;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "japon");
    c.population = 125072000;
    c.surface = 377975;
    c.pib = 4912;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "jordanie");
    c.population = 10820644;
    c.surface = 89342;
    c.pib = 47;
    c.littoral = 0;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "kazakhstan");
    c.population = 19245793;
    c.surface = 2724900;
    c.pib = 193;
    c.littoral = 0;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "kenya");
    c.population = 47564296;
    c.surface = 580367;
    c.pib = 78;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "kirghizistan");
    c.population = 6018789;
    c.surface = 198500;
    c.pib = 9;
    c.littoral = 0;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "kiribati");
    c.population = 121000;
    c.surface = 811;
    c.pib = 263;
    c.littoral = 1;
    c.continent = OCEANIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "kosovo");
    c.population = 1958773;
    c.surface = 10908;
    c.pib = 8;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "koweit");
    c.population = 2993706;
    c.surface = 17818;
    c.pib = 186;
    c.littoral = 0;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "laos");
    c.population = 7447396;
    c.surface = 237955;
    c.pib = 17;
    c.littoral = 0;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "lesotho");
    c.population = 1969334;
    c.surface = 30355;
    c.pib = 2;
    c.littoral = 0;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "lettonie");
    c.population = 1907675;
    c.surface = 64559;
    c.pib = 40;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "liban");
    c.population = 5261372;
    c.surface = 10452;
    c.pib = 18;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "liberia");
    c.population = 5073296;
    c.surface = 111369;
    c.pib = 2;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "libye");
    c.population = 6890535;
    c.surface = 1759540;
    c.pib = 48;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "liechtenstein");
    c.population = 38079;
    c.surface = 160;
    c.pib = 6;
    c.littoral = 0;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "lituanie");
    c.population = 2731464;
    c.surface = 65303;
    c.pib = 69;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "luxembourg");
    c.population = 645397;
    c.surface = 2586;
    c.pib = 87;
    c.littoral = 0;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "macedoine");
    c.population = 1836713;
    c.surface = 25713;
    c.pib = 14;
    c.littoral = 0;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "madagascar");
    c.population = 26955737;
    c.surface = 587041;
    c.pib = 10;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "malaisie");
    c.population = 32652083;
    c.surface = 329750;
    c.pib = 439;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "malawi");
    c.population = 21196629;
    c.surface = 118844;
    c.pib = 0;
    c.littoral = 0;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "maldives");
    c.population = 391904;
    c.surface = 298;
    c.pib = 5;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "mali");
    c.population = 21473764;
    c.surface = 1241238;
    c.pib = 17;
    c.littoral = 0;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "malte");
    c.population = 457267;
    c.surface = 316;
    c.pib = 17;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "maroc");
    c.population = 37344787;
    c.surface = 446550;
    c.pib = 133;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "marshall");
    c.population = 59194;
    c.surface = 181;
    c.pib = 0;
    c.littoral = 1;
    c.continent = OCEANIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "maurice");
    c.population = 1379365;
    c.surface = 2040;
    c.pib = 14;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "mauritanie");
    c.population = 4005475;
    c.surface = 1030700;
    c.pib = 6;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "mexique");
    c.population = 129150971;
    c.surface = 1964375;
    c.pib = 1322;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "micronesie");
    c.population = 102624;
    c.surface = 702;
    c.pib = 0;
    c.littoral = 1;
    c.continent = OCEANIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "moldavie");
    c.population = 2681735;
    c.surface = 33851;
    c.pib = 14;
    c.littoral = 0;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "monaco");
    c.population = 39150;
    c.surface = 2;
    c.pib = 3;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "mongolie");
    c.population = 3168026;
    c.surface = 1564116;
    c.pib = 18;
    c.littoral = 0;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "montenegro");
    c.population = 609859;
    c.surface = 13812;
    c.pib = 6;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "mozambique");
    c.population = 27233789;
    c.surface = 801590;
    c.pib = 16;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "namibie");
    c.population = 2630073;
    c.surface = 825418;
    c.pib = 10;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "nauru");
    c.population = 9770;
    c.surface = 21;
    c.pib = 0;
    c.littoral = 1;
    c.continent = OCEANIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "nepal");
    c.population = 30327877;
    c.surface = 147516;
    c.pib = 36;
    c.littoral = 0;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "nicaragua");
    c.population = 6203441;
    c.surface = 129494;
    c.pib = 15;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "niger");
    c.population = 22772361;
    c.surface = 1267000;
    c.pib = 8;
    c.littoral = 0;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "nigeria");
    c.population = 219463862;
    c.surface = 923768;
    c.pib = 510;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "niue");
    c.population = 1591;
    c.surface = 260;
    c.pib = 0;
    c.littoral = 1;
    c.continent = OCEANIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "norvege");
    c.population = 5425270;
    c.surface = 385207;
    c.pib = 541;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "nouvellezelande");
    c.population = 84926551;
    c.surface = 268680;
    c.pib = 170;
    c.littoral = 1;
    c.continent = OCEANIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "oman");
    c.population = 4664844;
    c.surface = 309500;
    c.pib = 110;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "ouganda");
    c.population = 41487965;
    c.surface = 241550;
    c.pib = 21;
    c.littoral = 0;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "ouzbekistan");
    c.population = 30842796;
    c.surface = 447400;
    c.pib = 73;
    c.littoral = 0;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "pakistan");
    c.population = 220892331;
    c.surface = 881913;
    c.pib = 276;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "palaos");
    c.population = 21500;
    c.surface = 465;
    c.pib = 0;
    c.littoral = 1;
    c.continent = OCEANIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "panama");
    c.population = 4285850;
    c.surface = 75420;
    c.pib = 70;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "papouasienouvelleguinee");
    c.population = 8300000;
    c.surface = 462840;
    c.pib = 26;
    c.littoral = 1;
    c.continent = OCEANIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "paraguay");
    c.population = 7356409;
    c.surface = 406752;
    c.pib = 41;
    c.littoral = 0;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "paysbas");
    c.population = 17483925;
    c.surface = 41530;
    c.pib = 1013;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "perou");
    c.population = 31914989;
    c.surface = 1285216;
    c.pib = 240;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "philippines");
    c.population = 110818325;
    c.surface = 300400;
    c.pib = 411;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "pologne");
    c.population = 38282325;
    c.surface = 312679;
    c.pib = 699;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "portugal");
    c.population = 10302674;
    c.surface = 92090;
    c.pib = 251;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "qatar");
    c.population = 2444174;
    c.surface = 11586;
    c.pib = 225;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "roumanie");
    c.population = 21302893;
    c.surface = 238397;
    c.pib = 286;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "royaumeuni");
    c.population = 67886004;
    c.surface = 246690;
    c.pib = 3376;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "russie");
    c.population = 146170015;
    c.surface = 17234033;
    c.pib = 1829;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "rwanda");
    c.population = 12712431;
    c.surface = 26338;
    c.pib = 11;
    c.littoral = 0;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "saintchristophe");
    c.population = 53821;
    c.surface = 261;
    c.pib = 1;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "saintelucie");
    c.population = 166487;
    c.surface = 620;
    c.pib = 2;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "saintmarin");
    c.population = 33607;
    c.surface = 61;
    c.pib = 2;
    c.littoral = 0;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "saintvincent");
    c.population = 101390;
    c.surface = 389;
    c.pib = 1;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "salomon");
    c.population = 685097;
    c.surface = 28450;
    c.pib = 1;
    c.littoral = 1;
    c.continent = OCEANIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "salvador");
    c.population = 6481102;
    c.surface = 20742;
    c.pib = 30;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "samoa");
    c.population = 193483;
    c.surface = 2944;
    c.pib = 1;
    c.littoral = 1;
    c.continent = OCEANIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "saotome");
    c.population = 211122;
    c.surface = 1001;
    c.pib = 1;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "senegal");
    c.population = 16209125;
    c.surface = 196722;
    c.pib = 27;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "serbie");
    c.population = 7012165;
    c.surface = 88361;
    c.pib = 65;
    c.littoral = 0;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "seychelles");
    c.population = 96387;
    c.surface = 455;
    c.pib = 1;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "sierraleone");
    c.population = 6624933;
    c.surface = 71740;
    c.pib = 4;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "singapour");
    c.population = 6209660;
    c.surface = 719;
    c.pib = 424;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "slovaquie");
    c.population = 5452025;
    c.surface = 49035;
    c.pib = 118;
    c.littoral = 0;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "slovenie");
    c.population = 2102678;
    c.surface = 20273;
    c.pib = 63;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "somalie");
    c.population = 17066000;
    c.surface = 637657;
    c.pib = 5;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "soudan");
    c.population = 43120843;
    c.surface = 1886068;
    c.pib = 27;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "soudandusud");
    c.population = 10561244;
    c.surface = 619745;
    c.pib = 3;
    c.littoral = 0;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "srilanka");
    c.population = 23044123;
    c.surface = 65610;
    c.pib = 81;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "suede");
    c.population = 10508669;
    c.surface = 449965;
    c.pib = 621;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "suisse");
    c.population = 8738791;
    c.surface = 41285;
    c.pib = 841;
    c.littoral = 0;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "suriname");
    c.population = 597927;
    c.surface = 163270;
    c.pib = 3;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "syrie");
    c.population = 19398448;
    c.surface = 185180;
    c.pib = 36;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "tadjikistan");
    c.population = 8990874;
    c.surface = 143100;
    c.pib = 8;
    c.littoral = 0;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "tanzanie");
    c.population = 62092761;
    c.surface = 945087;
    c.pib = 33;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "tchad");
    c.population = 15946882;
    c.surface = 1284000;
    c.pib = 12;
    c.littoral = 0;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "republiquetcheque");
    c.population = 10701777;
    c.surface = 78870;
    c.pib = 296;
    c.littoral = 0;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "thailande");
    c.population = 70174459;
    c.surface = 514000;
    c.pib = 522;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "timororiental");
    c.population = 1321929;
    c.surface = 15410;
    c.pib = 2;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "togo");
    c.population = 8608444;
    c.surface = 56785;
    c.pib = 5;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "tonga");
    c.population = 105517;
    c.surface = 747;
    c.pib = 1;
    c.littoral = 1;
    c.continent = OCEANIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "triniteettobago");
    c.population = 1208789;
    c.surface = 5128;
    c.pib = 25;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "tunisie");
    c.population = 11722038;
    c.surface = 163610;
    c.pib = 39;
    c.littoral = 1;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "turkmenistan");
    c.population = 6031187;
    c.surface = 488100;
    c.pib = 76;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "turquie");
    c.population = 84680273;
    c.surface = 783562;
    c.pib = 692;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "tuvalu");
    c.population = 11342;
    c.surface = 26;
    c.pib = 0;
    c.littoral = 1;
    c.continent = OCEANIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "ukraine");
    c.population = 42153201;
    c.surface = 576604;
    c.pib = 142;
    c.littoral = 1;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "uruguay");
    c.population = 3387605;
    c.surface = 176220;
    c.pib = 64;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "vanuatu");
    c.population = 298333;
    c.surface = 12189;
    c.pib = 1;
    c.littoral = 1;
    c.continent = OCEANIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "vatican");
    c.population = 825;
    c.surface = 0;
    c.pib = 0;
    c.littoral = 0;
    c.continent = EUROPE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "venezuela");
    c.population = 28436066;
    c.surface = 916445;
    c.pib = 49;
    c.littoral = 1;
    c.continent = AMERIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "vietnam");
    c.population = 102789598;
    c.surface = 330967;
    c.pib = 408;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "yemen");
    c.population = 28498683;
    c.surface = 527968;
    c.pib = 28;
    c.littoral = 1;
    c.continent = ASIE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "zambie");
    c.population = 18380425;
    c.surface = 752614;
    c.pib = 26;
    c.littoral = 0;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;

    strcpy(c.name, "zimbabwe");
    c.population = 14546314;
    c.surface = 390745;
    c.pib = 13;
    c.littoral = 0;
    c.continent = AFRIQUE;
    c.possible = 1;
    c.potential = 1;
    data[counter] = c;
    counter++;
}