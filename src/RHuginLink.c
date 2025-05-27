#include "RHugin.h"
#include "RHuginLink.h"

#ifndef WIN32
  #include <pthread.h>
#endif

/* Global variables defined in RHugin.c */

extern SEXP RHugin_domain_tag;
extern SEXP RHugin_node_tag;
extern SEXP RHugin_table_tag;
extern SEXP RHugin_expression_tag;
extern SEXP RHugin_model_tag;
extern SEXP RHugin_junction_tree_tag;
extern SEXP RHugin_clique_tag;
extern SEXP RHugin_class_tag;
extern SEXP RHugin_class_collection_tag;

extern SEXP RHUGIN_ERROR;

extern SEXP RHUGIN_CHANCE;
extern SEXP RHUGIN_DECISION;
extern SEXP RHUGIN_UTILITY;
extern SEXP RHUGIN_FUNCTION;
extern SEXP RHUGIN_INSTANCE;

extern SEXP RHUGIN_DISCRETE;
extern SEXP RHUGIN_CONTINUOUS;
extern SEXP RHUGIN_OTHER;

extern SEXP RHUGIN_LABELED;
extern SEXP RHUGIN_BOOLEAN;
extern SEXP RHUGIN_NUMBERED;
extern SEXP RHUGIN_INTERVAL;

extern SEXP RHUGIN_TM_CLIQUE_SIZE;
extern SEXP RHUGIN_TM_CLIQUE_WEIGHT;
extern SEXP RHUGIN_TM_FILL_IN_SIZE;
extern SEXP RHUGIN_TM_FILL_IN_WEIGHT;
extern SEXP RHUGIN_TM_BEST_GREEDY;
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

/* 1.6 Errors */

SEXP RHugin_error_code(void)
{
  SEXP ret = R_NilValue;
  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_error_code();
  UNPROTECT(1);

  return ret;
}


/* 1.6.1 Handling errors */

SEXP RHugin_error_name(SEXP Scode)
{
  SEXP ret = R_NilValue;
  h_error_t code = h_error_none;

  PROTECT(Scode = AS_NUMERIC(Scode));
  code = (h_error_t) REAL(Scode)[0];

  PROTECT(ret = allocVector(STRSXP, 1));
  SET_STRING_ELT(ret, 0, mkChar( (char*) h_error_name(code)));

  UNPROTECT(2);

  return ret;
}


SEXP RHugin_error_description(SEXP Scode)
{
  SEXP ret = R_NilValue;
  h_error_t code = h_error_none;

  PROTECT(Scode = AS_NUMERIC(Scode));
  code = (h_error_t) REAL(Scode)[0];

  PROTECT(ret = allocVector(STRSXP, 1));
  SET_STRING_ELT(ret, 0, mkChar( (char*) h_error_description(code)));

  UNPROTECT(2);

  return ret;
}


/* 1.7 Taking advantage of multiple processors */

SEXP RHugin_domain_set_concurrency_level(SEXP Sdomain, SEXP Slevel)
{
  size_t level = -1;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Slevel = AS_NUMERIC(Slevel));
  level = (size_t) REAL(Slevel)[0];
  UNPROTECT(1);

  RHugin_handle_status_code(h_domain_set_concurrency_level(domain, level));

#ifndef WIN32
  if(pthread_setconcurrency((int) level) != 0)
    error("pthread_setconcurrency returned a nonzero value");
#endif
  
  return R_NilValue;
}
  

SEXP RHugin_domain_get_concurrency_level(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_concurrency_level(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_set_grain_size(SEXP Sdomain, SEXP Ssize)
{
  size_t size = -1;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Ssize = AS_NUMERIC(Ssize));
  size = (size_t) REAL(Ssize)[0];
  UNPROTECT(1);

  RHugin_handle_status_code(h_domain_set_grain_size(domain, size));

  return R_NilValue;
}


SEXP RHugin_domain_get_grain_size(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_grain_size(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


/* 2.2 Domains: Creation and deletion */

SEXP RHugin_new_domain(void)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = h_new_domain();
  RHugin_handle_error();

  if(domain) {
    ret = R_MakeExternalPtr(domain, RHugin_domain_tag, R_NilValue);
    R_RegisterCFinalizerEx(ret, (R_CFinalizer_t) RHugin_domain_finalizer, TRUE);
  }

  return ret;
}


SEXP RHugin_domain_delete(SEXP Sdomain)
{
  h_status_t status = h_domain_delete(domainPointerFromSEXP(Sdomain));
  R_ClearExternalPtr(Sdomain);

  RHugin_handle_status_code(status);

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
    R_RegisterCFinalizerEx(ret, (R_CFinalizer_t) RHugin_domain_finalizer, TRUE);
  }

  return ret;
}


/* 2.3 Nodes: Creation and deletion */

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
  else if(asChar(Scategory) == RHUGIN_DECISION)
    category = h_category_decision;
  else if(asChar(Scategory) == RHUGIN_UTILITY)
    category = h_category_utility;
  else if(asChar(Scategory) == RHUGIN_FUNCTION)
    category = h_category_function;
  else if(asChar(Scategory) == RHUGIN_INSTANCE)
    category = h_category_instance;

  if(asChar(Skind) == RHUGIN_DISCRETE)
    kind = h_kind_discrete;
  else if(asChar(Skind) == RHUGIN_CONTINUOUS)
    kind = h_kind_continuous;
  else if(asChar(Skind) == RHUGIN_OTHER)
    kind = h_kind_other;

  UNPROTECT(2);

  node = h_domain_new_node(domain, category, kind);
  RHugin_handle_error();

  if(node) {
    PROTECT(ret = allocVector(VECSXP, 1));
    SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(node, RHugin_node_tag, R_NilValue));
    UNPROTECT(1);
  }

  return ret;
}


// SEXP RHugin_node_get_domain(SEXP Snode);


SEXP RHugin_node_get_category(SEXP Snodes)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_node_category_t category = h_category_error;
  R_len_t i = 0, n = LENGTH(Snodes);

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

      case h_category_function:
        SET_STRING_ELT(ret, i, RHUGIN_FUNCTION);
        break;

      case h_category_instance:
        SET_STRING_ELT(ret, i, RHUGIN_INSTANCE);
        break;

      case h_category_error:
        SET_STRING_ELT(ret, i, RHUGIN_ERROR);
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
  R_len_t i = 0, n = LENGTH(Snodes);

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

      case h_kind_other:
        SET_STRING_ELT(ret, i, RHUGIN_OTHER);
        break;

      case h_kind_error:
        SET_STRING_ELT(ret, i, RHUGIN_ERROR);
        break;
    }
  }

  setAttrib(ret, R_NamesSymbol, getAttrib(Snodes, R_NamesSymbol));

  UNPROTECT(1);
  return ret;
}


// SEXP RHugin_node_set_category(SEXP Snode);


SEXP RHugin_node_delete(SEXP Snodes)
{
  R_len_t i = 0, n = LENGTH(Snodes);

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


/* 2.4 The links of the network */

SEXP RHugin_node_add_parent(SEXP Schild, SEXP Sparents)
{
  R_len_t i = 0, n = LENGTH(Sparents);
  h_node_t parent = NULL, child = nodePointerFromSEXP(VECTOR_ELT(Schild, 0));

  for(i = 0; i < n; i++) {
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
  R_len_t i = 0, j = 0, n_parents = 0, n = LENGTH(Snodes);

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
  R_len_t i = 0, j = 0, n_children = 0, n = LENGTH(Snodes);

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


/* 2.4.1 The requisite parents and ancestors of decision nodes */

SEXP RHugin_node_get_requisite_parents(SEXP Snodes)
{
  SEXP ret = R_NilValue, child = R_NilValue, names = R_NilValue;
  h_node_t node = NULL;
  h_error_t error_code = h_error_none;
  h_node_t *req_parents = NULL, *parent = NULL;
  R_len_t i = 0, j = 0, n_parents = 0, n = LENGTH(Snodes);
  
  PROTECT(ret = allocVector(VECSXP, n));
  
  for(i = 0; i < n; i++) {
    node = nodePointerFromSEXP(VECTOR_ELT(Snodes, i));
    req_parents = h_node_get_requisite_parents(node);
    
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(1);
      RHugin_handle_error_code(error_code);
    }
    
    if(req_parents) {
      n_parents = 0;
      for(parent = req_parents; *parent != NULL; parent++) n_parents++;
      
      PROTECT(child = allocVector(VECSXP, n_parents));
      PROTECT(names = allocVector(STRSXP, n_parents));
      
      for(j = 0; j < n_parents; j++) {
        SET_VECTOR_ELT(child, j, R_MakeExternalPtr(req_parents[j], RHugin_node_tag, R_NilValue));
        SET_STRING_ELT(names, j, mkChar( (char*) h_node_get_name(req_parents[j])));
        
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


SEXP RHugin_node_get_requisite_ancestors(SEXP Snodes)
{
  SEXP ret = R_NilValue, child = R_NilValue, names = R_NilValue;
  h_node_t node = NULL;
  h_error_t error_code = h_error_none;
  h_node_t *req_ancestors = NULL, *ancestor = NULL;
  R_len_t i = 0, j = 0, n_ancestors = 0, n = LENGTH(Snodes);
  
  PROTECT(ret = allocVector(VECSXP, n));
  
  for(i = 0; i < n; i++) {
    node = nodePointerFromSEXP(VECTOR_ELT(Snodes, i));
    req_ancestors = h_node_get_requisite_ancestors(node);
    
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(1);
      RHugin_handle_error_code(error_code);
    }
    
    if(req_ancestors) {
      n_ancestors = 0;
      for(ancestor = req_ancestors; *ancestor != NULL; ancestor++) n_ancestors++;
      
      PROTECT(child = allocVector(VECSXP, n_ancestors));
      PROTECT(names = allocVector(STRSXP, n_ancestors));
      
      for(j = 0; j < n_ancestors; j++) {
        SET_VECTOR_ELT(child, j, R_MakeExternalPtr(req_ancestors[j], RHugin_node_tag, R_NilValue));
        SET_STRING_ELT(names, j, mkChar( (char*) h_node_get_name(req_ancestors[j])));
        
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


/* 2.5 The number of states of a node */

SEXP RHugin_node_set_number_of_states(SEXP Snode, SEXP Sstates)
{
  size_t count = -1;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sstates = AS_NUMERIC(Sstates));
  count = (size_t) REAL(Sstates)[0];
  UNPROTECT(1);

  RHugin_handle_status_code(h_node_set_number_of_states(node, count));

  return R_NilValue;
}


SEXP RHugin_node_get_number_of_states(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_node_get_number_of_states(node);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


/* 2.6 The conditional probability and the utility table */

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
  double *alpha = NULL, *indices = NULL;
  R_len_t i = 0, n = LENGTH(Si);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  if(LENGTH(Salpha) != n)
    error("Salpha and Si are not not the same length");

  PROTECT(Salpha = AS_NUMERIC(Salpha));
  PROTECT(Si = AS_NUMERIC(Si));
  alpha = REAL(Salpha);
  indices = REAL(Si);

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
  double *beta = NULL, *indices = NULL;
  R_len_t i = 0, n = LENGTH(Sbeta);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  h_node_t parent = nodePointerFromSEXP(VECTOR_ELT(Sparent, 0));

  PROTECT(Sbeta = AS_NUMERIC(Sbeta));
  PROTECT(Si = AS_NUMERIC(Si));
  beta = REAL(Sbeta);
  indices = REAL(Si);

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
  double *gamma = NULL, *indices = NULL;
  R_len_t i = 0, n = LENGTH(Sgamma);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sgamma = AS_NUMERIC(Sgamma));
  PROTECT(Si = AS_NUMERIC(Si));
  gamma = REAL(Sgamma);
  indices = REAL(Si);

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
  double *alpha = NULL, *indices = NULL;
  R_len_t i = 0, n = LENGTH(Si);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Si = AS_NUMERIC(Si));
  PROTECT(ret = allocVector(REALSXP, n));
  alpha = REAL(ret);
  indices = REAL(Si);

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
  double *beta = NULL, *indices = NULL;
  R_len_t i = 0, n = LENGTH(Si);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  h_node_t parent = nodePointerFromSEXP(VECTOR_ELT(Sparent, 0));

  PROTECT(Si = AS_NUMERIC(Si));
  PROTECT(ret = allocVector(REALSXP, n));
  beta = REAL(ret);
  indices = REAL(Si);

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
  double *gamma = NULL, *indices = NULL;
  R_len_t i = 0, n = LENGTH(Si);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Si = AS_NUMERIC(Si));
  PROTECT(ret = allocVector(REALSXP, n));
  gamma = REAL(ret);
  indices = REAL(Si);

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


/* 2.7 The name of a node */

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
  R_len_t i = 0, n = LENGTH(Snames);
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


/* 2.8 Iterating through the nodes of a domain */

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


/* 2.9.1 Arbitrary user data */

// SEXP RHugin_node_set_user_data(SEXP Snode, SEXP Sdata);
// SEXP RHugin_node_get_user_data(SEXP Snode);
// SEXP RHugin_domain_set_user_data(SEXP Sdomain, SEXP Sdata);
// SEXP RHugin_domain_get_user_data(SEXP Sdomain);


/* 2.9.2 User-defined attributes */

// SEXP RHugin_node_set_attribute(SEXP Snode, SEXP Skey, SEXP Svalue);
// SEXP RHugin_node_get_attribute(SEXP Snode, SEXP Skey);
// SEXP RHugin_domain_set_attribute(SEXP Sdomain, SEXP Skey, SEXP Svalue);
// SEXP RHugin_domain_get_attribute(SEXP Sdomain, SEXP Skey);
// SEXP RHugin_node_get_first_attribute(SEXP Snode);
// SEXP RHugin_domain_get_first_attribute(SEXP Sdomain);
// SEXP RHugin_attribute_get_next(SEXP Sattribute);
// SEXP RHugin_attribute_get_key(SEXP Sattribute);
// SEXP RHugin_attribute_get_value(SEXP Sattribute);


/* 2.10 HUGIN Knowledge Base files */

SEXP RHugin_domain_save_as_kb(SEXP Sdomain, SEXP Sfile_name, SEXP Spassword)
{
  h_status_t status = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  if(Spassword == R_NilValue) {
    PROTECT(Sfile_name = AS_CHARACTER(Sfile_name));
    status = h_domain_save_as_kb(domain,
                                 (h_string_t) CHAR(asChar(Sfile_name)),
                                 NULL);
    UNPROTECT(1);
  } else {
    PROTECT(Sfile_name = AS_CHARACTER(Sfile_name));
    PROTECT(Spassword = AS_CHARACTER(Spassword));
    status = h_domain_save_as_kb(domain,
                                 (h_string_t) CHAR(asChar(Sfile_name)),
                                 (h_string_t) CHAR(asChar(Spassword)));
    UNPROTECT(2);
  }

  RHugin_handle_status_code(status);

  return R_NilValue;
}


SEXP RHugin_kb_load_domain(SEXP Sfile_name, SEXP Spassword)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  if(Spassword == R_NilValue) {
    PROTECT(Sfile_name = AS_CHARACTER(Sfile_name));
    domain = h_kb_load_domain((h_string_t) CHAR(asChar(Sfile_name)), NULL);
    UNPROTECT(1);
  } else {
    PROTECT(Sfile_name = AS_CHARACTER(Sfile_name));
    PROTECT(Spassword = AS_CHARACTER(Spassword));
    domain = h_kb_load_domain((h_string_t) CHAR(asChar(Sfile_name)),
                              (h_string_t) CHAR(asChar(Spassword)));
    UNPROTECT(2);
  }

  RHugin_handle_error();

  if(domain) {
    ret = R_MakeExternalPtr(domain, RHugin_domain_tag, R_NilValue);
    R_RegisterCFinalizerEx(ret, (R_CFinalizer_t) RHugin_domain_finalizer, TRUE);
  }

  return ret;
}

/* 3 Object-Oriented Belief Networks and LIMIDs */
/* 3.2 */
SEXP RHugin_new_class_collection()
{
  SEXP ret = R_NilValue;
  h_class_collection_t cc = NULL;
  cc = h_new_class_collection();
  //RHugin_handle_error();
  if(cc){
    ret = R_MakeExternalPtr(cc, RHugin_class_collection_tag, R_NilValue);
    R_RegisterCFinalizerEx(ret, (R_CFinalizer_t)RHugin_class_collection_finalizer, TRUE);
  }
  return ret;
}

SEXP RHugin_cc_new_class(SEXP Sclass_collection)
{
  SEXP ret = R_NilValue;
  h_class_t class = NULL;
  h_class_collection_t cc = NULL;
  cc = classCollectionPointerFromSEXP(Sclass_collection);
  if(cc) {
    class = h_cc_new_class(cc);
    ret = R_MakeExternalPtr(class, RHugin_class_tag, R_NilValue);
  }
  return ret;
}

SEXP RHugin_cc_get_members(SEXP Sclass_collection)
{
  SEXP ret = R_NilValue;
  h_class_collection_t cc = NULL;
  cc = classCollectionPointerFromSEXP(Sclass_collection);
  if(Sclass_collection != R_NilValue) {
    h_class_t *classes = NULL;
    classes = h_cc_get_members(cc);
    ret = R_MakeExternalPtr(classes, RHugin_class_tag, R_NilValue);
  }
  return ret;
}

SEXP RHugin_class_get_class_collection(SEXP Sclass)
{
  SEXP ret = R_NilValue;
  h_class_collection_t collection = NULL;
  h_class_t class = NULL;
  class = classPointerFromSEXP(Sclass);
  if(Sclass != R_NilValue) {
    collection = h_class_get_class_collection(class);
    ret = R_MakeExternalPtr(collection, RHugin_class_collection_tag, R_NilValue);
  }
  return ret;
}

/* 3.3 Deleting classes and class collections */
SEXP RHugin_cc_delete(SEXP Sclass_collection) 
{
  //SEXP ret = R_NilValue;
  h_status_t status = 0;
  h_class_collection_t cc = NULL;
  cc = classCollectionPointerFromSEXP(Sclass_collection);
  if(Sclass_collection != R_NilValue){
    status = h_cc_delete(cc);
  }
  if(status != 0) {
    RHugin_handle_status_code(status);
  }
  return R_NilValue;
}

SEXP RHugin_class_delete(SEXP Sclass) 
{
  //SEXP ret = R_NilValue;
  h_status_t status = 0;
  h_class_t class = NULL;
  class = classPointerFromSEXP(Sclass);
  if(Sclass != R_NilValue){
    status = h_class_delete((h_class_t) Sclass);
  }
  if(status != 0) {
    RHugin_handle_status_code(status);
  }
  return R_NilValue;
}

/* 3.4 Naming classes */
SEXP RHugin_class_set_name(SEXP Sclass, SEXP Sname)
{
  h_status_t status = 0;
  h_class_t class = NULL;
  class = classPointerFromSEXP(Sclass);
  PROTECT(Sname = AS_CHARACTER(Sname));
  status = h_class_set_name(class, (h_string_t) CHAR(asChar(Sname)));
  UNPROTECT(1);

  RHugin_handle_status_code(status);

  return R_NilValue;
}

SEXP RHugin_class_get_name(SEXP Sclass)
{
  SEXP ret = R_NilValue;
  h_class_t class = classPointerFromSEXP(Sclass);
  h_string_t name = h_class_get_name(class);
  PROTECT(ret = allocVector(STRSXP, 1));
  SET_STRING_ELT(ret, 0, mkChar( (char*) name));
  UNPROTECT(1);
  return ret;
}

SEXP RHugin_cc_get_class_by_name(SEXP Sclass_collection, SEXP Sname)
{
  SEXP ret = R_NilValue;
  PROTECT(Sname = AS_CHARACTER(Sname));
  h_string_t class_name = CHAR(asChar(Sname));
  h_class_t class = NULL;
  h_class_collection_t cc = NULL;
  cc = classCollectionPointerFromSEXP(Sclass_collection);
  class = h_cc_get_class_by_name(cc, class_name);

  ret = R_MakeExternalPtr(class, RHugin_class_tag, R_NilValue);

  UNPROTECT(1);
  return ret;
}

/* 3.5 Creating basic nodes */
SEXP RHugin_class_new_node(SEXP Sclass, SEXP Scategory, SEXP Skind)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_class_t class = classPointerFromSEXP(Sclass);
  h_node_category_t category = h_category_error;
  h_node_kind_t kind = h_kind_error;

  PROTECT(Scategory = AS_CHARACTER(Scategory));
  PROTECT(Skind = AS_CHARACTER(Skind));

  if(asChar(Scategory) == RHUGIN_CHANCE)
    category = h_category_chance;
  else if(asChar(Scategory) == RHUGIN_DECISION)
    category = h_category_decision;
  else if(asChar(Scategory) == RHUGIN_UTILITY)
    category = h_category_utility;
  else if(asChar(Scategory) == RHUGIN_FUNCTION)
    category = h_category_function;
  else if(asChar(Scategory) == RHUGIN_INSTANCE)
    category = h_category_instance;

  if(asChar(Skind) == RHUGIN_DISCRETE)
    kind = h_kind_discrete;
  else if(asChar(Skind) == RHUGIN_CONTINUOUS)
    kind = h_kind_continuous;
  else if(asChar(Skind) == RHUGIN_OTHER)
    kind = h_kind_other;

  UNPROTECT(2);

  node = h_class_new_node(class, category, kind);
  RHugin_handle_error();

  if (node) {
    ret = R_MakeExternalPtr(node, RHugin_node_tag, R_NilValue);
  }

  return ret;
}

SEXP RHugin_node_get_home_class(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  h_class_t class = NULL;
  if(Snode != R_NilValue){
    class = h_node_get_home_class(node);
    ret = R_MakeExternalPtr(class, RHugin_class_tag, R_NilValue);
  }
  return ret;
}

/* 3.6 Naming nodes */
// SEXP RHugin_class_get_node_by_name(SEXP Sclass, SEXP Sname)
// {
//   SEXP ret = R_NilValue, names = R_NilValue;
//   PROTECT(Sname = AS_CHARACTER(Sname));
//   h_class_t class = NULL;
//   class = classPointerFromSEXP(Sclass);
//   h_node_t node = NULL;
//   h_string_t name = (h_string_t) CHAR(asChar(Sname));
//   node = h_class_get_node_by_name(class, name);
//   RHugin_handle_error();

//   if (node)
//     ret = R_MakeExternalPtr(node, RHugin_node_tag, R_NilValue);

//   // PROTECT(ret = allocVector(VECSXP, 1));
//   // PROTECT(names = allocVector(STRSXP, 1));
//   // SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(node, RHugin_node_tag, R_NilValue));  
//   // SET_STRING_ELT(names, 0, mkChar( (char*) h_node_get_name(node)));
//   // setAttrib(ret, R_NamesSymbol, names);
//   // setAttrib(ret, R_NameSymbol, name);
//   UNPROTECT(1);
//   // UNPROTECT(3);
//   return ret;
// }

SEXP RHugin_class_get_node_by_name(SEXP Sclass, SEXP Snames)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  R_len_t i = 0, n = LENGTH(Snames);
  h_class_t class = classPointerFromSEXP(Sclass);

  PROTECT(Snames = AS_CHARACTER(Snames));
  PROTECT(ret = allocVector(VECSXP, n));

  for(i = 0; i < n; i++) {
    node = h_class_get_node_by_name(class, (h_string_t) CHAR(STRING_ELT(Snames, i)));

    if(node)
      SET_VECTOR_ELT(ret, i, R_MakeExternalPtr(node, RHugin_node_tag, R_NilValue));
    else
      SET_VECTOR_ELT(ret, i, R_NilValue);
  }

  setAttrib(ret, R_NamesSymbol, Snames);

  UNPROTECT(2);
  return ret;
}

/* 3.7 The interface of a class */
SEXP RHugin_node_add_to_input(SEXP Snode)
{
  h_status_t status = 0;
  h_node_t node = NULL;
  node = nodePointerFromSEXP(Snode);
  status = h_node_add_to_inputs(node);
  if(status != 0) {
    RHugin_handle_status_code(status);
  }
  return R_NilValue;
}

SEXP RHugin_class_get_inputs(SEXP Sclass)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_class_t class = NULL;
  class = classPointerFromSEXP(Sclass);
  h_node_t* nodes = NULL;
  nodes = h_class_get_inputs(class);
  PROTECT(ret = allocVector(VECSXP, 1));
  PROTECT(names = allocVector(STRSXP, 1));
  SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(nodes, RHugin_node_tag, R_NilValue));  
  SET_STRING_ELT(names, 0, mkChar( (char*) h_node_get_name(nodes)));
  setAttrib(ret, R_NamesSymbol, names);
  UNPROTECT(2);
  return ret;
}

SEXP RHugin_node_remove_from_inputs(SEXP Snode)
{
  h_status_t status = 0;
  h_node_t node = NULL;
  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  status = h_node_remove_from_inputs(node);
  if(status != 0) {
    RHugin_handle_status_code(status);
  }
  return R_NilValue;
}

SEXP RHugin_node_add_to_outputs(SEXP Snode)
{
  h_status_t status = 0;
  h_node_t node = NULL;
  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  status = h_node_add_to_outputs(node);
  if(status != 0) {
    RHugin_handle_status_code(status);
  }
  return R_NilValue;
}

SEXP RHugin_class_get_outputs(SEXP Sclass)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_node_t* nodes = NULL;
  nodes = h_class_get_outputs((h_class_t) Sclass);
  PROTECT(ret = allocVector(VECSXP, 1));
  PROTECT(names = allocVector(STRSXP, 1));
  SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(nodes, RHugin_node_tag, R_NilValue));  
  SET_STRING_ELT(names, 0, mkChar( (char*) h_node_get_name(nodes)));
  setAttrib(ret, R_NamesSymbol, names);
  UNPROTECT(2);
  return ret;
}

SEXP RHugin_node_remove_from_outputs(SEXP Snode)
{
  h_status_t status = 0;
  h_node_t node = NULL;
  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  status = h_node_remove_from_outputs(node);
  if(status != 0) {
    RHugin_handle_status_code(status);
  }
  return R_NilValue;
}

/* 3.8 Creating instances of classes */
SEXP RHugin_class_new_instance(SEXP Sclass1, SEXP Sclass2) 
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_class_t class1 = NULL, class2 = NULL;
  class1 = classPointerFromSEXP(Sclass1);
  class2 = classPointerFromSEXP(Sclass2);
  h_node_t node = NULL;
  node = h_class_new_instance(class1, class2);
  PROTECT(ret = allocVector(VECSXP, 1));
  PROTECT(names = allocVector(STRSXP, 1));
  SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(node, RHugin_node_tag, R_NilValue));  
  SET_STRING_ELT(names, 0, mkChar( (char*) h_node_get_name(node)));
  setAttrib(ret, R_NamesSymbol, names);
  UNPROTECT(2);
  return ret;
}

SEXP RHugin_node_get_instance_class(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_class_t class = NULL;
  h_node_t node = NULL;
  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  class = h_node_get_instance_class(node);
  ret = R_MakeExternalPtr(class, RHugin_class_tag, R_NilValue);
  return ret;
}

SEXP RHugin_class_get_instance(SEXP Snode)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_node_t* nodes = NULL;
  h_node_t node = NULL;
  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  nodes = h_class_get_instances(node);
  PROTECT(ret = allocVector(VECSXP, 1));
  PROTECT(names = allocVector(STRSXP, 1));
  SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(nodes, RHugin_node_tag, R_NilValue));  
  SET_STRING_ELT(names, 0, mkChar( (char*) h_node_get_name(nodes)));
  setAttrib(ret, R_NamesSymbol, names);
  UNPROTECT(2);
  return nodes;
}

SEXP RHugin_node_get_master(SEXP Snode)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_node_t node = NULL, tmp_node = NULL;
  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  tmp_node = h_node_get_master(node);
  PROTECT(ret = allocVector(VECSXP, 1));
  PROTECT(names = allocVector(STRSXP, 1));
  SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(tmp_node, RHugin_node_tag, R_NilValue));  
  SET_STRING_ELT(names, 0, mkChar( (char*) h_node_get_name(tmp_node)));
  setAttrib(ret, R_NamesSymbol, names);
  UNPROTECT(2);
  return ret;
}

SEXP RHugin_node_get_instance(SEXP Snode)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_node_t node = NULL, tmp_node = NULL;
  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  tmp_node = h_node_get_instance(node);
  PROTECT(ret = allocVector(VECSXP, 1));
  PROTECT(names = allocVector(STRSXP, 1));
  SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(tmp_node, RHugin_node_tag, R_NilValue));  
  SET_STRING_ELT(names, 0, mkChar( (char*) h_node_get_name(tmp_node)));
  setAttrib(ret, R_NamesSymbol, names);
  UNPROTECT(2);
  return ret;
}

SEXP RHugin_node_get_output(SEXP Snode1, SEXP Snode2)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_node_t node1 = NULL, tmp_node = NULL;
  node1 = nodePointerFromSEXP(VECTOR_ELT(Snode1, 0));
  h_node_t node2 = NULL;
  node2 = nodePointerFromSEXP(VECTOR_ELT(Snode2, 0));
  tmp_node = h_node_get_output(node1, node2);
  PROTECT(ret = allocVector(VECSXP, 1));
  PROTECT(names = allocVector(STRSXP, 1));
  SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(tmp_node, RHugin_node_tag, R_NilValue));  
  SET_STRING_ELT(names, 0, mkChar( (char*) h_node_get_name(tmp_node)));
  setAttrib(ret, R_NamesSymbol, names);
  UNPROTECT(2);
  return ret;
}

SEXP RHugin_node_substitute_class(SEXP Snode, SEXP Sclass)
{
  h_status_t status = 0;
  h_class_t class = NULL;
  class = classPointerFromSEXP(Sclass);
  h_node_t node = NULL;
  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  status = h_node_substitute_class(node, class);
  if(status != 0) {
    RHugin_handle_status_code(status);
  }
  return R_NilValue;
}

/* 3.9 Putting the pieces together */
SEXP RHugin_node_set_input(SEXP Snode1, SEXP Snode2, SEXP Snode3)
{
  h_status_t status = 0;
  h_node_t node1 = NULL;
  node1 = nodePointerFromSEXP(VECTOR_ELT(Snode1, 0));
  h_node_t node2 = NULL;
  node2 = nodePointerFromSEXP(VECTOR_ELT(Snode2, 0));
  h_node_t node3 = NULL;
  node3 = nodePointerFromSEXP(VECTOR_ELT(Snode3, 0));
  status = h_node_set_input(node1, node2, node3);
  if(status != 0) {
    RHugin_handle_status_code(status);
  }
  return R_NilValue;
}

SEXP RHugin_node_get_input(SEXP Snode1, SEXP Snode2)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_node_t node1 = NULL, tmp_node = NULL;
  node1 = nodePointerFromSEXP(VECTOR_ELT(Snode1, 0));
  h_node_t node2 = NULL;
  node2 = nodePointerFromSEXP(VECTOR_ELT(Snode2, 0));
  tmp_node = h_node_get_input(node1, node2);
  PROTECT(ret = allocVector(VECSXP, 1));
  PROTECT(names = allocVector(STRSXP, 1));
  SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(tmp_node, RHugin_node_tag, R_NilValue));  
  SET_STRING_ELT(names, 0, mkChar( (char*) h_node_get_name(tmp_node)));
  setAttrib(ret, R_NamesSymbol, names);
  UNPROTECT(2);
  return ret;
}

SEXP RHugin_node_unset_input(SEXP Snode1, SEXP Snode2)
{
  h_status_t status = 0;
  h_node_t node1 = NULL;
  node1 = nodePointerFromSEXP(VECTOR_ELT(Snode1, 0));
  h_node_t node2 = NULL;
  node2 = nodePointerFromSEXP(VECTOR_ELT(Snode2, 0));
  status = h_node_unset_input(node1, node2);
  if(status != 0) {
    RHugin_handle_status_code(status);
  }
  return R_NilValue;
}

/* 3.10 Creating a runtime domain */
SEXP RHugin_class_create_domain(SEXP Sclass)
{
  SEXP ret = R_NilValue;
  h_class_t class = classPointerFromSEXP(Sclass);
  h_domain_t domain = h_class_create_domain(class);
  RHugin_handle_error();

  if (domain) {
    ret = R_MakeExternalPtr(domain, RHugin_domain_tag, R_NilValue);
    R_RegisterCFinalizerEx(ret, (R_CFinalizer_t) RHugin_domain_finalizer, TRUE);
  }

  return ret;
}

SEXP RHugin_node_get_source(SEXP Snode)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_node_t* nodes = NULL;
  h_node_t node = NULL;
  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  nodes = h_node_get_source(node);
  PROTECT(ret = allocVector(VECSXP, 1));
  PROTECT(names = allocVector(STRSXP, 1));
  SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(nodes, RHugin_node_tag, R_NilValue));  
  SET_STRING_ELT(names, 0, mkChar( (char*) h_node_get_name(nodes)));
  setAttrib(ret, R_NamesSymbol, names);
  UNPROTECT(2);
  return ret;
}

/* 3.11 Node iterator */
SEXP RHugin_class_get_first_node(SEXP Sclass)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_class_t class = NULL;
  class = classPointerFromSEXP(Sclass);
  h_node_t node = NULL;
  node = h_class_get_first_node(class);
  PROTECT(ret = allocVector(VECSXP, 1));
  PROTECT(names = allocVector(STRSXP, 1));
  SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(node, RHugin_node_tag, R_NilValue));  
  SET_STRING_ELT(names, 0, mkChar( (char*) h_node_get_name(node)));
  setAttrib(ret, R_NamesSymbol, names);
  UNPROTECT(2);
  return ret;
}

/* 3.12 User data */
/*SEXP RHugin_class_set_user_data(SEXP Sclass, SEXP Sdata)
{
  h_status_t status = 0;
  status = h_class_set_user_data((h_class_t) Sclass, Sdata);
  if(status != 0) {
    RHugin_handle_status_code(status);
  }
  return R_NilValue;
}

SEXP RHugin_class_get_user_data(SEXP Sclass)
{
  SEXP ret = R_NilValue;
  void* pointer = NULL;
  pointer = h_class_get_user_data((h_class_t) Sclass);
  return pointer;
}

SEXP RHugin_class_set_attribute(SEXP Sclass, SEXP Skey, SEXP Svalue)
{
  h_status_t status = 0;
  PROTECT(Skey = AS_CHARACTER(Skey));
  PROTECT(Svalue = AS_CHARACTER(Svalue));
  status = h_class_set_attribute((h_class_t) Sclass, (h_string_t) CHAR(asChar(Sname)), (h_string_t) CHAR(asChar(Sname)));
  if(status != 0) {
    RHugin_handle_status_code(status);
  }
  UNPROTECT(2);
  return R_NilValue;
}

SEXP RHugin_class_get_attribute(SEXP Sclass, SEXP Skey)
{
  SEXP ret = R_NilValue;
  h_string_t str = NULL;
  PROTECT(Skey = AS_CHARACTER(Skey));
  ret = h_class_get_attribute((h_class_t) Sclass, (h_string_t) CHAR(asChar(Sname)));
  UNPROTECT(1);
  return ret;
}

SEXP RHugin_class_get_first_attribute(SEXP Sclass)
{
  SEXP ret = R_NilValue;
  h_attribute_t attribute = NULL;
  attribute = h_class_get_first_attribute((h_class_t) Sclass);
  return attribute;
}

/* 3.13 Saving class collections as HKB files */
SEXP RHugin_cc_save_as_kb(SEXP Sclass_collection, SEXP Sfile_name, SEXP Spassword)
{
  h_status_t status = 0;
  PROTECT(Sfile_name = AS_CHARACTER(Sfile_name));
  PROTECT(Spassword = AS_CHARACTER(Spassword));
  status = h_cc_save_as_kb((h_class_collection_t) Sclass_collection, (h_string_t) CHAR(asChar(Sfile_name)), (h_string_t) CHAR(asChar(Spassword)));
  if(status != 0) {
    RHugin_handle_status_code(status);
  }
  UNPROTECT(2);
  return R_NilValue;
}

SEXP RHugin_kb_load_class_collection(SEXP Sfile_name, SEXP Spassword)
{
  SEXP ret = R_NilValue;
  h_class_collection_t class_collection = NULL;
  PROTECT(Sfile_name = AS_CHARACTER(Sfile_name));
  PROTECT(Spassword = AS_CHARACTER(Spassword));
  class_collection = h_kb_load_class_collection((h_string_t) CHAR(asChar(Sfile_name)), (h_string_t) CHAR(asChar(Spassword)));
  UNPROTECT(2);
  return class_collection;
}

SEXP RHugin_class_get_file_name(SEXP Sclass)
{
  SEXP ret = R_NilValue;
  h_class_t class = NULL;
  class = classPointerFromSEXP(Sclass);
  h_string_t str = NULL;
  str = h_class_get_file_name(class);
  PROTECT(ret = allocVector(STRSXP, 1));
  SET_STRING_ELT(ret, 0, mkChar( (char*) str));
  UNPROTECT(1);
  return ret;
}

/* 4 Dynamic Bayesian Network */ 
/* 4.1 Temporal clones */
SEXP RHugin_node_create_temporal_clone(SEXP Snode)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_node_t node = NULL, tmp_node = NULL;
  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  tmp_node = h_node_create_temporal_clone(node);

  PROTECT(ret = allocVector(VECSXP, 1));
  PROTECT(names = allocVector(STRSXP, 1));
  SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(tmp_node, RHugin_node_tag, R_NilValue));
  SET_STRING_ELT(names, 0, mkChar( (char*) h_node_get_name(tmp_node)));
  setAttrib(ret, R_NamesSymbol, names);
  UNPROTECT(2);

  return ret;
}

SEXP RHugin_node_get_temporal_clone(SEXP Snode)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_node_t node = NULL, tmp_node = NULL;
  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  tmp_node = h_node_get_temporal_clone(node);

  PROTECT(ret = allocVector(VECSXP, 1));
  PROTECT(names = allocVector(STRSXP, 1));
  SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(tmp_node, RHugin_node_tag, R_NilValue));
  SET_STRING_ELT(names, 0, mkChar( (char*) h_node_get_name(tmp_node)));
  setAttrib(ret, R_NamesSymbol, names);
  UNPROTECT(2);

  return ret;
}

SEXP RHugin_node_get_temporal_master(SEXP Snode)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_node_t node = NULL, tmp_node = NULL;
  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  tmp_node = h_node_get_temporal_master(node);

  PROTECT(ret = allocVector(VECSXP, 1));
  PROTECT(names = allocVector(STRSXP, 1));
  SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(tmp_node, RHugin_node_tag, R_NilValue));
  SET_STRING_ELT(names, 0, mkChar( (char*) h_node_get_name(tmp_node)));
  setAttrib(ret, R_NamesSymbol, names);
  UNPROTECT(2);

  return ret;
}

/* 4.2 DBN runtime domains */
SEXP RHugin_class_create_dbn_domain(SEXP Sclass, SEXP Snumber_of_slices)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;
  h_class_t class = classPointerFromSEXP(Sclass);

  PROTECT(Snumber_of_slices = AS_NUMERIC(Snumber_of_slices));
  size_t number_of_slices = REAL(Snumber_of_slices)[0];

  domain = h_class_create_dbn_domain(class, number_of_slices);
  UNPROTECT(1);

  RHugin_handle_error();

  if(domain) {
    ret = R_MakeExternalPtr(domain, RHugin_domain_tag, R_NilValue);
    R_RegisterCFinalizerEx(ret, (R_CFinalizer_t) RHugin_domain_finalizer, TRUE);
  }

  return ret;
}

/* 4.3 Inference in DBNs */
SEXP RHugin_domain_triangulate_dbn(SEXP Sdomain, SEXP Smethod)
{
  SEXP ret = R_NilValue;
  h_triangulation_method_t method = h_tm_best_greedy;
  h_status_t status = 0;
  h_domain_t domain = NULL;
  domain = domainPointerFromSEXP(VECTOR_ELT(Sdomain, 0));

  PROTECT(Smethod = AS_CHARACTER(Smethod));
  if(asChar(Smethod) == RHUGIN_TM_CLIQUE_SIZE)
    method = h_tm_clique_size;
  else if(asChar(Smethod) == RHUGIN_TM_CLIQUE_WEIGHT)
    method = h_tm_clique_weight;
  else if(asChar(Smethod) == RHUGIN_TM_FILL_IN_SIZE)
    method = h_tm_fill_in_size;
  else if(asChar(Smethod) == RHUGIN_TM_FILL_IN_WEIGHT)
    method = h_tm_fill_in_weight;
  else if(asChar(Smethod) == RHUGIN_TM_BEST_GREEDY)
    method = h_tm_best_greedy;
  else if(asChar(Smethod) == RHUGIN_TM_TOTAL_WEIGHT)
    method = h_tm_total_weight;

  UNPROTECT(1);

  status = h_domain_triangulate_dbn(domain, method);
  if(status != 0) {
    RHugin_handle_status_code(status);
  }
  return R_NilValue;
}

SEXP RHugin_domain_move_dbn_window(SEXP Sdomain, SEXP Ssize)
{
  // h_domain_t domain = domainPointerFromSEXP(VECTOR_ELT(Sdomain, 0));
  h_domain_t domain = domainPointerFromSEXP(Sdomain);
  PROTECT(Ssize = AS_NUMERIC(Ssize));
  size_t size = REAL(Ssize)[0];
  h_status_t status = h_domain_move_dbn_window(domain, size);
  UNPROTECT(1);

  RHugin_handle_status_code(status);

  return R_NilValue;
}

SEXP RHugin_domain_get_dbn_window_offset(SEXP Sdomain)
{
  h_domain_t domain = NULL;
  SEXP ret = R_NilValue;
  domain = domainPointerFromSEXP(VECTOR_ELT(Sdomain, 0));
  h_count_t count = NULL;
  count = h_domain_get_dbn_window_offset(domain);
  // create R vector with real
  PROTECT(ret = allocVector(INTSXP, (int) count));
  UNPROTECT(1);
  return ret;
}

SEXP RHugin_domain_initialize_dbn_window(SEXP Sdomain)
{
  h_status_t status = 0;
  h_domain_t domain = NULL;
  domain = domainPointerFromSEXP(VECTOR_ELT(Sdomain, 0));
  status = h_domain_initialize_dbn_window(domain);
  if(status != 0) {
    RHugin_handle_status_code(status);
  }
  return R_NilValue;
}

/* 4.4 Prediction */
SEXP RHugin_domain_compute_dbn_predictions(SEXP Sdomain, SEXP Snumber_of_time_instants)
{
  h_status_t status = 0;
  h_domain_t domain = NULL;
  size_t size = NULL;
  PROTECT(Snumber_of_time_instants = AS_NUMERIC(Snumber_of_time_instants));
  size = REAL(Snumber_of_time_instants);
  domain = domainPointerFromSEXP(VECTOR_ELT(Sdomain, 0));
  status = h_domain_compute_dbn_predictions(domain, size);
  if(status != 0) {
    RHugin_handle_status_code(status);
  }
  return R_NilValue;
}

SEXP RHugin_node_get_predicted_belief(SEXP Snode, SEXP Ss, SEXP Stime)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL;
  h_number_t number;
  size_t s = NULL, time = NULL;
  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  PROTECT(Ss = AS_NUMERIC(Ss));
  PROTECT(Stime = AS_NUMERIC(Stime));
  s = REAL(Ss);
  time = REAL(Stime);
  number = h_node_get_predicted_belief(node, s, time);
  PROTECT(ret = allocVector(REALSXP, (double) number));
  UNPROTECT(3);
  return ret;
}

SEXP RHugin_node_get_predicted_mean(SEXP Snode, SEXP Stime)
{
  SEXP ret = R_NilValue;
  h_number_t number;
  h_node_t node = NULL;
  size_t time = NULL;
  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  PROTECT(Stime = AS_NUMERIC(Stime));
  time = REAL(Stime);
  number = h_node_get_predicted_mean(node, time);
  PROTECT(ret = allocVector(REALSXP, (double) number));
  UNPROTECT(2);
  return ret;
}

SEXP RHugin_node_get_predicted_variance(SEXP Snode, SEXP Stime)
{
  SEXP ret = R_NilValue;
  h_number_t number;
  h_node_t node = NULL;
  size_t time = NULL;
  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  PROTECT(Stime = AS_NUMERIC(Stime));
  time = REAL(Stime);
  number = h_node_get_predicted_variance(node, time);
  PROTECT(ret = allocVector(REALSXP, (double) number));
  UNPROTECT(2);
  return ret;
}

SEXP RHugin_node_get_predicted_value(SEXP Snode, SEXP Stime)
{
  SEXP ret = R_NilValue;
  h_number_t number;
  h_node_t node = NULL;
  size_t time = NULL;
  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  PROTECT(Stime = AS_NUMERIC(Stime));
  time = REAL(Stime);
  number = h_node_get_predicted_value(node, time);
  PROTECT(ret = allocVector(REALSXP, (double) number));
  UNPROTECT(2);
  return ret;
}

/* 4.5 The Boyen-Koller approximation algorithm */
SEXP RHugin_domain_triangulate_dbn_for_bk(SEXP Sdomain, SEXP Smethod)
{
  SEXP ret = R_NilValue;
  h_status_t status = 0;
  h_domain_t domain = NULL;
  h_triangulation_method_t method = h_tm_best_greedy;

  PROTECT(Smethod = AS_CHARACTER(Smethod));
  if(asChar(Smethod) == RHUGIN_TM_CLIQUE_SIZE)
    method = h_tm_clique_size;
  else if(asChar(Smethod) == RHUGIN_TM_CLIQUE_WEIGHT)
    method = h_tm_clique_weight;
  else if(asChar(Smethod) == RHUGIN_TM_FILL_IN_SIZE)
    method = h_tm_fill_in_size;
  else if(asChar(Smethod) == RHUGIN_TM_FILL_IN_WEIGHT)
    method = h_tm_fill_in_weight;
  else if(asChar(Smethod) == RHUGIN_TM_BEST_GREEDY)
    method = h_tm_best_greedy;
  else if(asChar(Smethod) == RHUGIN_TM_TOTAL_WEIGHT)
    method = h_tm_total_weight;

  UNPROTECT(1);

  domain = domainPointerFromSEXP(VECTOR_ELT(Sdomain, 0));
  status = h_domain_triangulate_dbn_for_bk(domain, method);
  if(status != 0) {
    RHugin_handle_status_code(status);
  }
  return R_NilValue;
}

SEXP RHugin_domain_is_triangulated_for_bk(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_boolean_t boolean = NULL;
  h_domain_t domain = NULL;
  domain = domainPointerFromSEXP(VECTOR_ELT(Sdomain, 0));
  boolean = h_domain_is_triangulated_for_bk(domain);
  PROTECT(ret = allocVector(LGLSXP, boolean));
  UNPROTECT(1);
  return ret;
}

/* 5.1 What is a table? */

// SEXP RHugin_table_get_index_from_configuration(SEXP Stable,
//                                                SEXP Sconfiguration);
// SEXP RHugin_table_get_configuration_from_index(SEXP Stable,
//                                                SEXP Sconfiguration,
//                                                SEXP Sindex);


/* 5.2 The nodes and the contents of a table */

SEXP RHugin_table_get_nodes(SEXP Stable)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_error_t error_code = h_error_none;
  h_node_t *nodes = NULL, *node = NULL;
  R_len_t i = 0, n = 0;

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
  R_len_t i = 0;
  size_t size = 0;
  h_table_t table = tablePointerFromSEXP(Stable);

  table_data = h_table_get_data(table);
  RHugin_handle_error();

  size = h_table_get_size(table);
  if(size == (size_t) -1)
    error("h_table_get_size returned (size_t) -1");

  PROTECT(ret = allocVector(REALSXP, (R_len_t) size));
  data = REAL(ret);
  
  for(i = 0; i < (R_len_t) size; i++)
    data[i] = (double) table_data[i];

  UNPROTECT(1);

  return ret;
}


SEXP RHugin_table_set_data(SEXP Stable, SEXP Sdata)
{
  h_table_t table = NULL;
  double *data = NULL;
  h_number_t *table_data = NULL;
  R_len_t i = 0, size = -1;

  table = tablePointerFromSEXP(Stable);
  RHugin_handle_error();

  table_data = h_table_get_data(table);
  RHugin_handle_error();

  size = (R_len_t) h_table_get_size(table);

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
  double *mean = NULL, *indices = NULL;
  h_error_t error_code = h_error_none;
  R_len_t i = 0, n = LENGTH(Si);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  h_table_t table = tablePointerFromSEXP(Stable);

  PROTECT(Si = AS_NUMERIC(Si));
  PROTECT(ret = allocVector(REALSXP, n));
  mean = REAL(ret);
  indices = REAL(Si);

  for(i = 0; i < n; i++) {
    mean[i] = (double) h_table_get_mean(table, (size_t) indices[i], node);
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
  double *cov = NULL, *indices = NULL;
  h_node_t node1 = NULL, node2 = NULL;
  h_table_t table = NULL;
  R_len_t i = 0, n = LENGTH(Si);

  node1 = nodePointerFromSEXP(VECTOR_ELT(Snode1, 0));
  node2 = nodePointerFromSEXP(VECTOR_ELT(Snode2, 0));
  table = tablePointerFromSEXP(Stable);

  PROTECT(ret = allocVector(REALSXP, n));
  PROTECT(Si = AS_NUMERIC(Si));
  cov = REAL(ret);
  indices = REAL(Si);

  for(i = 0; i < n; i++) {
    cov[i] = (double) h_table_get_covariance(table, (size_t) indices[i], node1, node2);
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
  double *variance = NULL, *indices = NULL;
  R_len_t i = 0, n = LENGTH(Si);

  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  h_table_t table = tablePointerFromSEXP(Stable);

  PROTECT(Si = AS_NUMERIC(Si));
  PROTECT(ret = allocVector(REALSXP, n));
  indices = REAL(Si);
  variance = REAL(ret);

  for(i = 0; i < n; i++) {
    variance[i] = (double) h_table_get_variance(table, (size_t) indices[i], node);
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


/* 5.3 Deleting tables */

SEXP RHugin_table_delete(SEXP Stable)
{
  RHugin_handle_status_code(h_table_delete(tablePointerFromSEXP(Stable)));

  return R_NilValue;
}


/* 5.4 The size of a table */

SEXP RHugin_table_get_size(SEXP Stable)
{
  SEXP ret = R_NilValue;
  h_table_t table = tablePointerFromSEXP(Stable);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_table_get_size(table);
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_table_get_cg_size(SEXP Stable)
{
  SEXP ret = R_NilValue;
  h_table_t table = tablePointerFromSEXP(Stable);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_table_get_cg_size(table);
  UNPROTECT(1);

  return ret;
}


/* 5.5 Rearranging the contents of a table */

SEXP RHugin_table_reorder_nodes(SEXP Stable, SEXP Sorder)
{
  h_node_t *order = NULL;
  R_len_t i = 0, n = LENGTH(Sorder);
  h_table_t table = tablePointerFromSEXP(Stable);

  order = (h_node_t*) R_alloc(n + 1, sizeof(h_node_t));
  for(i = 0; i < n; i++)
    order[i] = nodePointerFromSEXP(VECTOR_ELT(Sorder, i));
  order[n] = NULL;

  RHugin_handle_status_code(h_table_reorder_nodes(table, order));

  return R_NilValue;
}


/* 6.1 Subtyping of discrete nodes */

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
  h_node_t node = NULL;
  h_node_subtype_t subtype = h_subtype_error;
  R_len_t i = 0, n = LENGTH(Snodes);

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
        SET_STRING_ELT(ret, i, RHUGIN_ERROR);
        break;
    }
  }

  setAttrib(ret, R_NamesSymbol, getAttrib(Snodes, R_NamesSymbol));

  UNPROTECT(1);
  return ret;
}


/* 6.2 Expressions */

// SEXP RHugin_node_make_expression(SEXP Snode);
// SEXP RHugin_label_make_expression(SEXP Slabel);
// SEXP RHugin_boolean_make_expression(SEXP Sb);
// SEXP RHugin_number_make_expression(SEXP Snumber);
// SEXP RHugin_make_composite_expression(SEXP Soperator, SEXP Sarguments);
// SEXP RHugin_expression_is_composite(SEXP Se);
// SEXP RHugin_expression_get_operator(SEXP Se);
// SEXP RHugin_expression_get_operands(SEXP Se);
// SEXP RHugin_expression_get_node(SEXP Se);
// SEXP RHugin_expression_get_number(SEXP Se);
// SEXP RHugin_expression_get_label(SEXP Se);
// SEXP RHugin_expression_get_boolean(SEXP Se);
// SEXP RHugin_expression_delete(SEXP Se);
// SEXP RHugin_expression_clone(SEXP Se);


/* 6.3 Syntax for expression */

// SEXP RHugin_string_parse_expression(SEXP Sstring, SEXP Smodel)
// SEXP RHugin_expression_to_string(SEXP Sexpressions)


/* 6.4 Creating and maintaining models */

SEXP RHugin_node_new_model(SEXP Snode, SEXP Smodel_nodes)
{
  SEXP ret = R_NilValue;
  h_node_t node = NULL, *model_nodes = NULL;
  h_model_t model = NULL;
  R_len_t i = 0, n = LENGTH(Smodel_nodes);

  node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  model_nodes = (h_node_t*) R_alloc(n + 1, sizeof(h_node_t));
  for(i = 0; i < n; i++)
    model_nodes[i] = nodePointerFromSEXP(VECTOR_ELT(Smodel_nodes, i));
  model_nodes[n] = NULL;

  model = h_node_new_model(node, model_nodes);

  RHugin_handle_error();

  PROTECT(ret = allocVector(VECSXP, 1));

  if(model)
    SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(model, RHugin_model_tag, R_NilValue));
  else
    SET_VECTOR_ELT(ret, 0, R_NilValue);

  setAttrib(ret, R_NamesSymbol, getAttrib(Snode, R_NamesSymbol));

  UNPROTECT(1);
  return ret;
}


SEXP RHugin_node_get_model(SEXP Snodes)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  h_model_t model = NULL;
  R_len_t i = 0, n = LENGTH(Snodes);

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
  R_len_t i = 0, n = LENGTH(Smodels);

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
  R_len_t i = 0, n = 0;

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
  double *sizes = NULL;
  size_t model_size = 0;
  R_len_t i = 0, n = LENGTH(Smodels);

  PROTECT(ret = allocVector(REALSXP, n));
  sizes = REAL(ret);

  for(i = 0; i < n; i++) {
    model_size = h_model_get_size(modelPointerFromSEXP(VECTOR_ELT(Smodels, i)));
    sizes[i] = model_size == (size_t) -1 ? -1.0 : (double) model_size;
  }

  setAttrib(ret, R_NamesSymbol, getAttrib(Smodels, R_NamesSymbol));
  UNPROTECT(1);
  return ret;
}


SEXP RHugin_model_set_expression(SEXP Smodel, SEXP Sexpressions)
{
  h_expression_t *expressions = NULL;
  h_string_t string = NULL;
  R_len_t i = 0, j = 0, n = LENGTH(Sexpressions);
  h_model_t model = modelPointerFromSEXP(VECTOR_ELT(Smodel, 0));

  if((R_len_t) h_model_get_size(model) != n)
    error("LENGTH(Sexpressions) is not equal to model size");

  PROTECT(Sexpressions = AS_CHARACTER(Sexpressions));
  expressions = (h_expression_t*) R_alloc(n, sizeof(h_expression_t));

  for(i = 0; i < n; i++) {
    string = (h_string_t) CHAR(STRING_ELT(Sexpressions, i));
    expressions[i] = h_string_parse_expression(string,
                                               model,
                                               RHuginExpressionParseError,
                                               NULL);

    if(expressions[i] == NULL) {
      Rprintf("Unable to parse expression:\n  %s\n", string);

      for(j = 0; j < i; j++) {
        free(expressions[i]);
        expressions[i] = NULL;
      }

      UNPROTECT(1);

      RHugin_handle_error();

      return R_NilValue;
    }
  }

  UNPROTECT(1);

  for(i = 0; i < n; i++)
    RHugin_handle_status_code(h_model_set_expression(model, (size_t) i, expressions[i]));

  return R_NilValue;
}


SEXP RHugin_model_get_expression(SEXP Smodel)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  h_expression_t expression = NULL;
  h_string_t string = NULL;
  char empty_string[] = "";
  R_len_t i = 0, size = 0;
  h_model_t model = modelPointerFromSEXP(VECTOR_ELT(Smodel, 0));

  size = (R_len_t) h_model_get_size(model);
  PROTECT(ret = allocVector(STRSXP, size));

  for(i = 0; i < size; i++) {
    expression = h_model_get_expression(model, (size_t) i);

    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(1);
      RHugin_handle_error_code(error_code);
    }

    if(expression) {
      string = h_expression_to_string(expression);
      SET_STRING_ELT(ret, i, mkChar( (char*) string));
      string = NULL;
    }
    
    else
      SET_STRING_ELT(ret, i, mkChar(empty_string));
  }

  UNPROTECT(1);

  return ret;
}


/* 6.5 State labels */

SEXP RHugin_node_set_state_label(SEXP Snode, SEXP Ss, SEXP Slabels)
{
  h_status_t status = 0;
  double *s = NULL;
  R_len_t i = 0, n = LENGTH(Ss);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  if(LENGTH(Slabels) != n)
    error("Slabels and Ss are not the same length");

  PROTECT(Ss = AS_NUMERIC(Ss));
  PROTECT(Slabels = AS_CHARACTER(Slabels));
  s = REAL(Ss);

  for(i = 0; i < n; i++) {
    status = h_node_set_state_label(node, (size_t) s[i], (h_string_t) CHAR(STRING_ELT(Slabels, i)));
    if(status != 0) {
      UNPROTECT(2);
      RHugin_handle_status_code(status);
    }
  }

  UNPROTECT(2);
  return R_NilValue;
}


SEXP RHugin_node_get_state_label(SEXP Snode, SEXP Ss)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *s = NULL;
  R_len_t i = 0, n = LENGTH(Ss);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(STRSXP, n));
  PROTECT(Ss = AS_NUMERIC(Ss));
  s = REAL(Ss);

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
  double *index = NULL;
  R_len_t i = 0, n = LENGTH(Slabels);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Slabels = AS_CHARACTER(Slabels));
  PROTECT(ret = allocVector(REALSXP, n));
  index = REAL(ret);

  for(i = 0; i < n; i++) {
    index[i] = (double) h_node_get_state_index_from_label(node, (h_string_t) CHAR(STRING_ELT(Slabels, i)));
    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


/* 6.6 State values */

SEXP RHugin_node_set_state_value(SEXP Snode, SEXP Ss, SEXP Svalues)
{
  h_status_t status = 0;
  h_double_t value = 0.0;
  double *s = NULL, *sv = NULL;
  R_len_t i = 0, n = LENGTH(Svalues);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Ss = AS_NUMERIC(Ss));
  s = REAL(Ss);
  PROTECT(Svalues = AS_NUMERIC(Svalues));
  sv = REAL(Svalues);
  
  for(i = 0; i < n; i++) {
    if(sv[i] == R_PosInf)
      value = h_infinity;
    else if(sv[i] == R_NegInf)
      value = -h_infinity;
    else
      value = (h_double_t) sv[i];

    status = h_node_set_state_value(node, (size_t) s[i], value);

    if(status != 0) {
      UNPROTECT(2);
      RHugin_handle_status_code(status);
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
  double *s = NULL, *sv = NULL;
  R_len_t i = 0, n = LENGTH(Ss);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Ss = AS_NUMERIC(Ss));
  s = REAL(Ss);
  PROTECT(ret = allocVector(REALSXP, n));
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
  double *values = NULL, *indices = NULL;
  R_len_t i = 0, n = LENGTH(Svalues);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(ret = allocVector(REALSXP, n));
  indices = REAL(ret);
  PROTECT(Svalues = AS_NUMERIC(Svalues));
  values = REAL(Svalues);

  for(i = 0; i < n; i++) {
    if(!R_FINITE(values[i]))
      indices[i] = -1;
    else
      indices[i] = (double) h_node_get_state_index_from_value(node, (h_double_t) values[i]);

    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(2);
      RHugin_handle_error_code(error_code);
    }
  }

  UNPROTECT(2);
  return ret;
}


/* 6.8 Generating tables */

SEXP RHugin_node_generate_table(SEXP Snode)
{
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  RHugin_handle_status_code(h_node_generate_table(node));

  return R_NilValue;
}


SEXP RHugin_domain_generate_tables(SEXP Sdomain)
{
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  RHugin_handle_status_code(h_domain_generate_tables(domain));

  return R_NilValue;
}


// SEXP RHugin_class_generate_tables(SEXP Sclass);
// SEXP RHugin_class_set_log_file(SEXP Sclass, SEXP Slog_file);


/* 6.9 How the computations are done */

SEXP RHugin_model_set_number_of_samples_per_interval(SEXP Smodel, SEXP Scount)
{
  h_status_t status = 0;
  h_model_t model = modelPointerFromSEXP(VECTOR_ELT(Smodel, 0));

  PROTECT(Scount = AS_NUMERIC(Scount));
  status = h_model_set_number_of_samples_per_interval(model, (size_t) REAL(Scount)[0]);
  UNPROTECT(1);

  RHugin_handle_status_code(status);

  return R_NilValue;
}


SEXP RHugin_model_get_number_of_samples_per_interval(SEXP Smodel)
{
  SEXP ret = R_NilValue;
  h_model_t model = modelPointerFromSEXP(VECTOR_ELT(Smodel, 0));

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_model_get_number_of_samples_per_interval(model);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


/* 7.2 Compilation */

SEXP RHugin_domain_compile(SEXP Sdomain)
{
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

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


/* 7.3 Triangulation */

SEXP RHugin_domain_set_initial_triangulation(SEXP Sdomain, SEXP Sorder)
{
  h_node_t *order = NULL;
  R_len_t i = 0, n = LENGTH(Sorder);
  h_domain_t domain = domainPointerFromSEXP(Sdomain);
  
  order = (h_node_t*) R_alloc(n + 1, sizeof(h_node_t));
  for(i = 0; i < n; i++)
    order[i] = nodePointerFromSEXP(VECTOR_ELT(Sorder, i));
  order[n] = NULL;
  
  RHugin_handle_status_code(h_domain_set_initial_triangulation(domain, order));
  
  return R_NilValue;
}


SEXP RHugin_domain_set_max_number_of_separators(SEXP Sdomain, SEXP Scount)
{
  h_status_t status = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Scount = AS_NUMERIC(Scount));
  status = h_domain_set_max_number_of_separators(domain, (size_t) REAL(Scount)[0]);
  UNPROTECT(1);

  RHugin_handle_status_code(status);

  return R_NilValue;
}


SEXP RHugin_domain_get_max_number_of_separators(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_max_number_of_separators(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_set_max_separator_size(SEXP Sdomain, SEXP Ssize)
{
  h_status_t status = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);
  
  PROTECT(Ssize = AS_NUMERIC(Ssize));
  status = h_domain_set_max_separator_size(domain, (size_t) REAL(Ssize)[0]);
  UNPROTECT(1);
  
  RHugin_handle_status_code(status);
  
  return R_NilValue;
}


SEXP RHugin_domain_get_max_separator_size(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);
  
  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_max_separator_size(domain);
  UNPROTECT(1);
  
  RHugin_handle_error();
  
  return ret;
}


SEXP RHugin_domain_triangulate(SEXP Sdomain, SEXP Smethod)
{
  h_triangulation_method_t method = h_tm_best_greedy;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Smethod = AS_CHARACTER(Smethod));

  if(asChar(Smethod) == RHUGIN_TM_CLIQUE_SIZE)
    method = h_tm_clique_size;
  else if(asChar(Smethod) == RHUGIN_TM_CLIQUE_WEIGHT)
    method = h_tm_clique_weight;
  else if(asChar(Smethod) == RHUGIN_TM_FILL_IN_SIZE)
    method = h_tm_fill_in_size;
  else if(asChar(Smethod) == RHUGIN_TM_FILL_IN_WEIGHT)
    method = h_tm_fill_in_weight;
  else if(asChar(Smethod) == RHUGIN_TM_BEST_GREEDY)
    method = h_tm_best_greedy;
  else if(asChar(Smethod) == RHUGIN_TM_TOTAL_WEIGHT)
    method = h_tm_total_weight;

  UNPROTECT(1);

  RHugin_handle_status_code(h_domain_triangulate(domain, method));

  return R_NilValue;
}


SEXP RHugin_domain_triangulate_with_order(SEXP Sdomain, SEXP Sorder)
{
  h_node_t *order = NULL;
  R_len_t i = 0, n = LENGTH(Sorder);
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
  R_len_t i = 0, n = 0;
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


// SEXP RHugin_domain_parse_nodes(SEXP Sdomain, SEXP Sfile_name, SEXP Serror_fun, SEXP Sdata);
// SEXP RHugin_class_parse_nodes(SEXP Sclass, SEXP Sfile_name, SEXP Serror_fun, SEXP Sdata);


/* 7.4 Getting a compilation log */

#ifndef WIN32
  SEXP RHugin_domain_set_log_file(SEXP Sdomain, SEXP Sfile_name)
  {
    h_status_t status = 0;
    log_file_info *lfi = NULL;
    h_domain_t domain = domainPointerFromSEXP(Sdomain);

    lfi = (log_file_info *) h_domain_get_user_data(domain);

    if(Sfile_name != R_NilValue) {
      if(lfi != NULL) {
        warning("domain already has a log file");
        return(R_NilValue);
      }

      PROTECT(Sfile_name = AS_CHARACTER(Sfile_name));
      lfi = RHugin_open_log_file(CHAR(asChar(Sfile_name)));
      UNPROTECT(1);

      if(lfi != NULL) {
        status = h_domain_set_log_file(domain, lfi->p_file);

        if(status != 0) {
          lfi = RHugin_close_log_file(lfi);
          RHugin_handle_status_code(status);
        }
      
        status = h_domain_set_user_data(domain, (void *) lfi);

        if(status != 0) {
          lfi = RHugin_close_log_file(lfi);
          RHugin_handle_status_code(status);
        }
      }
    } else { /* Sfile_name == R_NilValue */
      if(lfi != NULL) {
        lfi = RHugin_close_log_file(lfi);
        RHugin_handle_status_code(h_domain_set_log_file(domain, NULL));
        RHugin_handle_status_code(h_domain_set_user_data(domain, NULL));
      }
    }

    return R_NilValue;
  }
#else
  SEXP RHugin_domain_set_log_file(SEXP Sdomain, SEXP Sfile_name)
  {
    warning("log files are not supported on Microsoft Windows\n");
    return R_NilValue;
  }
#endif


/* 7.5 Uncompilation */

SEXP RHugin_domain_uncompile(SEXP Sdomain)
{
  RHugin_handle_status_code(h_domain_uncompile(domainPointerFromSEXP(Sdomain)));

  return R_NilValue;
}


/* 7.6 Compression */

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


/* 7.7 Approximation */

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


/* 8.2 Junction trees */

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

  if(jt) {
    PROTECT(ret = allocVector(VECSXP, 1));
    SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(jt, RHugin_junction_tree_tag, R_NilValue));
    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_node_get_junction_tree(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_junction_tree_t jt = NULL;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  jt = h_node_get_junction_tree(node);
  RHugin_handle_error();

  if(jt) {
    PROTECT(ret = allocVector(VECSXP, 1));
    SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(jt, RHugin_junction_tree_tag, R_NilValue));
    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_jt_get_cliques(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  h_clique_t *clique = NULL, *cliques = NULL;
  R_len_t i = 0, n = 0;
  h_junction_tree_t jt = jtPointerFromSEXP(VECTOR_ELT(Sjt, 0));

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
  h_junction_tree_t jt = jtPointerFromSEXP(VECTOR_ELT(Sjt, 0));

  clique = h_jt_get_root(jt);
  RHugin_handle_error();

  if(clique) {
    PROTECT(ret = allocVector(VECSXP, 1));
    SET_VECTOR_ELT(ret, 0, R_MakeExternalPtr(clique, RHugin_clique_tag, R_NilValue));
    UNPROTECT(1);
  }

  return ret;
}


SEXP RHugin_jt_get_total_size(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  size_t total_size = 0;
  h_junction_tree_t jt = jtPointerFromSEXP(VECTOR_ELT(Sjt, 0));

  total_size = h_jt_get_total_size(jt);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = total_size == (size_t) -1 ? -1.0 : (double) total_size;
  UNPROTECT(1);

  return ret;
}


SEXP RHugin_jt_get_total_cg_size(SEXP Sjt)
{
  SEXP ret = R_NilValue;
  size_t total_size = 0;
  h_junction_tree_t jt = jtPointerFromSEXP(VECTOR_ELT(Sjt, 0));

  total_size = h_jt_get_total_cg_size(jt);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = total_size == (size_t) -1 ? -1.0 : (double) total_size;
  UNPROTECT(1);

  return ret;
}


/* 8.3 Cliques */

SEXP RHugin_clique_get_members(SEXP Scliques)
{
  SEXP ret = R_NilValue, node_list = R_NilValue, names = R_NilValue;
  h_error_t error_code = h_error_none;
  h_node_t *node = NULL, *nodes = NULL;
  R_len_t i = 0, j = 0, n = 0, n_cliques = LENGTH(Scliques);
  h_clique_t clique = NULL;

  PROTECT(ret = allocVector(VECSXP, n_cliques));

  for(i = 0; i < n_cliques; i++) {

    clique = cliquePointerFromSEXP(VECTOR_ELT(Scliques, i));

    nodes = h_clique_get_members(clique);

    error_code = h_error_code();
    if(error_code != h_error_none) {
      UNPROTECT(1);
      RHugin_handle_error_code(error_code);
    }

    if(nodes) {
      n = 0;
      for(node = nodes; *node != NULL; node++) n++;

      PROTECT(node_list = allocVector(VECSXP, n));
      PROTECT(names = allocVector(STRSXP, n));

      for(j = 0; j < n; j++) {
        SET_VECTOR_ELT(node_list, j, R_MakeExternalPtr(nodes[j], RHugin_node_tag, R_NilValue));
        SET_STRING_ELT(names, j, mkChar( (char*) h_node_get_name(nodes[j])));

        error_code = h_error_code();
        if(error_code != h_error_none) {
          UNPROTECT(3);
          RHugin_handle_error_code(error_code);
        }
      }

      setAttrib(node_list, R_NamesSymbol, names);
      SET_VECTOR_ELT(ret, i, node_list);
      UNPROTECT(2);
    }
  }

  UNPROTECT(1);

  return ret;
}


SEXP RHugin_clique_get_neighbors(SEXP Sclique)
{
  SEXP ret = R_NilValue;
  h_clique_t *neighbor = NULL, *neighbors = NULL;
  R_len_t i = 0, n = 0;
  h_clique_t clique = cliquePointerFromSEXP(VECTOR_ELT(Sclique, 0));

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


/* 9.2 Entering evidence */

SEXP RHugin_node_select_state(SEXP Snode, SEXP Sstate)
{
  double state = -1.0;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sstate = AS_NUMERIC(Sstate));
  state = REAL(Sstate)[0];
  UNPROTECT(1);

  RHugin_handle_status_code(h_node_select_state(node, (size_t) state));

  return R_NilValue;
}


SEXP RHugin_node_enter_finding(SEXP Snode, SEXP Sstates, SEXP Svalues)
{
  h_status_t status = 0;
  double *state = NULL, *value = NULL;
  R_len_t i = 0, n = LENGTH(Sstates);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  if(LENGTH(Svalues) != n)
    error("Sstates and Svalues are not the same length");

  PROTECT(Sstates = AS_NUMERIC(Sstates));
  state = REAL(Sstates);
  PROTECT(Svalues = AS_NUMERIC(Svalues));
  value = REAL(Svalues);

  for(i = 0; i < n; i++) {
    status = h_node_enter_finding(node, (size_t) state[i], (h_number_t) value[i]);
    if(status != 0) {
      UNPROTECT(2);
      RHugin_handle_status_code(status);
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


/* 9.3 Retracting evidence */

SEXP RHugin_node_retract_findings(SEXP Snodes)
{
  h_node_t node = NULL;
  R_len_t i = 0, n = LENGTH(Snodes);

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


/* 9.4 Determining independence properties */

SEXP RHugin_domain_get_d_connected_nodes(SEXP Sdomain, SEXP Ssource, SEXP Shard, SEXP Ssoft)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_error_t error_code = h_error_none;
  h_node_t *source = NULL, *hard = NULL, *soft = NULL, *d_connected = NULL, *node = NULL;
  R_len_t i = 0, n = 0;
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
  R_len_t i = 0, n = 0;
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


/* 9.5 Retreiving beliefs */

SEXP RHugin_node_get_belief(SEXP Snode, SEXP Sstates)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *states = NULL, *belief = NULL;
  R_len_t i = 0, n = LENGTH(Sstates);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sstates = AS_NUMERIC(Sstates));
  states = REAL(Sstates);
  PROTECT(ret = allocVector(REALSXP, n));
  belief = REAL(ret);

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
  R_len_t i = 0, n = LENGTH(Snodes);
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


/* 9.6 Retrieving expected utilities */

SEXP RHugin_node_get_expected_utility(SEXP Snode, SEXP Sstates)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *states = NULL, *utility = NULL;
  R_len_t i = 0, n = LENGTH(Sstates);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sstates = AS_NUMERIC(Sstates));
  states = REAL(Sstates);
  PROTECT(ret = allocVector(REALSXP, n));
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


SEXP RHugin_domain_get_expected_utility(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_expected_utility(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


/* 9.7 Computing function values */

SEXP RHugin_node_get_value(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  
  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_node_get_value(node);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


/* 9.8 Examining Evidence */

SEXP RHugin_node_get_entered_finding(SEXP Snode, SEXP Sstates)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *states = NULL, *finding = NULL;
  R_len_t i = 0, n = LENGTH(Sstates);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sstates = AS_NUMERIC(Sstates));
  states = REAL(Sstates);

  PROTECT(ret = allocVector(REALSXP, n));
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
  double *states = NULL, *finding = NULL;
  R_len_t i = 0, n = LENGTH(Sstates);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sstates = AS_NUMERIC(Sstates));
  states = REAL(Sstates);

  PROTECT(ret = allocVector(REALSXP, n));
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


/* 9.9 Case files */

SEXP RHugin_domain_save_case(SEXP Sdomain, SEXP Sfile_name)
{
  h_status_t status = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Sfile_name = AS_CHARACTER(Sfile_name));
  status = h_domain_save_case(domain, (h_string_t) CHAR(asChar(Sfile_name)));
  UNPROTECT(1);

  RHugin_handle_status_code(status);

  return R_NilValue;
}


SEXP RHugin_domain_parse_case(SEXP Sdomain, SEXP Sfile_name)
{
  h_status_t status = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Sfile_name = AS_CHARACTER(Sfile_name));
  status = h_domain_parse_case(domain,
                               (h_string_t) CHAR(asChar(Sfile_name)),
                               RHuginFileParseError,
                               NULL);
  UNPROTECT(1);

  RHugin_handle_status_code(status);

  return R_NilValue;
}



/* 10.2 Propagation */

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


/* 10.3 Inference in LIMIDs: Computing optimal policies */

SEXP RHugin_domain_update_policies(SEXP Sdomain)
{
  RHugin_handle_status_code(h_domain_update_policies(domainPointerFromSEXP(Sdomain)));
  
  return R_NilValue;
}


/* 10.4 Conflict of evidence */

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


/* 10.5 The normalization constant */

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


/* 10.6 Initializing the inference engine */

SEXP RHugin_domain_save_to_memory(SEXP Sdomain)
{
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  RHugin_handle_status_code(h_domain_save_to_memory(domain));

  return R_NilValue;
}


SEXP RHugin_domain_reset_inference_engine(SEXP Sdomain)
{
  h_domain_t domain = domainPointerFromSEXP(Sdomain);
  
  RHugin_handle_status_code(h_domain_reset_inference_engine(domain));
  
  return R_NilValue;
}


SEXP RHugin_domain_initialize(SEXP Sdomain)
{
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  RHugin_handle_status_code(h_domain_initialize(domain));

  return R_NilValue;
}


/* 10.7 Querying the state of the inference engine */

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


/* 10.8 Simulation */

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

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_node_get_sampled_state(node);
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


SEXP RHugin_node_get_sampled_utility(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  
  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_node_get_sampled_utility(node);
  UNPROTECT(1);
  
  RHugin_handle_error();
  
  return ret;
}


SEXP RHugin_domain_seed_random(SEXP Sdomain, SEXP Sseed)
{
  unsigned int seed = 1;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Sseed = AS_NUMERIC(Sseed));
  seed = (unsigned int) REAL(Sseed)[0];
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


/* 10.9 Value of information analysis */

SEXP RHugin_node_get_entropy(SEXP Snodes)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  h_node_t node = NULL;
  double *entropy = NULL;
  R_len_t i = 0, n = LENGTH(Snodes);

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
  R_len_t i = 0, n = LENGTH(Snodes);

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


/* Section 10.10 Sensitivity analyis */

SEXP RHugin_node_compute_sensitivity_data(SEXP Snode, SEXP Sstate)
{
  size_t state = 0;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sstate = AS_NUMERIC(Sstate));
  state = (size_t) REAL(Sstate)[0];
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

  PROTECT(Sindex = AS_NUMERIC(Sindex));
  PROTECT(ret = allocVector(REALSXP, 4));
  constants = REAL(ret);
  PROTECT(names = allocVector(STRSXP, 4));

  pret = (h_number_t*) R_alloc(4, sizeof(h_number_t));

  status = h_node_get_sensitivity_constants(node, (size_t) REAL(Sindex)[0],
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
  R_len_t i = 0, n = 0;
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


SEXP RHugin_domain_compute_sensitivity_data(SEXP Sdomain, SEXP Snodes, SEXP Sstates)
{
  h_node_t *nodes = NULL;
  size_t *states = NULL;
  double *p_Sstates = NULL;
  R_len_t i = 0, n_nodes = LENGTH(Snodes);
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Sstates = AS_NUMERIC(Sstates));
  p_Sstates = REAL(Sstates);

  nodes = (h_node_t*) R_alloc(n_nodes + 1, sizeof(h_node_t));
  states = (size_t*) R_alloc(n_nodes, sizeof(size_t));

  for(i = 0; i < n_nodes; i++) {
    nodes[i] = nodePointerFromSEXP(VECTOR_ELT(Snodes, i));
    states[i] = (size_t) p_Sstates[i];
  }
  nodes[n_nodes] = NULL;

  UNPROTECT(1);

  RHugin_handle_status_code(h_domain_compute_sensitivity_data(domain, nodes, states));

  return R_NilValue;
}


SEXP RHugin_node_get_sensitivity_constants_by_output(SEXP Snode, SEXP Sinput, SEXP Soutput)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_status_t status = 0;
  double *constants = NULL;
  h_number_t *pret = NULL;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sinput = AS_NUMERIC(Sinput));
  PROTECT(Soutput = AS_NUMERIC(Soutput));
  PROTECT(ret = allocVector(REALSXP, 4));
  constants = REAL(ret);
  PROTECT(names = allocVector(STRSXP, 4));

  pret = (h_number_t*) R_alloc(4, sizeof(h_number_t));

  status = h_node_get_sensitivity_constants_by_output(node,
                                                      (size_t) REAL(Sinput)[0],
                                                      (size_t) REAL(Soutput)[0],
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

  UNPROTECT(4);

  RHugin_handle_status_code(status);

  return ret;
}


SEXP RHugin_domain_get_sensitivity_set_by_output(SEXP Sdomain, SEXP Soutput)
{
  SEXP ret = R_NilValue, names = R_NilValue;
  h_error_t error_code = h_error_none;
  h_node_t *sensitivity_set = NULL, *pnode = NULL;
  R_len_t i = 0, n = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Soutput = AS_NUMERIC(Soutput));

  sensitivity_set = h_domain_get_sensitivity_set_by_output(domain, (size_t) REAL(Soutput)[0]);
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
        UNPROTECT(3);
        RHugin_handle_error_code(error_code);
      }
    }
    setAttrib(ret, R_NamesSymbol, names);
    
    UNPROTECT(3);
  }
  
  return ret;
}


/* 10.11 Most probable configurations */

SEXP RHugin_domain_find_map_configurations(SEXP Sdomain, SEXP Snodes, SEXP Spmin)
{
  h_node_t *nodes = NULL;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);
  h_double_t pmin = 0.0;
  R_len_t i = 0, n_nodes = LENGTH(Snodes);

  PROTECT(Spmin = AS_NUMERIC(Spmin));
  pmin = (h_double_t) REAL(Spmin)[0];
  UNPROTECT(1);

  nodes = (h_node_t*) R_alloc(n_nodes + 1, sizeof(h_node_t));

  for(i = 0; i < n_nodes; i++)
    nodes[i] = nodePointerFromSEXP(VECTOR_ELT(Snodes, i));
  nodes[n_nodes] = NULL;

  RHugin_handle_status_code(h_domain_find_map_configurations(domain, nodes, pmin));

  return R_NilValue;
}


SEXP RHugin_domain_get_number_of_map_configurations(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);
  
  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_number_of_map_configurations(domain);
  UNPROTECT(1);
  
  RHugin_handle_error();
  
  return ret;
}


SEXP RHugin_domain_get_map_configuration(SEXP Sdomain, SEXP Sindex, SEXP Sn_nodes)
{
  SEXP ret = R_NilValue;
  double *p_ret = NULL;
  R_len_t i = 0, n_nodes = 0;
  size_t index = 0, *configuration = NULL;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Sindex = AS_NUMERIC(Sindex));
  index = (size_t) REAL(Sindex)[0];

  PROTECT(Sn_nodes = AS_NUMERIC(Sn_nodes));
  n_nodes = (R_len_t) REAL(Sn_nodes)[0];

  UNPROTECT(2);

  configuration = h_domain_get_map_configuration(domain, index);

  if(configuration) {
    PROTECT(ret = allocVector(REALSXP, n_nodes));
    p_ret = REAL(ret);

    for(i = 0; i < n_nodes; i++)
      p_ret[i] = (double) configuration[i];

    UNPROTECT(1);
  }

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_domain_get_probability_of_map_configuration(SEXP Sdomain, SEXP Sindex)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);
  size_t index = 0;

  PROTECT(Sindex = AS_NUMERIC(Sindex));
  index = (size_t) REAL(Sindex)[0];
  UNPROTECT(1);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = h_domain_get_probability_of_map_configuration(domain, index);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


/* 11.1 Experience counts and fading factors */

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


/* 11.2 Updating tables */

SEXP RHugin_domain_adapt(SEXP Sdomain)
{
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  RHugin_handle_status_code(h_domain_adapt(domain));

  return R_NilValue;
}


/* 12.1 Data */

SEXP RHugin_domain_set_number_of_cases(SEXP Sdomain, SEXP Scount)
{
  size_t count = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Scount = AS_NUMERIC(Scount));
  count = (size_t) REAL(Scount)[0];
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

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_number_of_cases(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


SEXP RHugin_node_set_case_state(SEXP Snode, SEXP Scase_indices, SEXP Sstates)
{
  h_status_t status = 0;
  double  *case_indices = NULL, *states = NULL;
  R_len_t i = 0, n = LENGTH(Scase_indices);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  if(LENGTH(Sstates) != n)
    error("Scase_indices and Sstates are not the same length");

  PROTECT(Scase_indices = AS_NUMERIC(Scase_indices));
  case_indices = REAL(Scase_indices);

  PROTECT(Sstates = AS_NUMERIC(Sstates));
  states = REAL(Sstates);

  for(i = 0; i < n; i++) {
    status = h_node_set_case_state(node, (size_t) case_indices[i], (size_t) states[i]);
    if(status != 0) {
      UNPROTECT(2);
      RHugin_handle_status_code(status);
    }
  }

  UNPROTECT(2);

  return R_NilValue;
}


SEXP RHugin_node_get_case_state(SEXP Snode, SEXP Scase_indices)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *states = NULL, *case_indices = NULL;
  R_len_t i = 0, n = LENGTH(Scase_indices);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Scase_indices = AS_NUMERIC(Scase_indices));
  case_indices = REAL(Scase_indices);

  PROTECT(ret = allocVector(REALSXP, n));
  states = REAL(ret);

  for(i = 0; i < n; i++) {
    states[i] = h_node_case_is_set(node, (size_t) case_indices[i]) ?
                (double) h_node_get_case_state(node, (size_t) case_indices[i]) :
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


SEXP RHugin_node_set_case_value(SEXP Snode, SEXP Scase_indices, SEXP Svalues)
{
  h_status_t status = 0;
  double *case_indices = NULL, *values = NULL;
  R_len_t i = 0, n = LENGTH(Scase_indices);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  if(LENGTH(Svalues) != n)
    error("Scase_indices and Svalues are not the same length");

  PROTECT(Scase_indices = AS_NUMERIC(Scase_indices));
  case_indices = REAL(Scase_indices);

  PROTECT(Svalues = AS_NUMERIC(Svalues));
  values = REAL(Svalues);

  for(i = 0; i < n; i++) {
    if(!R_FINITE(values[i]))
      status = h_node_unset_case(node, (size_t) case_indices[i]);
    else
      status = h_node_set_case_value(node, (size_t) case_indices[i], values[i]);

    if(status != 0) {
      UNPROTECT(2);
      RHugin_handle_status_code(status);
    }
  }

  UNPROTECT(2);

  return R_NilValue;
}


SEXP RHugin_node_get_case_value(SEXP Snode, SEXP Scase_indices)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *case_indices = NULL, *values = NULL;
  R_len_t i = 0, n = LENGTH(Scase_indices);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Scase_indices = AS_NUMERIC(Scase_indices));
  case_indices = REAL(Scase_indices);

  PROTECT(ret = allocVector(REALSXP, n));
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
  double *case_indices = NULL;
  R_len_t i = 0, n = LENGTH(Scase_indices);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Scase_indices = AS_NUMERIC(Scase_indices));
  case_indices = REAL(Scase_indices);

  for(i = 0; i < n; i++) {
    status = h_node_unset_case(node, (size_t) case_indices[i]);
    if(status != 0) {
      UNPROTECT(1);
      RHugin_handle_status_code(status);
    }
  }

  UNPROTECT(1);

  return R_NilValue;
}


SEXP RHugin_node_case_is_set(SEXP Snode, SEXP Scase_indices)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *case_indices = NULL;
  int *case_is_set = NULL;
  R_len_t i = 0, n = LENGTH(Scase_indices);
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Scase_indices = AS_NUMERIC(Scase_indices));
  case_indices = REAL(Scase_indices);

  PROTECT(ret = allocVector(LGLSXP, n));
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
  double *case_indices = NULL, *case_counts = NULL;
  R_len_t i = 0, n = LENGTH(Scase_indices);
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  if(LENGTH(Scase_counts) != n)
    error("Scase_indices and Scase_counts are not the same length");

  PROTECT(Scase_indices = AS_NUMERIC(Scase_indices));
  case_indices = REAL(Scase_indices);

  PROTECT(Scase_counts = AS_NUMERIC(Scase_counts));
  case_counts = REAL(Scase_counts);

  for(i = 0; i < n; i++) {
    status = h_domain_set_case_count(domain, (size_t) case_indices[i], (h_number_t) case_counts[i]);

    if(status != 0) {
      UNPROTECT(2);
      RHugin_handle_status_code(status);
    }
  }

  UNPROTECT(2);

  return R_NilValue;
}


SEXP RHugin_domain_get_case_count(SEXP Sdomain, SEXP Scase_indices)
{
  SEXP ret = R_NilValue;
  h_error_t error_code = h_error_none;
  double *case_indices = NULL, *counts = NULL;
  R_len_t i = 0, n = LENGTH(Scase_indices);
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Scase_indices = AS_NUMERIC(Scase_indices));
  case_indices = REAL(Scase_indices);

  PROTECT(ret = allocVector(REALSXP, n));
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
  size_t case_index = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Scase_index = AS_NUMERIC(Scase_index));
  case_index = (size_t) REAL(Scase_index)[0];
  UNPROTECT(1);

  RHugin_handle_status_code(h_domain_enter_case(domain, case_index));

  return R_NilValue;
}


/* 12.2 Scoring of graphical models */

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


/* 12.3 Data files */

SEXP RHugin_domain_parse_cases(SEXP Sdomain, SEXP Sfile_name)
{
  h_status_t status = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Sfile_name = AS_CHARACTER(Sfile_name));
  status = h_domain_parse_cases(domain,
                                (h_string_t) CHAR(asChar(Sfile_name)),
                                RHuginFileParseError,
                                NULL);
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
  double *cases = NULL;
  R_len_t i = 0, n_cases = -1, n_nodes = LENGTH(Snodes);
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Sfile_name = AS_CHARACTER(Sfile_name));
  PROTECT(Sinclude_case_counts = AS_LOGICAL(Sinclude_case_counts));
  PROTECT(Sseparator = AS_CHARACTER(Sseparator));
  PROTECT(Smissing_data = AS_CHARACTER(Smissing_data));

  nodes = (h_node_t*) R_alloc(n_nodes + 1, sizeof(h_node_t));
  for(i = 0; i < n_nodes; i++)
    nodes[i] = nodePointerFromSEXP(VECTOR_ELT(Snodes, i));
  nodes[n_nodes] = NULL;

  if(Scases != R_NilValue) {
    PROTECT(Scases = AS_NUMERIC(Scases));
    n_cases = LENGTH(Scases);
    cases = REAL(Scases);
    case_indices = (h_index_t*) R_alloc(n_cases + 1, sizeof(h_index_t));
    for(i = 0; i < n_cases; i++)
      case_indices[i] = (h_index_t) cases[i];
    case_indices[n_cases] = -1;
    UNPROTECT(1);
  }

  include_case_counts = (h_boolean_t) LOGICAL(Sinclude_case_counts)[0];

  status = h_domain_save_cases(domain,
                               (h_string_t) CHAR(asChar(Sfile_name)),
                               nodes,
                               case_indices,
                               include_case_counts,
                               (h_string_t) CHAR(asChar(Sseparator)),
                               (h_string_t) CHAR(asChar(Smissing_data)));

  UNPROTECT(4);

  RHugin_handle_status_code(status);

  return R_NilValue;
}


/* 12.4 Learning network structure */

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


/* 12.5 Domain knowledge */

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


/* 12.6 Learning conditional probability tables */

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
  size_t count = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(Scount = AS_NUMERIC(Scount));
  count = (size_t) REAL(Scount)[0];
  UNPROTECT(1);

  RHugin_handle_status_code(h_domain_set_max_number_of_em_iterations(domain, count));

  return R_NilValue;
}


SEXP RHugin_domain_get_max_number_of_em_iterations(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  PROTECT(ret = allocVector(REALSXP, 1));
  REAL(ret)[0] = (double) h_domain_get_max_number_of_em_iterations(domain);
  UNPROTECT(1);

  RHugin_handle_error();

  return ret;
}


// SEXP RHugin_domain_learn_class_tables(SEXP Sdomain);


/* 13.8 parsing NET files */

SEXP RHugin_net_parse_domain(SEXP Sfile_name)
{
  SEXP ret = R_NilValue;
  h_domain_t domain = NULL;

  PROTECT(Sfile_name = AS_CHARACTER(Sfile_name));

  domain = h_net_parse_domain((h_string_t) CHAR(asChar(Sfile_name)),
                              RHuginFileParseError, NULL);

  UNPROTECT(1);
  RHugin_handle_error();

  if(domain) {
    ret = R_MakeExternalPtr(domain, RHugin_domain_tag, R_NilValue);
    R_RegisterCFinalizerEx(ret, (R_CFinalizer_t) RHugin_domain_finalizer, TRUE);
  }

  return ret;
}


SEXP RHugin_net_parse_classes(SEXP Sfile_name) 
{
  SEXP ret = R_NilValue;
  h_status_t status = 0;
  h_class_collection_t cc = NULL;
  cc = h_new_class_collection();

  PROTECT(Sfile_name = CHAR(asChar(Sfile_name)));
  status = h_net_parse_classes((h_string_t) Sfile_name, cc, NULL, 
                                RHuginFileParseError, NULL);
  UNPROTECT(1);

  RHugin_handle_status_code(status);

  ret = R_MakeExternalPtr(cc, RHugin_class_collection_tag, R_NilValue);
  R_RegisterCFinalizerEx(ret, (R_CFinalizer_t) RHugin_class_collection_finalizer, TRUE);

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


/* 13.9 Saving class collections, classes, and domains as NET files */

// SEXP RHugin_cc_save_as_net(SEXP Scc, SEXP Sfile_name);
SEXP RHugin_class_save_as_net(SEXP Sclass, SEXP Sfile_name) {
  h_status_t status = 0;
  h_class_t class = classPointerFromSEXP(Sclass);

  PROTECT(Sfile_name = AS_CHARACTER(Sfile_name));
  status = h_class_save_as_net(class, (h_string_t) CHAR(asChar(Sfile_name)));
  UNPROTECT(1);

  RHugin_handle_status_code(status);

  return R_NilValue;
}
// SEXP RHugin_domain_save_as_net(SEXP Sdomain, SEXP Sfile_name);
// SEXP RHugin_class_get_file_name(SEXP Sclass);
// SEXP RHugin_domain_get_file_name(SEXP Sdomain);


/* 14.1 The label of a node */

SEXP RHugin_node_set_label(SEXP Snode, SEXP Slabel)
{
  h_status_t status = 0;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  
  PROTECT(Slabel = AS_CHARACTER(Slabel));
  status = h_node_set_label(node, (h_string_t) CHAR(asChar(Slabel)));
  UNPROTECT(1);
  
  RHugin_handle_status_code(status);
  
  return R_NilValue;
}


SEXP RHugin_node_get_label(SEXP Snode)
{
  SEXP ret = R_NilValue;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));
  
  PROTECT(ret = allocVector(STRSXP, 1));
  SET_STRING_ELT(ret, 0, mkChar( (char*) h_node_get_label(node)));
  UNPROTECT(1);
  
  RHugin_handle_error();
  
  return ret;
}


/*  14.2 The position of a node */

SEXP RHugin_node_set_position(SEXP Snode, SEXP Sposition)
{
  h_coordinate_t x = -1, y = -1;
  h_node_t node = nodePointerFromSEXP(VECTOR_ELT(Snode, 0));

  PROTECT(Sposition = AS_NUMERIC(Sposition));
  x = (h_coordinate_t) REAL(Sposition)[0];
  y = (h_coordinate_t) REAL(Sposition)[1];
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

  PROTECT(ret = allocVector(REALSXP, 2));
  REAL(ret)[0] = (double) position[0];
  REAL(ret)[1] = (double) position[1];
  UNPROTECT(1);

  return ret;
}


/* 14.3 The size of a node */

SEXP RHugin_domain_set_node_size(SEXP Sdomain, SEXP Ssize)
{
  size_t width = -1, height = -1;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);
  
  PROTECT(Ssize = AS_NUMERIC(Ssize));
  width = (size_t) REAL(Ssize)[0];
  height = (size_t) REAL(Ssize)[1];
  UNPROTECT(1);

  RHugin_handle_status_code(h_domain_set_node_size(domain, width, height));

  return R_NilValue;
}


SEXP RHugin_domain_get_node_size(SEXP Sdomain)
{
  SEXP ret = R_NilValue;
  size_t size[] = {0, 0};
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

  RHugin_handle_status_code(h_domain_get_node_size(domain, size, size + 1));

  PROTECT(ret = allocVector(REALSXP, 2));
  REAL(ret)[0] = (double) size[0];
  REAL(ret)[1] = (double) size[1];
  UNPROTECT(1);

  return ret;
}


// SEXP RHugin_class_set_node_size(SEXP Sclass, SEXP Ssize);
// SEXP RHugin_class_get_node_size(SEXP Sclass);


