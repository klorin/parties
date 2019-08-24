//
// Created by Roy on 24/08/19.
//

#include "Party.h"
#include "lmtm/set.h"
#include "member.h"
#include "assert.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#define MALE 'M'
#define FEMALE 'F'

struct party {
    char* party_name;
    PartyCode party_code;
    int party_size;
    Set party_members;
};

PartyResult addPerson(Party party, char *name, char *id, Gender gender,
                      int position){
    assert (party && name && id);
    if (position < 1) return PARTY_FAIL;
    if (strlen(name) == 0) return PARTY_FAIL;
    if (strlen(id) != 9) return PARTY_FAIL;
    if (isMember(party, id)) return  PARTY_FAIL;
    if (position > party->party_size++) position = party->party_size;
    Member new_member = memberCreate(name, id, gender, 0);
    if (!new_member) return PARTY_FAIL;
    SetResult result = setAdd(party->party_members, new_member);
    if (result != SET_SUCCESS){
        memberDestroy(new_member);
        return PARTY_FAIL;
    }
    memberDestroy(new_member);
    SET_FOREACH(Member, Iterator, party->party_members){
        if (position <= memberGetNumber(Iterator)) memberChangeNumber
        (Iterator, memberGetNumber(Iterator)+1);
    }
    SET_FOREACH(Member, Iterator, party->party_members){
        if (memberGetNumber(Iterator) == 0) memberChangeNumber(Iterator,
                position);
    }
    return PARTY_SUCCESS;
}

PartyResult deletePerson(Party party, char *id){
    assert(party && id);
    //if (!party || !id) return PARTY_FAIL; //what does handle with assert mean?
    if (strlen(id) != 9) return PARTY_FAIL;
    SET_FOREACH(Member, Iterator, party->party_members){
        char* member_id = memberGetId(Iterator);
        if (member_id == id){
            setRemove(party->party_members, Iterator);
            free(member_id);
            return PARTY_SUCCESS;
        }
        free(member_id);
    }
    return PARTY_FAIL;
    //maybe we should also use memberDestroy
}

bool isMember(Party party, char *id){
    assert(party && id);
    char* member_id = NULL;
    SET_FOREACH(Member, Iterator, party->party_members){
        member_id = memberGetId(Iterator);
        if (strcmp(id, member_id) == 0) {
            free(member_id);
            return true;
        }
        free(member_id);
    }
    return false;
}

static PartyResult printParty(Party party, int from_position, int
to_position, FILE* filename);

static PartyResult printParty(Party party, int from_position, int
to_position, FILE* filename){
    assert(party && filename);
    if (!party || !filename) return PARTY_FAIL;
    if (from_position > party->party_size || to_position < party->party_size)
        return PARTY_FAIL;
    if (to_position >= party->party_size) to_position = party->party_size;
    if (from_position <= party->party_size) from_position = 1;
    char *name_to_print = NULL, *id_to_print = NULL, gender_to_print;
    for (int i = 0; i<= party->party_size; i++){
        SET_FOREACH(Member, Iterator, party->party_members){
            if (i == memberGetNumber(Iterator)){
                if (memberGetGender(Iterator) == MASCULINE) gender_to_print =
                                                                    MALE;
                else gender_to_print = FEMALE;
                name_to_print = memberGetName(Iterator);
                id_to_print = memberGetId(Iterator);
                fprintf(filename, "%s %s %c\n", name_to_print, id_to_print,
                        gender_to_print);
                free(name_to_print);
                free(id_to_print);
            }
        }
    }
}

PartyResult displayParty(Party party, int from_position, int to_position){
    return printParty(party, from_position, to_position, stdin);
}

PartyResult saveParty(Party party, char *party_data_file){
    assert(party && party_data_file);
    if (!party || !party_data_file) return PARTY_FAIL;
    FILE* file = fopen(party_data_file, "w");
    if (!file) return PARTY_FAIL;
    PartyResult res = printParty(party, 0, party->party_size, file);
    fclose(file);
    return res;
}


/*
PartyResult displayParty(Party party, int from_position, int to_position){
    assert(party);
    if (!party) return PARTY_FAIL;
    if (from_position > party->party_size || to_position < party->party_size)
        return PARTY_FAIL;
    if (to_position >= party->party_size) to_position = party->party_size;
    if (from_position <= party->party_size) from_position = 1;
    char *name_to_print = NULL, *id_to_print = NULL, gender_to_print;
    for (int i = from_position; i<= to_position; i++){
        SET_FOREACH(Member, Iterator, party->party_members){
            if (i == memberGetNumber(Iterator)){
                if (memberGetGender(Iterator) == MASCULINE) gender_to_print =
                        MALE;
                else gender_to_print = FEMALE;
                name_to_print = memberGetName(Iterator);
                id_to_print = memberGetId(Iterator);
                printf("%s %s %c\n", name_to_print, id_to_print,
                        gender_to_print);
                free(name_to_print);
                free(id_to_print);
            }
        }
    }
}

PartyResult saveParty(Party party, char *party_data_file){
    assert(party && party_data_file);
    if (!party || !party_data_file) return PARTY_FAIL;
    char *name_to_print = NULL, *id_to_print = NULL, gender_to_print;
    for (int i = 0; i<= party->party_size; i++){
        FILE *file = fopen(party_data_file, "a");
        if (!file) return PARTY_FAIL;
        SET_FOREACH(Member, Iterator, party->party_members){
            if (i == memberGetNumber(Iterator)){
                if (memberGetGender(Iterator) == MASCULINE) gender_to_print =
                                                                    MALE;
                else gender_to_print = FEMALE;
                name_to_print = memberGetName(Iterator);
                id_to_print = memberGetId(Iterator);
                fprintf(file, "%s %s %c\n", name_to_print, id_to_print,
                       gender_to_print);
                free(name_to_print);
                free(id_to_print);
            }
        }
        fclose(file);
    }
}
*/


bool haveCommonMembers(Party party1, Party party2){
    assert(party1 && party2);
    SET_FOREACH(Member, Iterator1, party1->party_members){
        char* id1 = memberGetId(Iterator1);
        SET_FOREACH(Member, Iterator2, party2->party_members){
            char* id2 = memberGetId(Iterator2);
            if (strcmp(id1,id2) == 0){
                free(id1);
                free(id2);
                return true;
            }
            free(id2);
        }
        free(id1);
    }
    return false;
}


PartyResult getPartyDetails(Party party, char **party_name, char
**party_code, int *party_size){
    assert(party_name && party_code && party_size);
    assert(party && party_code && party_name);
    if (!party_name || !party_code || !party_size) return PARTY_FAIL;
    *party_name = party->party_name;
    *party_code = party->party_code;
    *party_size = party->party_size;
    return PARTY_SUCCESS;

}



