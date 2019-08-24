//
// Created by Roy on 23/08/19.
//

#ifndef PARTIES_member_H
#define PARTIES_member_H

typedef struct member_t* Member;
typedef enum gender_aux {MASCULINE , FEMININE} GenderAux;

Member memberCreate(const char* name, const char* id, char gender,
        int number);
void memberDestroy(Member member);
char* memberGetName(Member member);
char* memberGetId(Member member);
GenderAux memberGetGender(Member member);
int memberGetNumber(Member member);
Member memberCopy(Member copied_member);
int  memberCompare(Member member_1, Member member_2);
void memberChangeNumber(Member member, int number);

// 3 member functions to pass to member's Set as void*
int memberCompareShell(void *member_1, void *member_2);
void *memberCopyShell(void *member_to_copy);
void memberDestroyShell(void *member_to_destroy);
/////

/**
 * notes:
 * 1. this is a hidden mini-array to be used as a field in 'Party' struct.
 * 2. impelementation hasn't been tested yet.
 * 3. in my opinion Party struct should look like this:
 * party:

char* name
char* combination
int size
Set member

 */

#endif //PARTIES_member_H
