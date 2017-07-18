/* 
 * File:   ini_reder.h
 * Author: Marcos Cleison Silva Santana
 *
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include <string.h>
#include <ini.h>
#include"ini_reader.h"

IniItems* NewIniItems() {

    IniItems *instance;

    instance = (IniItems*) malloc(sizeof (IniItems));

    if (instance == NULL) {
        fprintf(stderr, "Cannot create new IniItems @NewIniItems\n");
        exit(1);
    }

    instance->key = (char*) malloc(strlen("*") + 1);
    instance->value = (char*) malloc(strlen("*") + 1);
    instance->section = (char*) malloc(strlen("*") + 1);

    instance->key = "*";
    instance->value = "*";
    instance->section = "*";
    instance->next = NULL;

    return instance;

}

IniItems* NewIniItemsValues(const char *section, const char *key, const char *value) {

    IniItems *instance;

    instance = (IniItems*) NewIniItems();

    instance->key = (char*) malloc(strlen(key) + 1);
    instance->value = (char*) malloc(strlen(value) + 1);
    instance->section = (char*) malloc(strlen(section) + 1);

    strcpy(instance->key, key);
    strcpy(instance->value, value);
    strcpy(instance->section, section);

    instance->next = NULL;

    return instance;

}

IniItems* AppendIniItems(IniItems* self, IniItems* item) {

    IniItems* interator = NULL;

    if (self == NULL) {
        fprintf(stderr, "Cannot create new Self @AppendIniItems\n");
        exit(1);
        return NULL;
    }
    if (item == NULL) {
        fprintf(stderr, "Cannot create new item @AppendIniItems\n");
        exit(1);
        return NULL;
    }

    interator = self;

    while (interator->next != NULL) {

        interator = interator->next;
    }

    interator->next = item;

    return item;

}

void PrintIniItems(IniItems* self) {

    IniItems* iterator;

    iterator = (IniItems *) self;

    while (iterator != NULL) {

        printf(" [Section %s] %s = %s \n", iterator->section, iterator->key, iterator->value);

        iterator = iterator->next;
    }
}

IniItems* AppendIniItemsValues(IniItems* self, const char *section, const char *key, const char *value) {

    IniItems *item;

    item = NewIniItemsValues(section, key, value);

    return AppendIniItems(self, item);
}

const char* getIniItem(IniItems* self, const char *section, const char *key) {

    IniItems *iterator;
    iterator = self;


    while ((iterator != NULL)) {

        if (MATCH(iterator->section, iterator->key)) {
            return iterator->value;
        }

        iterator = iterator->next;
    }

    return NULL;

}

const char* getIniValueAsString(IniItems* self, const char *section, const char *key, const char *_default) {

    const char* value;

    value = getIniItem(self, section, key);

    if (value == NULL) {
        return _default;
    } else {
        return value;
    }

}

int getIniValueAsInt(IniItems* self, const char *section, const char *key, int _default) {
    const char* value;

    value = getIniItem(self, section, key);

    if (value == NULL) {
        return _default;
    } else {

        return atoi(value);

    }
}

float getIniValueAsFloat(IniItems* self, const char *section, const char *key, float _default) {
    const char* value;

    value = getIniItem(self, section, key);

    if (value == NULL) {
        return _default;
    } else {
        return strtod(value, NULL);

    }

}

float getIniArrayAsFloat(IniItems* self, const char *section, const char *key, int index, float _default) {

    char arr_key[255];

    sprintf(arr_key, "%s[%d]", key, index);
    
    return getIniValueAsFloat(self, section, arr_key, _default);
}

int IniKeyExists(IniItems* self, const char *section, const char *key) {

    IniItems *iterator;
    iterator = self;
    while ((iterator != NULL)) {
        if (MATCH(iterator->section, iterator->key)) {
            return 1;
        }
        iterator = iterator->next;
    }
    return 0;
}

int IniKeyNonNullExists(IniItems* self, const char *section, const char *key) {

    if (IniKeyExists(self, section, key)) {

        if ((getIniValueAsString(self, section, key, "") != "") && (strlen(getIniValueAsString(self, section, key, "")) > 0)) {

            return 1;
        } else {
            return 0;
        }


    } else {
        return 0;
    }

}

int IniKeyNonNullExistsOrAbort(IniItems* self, const char *section, const char *key, const char *msg) {

    if (IniKeyNonNullExists(self, section, key)) {

        return 1;
    } else {
        if (strlen(msg) > 0) {
            fprintf(stderr, "[%s::%s] %s", section, key, msg);
        } else {
            fprintf(stderr, "[%s::%s] Section and keys does not exists.\n", section, key);
        }
        exit(1);
    }
}

static int IniFileHandle(void* data, const char* section, const char* name,
        const char* value) {

    IniItems* params = (IniItems*) data;

    //printf("Section = %s\n",section);

    AppendIniItemsValues(params, section, name, value);

    return 1;
}

IniItems* LoadIniFile(const char *filepath) {

    IniItems *params;

    params = NewIniItems();

    if (ini_parse(filepath, IniFileHandle, params) < 0) {
        printf("Can't load 'INI'  @LoadIniFile\n");

        exit(1);
        return NULL;
    }

    return params;

}