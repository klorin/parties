#include <stdio.h>
#include "member.h"
#include <stdlib.h>
#include "set.h"

int main() {
    printf("Hello, World!\n");
    Member member1 = memberCreate("yossi", "234567892", 'M', 2);
    Member member2 = memberCopy(member1);
    int i = memberCompare(member1, member2);
    printf("%d\n", i);
    memberDestroy(member1);
    char* name1 = memberGetName(member2);
    printf("%s\n", name1);
    char* id1 = memberGetId(member2);
    printf("%s\n", id1);
    printf("%d\n", memberGetGender(member2));
    printf("%d\n", memberGetNumber(member2));
    free(name1);
    free(id1);
    memberDestroy(member2);
}
