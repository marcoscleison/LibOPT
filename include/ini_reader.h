/* 
 * File:   ini_reder.h
 * Author: Marcos Cleison Silva Santana
 *
 * 
 */

#ifndef INI_REDER_H
#define INI_REDER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MATCH
#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(key, n) == 0
#endif

    //#ifndef REQUIRE_NON_NULL
    //#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(key, n) == 0
    //#endif   

    typedef struct _IniItems {
        char *section;
        char *key;
        char *value;

        struct _IniItems *next;

    } IniItems;

    IniItems* NewIniItems();

    IniItems* NewIniItemsValues(const char *section, const char *key, const char *value);

    IniItems* AppendIniItems(IniItems* self, IniItems* item);

    IniItems* AppendIniItemsValues(IniItems* self, const char *section, const char *key, const char *value);


    void PrintIniItems(IniItems* self);



    const char* getIniItem(IniItems* self, const char *section, const char *key);

    const char* getIniValueAsString(IniItems* self, const char *section, const char *key, const char *_default);

    int getIniValueAsInt(IniItems* self, const char *section, const char *key, int _default);

    float getIniValueAsFloat(IniItems* self, const char *section, const char *key, float _default);
    
    float getIniArrayAsFloat(IniItems* self, const char *section, const char *key, int index, float _default);

    int IniKeyExists(IniItems* self, const char *section, const char *key);

    int IniKeyNonNullExists(IniItems* self, const char *section, const char *key);
    int IniKeyNonNullExistsOrAbort(IniItems* self, const char *section, const char *key, const char *msg);


    int ReadSearchSpaceFromInitFileHandle(void* data, const char* section, const char* name,
            const char* value);

    IniItems* LoadIniFile(const char *filepath);







#ifdef __cplusplus
}
#endif

#endif /* INI_REDER_H */

