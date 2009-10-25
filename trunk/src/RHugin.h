#include "R.h"
#include "Rinternals.h"
#include "R_ext/Rdynload.h"
#include "R_ext/Utils.h"
#include "R_ext/libextern.h"
#include "R_ext/BLAS.h"
#include "hugin.h"


#ifdef WIN32
  #define DLLEXPORT __declspec(dllexport)
#else
  #define DLLEXPORT  
#endif


/* RHugin initialization routine - automatically called by library.dynam */

DLLEXPORT void R_init_RHugin(DllInfo *info);


/* Safe accessor methods for Hugin objects */

h_domain_t domainPointerFromSEXP(SEXP Sdomain);
h_node_t nodePointerFromSEXP(SEXP Snode);
h_table_t tablePointerFromSEXP(SEXP Stable);
h_junction_tree_t jtPointerFromSEXP(SEXP Sjt);
h_clique_t cliquePointerFromSEXP(SEXP Sclique);


/* Other utility functions */

void RHuginParseNETError(h_location_t line, h_string_t message, void *data);


