#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
char *reverse(char *input) {
    int len = strlen(input);
    char *output=malloc(sizeof(char)*(len));
    for (int i = 0; i < len; i++) {
        output[len - i - 1] = input[i];
    }
    assert(output[len]=='\0');
    return output;
}
int main(){
    printf("%s\n",reverse("basi qkoto"));
}
