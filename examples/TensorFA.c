#include "common.h"
#include "function.h"
#include "fa.h"

int main(){
    
    SearchSpace *s = NULL;
    int i;
    
    s = ReadSearchSpaceFromFile("examples/model_files/fa_model.txt", _FA_); /* It reads the model file and creates a search space. We are going to use FA to solve our problem. */
    
    s->t_g = AllocateTensor(s->n, _QUATERNION_);
    for (i = 0; i < s->m; i++)
        s->a[i]->t = AllocateTensor(s->n, _QUATERNION_); /* It allocates a new tensor for each agent */
        
    InitializeTensorSearchSpace(s, _QUATERNION_); /* It initializes the search space with tensors */
            
    if (CheckSearchSpace(s, _FA_)) /* It checks whether the search space is valid or not */
        runTensorFA(s, _QUATERNION_, Levy); /* It minimizes function Levy */
        
    DeallocateTensor(&s->t_g, s->n);
    for (i = 0; i < s->m; i++)
        DeallocateTensor(&s->a[i]->t, s->n); /* It deallocates the tensor for each agent */
    
    DestroySearchSpace(&s, _FA_); /* It deallocates the search space */
        
    return 0;
}
