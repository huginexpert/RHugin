#include "R.h"
#include "Rdefines.h"
#include "R_ext/Rdynload.h"
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


/* little doohickey to store open log file info */

#ifndef WIN32
  typedef struct {
    FILE *p_file;
    char *filename;
  } log_file_info;

  log_file_info *RHugin_open_log_file(const char *filename);
  log_file_info *RHugin_close_log_file(log_file_info *lfi);
#endif

DLLEXPORT SEXP RHugin_domain_get_logfile(SEXP Sdomain);


/* Finalizer */

void RHugin_domain_finalizer(SEXP Sdomain);


/* Safe accessor methods for Hugin objects */

h_domain_t domainPointerFromSEXP(SEXP Sdomain);
h_node_t nodePointerFromSEXP(SEXP Snode);
h_table_t tablePointerFromSEXP(SEXP Stable);
h_expression_t expressionPointerFromSEXP(SEXP Sexpression);
h_model_t modelPointerFromSEXP(SEXP Smodel);
h_junction_tree_t jtPointerFromSEXP(SEXP Sjt);
h_clique_t cliquePointerFromSEXP(SEXP Sclique);
h_class_t classPointerFromSEXP(SEXP Sclass);

/* Other utility functions */

void RHuginFileParseError(h_location_t line, h_string_t message, void *data);
void RHuginExpressionParseError(h_location_t index, h_string_t message, void *data);


