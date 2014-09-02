int
strlen(const char *str)
{
    int len = 0;

    while (*str++)
        len++;

    return len;
}

int
cmain(void)
{
    char str[] = "hello, world";
    unsigned char *video = (unsigned char *) 0xb8000;
    int i;

    for (i = 0; i < strlen(str); i++) {
        video[2*i] = str[i];
        video[2*i + 1] = 7;
    }

    return 0;
}
