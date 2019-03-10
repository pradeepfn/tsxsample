//
// Created by pfernando on 6/16/17.
//

#ifndef TSXSEQ_H
#define TSXSEQ_H

#include <immintrin.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_TSX_TRIES 3

extern unsigned int ntsx;
extern unsigned int nfallback;
extern unsigned int ntm;
extern unsigned int zero;
extern unsigned int capacity;
extern unsigned int conflict;
extern unsigned int tdebug;


static inline void tsxbegin(){
	int n_tries;
    unsigned int status;
    for(n_tries = 0; n_tries < MAX_TSX_TRIES; n_tries++) {
        status = _xbegin();
        if (status == _XBEGIN_STARTED) {
			ntsx++;
			ntm++;
            return;
        }else{
			if(status == 0){
				zero++;
			}
			if(status == _XABORT_CAPACITY){
				capacity++;
			}
			if(status == _XABORT_CONFLICT){
				conflict++;
			}
			if(status == _XABORT_DEBUG){
				tdebug++;
			}
		   	if(!(status & _XABORT_RETRY)){
				break;
			}
        }
    }   
    // fallback path
    nfallback++;
	ntm++;
}

static inline void tsxend(){
	if(_xtest()){
        _xend();
    }
}

#ifdef __cplusplus
}
#endif

#endif //TSXSEQ_H
