#include "common.h"
#include "function.h"
#include "pso.h"
#include "ini_reader.h"
#include<stdio.h>

int main() {

    // IniItems *params = LoadIniFile("../model_files/pso_ini_model.ini");

    /*
    PrintIniItems(params);

    const char* algo = getIniValueAsString(params, "algorith", "name", "None");

    printf("Algoritmo %s\n", algo);

    int np = getIniValueAsInt(params, "algorith", "number_particles", 0);
    printf("Number Particles %d\n", np);

    float w_min = getIniValueAsFloat(params, "PSO", "w_min", 0);

    printf("Number Particles %f\n", w_min);

    if (IniKeyExists(params, "PSO", "w_min")) {

        printf("PSO::W_min exists\n");
    } else {
        printf("PSO::W_min exists\n");
    }
    if (IniKeyExists(params, "PSO", "starter")) {

        printf("PSO::STARTER exists\n");
    } else {
        printf("PSO::STARTER does not exists\n");
    }

    if (IniKeyNonNullExists(params, "PSO", "starter")) {
        printf("PSO::STATER NON NULL exists\n");
    } else {
        printf("PSO::STATER NON NULL does not exists\n");
    }

     */

    SearchSpace *s = NULL;
    int i;

    ///IniItems *params = LoadIniFile("../model_files/pso_ini_model.ini");


    s = ReadSearchSpaceFromIniFile("../model_files/pso_ini_model.ini"); /* It reads the model file and creates a search space. We are going to use PSO to solve our problem. */

    InitializeSearchSpace(s, s->algorithm_id); /* It initalizes the search space */

    if (CheckSearchSpace(s, s->algorithm_id)) /* It checks wether the search space is valid or not */
        runPSO(s, Sphere); /* It minimizes function Sphere */

    DestroySearchSpace(&s, s->algorithm_id); /* It deallocates the search space */
    
    return 0;
}
