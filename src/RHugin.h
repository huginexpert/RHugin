#include "R.h"
#include "Rinternals.h"
#include "Rdefines.h"
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


/* Error handling */

void RHugin_handle_error();
void RHugin_handle_error_code(h_error_t error_code);
void RHugin_handle_status_code(h_status_t status);


/* Finalizer */

void RHugin_finalizer(SEXP Sdomain);


/* Safe accessor methods for Hugin objects */

h_domain_t domainPointerFromSEXP(SEXP Sdomain);
h_node_t nodePointerFromSEXP(SEXP Snode);
h_table_t tablePointerFromSEXP(SEXP Stable);
h_expression_t expressionPointerFromSEXP(SEXP Sexpression);
h_model_t modelPointerFromSEXP(SEXP Smodel);
h_junction_tree_t jtPointerFromSEXP(SEXP Sjt);
h_clique_t cliquePointerFromSEXP(SEXP Sclique);


/* Other utility functions */

void RHuginParseError(h_location_t line, h_string_t message, void *data);


