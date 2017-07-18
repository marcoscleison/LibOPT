#include "common.h"
#include "function.h"
#include "cs.h"

int main() {

    SearchSpace *s = NULL;
    int i;

    s = ReadSearchSpaceFromIniFile("../model_files/cs_ini_model.ini"); /* It reads the INI model  file and creates a search space. We are going to use PSO to solve our problem. */

    InitializeSearchSpace(s, s->algorithm_id); /* It initalizes the search space */

    if (CheckSearchSpace(s, s->algorithm_id)) /* It checks wether the search space is valid or not */
        runCS(s, Rosenbrock); /* It minimizes function Sphere */

    DestroySearchSpace(&s, s->algorithm_id); /* It deallocates the search space */


    return 0;
}
