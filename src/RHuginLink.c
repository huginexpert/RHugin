#include "RHugin.h"
#include "RHuginLink.h"

/* Global variables defined in RHugin.c */

extern SEXP RHugin_domain_tag;
extern SEXP RHugin_node_tag;
extern SEXP RHugin_table_tag;
extern SEXP RHugin_expression_tag;
extern SEXP RHugin_model_tag;
extern SEXP RHugin_junction_tree_tag;
extern SEXP RHugin_clique_tag;

extern SEXP RHUGIN_ERROR;

extern SEXP RHUGIN_CHANCE;
extern SEXP RHUGIN_UTILITY;
extern SEXP RHUGIN_DECISION;
extern SEXP RHUGIN_INSTANCE;

extern SEXP RHUGIN_DISCRETE;
extern SEXP RHUGIN_CONTINUOUS;

extern SEXP RHUGIN_LABELED;
extern SEXP RHUGIN_BOOLEAN;
extern SEXP RHUGIN_NUMBERED;
extern SEXP RHUGIN_INTERVAL;

extern SEXP RHUGIN_TM_CLIQUE_SIZE;
extern SEXP RHUGIN_TM_CLIQUE_WEIGHT;
extern SEXP RHUGIN_TM_FILL_IN_SIZE;
extern SEXP RHUGIN_TM_FILL_IN_WEIGHT;
extern SEXP RHUGIN_TM_TOTAL_WEIGHT;

extern SEXP RHUGIN_EQUILIBRIUM_SUM;
extern SEXP RHUGIN_EQUILIBRIUM_MAX;

extern SEXP RHUGIN_MODE_NORMAL;
extern SEXP RHUGIN_MODE_FAST_RETRACTION;

extern SEXP RHUGIN_CONSTRAINT_NONE;
extern SEXP RHUGIN_CONSTRAINT_EDGE_REQUIRED;
extern SEXP RHUGIN_CONSTRAINT_EDGE_FORBIDDEN;
extern SEXP RHUGIN_CONSTRAINT_FORWARD_EDGE_REQUIRED;
extern SEXP RHUGIN_CONSTRAINT_BACKWARD_EDGE_REQUIRED;
extern SEXP RHUGIN_CONSTRAINT_FORWARD_EDGE_FORBIDDEN;
extern SEXP RHUGIN_CONSTRAINT_BACKWARD_EDGE_FORBIDDEN;


/*******************************************************************************
  * The Hugin API 
*******************************************************************************/

/* Section 1.6 Errors */

SEXP RHugin_error_code(void)
{
  SEXP ret = R_NilValue;
  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_error_code();
  UNPROTECT(1);

  return ret;
}


/* Section 1.6.1 Handling errors */

SEXP RHugin_error_name(SEXP Scode)
{
  SEXP ret = R_NilValue;
  PROTECT(Scode = AS_INTEGER(Scode));
  PROTECT(ret = allocVector(STRSXP, 1));
  SET_STRING_ELT(ret, 0, mkChar( (char*) h_error_name(INTEGER(Scode)[0])));
  UNPROTECT(2);

  return ret;
}


SEXP RHugin_error_description(SEXP Scode)
{
  SEXP ret = R_NilValue;
  PROTECT(Scode = AS_INTEGER(Scode));
  PROTECT(ret = allocVector(STRSXP, 1));
  SET_STRING_ELT(ret, 0, mkChar( (char*) h_error_description(INTEGER(Scode)[0])));
  UNPROTECT(2);

  return ret;
}


/* Section 1.7 Taking advantage of multiple processors */

SEXP RHugin_domain_set_concurrency_level(SEXP Sdomain, SEXP Slevel)
{
  h_status_t status = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Slevel = AS_INTEGER(Slevel));
  status = h_domain_set_concurrency_level(domain, (size_t) INTEGER(Slevel)[0]);

  if((h_error_t) status != h_error_none) {
    UNPROTECT(1);
    RHugin_handle_error_code((h_error_t) status);
  }

  UNPROTECT(1);
  return R_NilValue;
}
  

SEXP RHugin_domain_get_concurrency_level(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_get_concurrency_level(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_set_grain_size(SEXP Sdomain, SEXP Ssize)
{
  h_status_t status = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Ssize = AS_INTEGER(Ssize));
  status = h_domain_set_grain_size(domain, (size_t) INTEGER(Ssize)[0]);

  if((h_error_t) status != h_error_none) {
    UNPROTECT(1);
    RHugin_handle_error_code((h_error_t) status);
  }

  UNPROTECT(1);
  return R_NilValue;
}


SEXP RHugin_domain_get_grain_size(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_get_grain_size(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}



/* Section 2.2 Domains: Creation and deletion */

SEXP RHugin_new_domain(void)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = h_new_domain();
  RHugin_handle_error();

  if(domain) {
    ret = R_MakeExternalPtr(domain, RHugin_domain_tag, R_NilValue);
    R_RegisterCFinalizer(ret, (R_CFinalizer_t) RHugin_domain_finalizer);
  }

  return ret;
}


SEXP RHugin_domain_delete(SEXP Sdomain)
{
  h_status_t status = h_domain_delete(domainPointerFromSEXP(Sdomain));
  R_ClearExternalPtr(Sdomain);

  RHugin_handle_error();

  return R_NilValue;
}


SEXP RHugin_domain_clone(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL, clonedDomain = NULL;

  domain = domainPointerFromSEXP(Sdomain);
  clonedDomain = h_domain_clone(domain);

  RHugin_handle_error();

  if(clonedDomain) {
    ret = R_MakeExternalPtr(clonedDomain, RHugin_domain_tag, R_NilValue);
    R_RegisterCFinalizer(ret, (R_CFinalizer_t) RHugin_domain_finalizer);
  }

  return ret;
}


/* Section 2.3 Nodes: Creation and deletion */

SEXP RHugin_domain_new_node(SEXP Sdomain, SEXP Scategory, SEXP Skind)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_node_t node = NULL;
  h_node_category_t category = h_category_error;
  h_node_kind_t kind = h_kind_error;

  PROTECT(Scategory = AS_CHARACTER(Scategory));
  PROTECT(Skind = AS_CHARACTER(Skind));

  domain = domainPointerFromSEXP(Sdomain);

  if(asChar(Scategory) == RHUGIN_CHANCE)
    category = h_category_chance;
  else if(asChar(Scategory) == RHUGIN_UTILITY)
    category = h_category_utility;
  else if(asChar(Scategory) == RHUGIN_DECISION)
    category = h_category_decision;
  else if(asChar(Scategory) == RHUGIN_INSTANCE)
    category = h_category_instance;

  if(asChar(Skind) == RHUGIN_DISCRETE)
    kind = h_kind_discrete;
  else if(asChar(Skind) == RHUGIN_CONTINUOUS)
    kind = h_kind_continuous;

  node = h_domain_new_node(domain, category, kind);
  RHugin_handle_error();

  if(node) {
    PROTECT(ret = allocVector(VECSXP, 1));
    SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(node, RHugin_node_tag, R_NilValue));
    UNPROTECT(1);
  }

  UNPROTECT(2);
  return ret;
}


// SEXP RHugin_node_get_domain(SEXP Snode)


SEXP RHugin_node_get_category(SEXP Snodes)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_node_category_t category = h_category_error;
  int i = 0, n = LENGTH(Snodes);

  PROTECT(ret = allocVector(STRSXP, n));

  for(i = 0; i < n; i++) {
    node = nodePointerFromSEXP(VECTOR_ELT(Snodes, i));
    category = h_node_get_category(node);

    switch(category) {
      case h_category_chance:
        SET_STRING_ELT(ret, i, RHUGIN_CHANCE);
        break;

      case h_category_utility:
        SET_STRING_ELT(ret, i, RHUGIN_UTILITY);
        break;

      case h_category_decision:
        SET_STRING_ELT(ret, i, RHUGIN_DECISION);
        break;

      case h_category_instance:
        SET_STRING_ELT(ret, i, RHUGIN_INSTANCE);
        break;

      case h_category_error:
        SET_STRING_ELT(ret, i, NA_STRING);
        break;
    }
  }

  setAttrib(ret, R_NamesSymbol, getAttrib(Snodes, R_NamesSymbol));

  UNPROTECT(1);
  return ret;
}


SEXP RHugin_node_get_kind(SEXP Snodes)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_node_kind_t kind = h_kind_error;
  int i = 0, n = LENGTH(Snodes);

  PROTECT(ret = allocVector(STRSXP, n));

  for(i = 0; i < n; i++) {
    node = nodePointerFromSEXP(VECTOR_ELT(Snodes, i));
    kind = h_node_get_kind(node);

    switch(kind) {
      case h_kind_continuous:
        SET_STRING_ELT(ret, i, RHUGIN_CONTINUOUS);
        break;

      case h_kind_discrete:
        SET_STRING_ELT(ret, i, RHUGIN_DISCRETE);
        break;

      case h_kind_error:
        SET_STRING_ELT(ret, i, NA_STRING);
        break;
    }
  }

  setAttrib(ret, R_NamesSymbol, getAttrib(Snodes, R_NamesSymbol));

  UNPROTECT(1);
  return ret;
}


SEXP RHugin_node_delete(SEXP Snodes)
{
  int i = 0, n = LENGTH(Snodes);

  for(i = 0; i < n; i++)
    RHugin_handle_status_code(h_node_delete(nodePointerFromSEXP(VECTOR_ELT(Snodes, i))));

  return R_NilValue;
}


SEXP RHugin_node_clone(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  node = h_node_clone(node);
  RHugin_handle_error();

  if(node) {
    PROTECT(ret = allocVector(VECSXP, 1));
    SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(node, RHugin_node_tag, R_NilValue));
    UNPROTECT(1);
  }

  return ret;
}


/* Section 2.4 The links of the network */

SEXP RHugin_node_add_parent(SEXP Schild, SEXP Sparents)
{
  int i = 0;
  h_node_t parent = NULL, child = nodePointerFromSEXP(VECTOR_ELT(Schild, 0));

  for(i = 0; i < LENGTH(Sparents); i++) {
    parent = nodePointerFromSEXP(VECTOR_ELT(Sparents, i));
    RHugin_handle_status_code(h_node_add_parent(child, parent));
  }

  return R_NilValue;
}


SEXP RHugin_node_remove_parent(SEXP Snode, SEXP Sparent)
{
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  h_node_t parent = nodePointerFromSEXP(VECTOR_ELT(Sparent, 0));
  RHugin_handle_status_code(h_node_remove_parent(node, parent));
  return R_NilValue;
}


SEXP RHugin_node_switch_parent(SEXP Snode, SEXP Sold_parent, SEXP Snew_parent)
{
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  h_node_t old_parent = nodePointerFromSEXP(VECTOR_ELT(Sold_parent, 0));
  h_node_t new_parent = nodePointerFromSEXP(VECTOR_ELT(Snew_parent, 0));

  RHugin_handle_status_code(h_node_switch_parent(node, old_parent, new_parent));

  return R_NilValue;
}


SEXP RHugin_node_reverse_edge(SEXP Snode1, SEXP Snode2)
{
  h_node_t node1 = nodePointerFromSEXP(VECTOR_ELT(Snode1, 0));
  h_node_t node2 = nodePointerFromSEXP(VECTOR_ELT(Snode2, 0));

  RHugin_handle_status_code(h_node_reverse_edge(node1, node2));

  return R_NilValue;
}


SEXP RHugin_node_get_parents(SEXP Snodes)
{
  SEXP ret = R_NilValue, child = R_NilValue, names = R_NilValue;
  h_node_t node = NULL;
  h_error_t error_code = h_error_none;
  h_node_t *parents = NULL, *parent = NULL;
  int i = 0, j = 0, n_parents = 0, n = LENGTH(Snodes);

  PROTECT(ret = allocVector(VECSXP, n));

  for(i = 0; i < n; i++) {
    node = nodePointerFromSEXP(VECTOR_ELT(Snodes, i));
    parents = h_node_get_parents(node);

    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(1);
      RHugin_handle_error_code(error_code);
    }

    if(parents) {
      n_parents = 0;
      for(parent = parents; *parent != NULL; parent++) n_parents++;

      PROTECT(child = allocVector(VECSXP, n_parents));
      PROTECT(names = allocVector(STRSXP, n_parents));

      for(j = 0; j < n_parents; j++) {
        SET_VECTOR_ELT(child, j, R_MakeExternalPtr(parents[j], RHugin_node_tag, R_NilValue));
        SET_STRING_ELT(names, j, mkChar( (char*) h_node_get_name(parents[j])));

        error_code = h_error_code();
        if(error_code != h_error_none) {
          UNPROTECT(2);
          RHugin_handle_error_code(error_code);
        }
      }
      setAttrib(child, R_NamesSymbol, names);

      SET_VECTOR_ELT(ret, i, child);
      UNPROTECT(2);
    }

    else
      SET_VECTOR_ELT(ret, i, R_NilValue);
  }

  setAttrib(ret, R_NamesSymbol, getAttrib(Snodes, R_NamesSymbol));

  UNPROTECT(1);
  return ret;
}


SEXP RHugin_node_get_children(SEXP Snodes)
{
  SEXP ret = R_NilValue, parent = R_NilValue, names = R_NilValue;
  h_node_t node = NULL;
  h_error_t error_code = h_error_none;
  h_node_t *children = NULL, *child = NULL;
  int i = 0, j = 0, n_children = 0, n = LENGTH(Snodes);

  PROTECT(ret = allocVector(VECSXP, n));

  for(i = 0; i < n; i++) {
    node = nodePointerFromSEXP(VECTOR_ELT(Snodes, i));
    children = h_node_get_children(node);

    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(1);
      RHugin_handle_error_code(error_code);
    }

    if(children) {
      n_children = 0;
      for(child = children; *child != NULL; child++) n_children++;

      PROTECT(parent = allocVector(VECSXP, n_children));
      PROTECT(names = allocVector(STRSXP, n_children));

      for(j = 0; j < n_children; j++) {
        SET_VECTOR_ELT(parent, j, R_MakeExternalPtr(children[j], RHugin_node_tag, R_NilValue));
        SET_STRING_ELT(names, j, mkChar( (char*) h_node_get_name(children[j])));

        error_code = h_error_code();
        if(error_code != h_error_none) {
          UNPROTECT(2);
          RHugin_handle_error_code(error_code);
        }
      }
      setAttrib(parent, R_NamesSymbol, names);

      SET_VECTOR_ELT(ret, i, parent);
      UNPROTECT(2);
    }

    else
      SET_VECTOR_ELT(ret, i, R_NilValue);
  }

  setAttrib(ret, R_NamesSymbol, getAttrib(Snodes, R_NamesSymbol));

  UNPROTECT(1);
  return ret;
}


/* Section 2.5 The number of states of a node */

SEXP RHugin_node_set_number_of_states(SEXP Snode, SEXP Sstates)
{
  size_t count = -1;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sstates = AS_INTEGER(Sstates));
  count = (size_t) INTEGER(Sstates)[0];
  UNPROTECT(1);

  RHugin_handle_status_code(h_node_set_number_of_states(node, count));

  return R_NilValue;
}


SEXP RHugin_node_get_number_of_states(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_node_get_number_of_states(node);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


/* Section 2.6 The conditional probability and the utility table */

SEXP RHugin_node_get_table(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_table_t table = NULL;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  table = h_node_get_table(node);
  RHugin_handle_error();

  if(table)
    ret = R_MakeExternalPtr(table, RHugin_table_tag, R_NilValue);

  return ret;
}


SEXP RHugin_node_touch_table(SEXP Snode)
{
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  RHugin_handle_status_code(h_node_touch_table(node));

  return R_NilValue;
}


SEXP RHugin_node_set_alpha(SEXP Snode, SEXP Salpha, SEXP Si)
{
  h_status_t status = 0;
  double *alpha = NULL;
  int i = 0, *indices = NULL, n = LENGTH(Si);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  if(LENGTH(Salpha) != n)
    error("Salpha and Si are not not the same length");

  PROTECT(Salpha = AS_NUMERIC(Salpha));
  PROTECT(Si = AS_INTEGER(Si));
  alpha = REAL(Salpha);
  indices = INTEGER(Si);

  for(i = 0; i < n; i++) {
    status = h_node_set_alpha(node, (h_double_t) alpha[i], (size_t) indices[i]);
    if((h_error_t) status != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code((h_error_t) status);
    }
  }

  UNPROTECT(2);
  return R_NilValue;
}


SEXP RHugin_node_set_beta(SEXP Snode, SEXP Sbeta, SEXP Sparent, SEXP Si)
{
  h_status_t status = 0;
  double *beta = NULL;
  int i = 0, *indices = NULL, n = LENGTH(Sbeta);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  h_node_t parent = nodePointerFromSEXP(VECTOR_ELT(Sparent, 0));

  PROTECT(Sbeta = AS_NUMERIC(Sbeta));
  PROTECT(Si = AS_INTEGER(Si));
  beta = REAL(Sbeta);
  indices = INTEGER(Si);

  if(LENGTH(Si) != n)
    error("Sbeta and Si are not the same length");

  for(i = 0; i < n; i++) {
    status = h_node_set_beta(node, (h_double_t) beta[i], parent, (size_t) indices[i]);
    if((h_error_t) status != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code((h_error_t) status);
    }
  }

  UNPROTECT(2);
  return R_NilValue;
}


SEXP RHugin_node_set_gamma(SEXP Snode, SEXP Sgamma, SEXP Si)
{
  h_status_t status = 0;
  double *gamma = NULL;
  int i = 0, *indices = NULL, n = LENGTH(Sgamma);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sgamma = AS_NUMERIC(Sgamma));
  PROTECT(Si = AS_INTEGER(Si));
  gamma = REAL(Sgamma);
  indices = INTEGER(Si);

  if(LENGTH(Si) != n)
    error("Sgamma and Si are not the same length");

  for(i = 0; i < n; i++) {
    status = h_node_set_gamma(node, (h_double_t) gamma[i], (size_t) indices[i]);
    if((h_error_t) status != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code((h_error_t) status);
    }
  }

  UNPROTECT(2);
  return R_NilValue;
}


SEXP RHugin_node_get_alpha(SEXP Snode, SEXP Si)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *alpha = NULL;
  int i = 0, *indices = NULL, n = LENGTH(Si);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Si = AS_INTEGER(Si));
  PROTECT(ret = allocVector(REALSXP, n));
  alpha = REAL(ret);
  indices = INTEGER(Si);

  for(i = 0; i < n; i++) {
    alpha[i] = (double) h_node_get_alpha(node, (size_t) indices[i]);
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


SEXP RHugin_node_get_beta(SEXP Snode, SEXP Sparent, SEXP Si)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *beta = NULL;
  int i = 0, *indices = NULL, n = LENGTH(Si);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  h_node_t parent = nodePointerFromSEXP(VECTOR_ELT(Sparent, 0));

  PROTECT(Si = AS_INTEGER(Si));
  PROTECT(ret = allocVector(REALSXP, n));
  beta = REAL(ret);
  indices = INTEGER(Si);

  for(i = 0; i < n; i++) {
    beta[i] = (double) h_node_get_beta(node, parent, (size_t) indices[i]);
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


SEXP RHugin_node_get_gamma(SEXP Snode, SEXP Si)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *gamma = NULL;
  int i = 0, *indices = NULL, n = LENGTH(Si);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Si = AS_INTEGER(Si));
  PROTECT(ret = allocVector(REALSXP, n));
  gamma = REAL(ret);
  indices = INTEGER(Si);

  for(i = 0; i < n; i++) {
    gamma[i] = (double) h_node_get_gamma(node, (size_t) indices[i]);
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


/* Section 2.7 The name of a node */

SEXP RHugin_node_set_name(SEXP Snode, SEXP Sname)
{
  h_status_t status = 0;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sname = AS_CHARACTER(Sname));
  status = h_node_set_name(node, (h_string_t) CHAR(asChar(Sname)));
  UNPROTECT(1);

  RHugin_handle_status_code(status);

  return R_NilValue;
}


SEXP RHugin_node_get_name(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(STRSXP, 1));
  SET_STRING_ELT(ret, 0, mkChar( (char*) h_node_get_name(node)));
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_get_node_by_name(SEXP Sdomain, SEXP Snames)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  int i = 0, n = LENGTH(Snames);
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Snames = AS_CHARACTER(Snames));
  PROTECT(ret = allocVector(VECSXP, n));

  for(i = 0; i < n; i++) {
    node = h_domain_get_node_by_name(domain, (h_string_t) CHAR(STRING_ELT(Snames, i)));

    if(node)
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(node, RHugin_node_tag, R_NilValue));
    else
      SET_VECTOR_ELT(ret, i, R_NilValue);
  }

  setAttrib(ret, R_NamesSymbol, Snames);

  UNPROTECT(2);
  return ret;
}


/* Section 2.8 Iterating through the nodes of a domain */

SEXP RHugin_domain_get_first_node(SEXP Sdomain)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_node_t node = NULL;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  node = h_domain_get_first_node(domain);
  RHugin_handle_error();

  if(node) {
    PROTECT(ret = allocVector(VECSXP, 1));
    PROTECT(names = allocVector(STRSXP, 1));
    SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(node, RHugin_node_tag, R_NilValue));
    SET_STRING_ELT(names, 0, mkChar( (char*) h_node_get_name(node)));
    setAttrib(ret, R_NamesSymbol, names);
    UNPROTECT(2);
  }

  return ret;
}


SEXP RHugin_node_get_next(SEXP Snode)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_node_t node = NULL, next = NULL;

  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  next = h_node_get_next(node);
  RHugin_handle_error();

  if(next) {
    PROTECT(ret = allocVector(VECSXP, 1));
    PROTECT(names = allocVector(STRSXP, 1));
    SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(next, RHugin_node_tag, R_NilValue));
    SET_STRING_ELT(names, 0, mkChar( (char*) h_node_get_name(next)));
    setAttrib(ret, R_NamesSymbol, names);
    UNPROTECT(2);
  }

  return ret;
}


/* Section 2.9 User data */

// SEXP RHugin_node_set_user_data(SEXP Snode, SEXP Sdata);
// SEXP RHugin_node_get_user_data(SEXP Snode);
// SEXP RHugin_domain_set_user_data(SEXP Sdomain, SEXP Sdata);
// SEXP RHugin_domain_get_user_data(SEXP Sdomain);
// SEXP RHugin_node_set_attribute(SEXP Snode, SEXP Skey, SEXP Svalue);
// SEXP RHugin_node_get_attribute(SEXP Snode, SEXP Skey);
// SEXP RHugin_domain_set_attribute(SEXP Sdomain, SEXP Skey, SEXP Svalue);
// SEXP RHugin_domain_get_attribute(SEXP Sdomain, SEXP Skey);
// SEXP RHugin_node_get_first_attribute(SEXP Snode);
// SEXP RHugin_domain_get_first_attribute(SEXP Sdomain);
// SEXP RHugin_attribute_get_next(SEXP Sattribute);
// SEXP RHugin_attribute_get_key(SEXP Sattribute);
// SEXP RHugin_attribute_get_value(SEXP Sattribute);


/* Section 2.10 HUGIN Knowledge Base files */

SEXP RHugin_domain_save_as_kb(SEXP Sdomain, SEXP Sfile_name, SEXP Spassword)
{
  h_status_t status = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  if(Spassword == R_NilValue)
    status = h_domain_save_as_kb(domain, (h_string_t) CHAR(asChar(Sfile_name)), NULL);
  else
    status = h_domain_save_as_kb(domain, (h_string_t) CHAR(asChar(Sfile_name)),
                                 (h_string_t) CHAR(asChar(Spassword)));

  RHugin_handle_status_code(status);

  return R_NilValue;
}


SEXP RHugin_kb_load_domain(SEXP Sfile_name, SEXP Spassword)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  if(Spassword == R_NilValue)
    domain = h_kb_load_domain((h_string_t) CHAR(asChar(Sfile_name)), NULL);
  else
    domain = h_kb_load_domain((h_string_t) CHAR(asChar(Sfile_name)),
                              (h_string_t) CHAR(asChar(Spassword)));

  RHugin_handle_error();

  if(domain) {
    ret = R_MakeExternalPtr(domain, RHugin_domain_tag, R_NilValue);
    R_RegisterCFinalizer(ret, (R_CFinalizer_t) RHugin_domain_finalizer); 
  }

  return ret;
}


/* 4.2 The nodes and the contents of a table */

SEXP RHugin_table_get_nodes(SEXP Stable)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_error_t error_code = h_error_none;
  h_node_t *nodes = NULL, *node = NULL;
  int i = 0, n = 0;

  nodes = h_table_get_nodes(tablePointerFromSEXP(Stable));
  RHugin_handle_error();

  if(nodes) {
    for(node = nodes; *node != NULL; node++) n++;

    PROTECT(ret = allocVector(VECSXP, n));
    PROTECT(names = allocVector(STRSXP, n));

    for(i = 0; i < n; i++) {
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(nodes[i], RHugin_node_tag, R_NilValue));
      SET_STRING_ELT(names, i, mkChar( (char*) h_node_get_name(nodes[i])));
      error_code = h_error_code();
      if(error_code != h_error_none) {
        UNPROTECT(2);
        RHugin_handle_error_code(error_code);
      }
    }
    setAttrib(ret, R_NamesSymbol, names);

    UNPROTECT(2);
  }

  return ret;
}


SEXP RHugin_table_get_data(SEXP Stable)
{
  SEXP ret = R_NilValue;
  double *data = NULL;
  h_number_t *table_data = NULL;
  int i = 0, size = -1;
  h_table_t table = tablePointerFromSEXP(Stable);

  table_data = h_table_get_data(table);
  RHugin_handle_error();
  size = (int) h_table_get_size(table);
  RHugin_handle_error();

  PROTECT(ret = allocVector(REALSXP, size));
  data = REAL(ret);
  
  for(i = 0; i < size; i++)
    data[i] = (double) table_data[i];

  UNPROTECT(1);
  return ret;
}


SEXP RHugin_table_set_data(SEXP Stable, SEXP Sdata)
{
  h_table_t table = NULL;
  double *data = NULL;
  h_number_t *table_data = NULL;
  int i = 0, size = -1;

  table = tablePointerFromSEXP(Stable);
  RHugin_handle_error();

  table_data = h_table_get_data(table);
  size = (int) h_table_get_size(table);

  if(LENGTH(Sdata) != size)
    error("the length of Sdata is not equal to the table size");

  PROTECT(Sdata = AS_NUMERIC(Sdata));
  data = REAL(Sdata);

  for(i = 0; i < size; i++)
    table_data[i] = (h_number_t) data[i];

  UNPROTECT(1);
  return R_NilValue;
}


SEXP RHugin_table_get_mean(SEXP Stable, SEXP Si, SEXP Snode)
{
  SEXP ret = R_NilValue;
  double *mean = NULL;
  h_error_t error_code = h_error_none;
  int i = 0, *indices = NULL, n = LENGTH(Si);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  h_table_t table = tablePointerFromSEXP(Stable);

  PROTECT(Si = AS_INTEGER(Si));
  PROTECT(ret = allocVector(REALSXP, n));
  mean = REAL(ret);
  indices = INTEGER(Si);

  for(i = 0; i < n; i++) {
    mean[i] = h_table_get_mean(table, (size_t) indices[i], node);
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


SEXP RHugin_table_get_covariance(SEXP Stable, SEXP Si, SEXP Snode1, SEXP Snode2)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *cov = NULL;
  h_node_t node1 = NULL, node2 = NULL;
  h_table_t table = NULL;
  int i = 0, *indices = NULL, n = LENGTH(Si);

  node1 = nodePointerFromSEXP(VECTOR_ELT(Snode1, 0));
  node2 = nodePointerFromSEXP(VECTOR_ELT(Snode2, 0));
  table = tablePointerFromSEXP(Stable);

  PROTECT(ret = allocVector(REALSXP, n));
  PROTECT(Si = AS_INTEGER(Si));
  cov = REAL(ret);
  indices = INTEGER(Si);

  for(i = 0; i < n; i++) {
    cov[i] = h_table_get_covariance(table, (size_t) indices[i], node1, node2);
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


SEXP RHugin_table_get_variance(SEXP Stable, SEXP Si, SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *variance = NULL;
  int i = 0, *indices = NULL, n = LENGTH(Si);

  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  h_table_t table = tablePointerFromSEXP(Stable);

  PROTECT(Si = AS_INTEGER(Si));
  PROTECT(ret = allocVector(REALSXP, n));
  indices = INTEGER(Si);
  variance = REAL(ret);

  for(i = 0; i < n; i++) {
    variance[i] = h_table_get_variance(table, (size_t) indices[i], node);
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


SEXP RHugin_table_delete(SEXP Stable)
{
  RHugin_handle_status_code(h_table_delete(tablePointerFromSEXP(Stable)));

  return R_NilValue;
}


SEXP RHugin_table_get_size(SEXP Stable)
{
  SEXP ret = R_NilValue;
  h_table_t table = tablePointerFromSEXP(Stable);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_table_get_size(table);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_table_get_cg_size(SEXP Stable)
{
  SEXP ret = R_NilValue;
  h_table_t table = tablePointerFromSEXP(Stable);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_table_get_cg_size(table);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_table_reorder_nodes(SEXP Stable, SEXP Sorder)
{
  h_node_t *order = NULL;
  int i = 0, n = LENGTH(Sorder);
  h_table_t table = tablePointerFromSEXP(Stable);

  order = (h_node_t*) R_alloc(n + 1, sizeof(h_node_t));
  for(i = 0; i < n; i++)
    order[i] = nodePointerFromSEXP(VECTOR_ELT(Sorder, i));
  order[n] = NULL;

  RHugin_handle_status_code(h_table_reorder_nodes(table, order));

  return R_NilValue;
}


SEXP RHugin_node_set_subtype(SEXP Snode, SEXP Ssubtype)
{
  h_node_subtype_t subtype = h_subtype_error;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Ssubtype = AS_CHARACTER(Ssubtype));

  if(asChar(Ssubtype) == RHUGIN_LABELED)
    subtype = h_subtype_label;
  else if(asChar(Ssubtype) == RHUGIN_NUMBERED)
    subtype = h_subtype_number;
  else if(asChar(Ssubtype) == RHUGIN_BOOLEAN)
    subtype = h_subtype_boolean;
  else if(asChar(Ssubtype) == RHUGIN_INTERVAL)
    subtype = h_subtype_interval;
  else
    subtype = h_subtype_error;

  UNPROTECT(1);

  RHugin_handle_status_code(h_node_set_subtype(node, subtype));

  return R_NilValue;
}


SEXP RHugin_node_get_subtype(SEXP Snodes)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  h_node_t node = NULL;
  h_node_subtype_t subtype;
  int i = 0, n = LENGTH(Snodes);

  PROTECT(ret = allocVector(STRSXP, n));

  for(i = 0; i < n; i++) {
    node = nodePointerFromSEXP(VECTOR_ELT(Snodes, i));
    subtype = h_node_get_subtype(node);

    switch(subtype) {
      case h_subtype_label:
        SET_STRING_ELT(ret, i, RHUGIN_LABELED);
        break;

      case h_subtype_number:
        SET_STRING_ELT(ret, i, RHUGIN_NUMBERED);
        break;

      case h_subtype_boolean:
        SET_STRING_ELT(ret, i, RHUGIN_BOOLEAN);
        break;

      case h_subtype_interval:
        SET_STRING_ELT(ret, i, RHUGIN_INTERVAL);
        break;

      case h_subtype_error:
        SET_STRING_ELT(ret, i, NA_STRING);
        break;
    }
  }

  setAttrib(ret, R_NamesSymbol, getAttrib(Snodes, R_NamesSymbol));

  UNPROTECT(1);
  return ret;
}



/* Section 5.2 Expressions */

// Removed by Kjell Konis 16.10.2009


/* Section 5.3 Syntax for expression */

SEXP RHugin_string_parse_expression(SEXP Sstring, SEXP Smodel)
{
  SEXP ret = R_NilValue;
  h_expression_t expression = NULL;
  h_model_t model = modelPointerFromSEXP(Smodel);

  expression = h_string_parse_expression((h_string_t) STRING_ELT(Sstring, 0),
                                          model, RHuginParseError, NULL);

  RHugin_handle_error();

  if(expression)
    ret = R_MakeExternalPtr(expression, RHugin_expression_tag, R_NilValue);

  return ret;
}


SEXP RHugin_expression_to_string(SEXP Sexpression)
{
  SEXP ret = R_NilValue;
  h_string_t string = NULL;

  h_expression_t expression = expressionPointerFromSEXP(Sexpression);
  string = h_expression_to_string(expression);

  RHugin_handle_error();

  if(string) {
    PROTECT(ret = allocVector(STRSXP, 1));
    SET_STRING_ELT(ret, 0, mkChar( (char*) string));
    free(string);
    string = NULL;
    UNPROTECT(1);
  }

  return ret;
}


/* Section 5.4 Creating and maintaining models */

SEXP RHugin_node_new_model(SEXP Snode, SEXP Smodel_nodes)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_node_t *model_nodes = NULL;
  h_model_t model = NULL;
  int i = 0, n = LENGTH(Smodel_nodes);

  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  model_nodes = (h_node_t*) R_alloc(n + 1, sizeof(h_node_t));
  for(i = 0; i < n; i++)
    model_nodes[i] = nodePointerFromSEXP(VECTOR_ELT(Smodel_nodes, i));
  model_nodes[n] = NULL;

  model = h_node_new_model(node, model_nodes);

  RHugin_handle_error();

  PROTECT(ret = allocVector(VECSXP, 1));

  if(model)
    SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(model, RHugin_model_tag, R_NilValue));
  else
    SET_VECTOR_ELT(ret, i, R_NilValue);

  setAttrib(ret, R_NamesSymbol, getAttrib(Snode, R_NamesSymbol));

  UNPROTECT(1);
  return ret;
}


SEXP RHugin_node_get_model(SEXP Snodes)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  h_model_t model = NULL;
  int i = 0, n = LENGTH(Snodes);

  PROTECT(ret = allocVector(VECSXP, n));

  for(i = 0; i < n; i++) {
    model = h_node_get_model(nodePointerFromSEXP(VECTOR_ELT(Snodes, i)));
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(1);
      RHugin_handle_error_code(error_code);
    }

    if(model)
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(model, RHugin_model_tag, R_NilValue));
    else
      SET_VECTOR_ELT(ret, i, R_NilValue);
  }

  setAttrib(ret, R_NamesSymbol, getAttrib(Snodes, R_NamesSymbol));

  UNPROTECT(1);
  return ret;
}


SEXP RHugin_model_delete(SEXP Smodels)
{
  h_model_t model = NULL;
  int i = 0, n = LENGTH(Smodels);

  for(i = 0; i < n; i++) {
    model = modelPointerFromSEXP(VECTOR_ELT(Smodels, i));
    RHugin_handle_status_code(h_model_delete(model));
  }

  return R_NilValue;
}


SEXP RHugin_model_get_nodes(SEXP Smodel)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_error_t error_code = h_error_none;
  h_node_t *node = NULL, *nodes = NULL;
  int i = 0, n = 0;

  nodes = h_model_get_nodes(modelPointerFromSEXP(VECTOR_ELT(Smodel, 0)));
  RHugin_handle_error();

  if(nodes) {
    for(node = nodes; *node != NULL; node++) n++;

    PROTECT(ret = allocVector(VECSXP, n));
    PROTECT(names = allocVector(STRSXP, n));

    for(i = 0; i < n; i++) {
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(nodes[i], RHugin_node_tag, R_NilValue));
      SET_STRING_ELT(names, i, mkChar( (char*) h_node_get_name(nodes[i])));
      error_code = h_error_code();
      if(error_code != h_error_none) {
        UNPROTECT(2);
        RHugin_handle_error_code(error_code);
      }
    }

    setAttrib(ret, R_NamesSymbol, names);
    UNPROTECT(2);
  }

  return ret;
}


SEXP RHugin_model_get_size(SEXP Smodels)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  int i = 0, *size = NULL, n = LENGTH(Smodels);

  PROTECT(ret = allocVector(INTSXP, n));
  size = INTEGER(ret);

  for(i = 0; i < n; i++) {
    size[i] = h_model_get_size(modelPointerFromSEXP(VECTOR_ELT(Smodels, i)));
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(1);
      RHugin_handle_error_code(error_code);
    }
  }

  setAttrib(ret, R_NamesSymbol, getAttrib(Smodels, R_NamesSymbol));
  UNPROTECT(1);
  return ret;
}


SEXP RHugin_model_set_expression(SEXP Smodel, SEXP Sindex, SEXP Sexpression)
{
  h_model_t model = modelPointerFromSEXP(VECTOR_ELT(Smodel, 0));
  h_expression_t expression = expressionPointerFromSEXP(Sexpression);
  size_t size = (size_t) INTEGER(Sindex)[0];

  RHugin_handle_status_code(h_model_set_expression(model, size, expression));

  return R_NilValue;
}


SEXP RHugin_model_get_expression(SEXP Smodel, SEXP Sindex)
{
  SEXP ret = R_NilValue;
  h_expression_t expression = NULL;
  h_model_t model = modelPointerFromSEXP(VECTOR_ELT(Smodel, 0));
  size_t index = (size_t) INTEGER(Sindex)[0];

  expression = h_model_get_expression(model, index);
  RHugin_handle_error();

  if(expression)
    ret = R_MakeExternalPtr(expression, RHugin_expression_tag, R_NilValue);

  return ret;
}


/* Section 5.5 State labels */

SEXP RHugin_node_set_state_label(SEXP Snode, SEXP Ss, SEXP Slabels)
{
  h_status_t status = 0;
  int i = 0, *s = NULL, n = LENGTH(Ss);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  if(LENGTH(Slabels) != n)
    error("Slabels and Ss are not the same length");

  PROTECT(Ss = AS_INTEGER(Ss));
  PROTECT(Slabels = AS_CHARACTER(Slabels));
  s = INTEGER(Ss);

  for(i = 0; i < n; i++) {
    status = h_node_set_state_label(node, (size_t) s[i], (h_string_t) CHAR(STRING_ELT(Slabels, i)));
    if((h_error_t) status != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code((h_error_t) status);
    }
  }

  UNPROTECT(2);
  return R_NilValue;
}


SEXP RHugin_node_get_state_label(SEXP Snode, SEXP Ss)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  int i = 0, *s = NULL, n = LENGTH(Ss);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(STRSXP, n));
  PROTECT(Ss = AS_INTEGER(Ss));
  s = INTEGER(Ss);

  for(i = 0; i < n; i++) {
    SET_STRING_ELT(ret, i, mkChar( (char*) h_node_get_state_label(node, (size_t) s[i])));
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


SEXP RHugin_node_get_state_index_from_label(SEXP Snode, SEXP Slabels)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  int i = 0, *index = NULL, n = LENGTH(Slabels);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Slabels = AS_CHARACTER(Slabels));
  PROTECT(ret = allocVector(INTSXP, n));
  index = INTEGER(ret);

  for(i = 0; i < n; i++) {
    index[i] = (int) h_node_get_state_index_from_label(node, (h_string_t) CHAR(STRING_ELT(Slabels, i)));
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


/* Section 5.6 State values */

SEXP RHugin_node_set_state_value(SEXP Snode, SEXP Ss, SEXP Svalues)
{
  h_status_t status = 0;
  h_double_t value = 0.0;
  double *sv = NULL;
  int i = 0, *s = NULL, n = LENGTH(Svalues);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Ss = AS_INTEGER(Ss));
  PROTECT(Svalues = AS_NUMERIC(Svalues));
  s = INTEGER(Ss);
  sv = REAL(Svalues);
  
  for(i = 0; i < n; i++) {
    if(sv[i] == R_PosInf)
      value = h_infinity;
    else if(sv[i] == R_NegInf)
      value = -h_infinity;
    else
      value = (h_double_t) sv[i];

    status = h_node_set_state_value(node, (size_t) INTEGER(Ss)[i], value);
    if((h_error_t) status != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code((h_error_t) status);
    }
  }

  UNPROTECT(2);
  return R_NilValue;
}


SEXP RHugin_node_get_state_value(SEXP Snode, SEXP Ss)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  h_double_t value = 0.0;
  double *sv = NULL;
  int i = 0, *s = NULL, n = LENGTH(Ss);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Ss = AS_INTEGER(Ss));
  PROTECT(ret = allocVector(REALSXP, n));
  s = INTEGER(Ss);
  sv = REAL(ret);

  for(i = 0; i < n; i++) {
    value = h_node_get_state_value(node, (size_t) s[i]);
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }

    if(value == h_infinity)
      sv[i] = R_PosInf;
    else if(value == -h_infinity)
      sv[i] = R_NegInf;
    else
      sv[i] = (double) value;
  }

  UNPROTECT(2);
  return ret;
}


SEXP RHugin_node_get_state_index_from_value(SEXP Snode, SEXP Svalues)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *values = NULL;
  int i = 0, *indices = NULL, n = LENGTH(Svalues);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(INTSXP, n));
  PROTECT(Svalues = AS_NUMERIC(Svalues));
  indices = INTEGER(ret);
  values = REAL(Svalues);

  for(i = 0; i < n; i++) {
    if(!R_FINITE(values[i]))
      indices[i] = -1;
    else
      indices[i] = (int) h_node_get_state_index_from_value(node, (h_double_t) values[i]);

    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


/* Section 5.8 Generating tables */

SEXP RHugin_node_generate_table(SEXP Snodes)
{
  int i = 0, n = LENGTH(Snodes);

  for(i = 0; i < n; i++)
    RHugin_handle_status_code(h_node_generate_table(nodePointerFromSEXP(VECTOR_ELT(Snodes, i))));

  return R_NilValue;
}


SEXP RHugin_domain_generate_tables(SEXP Sdomain)
{
  RHugin_handle_status_code(h_domain_generate_tables(domainPointerFromSEXP(Sdomain)));

  return R_NilValue;
}


// SEXP RHugin_class_generate_tables(SEXP Sclass)
// SEXP RHugin_class_set_log_file(SEXP Sclass, SEXP Slog_file)


/* Section 5.9 How the computations are done */

SEXP RHugin_model_set_number_of_samples_per_interval(SEXP Smodel, SEXP Scount)
{
  h_status_t status = 0;
  h_model_t model = modelPointerFromSEXP(VECTOR_ELT(Smodel, 0));

  PROTECT(Scount = AS_INTEGER(Scount));
  status = h_model_set_number_of_samples_per_interval(model, (size_t) INTEGER(Scount)[0]);
  UNPROTECT(1);

  RHugin_handle_error_code((h_error_t) status);

  return R_NilValue;
}


SEXP RHugin_model_get_number_of_samples_per_interval(SEXP Smodel)
{
  SEXP ret = R_NilValue;
  h_model_t model = modelPointerFromSEXP(VECTOR_ELT(Smodel, 0));

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_model_get_number_of_samples_per_interval(model);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


/* Section 6.2 Compilation */

SEXP RHugin_domain_compile(SEXP Sdomain)
{
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  if(!h_domain_is_compiled(domain))
    RHugin_handle_status_code(h_domain_compile(domain));

  return R_NilValue;
}


SEXP RHugin_domain_is_compiled(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_is_compiled(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_set_max_number_of_separators(SEXP Sdomain, SEXP Scount)
{
  h_status_t status = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Scount = AS_INTEGER(Scount));
  status = h_domain_set_max_number_of_separators(domain, (size_t) INTEGER(Scount)[0]);
  UNPROTECT(1);

  RHugin_handle_error_code((h_error_t) status);

  return R_NilValue;
}


SEXP RHugin_domain_get_max_number_of_separators(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_get_max_number_of_separators(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_triangulate(SEXP Sdomain, SEXP Smethod)
{
  h_triangulation_method_t method = h_tm_fill_in_weight;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Smethod = AS_CHARACTER(Smethod));

  if(asChar(Smethod) == RHUGIN_TM_CLIQUE_SIZE)
    method = h_tm_clique_size;
  else if(asChar(Smethod) == RHUGIN_TM_CLIQUE_WEIGHT)
    method = h_tm_fill_in_weight;
  else if(asChar(Smethod) == RHUGIN_TM_FILL_IN_SIZE)
    method = h_tm_clique_weight;
  else if(asChar(Smethod) == RHUGIN_TM_TOTAL_WEIGHT)
    method = h_tm_total_weight;

  UNPROTECT(1);

  RHugin_handle_status_code(h_domain_triangulate(domain, method));

  return R_NilValue;
}


SEXP RHugin_domain_triangulate_with_order(SEXP Sdomain, SEXP Sorder)
{
  h_node_t *order = NULL;
  int i = 0, n = LENGTH(Sorder);
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  order = (h_node_t*) R_alloc(n + 1, sizeof(h_node_t));
  for(i = 0; i < n; i++)
    order[i] = nodePointerFromSEXP(VECTOR_ELT(Sorder, i));
  order[n] = NULL;

  RHugin_handle_status_code(h_domain_triangulate_with_order(domain, order));

  return R_NilValue;
}


SEXP RHugin_domain_is_triangulated(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_is_triangulated(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_get_elimination_order(SEXP Sdomain)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_error_t error_code = h_error_none;
  h_node_t *order = NULL, *pnode = NULL;
  int i = 0, n = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  order = h_domain_get_elimination_order(domain);
  RHugin_handle_error();

  if(order) {
    for(pnode = order; *pnode != NULL; pnode++) n++;

    PROTECT(ret = allocVector(VECSXP, n));
    PROTECT(names = allocVector(STRSXP, n));

    for(i = 0; i < n; i++) {
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(order[i], RHugin_node_tag, R_NilValue));
      SET_STRING_ELT(names, i, mkChar( (char*) h_node_get_name(order[i])));
      error_code = h_error_code();
      if(error_code != h_error_none) {
        UNPROTECT(2);
        RHugin_handle_error_code(error_code);
      }
    }
    setAttrib(ret, R_NamesSymbol, names);

    UNPROTECT(2);
  }

  return ret;
}


// SEXP RHugin_domain_parse_nodes(SEXP Sdomain, SEXP Sfile_name, SEXP Serror_fun, SEXP Sdata)
// SEXP RHugin_class_parse_nodes(SEXP Sclass, SEXP Sfile_name, SEXP Serror_fun, SEXP Sdata)


/* Section 6.4 Getting a compilation log */

// SEXP RHugin_domain_set_log_file(SEXP Sdomain, SEXP Slog_file)


/* Section 6.5 Uncompilation */

SEXP RHugin_domain_uncompile(SEXP Sdomain)
{
  RHugin_handle_status_code(h_domain_uncompile(domainPointerFromSEXP(Sdomain)));

  return R_NilValue;
}


/* Section 6.5 Compression */

SEXP RHugin_domain_compress(SEXP Sdomain)
{
  SEXP ret = R_NilValue;

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_compress(domainPointerFromSEXP(Sdomain));
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_is_compressed(SEXP Sdomain)
{
  SEXP ret = R_NilValue;

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_is_compressed(domainPointerFromSEXP(Sdomain));
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


/* Section 6.7 Approximation */

SEXP RHugin_domain_approximate(SEXP Sdomain, SEXP Sepsilon)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Sepsilon = AS_NUMERIC(Sepsilon));
  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_approximate(domain, (h_double_t) REAL(Sepsilon)[0]);
  UNPROTECT(2);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_get_approximation_constant(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_approximation_constant(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


/* Section 7.2 Junction trees */

SEXP RHugin_domain_get_first_junction_tree(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = NULL;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  jt = h_domain_get_first_junction_tree(domain);
  RHugin_handle_error();

  if(jt)
    ret = R_MakeExternalPtr(jt, RHugin_junction_tree_tag, R_NilValue);

  return ret;
}


SEXP RHugin_jt_get_next(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = jtPointerFromSEXP(Sjt);

  jt = h_jt_get_next(jt);
  RHugin_handle_error();

  if(jt)
    ret = R_MakeExternalPtr(jt, RHugin_junction_tree_tag, R_NilValue);

  return ret;
}


SEXP RHugin_clique_get_junction_tree(SEXP Sclique)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = NULL;
  h_clique_t clique = cliquePointerFromSEXP(Sclique);

  jt = h_clique_get_junction_tree(clique);
  RHugin_handle_error();

  if(jt)
    ret = R_MakeExternalPtr(jt, RHugin_junction_tree_tag, R_NilValue);

  return ret;
}


SEXP RHugin_node_get_junction_tree(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = NULL;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  jt = h_node_get_junction_tree(node);
  RHugin_handle_error();

  if(jt)
    ret = R_MakeExternalPtr(jt, RHugin_junction_tree_tag, R_NilValue);

  return ret;
}


SEXP RHugin_jt_get_cliques(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_clique_t *clique = NULL, *cliques = NULL;
  int i = 0, n = 0;
  h_junction_tree_t jt = jtPointerFromSEXP(Sjt);

  cliques = h_jt_get_cliques(jt);
  RHugin_handle_error();

  if(cliques) {
    for(clique = cliques; *clique != NULL; clique++) n++;

    PROTECT(ret = allocVector(VECSXP, n));
    for(i = 0; i < n; i++)
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(cliques[i], RHugin_clique_tag, R_NilValue));
    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_jt_get_root(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_clique_t clique = NULL;
  h_junction_tree_t jt = jtPointerFromSEXP(Sjt);

  clique = h_jt_get_root(jt);
  RHugin_handle_error();

  if(clique)
    ret = R_MakeExternalPtr(clique, RHugin_clique_tag, R_NilValue);

  return ret;
}


/* Section 7.3 Cliques */

SEXP RHugin_clique_get_members(SEXP Sclique)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_error_t error_code = h_error_none;
  h_node_t *node = NULL, *nodes = NULL;
  int i = 0, n = 0;
  h_clique_t clique = cliquePointerFromSEXP(Sclique);

  nodes = h_clique_get_members(clique);
  RHugin_handle_error();

  if(nodes) {
    for(node = nodes; *node != NULL; node++) n++;

    PROTECT(ret = allocVector(VECSXP, n));
    PROTECT(names = allocVector(STRSXP, n));

    for(i = 0; i < n; i++) {
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(nodes[i], RHugin_node_tag, R_NilValue));
      SET_STRING_ELT(names, i, mkChar( (char*) h_node_get_name(nodes[i])));
      error_code = h_error_code();
      if(error_code != h_error_none) {
        UNPROTECT(2);
        RHugin_handle_error_code(error_code);
      }
    }
    setAttrib(ret, R_NamesSymbol, names);

    UNPROTECT(2);
  }

  return ret;
}


SEXP RHugin_clique_get_neighbors(SEXP Sclique)
{
  SEXP ret = R_NilValue;
  h_clique_t *neighbor = NULL, *neighbors = NULL;
  int i = 0, n = 0;
  h_clique_t clique = cliquePointerFromSEXP(Sclique);

  neighbors = h_clique_get_neighbors(clique);
  RHugin_handle_error();

  if(neighbors) {
    for(neighbor = neighbors; *neighbor != NULL; neighbor++) n++;

    PROTECT(ret = allocVector(VECSXP, n));
    for(i = 0; i < n; i++)
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(neighbors[i], RHugin_clique_tag, R_NilValue));
    UNPROTECT(1);
  }

  return ret;
}


/* Section 8.2 Entering evidence */

SEXP RHugin_node_select_state(SEXP Snode, SEXP Sstate)
{
  int state = -1;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sstate = AS_INTEGER(Sstate));
  state = INTEGER(Sstate)[0];
  UNPROTECT(1);

  RHugin_handle_status_code(h_node_select_state(node, (size_t) state));

  return R_NilValue;
}


SEXP RHugin_node_enter_finding(SEXP Snode, SEXP Sstates, SEXP Svalues)
{
  h_status_t status = 0;
  double *value = NULL;
  int i = 0, *state = NULL, n = LENGTH(Sstates);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  if(LENGTH(Svalues) != n)
    error("Sstates and Svalues are not the same length");

  PROTECT(Sstates = AS_INTEGER(Sstates));
  PROTECT(Svalues = AS_NUMERIC(Svalues));
  state = INTEGER(Sstates);
  value = REAL(Svalues);

  for(i = 0; i < n; i++) {
    status = h_node_enter_finding(node, (size_t) state[i], (h_number_t) value[i]);
    if((h_error_t) status != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code((h_error_t) status);
    }
  }

  UNPROTECT(2);
  return R_NilValue;
}


SEXP RHugin_node_enter_value(SEXP Snode, SEXP Svalue)
{
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  h_double_t value = 0.0;

  PROTECT(Svalue = AS_NUMERIC(Svalue));
  value = (h_double_t) REAL(Svalue)[0];
  UNPROTECT(1);

  RHugin_handle_status_code(h_node_enter_value(node, value));

  return R_NilValue;
}


/* Section 8.3 Retracting evidence */

SEXP RHugin_node_retract_findings(SEXP Snodes)
{
  h_node_t node = NULL;
  int i = 0, n = LENGTH(Snodes);

  for(i = 0; i < n; i++) {
    node = nodePointerFromSEXP(VECTOR_ELT(Snodes, i));
    RHugin_handle_status_code(h_node_retract_findings(node));
  }

  return R_NilValue;
}


SEXP RHugin_domain_retract_findings(SEXP Sdomain)
{
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  RHugin_handle_status_code(h_domain_retract_findings(domain));

  return R_NilValue;
}


/* Section 8.4 Determining independence properties */

SEXP RHugin_domain_get_d_connected_nodes(SEXP Sdomain, SEXP Ssource, SEXP Shard, SEXP Ssoft)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_error_t error_code = h_error_none;
  h_node_t *source = NULL, *hard = NULL, *soft = NULL, *d_connected = NULL, *node = NULL;
  int i = 0, n = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  source = (h_node_t*) R_alloc(1 + LENGTH(Ssource), sizeof(h_node_t));
  for(i = 0; i < LENGTH(Ssource); i++)
    source[i] = nodePointerFromSEXP(VECTOR_ELT(Ssource, i));
  source[LENGTH(Ssource)] = NULL;

  hard = (h_node_t*) R_alloc(1 + LENGTH(Shard), sizeof(h_node_t));
  for(i = 0; i < LENGTH(Shard); i++)
    hard[i] = nodePointerFromSEXP(VECTOR_ELT(Shard, i));
  hard[LENGTH(Shard)] = NULL;

  soft = (h_node_t*) R_alloc(1 + LENGTH(Ssoft), sizeof(h_node_t));
  for(i = 0; i < LENGTH(Ssoft); i++)
    soft[i] = nodePointerFromSEXP(VECTOR_ELT(Ssoft, i));
  soft[LENGTH(Ssoft)] = NULL;

  d_connected = h_domain_get_d_connected_nodes(domain, source, hard, soft);
  RHugin_handle_error();

  if(d_connected) {
    for(node = d_connected; *node != NULL; node++) n++;

    PROTECT(ret = allocVector(VECSXP, n));
    PROTECT(names = allocVector(STRSXP, n));

    for(i = 0; i < n; i++) {
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(d_connected[i], RHugin_node_tag, R_NilValue));
      SET_STRING_ELT(names, i, mkChar( (char*) h_node_get_name(d_connected[i])));
      error_code = h_error_code();
      if(error_code != h_error_none) {
        UNPROTECT(2);
        RHugin_handle_error_code(error_code);
      }
    }
    setAttrib(ret, R_NamesSymbol, names);

    UNPROTECT(2);
  }

  return ret;
}


SEXP RHugin_domain_get_d_separated_nodes(SEXP Sdomain, SEXP Ssource, SEXP Shard, SEXP Ssoft)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_error_t error_code = h_error_none;
  h_node_t *source = NULL, *hard = NULL, *soft = NULL, *d_separated = NULL, *node = NULL;
  int i = 0, n = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  source = (h_node_t*) R_alloc(1 + LENGTH(Ssource), sizeof(h_node_t));
  for(i = 0; i < LENGTH(Ssource); i++)
    source[i] = nodePointerFromSEXP(VECTOR_ELT(Ssource, i));
  source[LENGTH(Ssource)] = NULL;

  hard = (h_node_t*) R_alloc(1 + LENGTH(Shard), sizeof(h_node_t));
  for(i = 0; i < LENGTH(Shard); i++)
    hard[i] = nodePointerFromSEXP(VECTOR_ELT(Shard, i));
  hard[LENGTH(Shard)] = NULL;

  soft = (h_node_t*) R_alloc(1 + LENGTH(Ssoft), sizeof(h_node_t));
  for(i = 0; i < LENGTH(Ssoft); i++)
    soft[i] = nodePointerFromSEXP(VECTOR_ELT(Ssoft, i));
  soft[LENGTH(Ssoft)] = NULL;

  d_separated = h_domain_get_d_separated_nodes(domain, source, hard, soft);
  RHugin_handle_error();

  if(d_separated) {
    for(node = d_separated; *node != NULL; node++) n++;

    PROTECT(ret = allocVector(VECSXP, n));
    PROTECT(names = allocVector(STRSXP, n));

    for(i = 0; i < n; i++) {
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(d_separated[i], RHugin_node_tag, R_NilValue));
      SET_STRING_ELT(names, i, mkChar( (char*) h_node_get_name(d_separated[i])));
      error_code = h_error_code();
      if(error_code != h_error_none) {
        UNPROTECT(2);
        RHugin_handle_error_code(error_code);
      }
    }
    setAttrib(ret, R_NamesSymbol, names);
    UNPROTECT(2);
  }

  return ret;
}


/* Section 8.5 Retreiving beliefs */

SEXP RHugin_node_get_belief(SEXP Snode, SEXP Sstates)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *belief = NULL;
  int i = 0, *states = NULL, n = LENGTH(Sstates);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sstates = AS_INTEGER(Sstates));
  PROTECT(ret = allocVector(REALSXP, n));
  belief = REAL(ret);
  states = INTEGER(Sstates);

  for(i = 0; i < n; i++) {
    belief[i] = (double) h_node_get_belief(node, (size_t) states[i]);
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


SEXP RHugin_node_get_mean(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_node_get_mean(node);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_node_get_variance(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_node_get_variance(node);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_get_marginal(SEXP Sdomain, SEXP Snodes)
{
  SEXP ret = R_NilValue;
  h_node_t *nodes = NULL;
  h_table_t table = NULL;
  int i = 0, n = LENGTH(Snodes);
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  nodes = (h_node_t*) R_alloc(n + 1, sizeof(h_node_t));
  for(i = 0; i < n; i++)
    nodes[i] = nodePointerFromSEXP(VECTOR_ELT(Snodes, i));
  nodes[n] = NULL;

  table = h_domain_get_marginal(domain, nodes);
  RHugin_handle_error();

  if(table)
     ret = R_MakeExternalPtr(table, RHugin_table_tag, R_NilValue);

  return ret;
}


SEXP RHugin_node_get_distribution(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_table_t table = NULL;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  table = h_node_get_distribution(node);
  RHugin_handle_error();

  if(table)
     ret = R_MakeExternalPtr(table, RHugin_table_tag, R_NilValue);

  return ret;
}


/* Section 8.6 Retrieving expected utilities */

SEXP RHugin_node_get_expected_utility(SEXP Snode, SEXP Sstates)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *utility = NULL;
  int i = 0, *states = NULL, n = LENGTH(Sstates);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sstates = AS_INTEGER(Sstates));
  PROTECT(ret = allocVector(REALSXP, n));
  states = INTEGER(Sstates);
  utility = REAL(ret);

  for(i = 0; i < n; i++) {
    utility[i] = (double) h_node_get_expected_utility(node, (size_t) states[i]);
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


/* Section 8.7 Examining Evidence */

SEXP RHugin_node_get_entered_finding(SEXP Snode, SEXP Sstates)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *finding = NULL;
  int i = 0, *states = NULL, n = LENGTH(Sstates);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sstates = AS_INTEGER(Sstates));
  PROTECT(ret = allocVector(REALSXP, n));
  states = INTEGER(Sstates);
  finding = REAL(ret);

  for(i = 0; i < n; i++) {
    finding[i] = (double) h_node_get_entered_finding(node, (size_t) states[i]);
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


SEXP RHugin_node_get_propagated_finding(SEXP Snode, SEXP Sstates)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *finding = NULL;
  int i = 0, *states = NULL, n = LENGTH(Sstates);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sstates = AS_INTEGER(Sstates));
  PROTECT(ret = allocVector(REALSXP, n));
  states = INTEGER(Sstates);
  finding = REAL(ret);

  for(i = 0; i < n; i++) {
    finding[i] = (double) h_node_get_propagated_finding(node, (size_t) states[i]);
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


SEXP RHugin_node_get_entered_value(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_node_get_entered_value(node);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_node_get_propagated_value(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_node_get_propagated_value(node);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_node_evidence_is_entered(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_node_evidence_is_entered(node);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_node_likelihood_is_entered(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_node_likelihood_is_entered(node);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_node_evidence_is_propagated(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_node_evidence_is_propagated(node);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_node_likelihood_is_propagated(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_node_likelihood_is_propagated(node);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


/* Section 8.8 Case files */

SEXP RHugin_domain_save_case(SEXP Sdomain, SEXP Sfile_name)
{
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  RHugin_handle_status_code(h_domain_save_case(domain, (h_string_t) CHAR(asChar(Sfile_name))));

  return R_NilValue;
}


// SEXP RHugin_domain_parse_case(SEXP Sdomain, SEXP Sfile_name)


/* Section 9.2 Propagation */

SEXP RHugin_domain_propagate(SEXP Sdomain, SEXP Sequilibrium, SEXP Smode)
{
  h_equilibrium_t equilibrium = h_equilibrium_sum;
  h_evidence_mode_t mode = h_mode_normal;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Sequilibrium = AS_CHARACTER(Sequilibrium));
  PROTECT(Smode = AS_CHARACTER(Smode));

  if(asChar(Sequilibrium) == RHUGIN_EQUILIBRIUM_MAX)
    equilibrium = h_equilibrium_max;

  if(asChar(Smode) == RHUGIN_MODE_FAST_RETRACTION)
    mode = h_mode_fast_retraction;

  UNPROTECT(2);

  RHugin_handle_status_code(h_domain_propagate(domain, equilibrium, mode));

  return R_NilValue;
}


SEXP RHugin_jt_propagate(SEXP Sjt, SEXP Sequilibrium, SEXP Smode)
{
  h_equilibrium_t equilibrium = h_equilibrium_sum;
  h_evidence_mode_t mode = h_mode_normal;
  h_junction_tree_t jt = jtPointerFromSEXP(Sjt);

  PROTECT(Sequilibrium = AS_CHARACTER(Sequilibrium));
  PROTECT(Smode = AS_CHARACTER(Smode));

  if(asChar(Sequilibrium) == RHUGIN_EQUILIBRIUM_MAX)
    equilibrium = h_equilibrium_max;

  if(asChar(Smode) == RHUGIN_MODE_FAST_RETRACTION)
    mode = h_mode_fast_retraction;

  UNPROTECT(2);

  RHugin_handle_status_code(h_jt_propagate(jt, equilibrium, mode));

  return R_NilValue;
}


/* Section 9.3 Conflict of evidence */

SEXP RHugin_domain_get_conflict(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_conflict(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_jt_get_conflict(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = jtPointerFromSEXP(Sjt);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_jt_get_conflict(jt);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_reset_inference_engine(SEXP Sdomain)
{
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  RHugin_handle_status_code(h_domain_reset_inference_engine(domain));

  return R_NilValue;
}


/* Secttion 9.4 The normalization constant */

SEXP RHugin_domain_get_normalization_constant(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_normalization_constant(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_get_log_normalization_constant(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_log_normalization_constant(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


/* Section 9.5 Initializing the domain */

SEXP RHugin_domain_save_to_memory(SEXP Sdomain)
{
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  RHugin_handle_status_code(h_domain_save_to_memory(domain));

  return R_NilValue;
}


SEXP RHugin_domain_initialize(SEXP Sdomain)
{
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  RHugin_handle_status_code(h_domain_initialize(domain));

  return R_NilValue;
}


/* Section 9.6 Querying the state of the inference engine */

SEXP RHugin_domain_equilibrium_is(SEXP Sdomain, SEXP Sequilibrium)
{
  SEXP ret = R_NilValue;
  h_equilibrium_t equilibrium = h_equilibrium_sum;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Sequilibrium = AS_CHARACTER(Sequilibrium));

  if(asChar(Sequilibrium) == RHUGIN_EQUILIBRIUM_MAX)
    equilibrium = h_equilibrium_max;

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_equilibrium_is(domain, equilibrium);
  UNPROTECT(2);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_jt_equilibrium_is(SEXP Sjt, SEXP Sequilibrium)
{
  SEXP ret = R_NilValue;
  h_equilibrium_t equilibrium = h_equilibrium_sum;
  h_junction_tree_t jt = jtPointerFromSEXP(Sjt);

  PROTECT(Sequilibrium = AS_CHARACTER(Sequilibrium));

  if(asChar(Sequilibrium) == RHUGIN_EQUILIBRIUM_MAX)
    equilibrium = h_equilibrium_max;

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_jt_equilibrium_is(jt, equilibrium);
  UNPROTECT(2);

  return ret;
}


SEXP RHugin_domain_evidence_mode_is(SEXP Sdomain, SEXP Smode)
{
  SEXP ret = R_NilValue;
  h_evidence_mode_t mode = h_mode_normal;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Smode = AS_CHARACTER(Smode));

  if(asChar(Smode) == RHUGIN_MODE_FAST_RETRACTION)
    mode = h_mode_fast_retraction;

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_evidence_mode_is(domain, mode);
  UNPROTECT(2);

  return ret;
}


SEXP RHugin_jt_evidence_mode_is(SEXP Sjt, SEXP Smode)
{
  SEXP ret = R_NilValue;
  h_evidence_mode_t mode = h_mode_normal;
  h_junction_tree_t jt = jtPointerFromSEXP(Sjt);

  PROTECT(Smode = AS_CHARACTER(Smode));

  if(asChar(Smode) == RHUGIN_MODE_FAST_RETRACTION)
    mode = h_mode_fast_retraction;

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_jt_evidence_mode_is(jt, mode);
  UNPROTECT(2);

  return ret;
}


SEXP RHugin_domain_evidence_is_propagated(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_evidence_is_propagated(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_jt_evidence_is_propagated(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = jtPointerFromSEXP(Sjt);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_jt_evidence_is_propagated(jt);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_likelihood_is_propagated(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_likelihood_is_propagated(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_jt_likelihood_is_propagated(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = jtPointerFromSEXP(Sjt);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_jt_likelihood_is_propagated(jt);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_cg_evidence_is_propagated(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_cg_evidence_is_propagated(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_jt_cg_evidence_is_propagated(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = jtPointerFromSEXP(Sjt);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_jt_cg_evidence_is_propagated(jt);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_evidence_to_propagate(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_evidence_to_propagate(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_jt_evidence_to_propagate(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = jtPointerFromSEXP(Sjt);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_jt_evidence_to_propagate(jt);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_node_evidence_to_propagate(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_node_evidence_to_propagate(node);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_tables_to_propagate(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_domain_tables_to_propagate(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_jt_tables_to_propagate(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = jtPointerFromSEXP(Sjt);

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_jt_tables_to_propagate(jt);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


/* Section 9.7 Simulation */

SEXP RHugin_domain_simulate(SEXP Sdomain)
{
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  RHugin_handle_status_code(h_domain_simulate(domain));

  return R_NilValue;
}


SEXP RHugin_node_get_sampled_state(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_node_get_sampled_state(node);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_node_get_sampled_value(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_node_get_sampled_value(node);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_seed_random(SEXP Sdomain, SEXP Sseed)
{
  SEXP ret = R_NilValue;
  unsigned int seed = 1;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Sseed = AS_INTEGER(Sseed));
  seed = (unsigned int) INTEGER(Sseed)[0];
  UNPROTECT(1);

  RHugin_handle_status_code(h_domain_seed_random(domain, seed));

  return R_NilValue;
}


SEXP RHugin_domain_get_uniform_deviate(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_uniform_deviate(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_get_normal_deviate(SEXP Sdomain, SEXP Smean, SEXP Svariance)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Smean = AS_NUMERIC(Smean));
  PROTECT(Svariance = AS_NUMERIC(Svariance));
  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_normal_deviate(domain, REAL(Smean)[0], REAL(Svariance)[0]);
  UNPROTECT(3);

  RHugin_handle_error();

  return ret;
}


/* Section 9.8 Value of information analysis */

SEXP RHugin_node_get_entropy(SEXP Snodes)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  h_node_t node = NULL;
  double *entropy = NULL;
  int i = 0, n = LENGTH(Snodes);

  PROTECT(ret = allocVector(REALSXP, n));
  entropy = REAL(ret);

  for(i = 0; i < n; i++) {
    node = nodePointerFromSEXP(VECTOR_ELT(Snodes, i));
    entropy[i] = (double) h_node_get_entropy(node);
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(1);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(1);
  return ret;
}


SEXP RHugin_node_get_mutual_information(SEXP Snodes, SEXP Sothers)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  h_node_t node = NULL, other = NULL;
  double *mi = NULL;
  int i = 0, n = LENGTH(Snodes);

  if(LENGTH(Sothers) != n)
    error("Snodes and Sothers are not the same length");

  PROTECT(ret = allocVector(REALSXP, n));
  mi = REAL(ret);

  for(i = 0; i < n; i++) {
    node = nodePointerFromSEXP(VECTOR_ELT(Snodes, i));
    other = nodePointerFromSEXP(VECTOR_ELT(Sothers, i));
    mi[i] = (double) h_node_get_mutual_information(node, other);
    if(error_code != h_error_none) {
      UNPROTECT(1);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(1);

  return ret;
}


/* Section 9.9 Sensitivity analyis */

SEXP RHugin_node_compute_sensitivity_data(SEXP Snode, SEXP Sstate)
{
  size_t state = -1;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sstate = AS_INTEGER(Sstate));
  state = (size_t) INTEGER(Sstate)[0];
  UNPROTECT(1);

  RHugin_handle_status_code(h_node_compute_sensitivity_data(node, state));

  return R_NilValue;
}


SEXP RHugin_node_get_sensitivity_constants(SEXP Snode, SEXP Sindex)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_status_t status = 0;
  double *constants = NULL;
  h_number_t *pret = NULL;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sindex = AS_INTEGER(Sindex));
  PROTECT(ret = allocVector(REALSXP, 4));
  constants = REAL(ret);
  PROTECT(names = allocVector(STRSXP, 4));

  pret = (h_number_t*) R_alloc(4, sizeof(h_number_t));

  status = h_node_get_sensitivity_constants(node, (size_t) INTEGER(Sindex)[0],
                                            pret, pret + 1, pret + 2, pret + 3);

  constants[0] = (double) pret[0];
  SET_STRING_ELT(names, 0, mkChar("alpha"));
  constants[1] = (double) pret[1];
  SET_STRING_ELT(names, 1, mkChar("beta"));
  constants[2] = (double) pret[2];
  SET_STRING_ELT(names, 2, mkChar("gamma"));
  constants[3] = (double) pret[3];
  SET_STRING_ELT(names, 3, mkChar("delta"));
  setAttrib(ret, R_NamesSymbol, names);
  UNPROTECT(3);

  RHugin_handle_status_code(status);

  return ret;
}


SEXP RHugin_domain_get_sensitivity_set(SEXP Sdomain)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_error_t error_code = h_error_none;
  h_node_t *sensitivity_set = NULL, *pnode = NULL;
  int i = 0, n = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  sensitivity_set = h_domain_get_sensitivity_set(domain);
  RHugin_handle_error();

  if(sensitivity_set) {
    for(pnode = sensitivity_set; *pnode != NULL; pnode++) n++;

    PROTECT(ret = allocVector(VECSXP, n));
    PROTECT(names = allocVector(STRSXP, n));

    for(i = 0; i < n; i++) {
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(sensitivity_set[i], RHugin_node_tag, R_NilValue));
      SET_STRING_ELT(names, i, mkChar( (char*) h_node_get_name(sensitivity_set[i])));
      error_code = h_error_code();
      if(error_code != h_error_none) {
        UNPROTECT(2);
        RHugin_handle_error_code(error_code);
      }
    }
    setAttrib(ret, R_NamesSymbol, names);

    UNPROTECT(2);
  }

  return ret;
}


/* Section 10.1 Experience counts and fading factors */

SEXP RHugin_node_get_experience_table(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_table_t table = NULL;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  table = h_node_get_experience_table(node);
  RHugin_handle_error();

  if(table)
    ret = R_MakeExternalPtr(table, RHugin_table_tag, R_NilValue);

  return ret;
}


SEXP RHugin_node_has_experience_table(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_node_has_experience_table(node);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_node_get_fading_table(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_table_t table = NULL;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  table = h_node_get_fading_table(node);
  RHugin_handle_error();

  if(table)
    ret = R_MakeExternalPtr(table, RHugin_table_tag, R_NilValue);

  return ret;
}


SEXP RHugin_node_has_fading_table(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = (int) h_node_has_fading_table(node);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


/* Section 10.2 Updating tables */

SEXP RHugin_domain_adapt(SEXP Sdomain)
{
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  RHugin_handle_status_code(h_domain_adapt(domain));

  return R_NilValue;
}


/* Section 11.1 Data */

SEXP RHugin_domain_set_number_of_cases(SEXP Sdomain, SEXP Scount)
{
  size_t count = -1;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Scount = AS_INTEGER(Scount));
  count = (size_t) INTEGER(Scount)[0];
  UNPROTECT(1);

  RHugin_handle_status_code(h_domain_set_number_of_cases(domain, count));

  return R_NilValue;
}


SEXP RHugin_domain_new_case(SEXP Sdomain)
{
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  RHugin_handle_status_code(h_domain_new_case(domain));

  return R_NilValue;
}


SEXP RHugin_domain_get_number_of_cases(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_get_number_of_cases(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_node_set_case_state(SEXP Snode, SEXP Scase_indices, SEXP Sstates)
{
  h_status_t status = 0;
  int i = 0, *case_indices = NULL, *states = NULL, n = LENGTH(Scase_indices);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  if(LENGTH(Sstates) != n)
    error("Scase_indices and Sstates are not the same length");

  PROTECT(Scase_indices = AS_INTEGER(Scase_indices));
  PROTECT(Sstates = AS_INTEGER(Sstates));
  case_indices = INTEGER(Scase_indices);
  states = INTEGER(Sstates);

  for(i = 0; i < n; i++) {
    status = h_node_set_case_state(node, (size_t) case_indices[i], (size_t) states[i]);
    if((h_error_t) status != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code((h_error_t) status);
    }
  }

  UNPROTECT(2);
  return R_NilValue;
}


SEXP RHugin_node_get_case_state(SEXP Snode, SEXP Scase_indices)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  int i = 0, *states = NULL, *case_indices = NULL, n = LENGTH(Scase_indices);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Scase_indices = AS_INTEGER(Scase_indices));
  PROTECT(ret = allocVector(INTSXP, n));
  states = INTEGER(ret);
  case_indices = INTEGER(Scase_indices);

  for(i = 0; i < n; i++) {
    states[i] = h_node_case_is_set(node, (size_t) case_indices[i]) ?
                (int) h_node_get_case_state(node, (size_t) case_indices[i]) :
                NA_INTEGER;
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


SEXP RHugin_node_set_case_value(SEXP Snode, SEXP Scase_indices, SEXP Svalues)
{
  SEXP ret = R_NilValue;
  h_status_t status = 0;
  double *values = NULL;
  int i = 0, *case_indices = NULL, n = LENGTH(Scase_indices);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  if(LENGTH(Svalues) != n)
    error("Scase_indices and Svalues are not the same length");

  PROTECT(Scase_indices = AS_INTEGER(Scase_indices));
  PROTECT(Svalues = AS_NUMERIC(Svalues));
  case_indices = INTEGER(Scase_indices);
  values = REAL(Svalues);

  for(i = 0; i < n; i++) {
    if(!R_FINITE(values[i]))
      status = h_node_unset_case(node, (size_t) case_indices[i]);
    else
      status = h_node_set_case_value(node, (size_t) case_indices[i], values[i]);

    if((h_error_t) status != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code((h_error_t) status);
    }
  }

  UNPROTECT(2);
  return R_NilValue;
}


SEXP RHugin_node_get_case_value(SEXP Snode, SEXP Scase_indices)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *values = NULL;
  int i = 0, *case_indices = NULL, n = LENGTH(Scase_indices);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Scase_indices = AS_INTEGER(Scase_indices));
  PROTECT(ret = allocVector(REALSXP, n));
  case_indices = INTEGER(Scase_indices);
  values = REAL(ret);

  for(i = 0; i < n; i++) {
    values[i] = h_node_case_is_set(node, (size_t) case_indices[i]) ?
                (double) h_node_get_case_value(node, (size_t) case_indices[i]) :
                NA_REAL;
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


SEXP RHugin_node_unset_case(SEXP Snode, SEXP Scase_indices)
{
  h_status_t status = 0;
  int i = 0, *case_indices = NULL;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Scase_indices = AS_INTEGER(Scase_indices));
  case_indices = INTEGER(Scase_indices);

  for(i = 0; i < LENGTH(Scase_indices); i++) {
    status = h_node_unset_case(node, (size_t) case_indices[i]);
    if((h_error_t) status != h_error_none) {
      UNPROTECT(1);
      RHugin_handle_error_code((h_error_t) status);
    }
  }

  UNPROTECT(1);
  return R_NilValue;
}


SEXP RHugin_node_case_is_set(SEXP Snode, SEXP Scase_indices)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  int i = 0, *case_indices = NULL, *case_is_set = NULL, n = LENGTH(Scase_indices);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Scase_indices = AS_INTEGER(Scase_indices));
  PROTECT(ret = allocVector(LGLSXP, n));
  case_indices = INTEGER(Scase_indices);
  case_is_set = LOGICAL(ret);

  for(i = 0; i < n; i++) {
    case_is_set[i] = (int) h_node_case_is_set(node, (size_t) case_indices[i]);
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


SEXP RHugin_domain_set_case_count(SEXP Sdomain, SEXP Scase_indices, SEXP Scase_counts)
{
  h_status_t status = 0;
  h_error_t error_code = h_error_none;
  double *case_counts = NULL;
  int i = 0, *case_indices = NULL, n = LENGTH(Scase_indices);
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  if(LENGTH(Scase_counts) != n)
    error("Scase_indices and Scase_counts are not the same length");

  PROTECT(Scase_indices = AS_INTEGER(Scase_indices));
  PROTECT(Scase_counts = AS_NUMERIC(Scase_counts));
  case_indices = INTEGER(Scase_indices);
  case_counts = REAL(Scase_counts);

  for(i = 0; i < n; i++) {
    status = h_domain_set_case_count(domain, (size_t) case_indices[i], (h_number_t) case_counts[i]);
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return R_NilValue;
}


SEXP RHugin_domain_get_case_count(SEXP Sdomain, SEXP Scase_indices)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *counts = NULL;
  int i = 0, *case_indices = NULL, n = LENGTH(Scase_indices);
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Scase_indices = AS_INTEGER(Scase_indices));
  PROTECT(ret = allocVector(REALSXP, n));
  case_indices = INTEGER(Scase_indices);
  counts = REAL(ret);

  for(i = 0; i < n; i++) {
    counts[i] = (double) h_domain_get_case_count(domain, (size_t) case_indices[i]);
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


SEXP RHugin_domain_enter_case(SEXP Sdomain, SEXP Scase_index)
{
  size_t case_index = -1;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Scase_index = AS_INTEGER(Scase_index));
  case_index = (size_t) INTEGER(Scase_index)[0];
  UNPROTECT(1);

  RHugin_handle_status_code(h_domain_enter_case(domain, case_index));

  return R_NilValue;
}


/* Section 11.2 Scoring of graphical models */

SEXP RHugin_domain_get_log_likelihood(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_log_likelihood(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_get_AIC(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_AIC(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_get_BIC(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_BIC(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


/* Section 11.3 Data files */

SEXP RHugin_domain_parse_cases(SEXP Sdomain, SEXP Sfile_name)
{
  h_status_t status = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Sfile_name = AS_CHARACTER(Sfile_name));
  status = h_domain_parse_cases(domain, (h_string_t) CHAR(asChar(Sfile_name)),
                                RHuginParseError, NULL);
  UNPROTECT(1);

  RHugin_handle_status_code(status);

  return R_NilValue;
}


SEXP RHugin_domain_save_cases(SEXP Sdomain, SEXP Sfile_name, SEXP Snodes,
                              SEXP Scases, SEXP Sinclude_case_counts,
                              SEXP Sseparator, SEXP Smissing_data)
{
  h_status_t status = 0;
  h_boolean_t include_case_counts = FALSE;
  h_index_t *case_indices = NULL;
  h_node_t *nodes = NULL;
  int i = 0, n_cases = -1, *cases = NULL, n_nodes = LENGTH(Snodes);
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Sfile_name = AS_CHARACTER(Sfile_name));
  PROTECT(Sinclude_case_counts = AS_LOGICAL(Sinclude_case_counts));
  PROTECT(Sseparator = AS_CHARACTER(Sseparator));
  PROTECT(Smissing_data = AS_CHARACTER(Smissing_data));

  nodes = (h_node_t*) R_alloc(n_nodes + 1, sizeof(h_node_t));
  for(i = 0; i < n_nodes; i++)
    nodes[i] = nodePointerFromSEXP(VECTOR_ELT(Snodes, i));
  nodes[n_nodes] = NULL;

  if(Scases == R_NilValue)
    case_indices = NULL;
  else {
    PROTECT(Scases = AS_INTEGER(Scases));
    n_cases = LENGTH(Scases);
    cases = INTEGER(Scases);
    case_indices = (h_index_t*) R_alloc(n_cases + 1, sizeof(h_index_t));
    for(i = 0; i < n_cases; i++)
      case_indices[i] = (h_index_t) cases[i];
    case_indices[n_cases] = -1;
    UNPROTECT(1);
  }

  include_case_counts = (h_boolean_t) LOGICAL(Sinclude_case_counts)[0];

  status = h_domain_save_cases(domain, (h_string_t) CHAR(asChar(Sfile_name)),
                               nodes, case_indices, include_case_counts,
                               (h_string_t) CHAR(asChar(Sseparator)),
                               (h_string_t) CHAR(asChar(Smissing_data)));

  UNPROTECT(4);

  RHugin_handle_status_code(status);

  return R_NilValue;
}


/* Section 11.4 Learning network structure */

SEXP RHugin_domain_learn_structure(SEXP Sdomain)
{
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  RHugin_handle_status_code(h_domain_learn_structure(domain));

  return R_NilValue;
}
  

SEXP RHugin_domain_set_significance_level(SEXP Sdomain, SEXP Sprobability)
{
  h_double_t probability = -1.0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Sprobability = AS_NUMERIC(Sprobability));
  probability = (h_double_t) REAL(Sprobability)[0];
  UNPROTECT(1);

  RHugin_handle_status_code(h_domain_set_significance_level(domain, probability));

  return R_NilValue;
}


SEXP RHugin_domain_get_significance_level(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_significance_level(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


/* Section 11.5 Domain knowledge */

SEXP RHugin_node_set_edge_constraint(SEXP Sa, SEXP Sb, SEXP Sconstraint)
{
  h_node_t a = NULL, b = NULL;
  h_edge_constraint_t constraint = h_constraint_error;

  a = nodePointerFromSEXP(VECTOR_ELT(Sa, 0));
  b = nodePointerFromSEXP(VECTOR_ELT(Sb, 0));

  PROTECT(Sconstraint = AS_CHARACTER(Sconstraint));

  if(asChar(Sconstraint) == RHUGIN_CONSTRAINT_NONE)
    constraint = h_constraint_none;
  else if(asChar(Sconstraint) == RHUGIN_CONSTRAINT_EDGE_REQUIRED)
    constraint = h_constraint_edge_required;
  else if(asChar(Sconstraint) == RHUGIN_CONSTRAINT_EDGE_FORBIDDEN)
    constraint = h_constraint_edge_forbidden;
  else if(asChar(Sconstraint) == RHUGIN_CONSTRAINT_FORWARD_EDGE_REQUIRED)
    constraint = h_constraint_forward_edge_required;
  else if(asChar(Sconstraint) == RHUGIN_CONSTRAINT_BACKWARD_EDGE_REQUIRED)
    constraint = h_constraint_backward_edge_required;
  else if(asChar(Sconstraint) == RHUGIN_CONSTRAINT_FORWARD_EDGE_FORBIDDEN)
    constraint = h_constraint_forward_edge_forbidden;
  else if(asChar(Sconstraint) == RHUGIN_CONSTRAINT_BACKWARD_EDGE_FORBIDDEN)
    constraint = h_constraint_backward_edge_forbidden;

  UNPROTECT(1);

  RHugin_handle_status_code(h_node_set_edge_constraint(a, b, constraint));

  return R_NilValue;
}


SEXP RHugin_node_get_edge_constraint(SEXP Sa, SEXP Sb)
{
  SEXP ret = R_NilValue;
  h_node_t a = NULL, b = NULL;
  h_edge_constraint_t constraint = h_constraint_error;

  a = nodePointerFromSEXP(VECTOR_ELT(Sa, 0));
  b = nodePointerFromSEXP(VECTOR_ELT(Sb, 0));
  constraint = h_node_get_edge_constraint(a, b);
  RHugin_handle_error();

  PROTECT(ret = allocVector(STRSXP, 1));

  switch(constraint) {
    case h_constraint_none:
      SET_STRING_ELT(ret, 0, mkChar("none"));
      break;

    case h_constraint_edge_required:
      SET_STRING_ELT(ret, 0, mkChar("edge.required"));
      break;

    case h_constraint_edge_forbidden:
      SET_STRING_ELT(ret, 0, mkChar("edge.forbidden"));
      break;

    case h_constraint_forward_edge_required:
      SET_STRING_ELT(ret, 0, mkChar("forward.edge.required"));
      break;

    case h_constraint_backward_edge_required:
      SET_STRING_ELT(ret, 0, mkChar("backward.edge.required"));
      break;

    case h_constraint_forward_edge_forbidden:
      SET_STRING_ELT(ret, 0, mkChar("forward.edge.forbidden"));
      break;

    case h_constraint_backward_edge_forbidden:
      SET_STRING_ELT(ret, 0, mkChar("backward.edge.forbidden"));
      break;

    case h_constraint_error:
      SET_STRING_ELT(ret, 0, mkChar("error"));
      break;
  }

  UNPROTECT(1);
  return ret;
}


/* Section 11.6 Learning conditional probability tables */

SEXP RHugin_domain_learn_tables(SEXP Sdomain)
{
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  RHugin_handle_status_code(h_domain_learn_tables(domain));

  return R_NilValue;
}


SEXP RHugin_domain_set_log_likelihood_tolerance(SEXP Sdomain, SEXP Stolerance)
{
  h_double_t tolerance = -1.0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Stolerance = AS_NUMERIC(Stolerance));
  tolerance = (h_double_t) REAL(Stolerance)[0];
  UNPROTECT(1);

  RHugin_handle_status_code(h_domain_set_log_likelihood_tolerance(domain, tolerance));

  return R_NilValue;
}


SEXP RHugin_domain_get_log_likelihood_tolerance(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_log_likelihood_tolerance(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_set_max_number_of_em_iterations(SEXP Sdomain, SEXP Scount)
{
  size_t count = -1;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Scount = AS_INTEGER(Scount));
  count = (size_t) INTEGER(Scount)[0];
  UNPROTECT(1);

  RHugin_handle_status_code(h_domain_set_max_number_of_em_iterations(domain, count));

  return R_NilValue;
}


SEXP RHugin_domain_get_max_number_of_em_iterations(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(INTSXP, 1));
  INTEGER(ret)[0] = (int) h_domain_get_max_number_of_em_iterations(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_learn_class_tables(SEXP Sdomain)
{
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  RHugin_handle_status_code(h_domain_learn_class_tables(domain));

  return R_NilValue;
}


/* Section 12.8 parsing NET files */

SEXP RHugin_net_parse_domain(SEXP Sfile_name)
{
  SEXP ret = R_NilValue;

  PROTECT(Sfile_name = AS_CHARACTER(Sfile_name));

  h_domain_t domain = h_net_parse_domain((h_string_t) CHAR(asChar(Sfile_name)),
                                         RHuginParseError,
                                         NULL);

  RHugin_handle_error();

  if(domain) {
    ret = R_MakeExternalPtr(domain, RHugin_domain_tag, R_NilValue);
    R_RegisterCFinalizer(ret, (R_CFinalizer_t) RHugin_domain_finalizer); 
  }

  return ret;
}


SEXP RHugin_domain_save_as_net(SEXP Sdomain, SEXP Sfile_name)
{
  h_status_t status = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Sfile_name = AS_CHARACTER(Sfile_name));
  status = h_domain_save_as_net(domain, (h_string_t) CHAR(asChar(Sfile_name)));
  UNPROTECT(1);

  RHugin_handle_status_code(status);

  return R_NilValue;
}


/* Section 13.2 the position of a node */

SEXP RHugin_node_set_position(SEXP Snode, SEXP Sposition)
{
  h_coordinate_t x = -1, y = -1;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sposition = AS_INTEGER(Sposition));
  x = (h_coordinate_t) INTEGER(Sposition)[0];
  y = (h_coordinate_t) INTEGER(Sposition)[1];
  UNPROTECT(1);

  RHugin_handle_status_code(h_node_set_position(node, x, y));

  return R_NilValue;
}


SEXP RHugin_node_get_position(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_coordinate_t position[] = {-1, -1};
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  
  RHugin_handle_status_code(h_node_get_position(node, position, position + 1));

  PROTECT(ret = allocVector(INTSXP, 2));
  INTEGER(ret)[0] = (int) position[0];
  INTEGER(ret)[1] = (int) position[1];
  UNPROTECT(1);

  return ret;
}


/* Section 13.3 the size of a node */

SEXP RHugin_domain_set_node_size(SEXP Sdomain, SEXP Ssize)
{
  size_t width = -1, height = -1;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);
  
  PROTECT(Ssize = AS_INTEGER(Ssize));
  width = (size_t) INTEGER(Ssize)[0];
  height = (size_t) INTEGER(Ssize)[1];
  UNPROTECT(1);

  RHugin_handle_status_code(h_domain_set_node_size(domain, width, height));

  return R_NilValue;
}


SEXP RHugin_domain_get_node_size(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  size_t size[] = {-1, -1};
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  RHugin_handle_status_code(h_domain_get_node_size(domain, size, size + 1));

  PROTECT(ret = allocVector(INTSXP, 2));
  INTEGER(ret)[0] = (int) size[0];
  INTEGER(ret)[1] = (int) size[1];
  UNPROTECT(1);

  return ret;
}


