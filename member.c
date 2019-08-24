//
// Created by Roy on 23/08/19.
//

#include "member.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#define ID_LENGTH 9
struct member_t {
    char* member_name;
    char* member_id;
    Gender member_gender;
    int member_number;
};

Member memberCreate(const char* given_name, const char* given_id, char
given_gender, int given_number){
    assert(given_name && given_id);
    Member member = malloc(sizeof(*member));
    if (!member) return NULL;
    int name_length = (int)strlen(given_name);
    member->member_name = malloc((name_length+1)*(sizeof(char)));
    if (member->member_name == NULL) {
        free(member);
        return NULL;
    }
    strcpy(member->member_name, given_name);
    member->member_id = malloc((ID_LENGTH+1)*(sizeof(char)));
    if (member->member_id == NULL) {
        free(member);
        return NULL;
    }
    strcpy(member->member_id, given_id);
    assert(given_gender == 'M' || given_gender == 'F');
    if (given_gender == 'M') member->member_gender = given_gender;
    if (given_gender == 'F') member->member_gender = given_gender;
    member->member_number = given_number;
    return member;
}

void memberDestroy(Member member){
    if (!member) return;
    assert(member->member_id);
    assert(member->member_name);
    free(member->member_name);
    free(member->member_id);
    free(member);
}

Member memberCopy(Member copied_member) {
    if (!copied_member) return NULL;
    assert(copied_member->member_name && copied_member->member_id);
    Member new_member = memberCreate(copied_member->member_name,
            copied_member->member_id,
            copied_member->member_gender, copied_member->member_number);
    assert (new_member);
    return new_member;
}

char* memberGetName(Member member){
    assert(member);
    int name_copy_length = (int)strlen(member->member_name);
    char* name_copy = malloc((name_copy_length+1)*sizeof(char));
    assert(name_copy);
    strcpy (name_copy, member->member_name);
    return name_copy;
}

char* memberGetId(Member member){
    assert(member);
    char* id_copy = malloc((ID_LENGTH+1)*(sizeof(char)));
    assert(id_copy);
    strcpy (id_copy, member->member_id);
    return id_copy;
}

Gender memberGetGender(Member member){
    assert(member);
    return member->member_gender;
}

int memberGetNumber(Member member){
    assert(member);
    return member->member_number;
}

int  memberCompare(Member member_1, Member member_2) {
    assert (member_1 && member_2);
    if (member_1->member_number > member_2->member_number) return 1;
    if (member_1->member_number == member_2->member_number)
        return 0;
    else return -1;
}


// 3 Member functions to pass to Member's Set as void*
int memberCompareShell(void *member_1, void *member_2) {
    assert (member_1 && member_2);
    return memberCompare((Member) member_1, (Member) member_2);
}

void *memberCopyShell(void *member_to_copy) {
    return memberCopy((Member) member_to_copy);
}

void memberDestroyShell(void *member_to_destroy) {
    memberDestroy((Member) member_to_destroy);
}
/////////////////////////