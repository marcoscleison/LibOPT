#include "ba.h"

/* It updates the velocity of an agent (bat)
Parameters:
S: search space
i: particle's index */
void UpdateBatVelocity(SearchSpace *s, int i){
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @UpdateBatVelocity.\n");
        exit(-1);
    }
     
    int j;
    
    for(j = 0; j < s->n; j++)
        s->a[i]->v[j] = s->a[i]->v[j]+(s->a[i]->x[j]-s->g[j])*s->a[i]->f;
}

/* It sets the frequency of an agent (bat)
Parameters:
S: search space
i: particle's index */ 
void SetBatFrequency(SearchSpace *s, int i){
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @SetBatFrequency.\n");
        exit(-1);
    }
    
    double beta = GenerateRandomNumber(0,1);
    s->a[i]->f = s->f_min+(s->f_max-s->f_min)*beta;
}

/* It evaluates the entire search space
Parameters:
s: search space
EvaluateFun: pointer to the function used to evaluate particles (agents)
arg: list of additional arguments */
/*void EvaluateBats(SearchSpace *s, prtFun Evaluate, va_list arg){
    va_list argtmp;
    int i, j;
    double f;
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @EvaluateBats.\n");
        exit(-1);
    }
    
    va_copy(argtmp, arg);
    for(i = 0; i < s->m; i++){
        f = Evaluate(s->a[i], arg); /* It executes the fitness function for agent i */
                    
        /*if(s->a[i]->fit < s->gfit){ /* It updates the global best value and position */
          /*  s->gfit = s->a[i]->fit;
            for(j = 0; j < s->n; j++)
                s->g[j] = s->a[i]->x[j];
        }
        
        va_copy(arg, argtmp);
    }
}*/

/* It executes the Bat Algorithm for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runBA(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i;
    double beta, prob;
    		
    va_start(arg, Evaluate);
    va_copy(argtmp, arg);
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runBA.\n");
        exit(-1);
    }
        
    EvaluateSearchSpace(s, Evaluate, arg); /* Initial evaluation of the search space */
        
    /*for(t = 1; t <= s->iterations; t++){
        fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);
        va_copy(arg, argtmp);
            
        /* for each particle */
       /* for(i = 0; i < s->m; i++){
            UpdateParticleVelocity(s, i);
            UpdateParticlePosition(s, i);
            CheckAgentLimits(s, s->a[i]);
        }
	        			
	EvaluateSwarm(s, Evaluate, arg);
        va_copy(arg, argtmp);            
	        
	fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }*/

    va_end(arg);
}
/*************************/