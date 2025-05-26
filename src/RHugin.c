#include "RHugin.h"
#include "RHuginLink.h"

SEXP RHugin_domain_tag;
SEXP RHugin_node_tag;
SEXP RHugin_table_tag;
SEXP RHugin_expression_tag;
SEXP RHugin_model_tag;
SEXP RHugin_junction_tree_tag;
SEXP RHugin_clique_tag;
SEXP RHugin_class_tag;
SEXP RHugin_class_collection_tag;

SEXP RHUGIN_ERROR;

SEXP RHUGIN_CHANCE;
SEXP RHUGIN_UTILITY;
SEXP RHUGIN_DECISION;
SEXP RHUGIN_FUNCTION;
SEXP RHUGIN_INSTANCE;

SEXP RHUGIN_DISCRETE;
SEXP RHUGIN_CONTINUOUS;
SEXP RHUGIN_OTHER;

SEXP RHUGIN_LABELED;
SEXP RHUGIN_BOOLEAN;
SEXP RHUGIN_NUMBERED;
SEXP RHUGIN_INTERVAL;

SEXP RHUGIN_TM_CLIQUE_SIZE;
SEXP RHUGIN_TM_CLIQUE_WEIGHT;
SEXP RHUGIN_TM_FILL_IN_SIZE;
SEXP RHUGIN_TM_FILL_IN_WEIGHT;
SEXP RHUGIN_TM_BEST_GREEDY;
SEXP RHUGIN_TM_TOTAL_WEIGHT;

SEXP RHUGIN_EQUILIBRIUM_SUM;
SEXP RHUGIN_EQUILIBRIUM_MAX;

SEXP RHUGIN_MODE_NORMAL;
SEXP RHUGIN_MODE_FAST_RETRACTION;

SEXP RHUGIN_CONSTRAINT_NONE;
SEXP RHUGIN_CONSTRAINT_EDGE_REQUIRED;
SEXP RHUGIN_CONSTRAINT_EDGE_FORBIDDEN;
SEXP RHUGIN_CONSTRAINT_FORWARD_EDGE_REQUIRED;
SEXP RHUGIN_CONSTRAINT_BACKWARD_EDGE_REQUIRED;
SEXP RHUGIN_CONSTRAINT_FORWARD_EDGE_FORBIDDEN;
SEXP RHUGIN_CONSTRAINT_BACKWARD_EDGE_FORBIDDEN;


void RHugin_handle_error(void)
{
  h_error_t error_code = h_error_code();
  if(error_code == h_error_none) return;

  error("\nHugin Error Code: %d\nError Name: %s\nError Description: %s\n",
        (int) error_code,
        (char*) h_error_name(error_code),
        (char*) h_error_description(error_code));
}


void RHugin_handle_error_code(h_error_t error_code)
{
  if(error_code == h_error_none) return;

  error("\nHugin Error Code: %d\nError Name: %s\nError Description: %s\n",
        (int) error_code,
        (char*) h_error_name((h_error_t) error_code),
        (char*) h_error_description((h_error_t) error_code));
}


void RHugin_handle_status_code(h_status_t status)
{
  if(status != 0)
    error("\nHugin Error Code: %d\nError Name: %s\nError Description: %s\n",
          (int) status,
          (char*) h_error_name((h_error_t) status),
          (char*) h_error_description((h_error_t) status));
}


#ifndef WIN32
  log_file_info *RHugin_open_log_file(const char *filename)
  {
    log_file_info *lfi = NULL;
    size_t n = 0;

    if((lfi = malloc(sizeof(log_file_info))) != NULL) {
      lfi->p_file = fopen(filename, "a");

      if(lfi->p_file != NULL) {
        n = strlen(filename);
        lfi->filename = (char *) malloc((n + 1) * sizeof(char));
        lfi->filename = strncpy(lfi->filename, filename, n + 1);
      } else {
        free(lfi);
        return NULL;
      }
    }

    return lfi;
  }


  log_file_info *RHugin_close_log_file(log_file_info *lfi)
  {
    if(lfi != NULL) {
      if(lfi->p_file != NULL) {
        fclose(lfi->p_file);
        lfi->p_file = NULL;
      }

      if(lfi->filename != NULL) {
        free(lfi->filename);
        lfi->filename = NULL;
      }

      free(lfi);
    }

    return NULL;
  }


  SEXP RHugin_domain_get_logfile(SEXP Sdomain)
  {
    SEXP ret = R_NilValue;
    log_file_info *lfi = NULL;
    h_domain_t domain = domainPointerFromSEXP(Sdomain);

    lfi = (log_file_info *) h_domain_get_user_data(domain);

    if(lfi != NULL) {
      if(lfi->filename != NULL) {
        PROTECT(ret = allocVector(STRSXP, 1));
        SET_STRING_ELT(ret, 0, mkChar(lfi->filename));
        UNPROTECT(1);
      }
    }

    return ret;
  }
#else
  SEXP RHugin_domain_get_logfile(SEXP Sdomain)
  {
    warning("log files are not supported on Microsoft Windows\n");
    return R_NilValue;
  }
#endif


void RHugin_domain_finalizer(SEXP Sdomain)
{
#ifndef WIN32
  log_file_info *lfi = NULL;
#endif
  h_status_t status = 0;
  h_domain_t domain = domainPointerFromSEXP(Sdomain);

#ifndef WIN32
  lfi = (log_file_info *) h_domain_get_user_data(domain);
  
  if(lfi != NULL)
    lfi = RHugin_close_log_file(lfi);
#endif

  status = h_domain_delete(domain);
  R_ClearExternalPtr(Sdomain);

  if(status != 0)
    warning("in RHugin_domain_finalizer:\nHugin Error Code: %d\nError Name: %s\nError Description: %s\n",
            (int) status,
            (char*) h_error_name((h_error_t) status),
            (char*) h_error_description((h_error_t) status));
}

void RHugin_class_collection_finalizer(SEXP Sclass_collection)
{
#ifndef WIN32
  log_file_info *lfi = NULL;
#endif
  h_status_t status = 0;
  h_class_collection_t cc = classCollectionPointerFromSEXP(Sclass_collection);

  status = h_cc_delete(cc);
  R_ClearExternalPtr(Sclass_collection);

  if(status != 0)
    warning("in RHugin_domain_finalizer:\nHugin Error Code: %d\nError Name: %s\nError Description: %s\n",
            (int) status,
            (char*) h_error_name((h_error_t) status),
            (char*) h_error_description((h_error_t) status));
}

h_class_collection_t classCollectionPointerFromSEXP(SEXP Sclass_collection)
{
  h_class_collection_t cc = NULL;

  if(TYPEOF(Sclass_collection) != EXTPTRSXP || R_ExternalPtrTag(Sclass_collection) != RHugin_class_collection_tag)
    error("Sclass_collection is not a Hugin class collection");

  cc = (h_class_collection_t) R_ExternalPtrAddr(Sclass_collection);

  if(cc == NULL)
    error("class collection is NULL");

  return cc;
}

SEXP isDomainOrClass(SEXP SdomainOrClass) {
  SEXP res = PROTECT(allocVector(REALSXP, 1));

  if (TYPEOF(SdomainOrClass) != EXTPTRSXP){
    error("SdomainOrClass is not a pointer");
    REAL(res)[0] = (-1);
    return res;
  }

  if (R_ExternalPtrTag(SdomainOrClass) == RHugin_domain_tag) {
    REAL(res)[0] = 0;
  } else if (R_ExternalPtrTag(SdomainOrClass) == RHugin_class_tag) {
    REAL(res)[0] = 1;
  }

  return res;
}

h_class_t classPointerFromSEXP(SEXP Sclass)
{
  h_class_t class = NULL;

  if(TYPEOF(Sclass) != EXTPTRSXP || R_ExternalPtrTag(Sclass) != RHugin_class_tag)
    error("Sclass is not a Hugin class");

  class = (h_class_t) R_ExternalPtrAddr(Sclass);

  if(class == NULL)
    error("class is NULL");

  return class;
}

h_domain_t domainPointerFromSEXP(SEXP Sdomain)
{
  h_domain_t domain = NULL;

  if(TYPEOF(Sdomain) != EXTPTRSXP || R_ExternalPtrTag(Sdomain) != RHugin_domain_tag)
    error("Sdomain is not a Hugin domain");

  domain = (h_domain_t) R_ExternalPtrAddr(Sdomain);

  if(domain == NULL)
    error("domain is NULL");

  return domain;
}


h_node_t nodePointerFromSEXP(SEXP Snode)
{
  h_node_t node = NULL;

  if(TYPEOF(Snode) != EXTPTRSXP || R_ExternalPtrTag(Snode) != RHugin_node_tag)
    return NULL;

  node = (h_node_t) R_ExternalPtrAddr(Snode);

  if(node == NULL)
    return NULL;

  return node;
}


h_table_t tablePointerFromSEXP(SEXP Stable)
{
  h_table_t table = NULL;

  if(TYPEOF(Stable) != EXTPTRSXP || R_ExternalPtrTag(Stable) != RHugin_table_tag)
    error("Stable is not a Hugin table");

  table = (h_table_t) R_ExternalPtrAddr(Stable);

  if(table == NULL)
    error("table is NULL");

  return table;
}


h_expression_t expressionPointerFromSEXP(SEXP Sexpression)
{
  h_expression_t expression = NULL;

  if(TYPEOF(Sexpression) != EXTPTRSXP || R_ExternalPtrTag(Sexpression) != RHugin_expression_tag)
    error("Sexpression is not a Hugin expression");

  expression = (h_expression_t) R_ExternalPtrAddr(Sexpression);

  if(expression == NULL)
    error("expresion is NULL");

  return expression;
}


h_model_t modelPointerFromSEXP(SEXP Smodel)
{
  h_model_t model = NULL;
  
  if(TYPEOF(Smodel) != EXTPTRSXP || R_ExternalPtrTag(Smodel) != RHugin_model_tag)
    error("Smodel is not a Hugin model");

  model = (h_model_t) R_ExternalPtrAddr(Smodel);

  if(model == NULL)
    error("model is NULL");

  return model;
}


h_junction_tree_t jtPointerFromSEXP(SEXP Sjt)
{
  h_junction_tree_t jt = NULL;

  if(TYPEOF(Sjt) != EXTPTRSXP || R_ExternalPtrTag(Sjt) != RHugin_junction_tree_tag)
    error("Sjt is not a Hugin junction tree");

  jt = (h_junction_tree_t) R_ExternalPtrAddr(Sjt);

  if(jt == NULL)
    error("jt is NULL");

  return jt;
}


h_clique_t cliquePointerFromSEXP(SEXP Sclique)
{
  h_clique_t clique = NULL;

  if(TYPEOF(Sclique) != EXTPTRSXP || R_ExternalPtrTag(Sclique) != RHugin_clique_tag)
    error("Sclique is not a Hugin clique");

  clique = (h_clique_t) R_ExternalPtrAddr(Sclique);

  if(clique == NULL)
    error("clique is NULL");

  return clique;
}


void RHuginFileParseError(h_location_t line, h_string_t message, void *data)
{
  Rprintf("Parse error at line %d: %s\n", (int) line, message);
}


void RHuginExpressionParseError(h_location_t index, h_string_t message, void *data)
{
  Rprintf("Parse error at index %d: %s\n", (int) index, message);
}


void R_init_RHugin(DllInfo *info)
{
  R_CallMethodDef dotCallMethods[] = {
    /* Helper funtions from RHugin.c */
    {"RHugin_domain_get_logfile", (DL_FUNC) RHugin_domain_get_logfile, 1},
    {"isDomainOrClass", (DL_FUNC) isDomainOrClass, 1},

    /* 1.6 Errors */
    {"RHugin_error_code", (DL_FUNC) RHugin_error_code, 0},

    /* 1.6.1 Handling errors */
    {"RHugin_error_name", (DL_FUNC) RHugin_error_name, 1},
    {"RHugin_error_description", (DL_FUNC) RHugin_error_description, 1},

    /* 1.7 Taking advantage of multiple processors */
    {"RHugin_domain_set_concurrency_level", (DL_FUNC) RHugin_domain_set_concurrency_level, 2},
    {"RHugin_domain_get_concurrency_level", (DL_FUNC) RHugin_domain_get_concurrency_level, 1},
    {"RHugin_domain_set_grain_size", (DL_FUNC) RHugin_domain_set_grain_size, 2},
    {"RHugin_domain_get_grain_size", (DL_FUNC) RHugin_domain_get_grain_size, 1},

    /* 2.2 Domains: Creation and deletion */
    {"RHugin_new_domain", (DL_FUNC) RHugin_new_domain, 0},
    {"RHugin_domain_delete", (DL_FUNC) RHugin_domain_delete, 1},
    {"RHugin_domain_clone", (DL_FUNC) RHugin_domain_clone, 1},

    /* 2.3 Nodes: Creation and deletion */
    {"RHugin_domain_new_node", (DL_FUNC) RHugin_domain_new_node, 3},
    // SEXP RHugin_node_get_domain(SEXP Snode);
    {"RHugin_node_get_category", (DL_FUNC) RHugin_node_get_category, 1},
    {"RHugin_node_get_kind", (DL_FUNC) RHugin_node_get_kind, 1},
    // SEXP RHugin_node_set_category(SEXP Snode);
    {"RHugin_node_delete", (DL_FUNC) RHugin_node_delete, 1},
    {"RHugin_node_clone", (DL_FUNC) RHugin_node_clone, 1},

    /* 2.4 The links of the network */
    {"RHugin_node_add_parent", (DL_FUNC) RHugin_node_add_parent, 2},
    {"RHugin_node_remove_parent", (DL_FUNC) RHugin_node_remove_parent, 2},
    {"RHugin_node_switch_parent", (DL_FUNC) RHugin_node_switch_parent, 3},
    {"RHugin_node_reverse_edge", (DL_FUNC) RHugin_node_reverse_edge, 2},
    {"RHugin_node_get_parents", (DL_FUNC) RHugin_node_get_parents, 1},
    {"RHugin_node_get_children", (DL_FUNC) RHugin_node_get_children, 1},

    /* 2.4.1 The requisite parents and ancestors of decision nodes */
    {"RHugin_node_get_requisite_parents", (DL_FUNC) RHugin_node_get_requisite_parents, 1},
    {"RHugin_node_get_requisite_ancestors", (DL_FUNC) RHugin_node_get_requisite_ancestors, 1},

    /* 2.5 The number of states of a node */
    {"RHugin_node_set_number_of_states", (DL_FUNC) RHugin_node_set_number_of_states, 2},
    {"RHugin_node_get_number_of_states", (DL_FUNC) RHugin_node_get_number_of_states, 1},

    /* 2.6 The conditional probability and the utility table */
    {"RHugin_node_get_table", (DL_FUNC) RHugin_node_get_table, 1},
    {"RHugin_node_touch_table", (DL_FUNC) RHugin_node_touch_table, 1},
    {"RHugin_node_set_alpha", (DL_FUNC) RHugin_node_set_alpha, 3},
    {"RHugin_node_set_beta", (DL_FUNC) RHugin_node_set_beta, 4},
    {"RHugin_node_set_gamma", (DL_FUNC) RHugin_node_set_gamma, 3},
    {"RHugin_node_get_alpha", (DL_FUNC) RHugin_node_get_alpha, 2},
    {"RHugin_node_get_beta", (DL_FUNC) RHugin_node_get_beta, 3},
    {"RHugin_node_get_gamma", (DL_FUNC) RHugin_node_get_gamma, 2},

    /* 2.7 The name of a node */
    {"RHugin_node_set_name", (DL_FUNC) RHugin_node_set_name, 2},
    {"RHugin_node_get_name", (DL_FUNC) RHugin_node_get_name, 1},
    {"RHugin_domain_get_node_by_name", (DL_FUNC) RHugin_domain_get_node_by_name, 2},

    /* 2.8 Iterating through the nodes of a domain */
    {"RHugin_domain_get_first_node", (DL_FUNC) RHugin_domain_get_first_node, 1},
    {"RHugin_node_get_next", (DL_FUNC) RHugin_node_get_next, 1},

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
    {"RHugin_domain_save_as_kb", (DL_FUNC) RHugin_domain_save_as_kb, 3},
    {"RHugin_kb_load_domain", (DL_FUNC) RHugin_kb_load_domain, 2},

    /* 3 Object-Oriented Belief Networks and LIMIDs */
    /* 3.2 */
    {"RHugin_new_class_collection", (DL_FUNC) RHugin_new_class_collection, 0},
    {"RHugin_cc_new_class", (DL_FUNC) RHugin_cc_new_class, 1},
    {"RHugin_cc_get_members", (DL_FUNC) RHugin_cc_get_members, 1},
    {"RHugin_class_get_class_collection", (DL_FUNC) RHugin_class_get_class_collection, 1},

    /* 3.3 Deleting classes and class collections */
    {"RHugin_cc_delete", (DL_FUNC) RHugin_cc_delete, 1},
    {"RHugin_class_delete", (DL_FUNC) RHugin_class_delete, 1},

    /* 3.4 Naming classes */
    {"RHugin_class_set_name", (DL_FUNC) RHugin_class_set_name, 2},
    {"RHugin_class_get_name", (DL_FUNC) RHugin_class_get_name, 1},
    {"RHugin_cc_get_class_by_name", (DL_FUNC) RHugin_cc_get_class_by_name, 2},

    /* 3.5 Creating basic nodes */
    {"RHugin_class_new_node", (DL_FUNC) RHugin_class_new_node, 3},
    {"RHugin_node_get_home_class", (DL_FUNC) RHugin_node_get_home_class, 1},

    /* 3.6 Naming nodes */
    {"RHugin_class_get_node_by_name", (DL_FUNC) RHugin_class_get_node_by_name, 2},

    /* 3.7 The interface of a class */
    {"RHugin_node_add_to_input", (DL_FUNC) RHugin_node_add_to_input, 1},
    {"RHugin_class_get_inputs", (DL_FUNC) RHugin_class_get_inputs, 1},
    {"RHugin_node_remove_from_inputs", (DL_FUNC) RHugin_node_remove_from_inputs, 1},
    {"RHugin_node_add_to_outputs", (DL_FUNC) RHugin_node_add_to_outputs, 1},
    {"RHugin_class_get_outputs", (DL_FUNC) RHugin_class_get_outputs, 1},
    {"RHugin_node_remove_from_outputs", (DL_FUNC) RHugin_node_remove_from_outputs, 1},

    /* 3.8 Creating instances of classes */
    {"RHugin_class_new_instance", (DL_FUNC) RHugin_class_new_instance, 2},
    {"RHugin_node_get_instance_class", (DL_FUNC) RHugin_node_get_instance_class, 1},
    {"RHugin_class_get_instance", (DL_FUNC) RHugin_class_get_instance, 1},
    {"RHugin_node_get_master", (DL_FUNC) RHugin_node_get_master, 1},
    {"RHugin_node_get_instance", (DL_FUNC) RHugin_node_get_instance, 1},
    {"RHugin_node_get_output", (DL_FUNC) RHugin_node_get_output, 2},
    {"RHugin_node_substitute_class", (DL_FUNC) RHugin_node_substitute_class, 2},
    
    /* 3.9 Putting the pieces together */
    {"RHugin_node_set_input", (DL_FUNC) RHugin_node_set_input, 3},
    {"RHugin_node_get_input", (DL_FUNC) RHugin_node_get_input, 2},
    {"RHugin_node_unset_input", (DL_FUNC) RHugin_node_unset_input, 2},
    
    /* 3.10 Creating a runtime domain */
    {"RHugin_class_create_domain", (DL_FUNC) RHugin_class_create_domain, 1},
    {"RHugin_node_get_source", (DL_FUNC) RHugin_node_get_source, 1},

    /* 3.11 Node iterator */
    {"RHugin_class_get_first_node", (DL_FUNC) RHugin_class_get_first_node, 1},

    /* 3.13 Saving class collections as HKB files */
    {"RHugin_cc_save_as_kb", (DL_FUNC) RHugin_cc_save_as_kb, 3},
    {"RHugin_kb_load_class_collection", (DL_FUNC) RHugin_kb_load_class_collection, 2},
    {"RHugin_class_get_file_name", (DL_FUNC) RHugin_class_get_file_name, 1},

    /* 4 Dynamic Bayesian Network */ 
    /* 4.1 Temporal clones */
    {"RHugin_node_create_temporal_clone", (DL_FUNC) RHugin_node_create_temporal_clone, 1},
    {"RHugin_node_get_temporal_clone", (DL_FUNC) RHugin_node_get_temporal_clone, 1},
    {"RHugin_node_get_temporal_master", (DL_FUNC) RHugin_node_get_temporal_master, 1},

    /* 4.2 DBN runtime domains */
    {"RHugin_class_create_dbn_domain", (DL_FUNC) RHugin_class_create_dbn_domain, 2},

    /* 4.3 Inference in DBNs */
    {"RHugin_domain_triangulate_dbn", (DL_FUNC) RHugin_domain_triangulate_dbn, 2},
    {"RHugin_domain_move_dbn_window", (DL_FUNC) RHugin_domain_move_dbn_window, 2},
    {"RHugin_domain_get_dbn_window_offset", (DL_FUNC) RHugin_domain_get_dbn_window_offset, 1},
    {"RHugin_domain_initialize_dbn_window", (DL_FUNC) RHugin_domain_initialize_dbn_window, 1},

    /* 4.4 Prediction */
    {"RHugin_domain_compute_dbn_predictions", (DL_FUNC) RHugin_domain_compute_dbn_predictions, 2},
    {"RHugin_node_get_predicted_belief", (DL_FUNC) RHugin_node_get_predicted_belief, 3},
    {"RHugin_node_get_predicted_mean", (DL_FUNC) RHugin_node_get_predicted_mean, 2},
    {"RHugin_node_get_predicted_variance", (DL_FUNC) RHugin_node_get_predicted_variance, 2},
    {"RHugin_node_get_predicted_value", (DL_FUNC) RHugin_node_get_predicted_value, 2},

    /* 4.5 The Boyen-Koller approximation algorithm */
    {"RHugin_domain_triangulate_dbn_for_bk", (DL_FUNC) RHugin_domain_triangulate_dbn_for_bk, 2},
    {"RHugin_domain_is_triangulated_for_bk", (DL_FUNC) RHugin_domain_is_triangulated_for_bk, 1},

    /* 5.1 What is a table? */

    // SEXP RHugin_table_get_index_from_configuration(SEXP Stable, SEXP Sconfiguration);
    // SEXP RHugin_table_get_configuration_from_index(SEXP Stable, SEXP Sconfiguration, SEXP Sindex);

    /* 5.2 The nodes and the contents of a table */
    {"RHugin_table_get_nodes", (DL_FUNC) RHugin_table_get_nodes, 1},
    {"RHugin_table_get_data", (DL_FUNC) RHugin_table_get_data, 1},
    {"RHugin_table_set_data", (DL_FUNC) RHugin_table_set_data, 2},
    {"RHugin_table_get_mean", (DL_FUNC) RHugin_table_get_mean, 3},
    {"RHugin_table_get_covariance", (DL_FUNC) RHugin_table_get_covariance, 4},
    {"RHugin_table_get_variance", (DL_FUNC) RHugin_table_get_variance, 3},

    /* 5.3 Deleting tables */
    {"RHugin_table_delete", (DL_FUNC) RHugin_table_delete, 1},

    /* 5.4 The size of a table */
    {"RHugin_table_get_size", (DL_FUNC) RHugin_table_get_size, 1},
    {"RHugin_table_get_cg_size", (DL_FUNC) RHugin_table_get_cg_size, 1},

    /* 5.5 Rearranging the contents of a table */
    {"RHugin_table_reorder_nodes", (DL_FUNC) RHugin_table_reorder_nodes, 2},

    /* 6.1 Subtyping of discrete nodes */
    {"RHugin_node_set_subtype", (DL_FUNC) RHugin_node_set_subtype, 2},
    {"RHugin_node_get_subtype", (DL_FUNC) RHugin_node_get_subtype, 1},

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
    // SEXP RHugin_string_parse_expression(SEXP Sstrings, SEXP Smodel);
    // SEXP RHugin_expression_to_string(SEXP Sexpression);

    /* 6.4 Creating and maintaining models */
    {"RHugin_node_new_model", (DL_FUNC) RHugin_node_new_model, 2},
    {"RHugin_node_get_model", (DL_FUNC) RHugin_node_get_model, 1},
    {"RHugin_model_delete", (DL_FUNC) RHugin_model_delete, 1},
    {"RHugin_model_get_nodes", (DL_FUNC) RHugin_model_get_nodes, 1},
    {"RHugin_model_get_size", (DL_FUNC) RHugin_model_get_size, 1},
    {"RHugin_model_set_expression", (DL_FUNC) RHugin_model_set_expression, 2},
    {"RHugin_model_get_expression", (DL_FUNC) RHugin_model_get_expression, 1},

    /* 6.5 State labels */
    {"RHugin_node_set_state_label", (DL_FUNC) RHugin_node_set_state_label, 3},
    {"RHugin_node_get_state_label", (DL_FUNC) RHugin_node_get_state_label, 2},
    {"RHugin_node_get_state_index_from_label", (DL_FUNC) RHugin_node_get_state_index_from_label, 2},

    /* 6.6 State values */
    {"RHugin_node_set_state_value", (DL_FUNC) RHugin_node_set_state_value, 3},
    {"RHugin_node_get_state_value", (DL_FUNC) RHugin_node_get_state_value, 2},
    {"RHugin_node_get_state_index_from_value", (DL_FUNC) RHugin_node_get_state_index_from_value, 2},

    /* 6.8 Generating tables */
    {"RHugin_node_generate_table", (DL_FUNC) RHugin_node_generate_table, 1},
    {"RHugin_domain_generate_tables", (DL_FUNC) RHugin_domain_generate_tables, 1},
    // SEXP RHugin_class_generate_tables(SEXP Sclass);
    // SEXP RHugin_class_set_log_file(SEXP Sclass, SEXP Slog_file);

    /* 6.9 How the computations are done */
    {"RHugin_model_set_number_of_samples_per_interval", (DL_FUNC) RHugin_model_set_number_of_samples_per_interval, 2},
    {"RHugin_model_get_number_of_samples_per_interval", (DL_FUNC) RHugin_model_get_number_of_samples_per_interval, 1},

    /* 7.2 Compilation */
    {"RHugin_domain_compile", (DL_FUNC) RHugin_domain_compile, 1},
    {"RHugin_domain_is_compiled", (DL_FUNC) RHugin_domain_is_compiled, 1},

    /* 7.3 Triangulation */
    {"RHugin_domain_set_initial_triangulation", (DL_FUNC) RHugin_domain_set_initial_triangulation, 2},
    {"RHugin_domain_set_max_number_of_separators", (DL_FUNC) RHugin_domain_set_max_number_of_separators, 2},
    {"RHugin_domain_get_max_number_of_separators", (DL_FUNC) RHugin_domain_get_max_number_of_separators, 1},
    {"RHugin_domain_set_max_separator_size", (DL_FUNC) RHugin_domain_set_max_separator_size, 2},
    {"RHugin_domain_get_max_separator_size", (DL_FUNC) RHugin_domain_get_max_separator_size, 1},
    {"RHugin_domain_triangulate", (DL_FUNC) RHugin_domain_triangulate, 2},
    {"RHugin_domain_triangulate_with_order", (DL_FUNC) RHugin_domain_triangulate_with_order, 2},
    {"RHugin_domain_is_triangulated", (DL_FUNC) RHugin_domain_is_triangulated, 1},
    {"RHugin_domain_get_elimination_order", (DL_FUNC) RHugin_domain_get_elimination_order, 1},
    // SEXP RHugin_domain_parse_nodes(SEXP Sdomain, SEXP Sfile_name, SEXP Serror_fun, SEXP Sdata);
    // SEXP RHugin_class_parse_nodes(SEXP Sclass, SEXP Sfile_name, SEXP Serror_fun, SEXP Sdata);

    /* 7.4 Getting a compilation log */
    {"RHugin_domain_set_log_file", (DL_FUNC) RHugin_domain_set_log_file, 2},

    /* 7.5 Uncompilation */
    {"RHugin_domain_uncompile", (DL_FUNC) RHugin_domain_uncompile, 1},

    /* 7.6 Compression */
    {"RHugin_domain_compress", (DL_FUNC) RHugin_domain_compress, 1},
    {"RHugin_domain_is_compressed", (DL_FUNC) RHugin_domain_is_compressed, 1},

    /* 7.7 Approximation */
    {"RHugin_domain_approximate", (DL_FUNC) RHugin_domain_approximate, 2},
    {"RHugin_domain_get_approximation_constant", (DL_FUNC) RHugin_domain_get_approximation_constant, 1},

    /* 8.2 Junction trees */
    {"RHugin_domain_get_first_junction_tree", (DL_FUNC) RHugin_domain_get_first_junction_tree, 1},
    {"RHugin_jt_get_next", (DL_FUNC) RHugin_jt_get_next, 1},
    {"RHugin_clique_get_junction_tree", (DL_FUNC) RHugin_clique_get_junction_tree, 1},
    {"RHugin_node_get_junction_tree", (DL_FUNC) RHugin_node_get_junction_tree, 1},
    {"RHugin_jt_get_cliques", (DL_FUNC) RHugin_jt_get_cliques, 1},
    {"RHugin_jt_get_root", (DL_FUNC) RHugin_jt_get_root, 1},
    {"RHugin_jt_get_total_size", (DL_FUNC) RHugin_jt_get_total_size, 1},
    {"RHugin_jt_get_total_cg_size", (DL_FUNC) RHugin_jt_get_total_cg_size, 1},

    /* 8.3 Cliques */
    {"RHugin_clique_get_members", (DL_FUNC) RHugin_clique_get_members, 1},
    {"RHugin_clique_get_neighbors", (DL_FUNC) RHugin_clique_get_neighbors, 1},

    /* 9.2 Entering evidence */
    {"RHugin_node_select_state", (DL_FUNC) RHugin_node_select_state, 2},
    {"RHugin_node_enter_finding", (DL_FUNC) RHugin_node_enter_finding, 3},
    {"RHugin_node_enter_value", (DL_FUNC) RHugin_node_enter_value, 2},

    /* 9.3 Retracting evidence */
    {"RHugin_node_retract_findings", (DL_FUNC) RHugin_node_retract_findings, 1},
    {"RHugin_domain_retract_findings", (DL_FUNC) RHugin_domain_retract_findings, 1},

    /* 9.4 Determining independence properties */
    {"RHugin_domain_get_d_connected_nodes", (DL_FUNC) RHugin_domain_get_d_connected_nodes, 4},
    {"RHugin_domain_get_d_separated_nodes", (DL_FUNC) RHugin_domain_get_d_separated_nodes, 4},

    /* 9.5 Retreiving beliefs */
    {"RHugin_node_get_belief", (DL_FUNC) RHugin_node_get_belief, 2},
    {"RHugin_node_get_mean", (DL_FUNC) RHugin_node_get_mean, 1},
    {"RHugin_node_get_variance", (DL_FUNC) RHugin_node_get_variance, 1},
    {"RHugin_domain_get_marginal", (DL_FUNC) RHugin_domain_get_marginal, 2},
    {"RHugin_node_get_distribution", (DL_FUNC) RHugin_node_get_distribution, 1},

    /* 9.6 Retrieving expected utilities */
    {"RHugin_node_get_expected_utility", (DL_FUNC) RHugin_node_get_expected_utility, 2},
    {"RHugin_domain_get_expected_utility", (DL_FUNC) RHugin_domain_get_expected_utility, 1},

    /* 9.7 Computing function values */
    {"RHugin_node_get_value", (DL_FUNC) RHugin_node_get_value, 1},

    /* 9.8 Examining Evidence */
    {"RHugin_node_get_entered_finding", (DL_FUNC) RHugin_node_get_entered_finding, 2},
    {"RHugin_node_get_propagated_finding", (DL_FUNC) RHugin_node_get_propagated_finding, 2},
    {"RHugin_node_get_entered_value", (DL_FUNC) RHugin_node_get_entered_value, 1},
    {"RHugin_node_get_propagated_value", (DL_FUNC) RHugin_node_get_propagated_value, 1},
    {"RHugin_node_evidence_is_entered", (DL_FUNC) RHugin_node_evidence_is_entered, 1},
    {"RHugin_node_likelihood_is_entered", (DL_FUNC) RHugin_node_likelihood_is_entered, 1},
    {"RHugin_node_evidence_is_propagated", (DL_FUNC) RHugin_node_evidence_is_propagated, 1},
    {"RHugin_node_likelihood_is_propagated", (DL_FUNC) RHugin_node_likelihood_is_propagated, 1},

    /* 9.9 Case files */
    {"RHugin_domain_save_case", (DL_FUNC) RHugin_domain_save_case, 2},
    {"RHugin_domain_parse_case", (DL_FUNC) RHugin_domain_parse_case, 2},

    /* 10.2 Propagation */
    {"RHugin_domain_propagate", (DL_FUNC) RHugin_domain_propagate, 3},
    {"RHugin_jt_propagate", (DL_FUNC) RHugin_jt_propagate, 3},

    /* 10.3 Inference in LIMIDs: Computing optimal policies */
    {"RHugin_domain_update_policies", (DL_FUNC) RHugin_domain_update_policies, 1},

    /* 10.4 Conflict of evidence */
    {"RHugin_domain_get_conflict", (DL_FUNC) RHugin_domain_get_conflict, 1},
    {"RHugin_jt_get_conflict", (DL_FUNC) RHugin_jt_get_conflict, 1},

    /* 10.5 The normalization constant */
    {"RHugin_domain_get_normalization_constant", (DL_FUNC) RHugin_domain_get_normalization_constant, 1},
    {"RHugin_domain_get_log_normalization_constant", (DL_FUNC) RHugin_domain_get_log_normalization_constant, 1},

    /* 10.6 Initializing the inference engine */
    {"RHugin_domain_save_to_memory", (DL_FUNC) RHugin_domain_save_to_memory, 1},
    {"RHugin_domain_reset_inference_engine", (DL_FUNC) RHugin_domain_reset_inference_engine, 1},
    {"RHugin_domain_initialize", (DL_FUNC) RHugin_domain_initialize, 1},

    /* 10.7 Querying the state of the inference engine */
    {"RHugin_domain_equilibrium_is", (DL_FUNC) RHugin_domain_equilibrium_is, 2},
    {"RHugin_jt_equilibrium_is", (DL_FUNC) RHugin_jt_equilibrium_is, 2},
    {"RHugin_domain_evidence_mode_is", (DL_FUNC) RHugin_domain_evidence_mode_is, 2},
    {"RHugin_jt_evidence_mode_is", (DL_FUNC) RHugin_jt_evidence_mode_is, 2},
    {"RHugin_domain_evidence_is_propagated", (DL_FUNC) RHugin_domain_evidence_is_propagated, 1},
    {"RHugin_jt_evidence_is_propagated", (DL_FUNC) RHugin_jt_evidence_is_propagated, 1},
    {"RHugin_domain_likelihood_is_propagated", (DL_FUNC) RHugin_domain_likelihood_is_propagated, 1},
    {"RHugin_jt_likelihood_is_propagated", (DL_FUNC) RHugin_jt_likelihood_is_propagated, 1},
    {"RHugin_domain_cg_evidence_is_propagated", (DL_FUNC) RHugin_domain_cg_evidence_is_propagated, 1},
    {"RHugin_jt_cg_evidence_is_propagated", (DL_FUNC) RHugin_jt_cg_evidence_is_propagated, 1},
    {"RHugin_domain_evidence_to_propagate", (DL_FUNC) RHugin_domain_evidence_to_propagate, 1},
    {"RHugin_jt_evidence_to_propagate", (DL_FUNC) RHugin_jt_evidence_to_propagate, 1},
    {"RHugin_node_evidence_to_propagate", (DL_FUNC) RHugin_node_evidence_to_propagate, 1},
    {"RHugin_domain_tables_to_propagate", (DL_FUNC) RHugin_domain_tables_to_propagate, 1},
    {"RHugin_jt_tables_to_propagate", (DL_FUNC) RHugin_jt_tables_to_propagate, 1},

    /* 10.8 Simulation */
    {"RHugin_domain_simulate", (DL_FUNC) RHugin_domain_simulate, 1},
    {"RHugin_node_get_sampled_state", (DL_FUNC) RHugin_node_get_sampled_state, 1},
    {"RHugin_node_get_sampled_value", (DL_FUNC) RHugin_node_get_sampled_value, 1},
    {"RHugin_node_get_sampled_utility", (DL_FUNC) RHugin_node_get_sampled_utility, 1},
    {"RHugin_domain_seed_random", (DL_FUNC) RHugin_domain_seed_random, 2},
    {"RHugin_domain_get_uniform_deviate", (DL_FUNC) RHugin_domain_get_uniform_deviate, 1},
    {"RHugin_domain_get_normal_deviate", (DL_FUNC) RHugin_domain_get_normal_deviate, 3},

    /* 10.9 Value of information analysis */
    {"RHugin_node_get_entropy", (DL_FUNC) RHugin_node_get_entropy, 1},
    {"RHugin_node_get_mutual_information", (DL_FUNC) RHugin_node_get_mutual_information, 2},

    /* Section 10.10 Sensitivity analyis */
    {"RHugin_node_compute_sensitivity_data", (DL_FUNC) RHugin_node_compute_sensitivity_data, 2},
    {"RHugin_node_get_sensitivity_constants", (DL_FUNC) RHugin_node_get_sensitivity_constants, 2},
    {"RHugin_domain_get_sensitivity_set", (DL_FUNC) RHugin_domain_get_sensitivity_set, 1},
    {"RHugin_domain_compute_sensitivity_data", (DL_FUNC) RHugin_domain_compute_sensitivity_data, 3},
    {"RHugin_node_get_sensitivity_constants_by_output", (DL_FUNC) RHugin_node_get_sensitivity_constants_by_output, 3},
    {"RHugin_domain_get_sensitivity_set_by_output", (DL_FUNC) RHugin_domain_get_sensitivity_set_by_output, 2},

    /* 10.11 Most probable configurations */
    {"RHugin_domain_find_map_configurations", (DL_FUNC) RHugin_domain_find_map_configurations, 3},
    {"RHugin_domain_get_number_of_map_configurations", (DL_FUNC) RHugin_domain_get_number_of_map_configurations, 1},
    {"RHugin_domain_get_map_configuration", (DL_FUNC) RHugin_domain_get_map_configuration, 3},
    {"RHugin_domain_get_probability_of_map_configuration", (DL_FUNC) RHugin_domain_get_probability_of_map_configuration, 2},

    /* 11.1 Experience counts and fading factors */
    {"RHugin_node_get_experience_table", (DL_FUNC) RHugin_node_get_experience_table, 1},
    {"RHugin_node_has_experience_table", (DL_FUNC) RHugin_node_has_experience_table, 1},
    {"RHugin_node_get_fading_table", (DL_FUNC) RHugin_node_get_fading_table, 1},
    {"RHugin_node_has_fading_table", (DL_FUNC) RHugin_node_has_fading_table, 1},

    /* 11.2 Updating tables */
    {"RHugin_domain_adapt", (DL_FUNC) RHugin_domain_adapt, 1},

    /* 12.1 Data */
    {"RHugin_domain_set_number_of_cases", (DL_FUNC) RHugin_domain_set_number_of_cases, 2},
    {"RHugin_domain_new_case", (DL_FUNC) RHugin_domain_new_case, 1},
    {"RHugin_domain_get_number_of_cases", (DL_FUNC) RHugin_domain_get_number_of_cases, 1},
    {"RHugin_node_set_case_state", (DL_FUNC) RHugin_node_set_case_state, 3},
    {"RHugin_node_get_case_state", (DL_FUNC) RHugin_node_get_case_state, 2},
    {"RHugin_node_set_case_value", (DL_FUNC) RHugin_node_set_case_value, 3},
    {"RHugin_node_get_case_value", (DL_FUNC) RHugin_node_get_case_value, 2},
    {"RHugin_node_unset_case", (DL_FUNC) RHugin_node_unset_case, 2},
    {"RHugin_node_case_is_set", (DL_FUNC) RHugin_node_case_is_set, 2},
    {"RHugin_domain_set_case_count", (DL_FUNC) RHugin_domain_set_case_count, 3},
    {"RHugin_domain_get_case_count", (DL_FUNC) RHugin_domain_get_case_count, 2},
    {"RHugin_domain_enter_case", (DL_FUNC) RHugin_domain_enter_case, 2},

    /* 12.2 Scoring of graphical models */
    {"RHugin_domain_get_log_likelihood", (DL_FUNC) RHugin_domain_get_log_likelihood, 1},
    {"RHugin_domain_get_AIC", (DL_FUNC) RHugin_domain_get_AIC, 1},
    {"RHugin_domain_get_BIC", (DL_FUNC) RHugin_domain_get_BIC, 1},

    /* 12.3 Data files */
    {"RHugin_domain_parse_cases", (DL_FUNC) RHugin_domain_parse_cases, 2},
    {"RHugin_domain_save_cases", (DL_FUNC) RHugin_domain_save_cases, 7},

    /* 12.4 Learning network structure */
    {"RHugin_domain_learn_structure", (DL_FUNC) RHugin_domain_learn_structure, 1},
    {"RHugin_domain_set_significance_level", (DL_FUNC) RHugin_domain_set_significance_level, 2},
    {"RHugin_domain_get_significance_level", (DL_FUNC) RHugin_domain_get_significance_level, 1},

    /* 12.5 Domain knowledge */
    {"RHugin_node_set_edge_constraint", (DL_FUNC) RHugin_node_set_edge_constraint, 3},
    {"RHugin_node_get_edge_constraint", (DL_FUNC) RHugin_node_get_edge_constraint, 2},

    /* 12.6 Learning conditional probability tables */
    {"RHugin_domain_learn_tables", (DL_FUNC) RHugin_domain_learn_tables, 1},
    {"RHugin_domain_set_log_likelihood_tolerance", (DL_FUNC) RHugin_domain_set_log_likelihood_tolerance, 2},
    {"RHugin_domain_get_log_likelihood_tolerance", (DL_FUNC) RHugin_domain_get_log_likelihood_tolerance, 1},
    {"RHugin_domain_set_max_number_of_em_iterations", (DL_FUNC) RHugin_domain_set_max_number_of_em_iterations, 2},
    {"RHugin_domain_get_max_number_of_em_iterations", (DL_FUNC) RHugin_domain_get_max_number_of_em_iterations, 1},
    // SEXP RHugin_domain_learn_class_tables(SEXP Sdomain);

    /* 13.8 parsing NET files */
    {"RHugin_net_parse_domain", (DL_FUNC) RHugin_net_parse_domain, 1},
    {"RHugin_net_parse_classes", (DL_FUNC) RHugin_net_parse_classes, 1},
    {"RHugin_domain_save_as_net", (DL_FUNC) RHugin_domain_save_as_net, 2},

    /* 13.9 Saving class collections, classes, and domains as NET files */
    // SEXP RHugin_cc_save_as_net(SEXP Scc, SEXP Sfile_name);
    // SEXP RHugin_class_save_as_net(SEXP Sclass, SEXP Sfile_name);
    {"RHugin_class_save_as_net", (DL_FUNC) RHugin_class_save_as_net, 2},
    // SEXP RHugin_domain_save_as_net(SEXP Sdomain, SEXP Sfile_name);
    // SEXP RHugin_class_get_file_name(SEXP Sclass);
    // SEXP RHugin_domain_get_file_name(SEXP Sdomain);

    /* 14.1 The label of a node */
    {"RHugin_node_set_label", (DL_FUNC) RHugin_node_set_label, 2},
    {"RHugin_node_get_label", (DL_FUNC) RHugin_node_get_label, 1},

    /*  14.2 The position of a node */
    {"RHugin_node_set_position", (DL_FUNC) RHugin_node_set_position, 2},
    {"RHugin_node_get_position", (DL_FUNC) RHugin_node_get_position, 1},

    /* 14.3 The size of a node */
    {"RHugin_domain_set_node_size", (DL_FUNC) RHugin_domain_set_node_size, 2},
    {"RHugin_domain_get_node_size", (DL_FUNC) RHugin_domain_get_node_size, 1},
    // SEXP RHugin_class_set_node_size(SEXP Sclass, SEXP Ssize);
    // SEXP RHugin_class_get_node_size(SEXP Sclass);    
    {NULL, NULL, 0}};

  R_registerRoutines(info, NULL, dotCallMethods, NULL, NULL);


  RHugin_domain_tag = install("RHUGIN_DOMAIN_TAG");
  R_PreserveObject(RHugin_domain_tag);
  RHugin_node_tag = install("RHUGIN_NODE_TAG");
  R_PreserveObject(RHugin_node_tag);
  RHugin_table_tag = install("RHUGIN_TABLE_TAG");
  R_PreserveObject(RHugin_table_tag);
  RHugin_expression_tag = install("RHUGIN_EXPRESSION_TAG");
  R_PreserveObject(RHugin_expression_tag);
  RHugin_model_tag = install("RHUGIN_MODEL_TAG");
  R_PreserveObject(RHugin_model_tag);
  RHugin_junction_tree_tag = install("RHUGIN_JUNCTION_TREE_TAG");
  R_PreserveObject(RHugin_junction_tree_tag);
  RHugin_clique_tag = install("RHUGIN_CLIQUE_TAG");
  R_PreserveObject(RHugin_clique_tag);
  RHugin_class_tag = install("RHUGIN_CLASS_TAG");
  R_PreserveObject(RHugin_class_tag);
  RHugin_class_collection_tag = install("RHUGIN_CLASS_COLLECTION_TAG");
  R_PreserveObject(RHugin_class_collection_tag);

  RHUGIN_ERROR = mkChar("error");
  R_PreserveObject(RHUGIN_ERROR);

  RHUGIN_CHANCE = mkChar("chance");
  R_PreserveObject(RHUGIN_CHANCE);
  RHUGIN_DECISION = mkChar("decision");
  R_PreserveObject(RHUGIN_DECISION);
  RHUGIN_UTILITY = mkChar("utility");
  R_PreserveObject(RHUGIN_UTILITY);
  RHUGIN_FUNCTION = mkChar("function");
  R_PreserveObject(RHUGIN_FUNCTION);
  RHUGIN_INSTANCE = mkChar("instance");
  R_PreserveObject(RHUGIN_INSTANCE);

  RHUGIN_DISCRETE = mkChar("discrete");
  R_PreserveObject(RHUGIN_DISCRETE);
  RHUGIN_CONTINUOUS = mkChar("continuous");
  R_PreserveObject(RHUGIN_CONTINUOUS);
  RHUGIN_OTHER = mkChar("other");
  R_PreserveObject(RHUGIN_OTHER);

  RHUGIN_LABELED = mkChar("labeled");
  R_PreserveObject(RHUGIN_LABELED);
  RHUGIN_BOOLEAN = mkChar("boolean");
  R_PreserveObject(RHUGIN_BOOLEAN);
  RHUGIN_NUMBERED = mkChar("numbered");
  R_PreserveObject(RHUGIN_NUMBERED);
  RHUGIN_INTERVAL = mkChar("interval");
  R_PreserveObject(RHUGIN_INTERVAL);

  RHUGIN_TM_CLIQUE_SIZE = mkChar("clique.size");
  R_PreserveObject(RHUGIN_TM_CLIQUE_SIZE);
  RHUGIN_TM_CLIQUE_WEIGHT = mkChar("clique.weight");
  R_PreserveObject(RHUGIN_TM_CLIQUE_WEIGHT);
  RHUGIN_TM_FILL_IN_SIZE = mkChar("fill.in.size");
  R_PreserveObject(RHUGIN_TM_FILL_IN_SIZE);
  RHUGIN_TM_FILL_IN_WEIGHT = mkChar("fill.in.weight");
  R_PreserveObject(RHUGIN_TM_FILL_IN_WEIGHT);
  RHUGIN_TM_BEST_GREEDY = mkChar("best.greedy");
  R_PreserveObject(RHUGIN_TM_BEST_GREEDY);
  RHUGIN_TM_TOTAL_WEIGHT = mkChar("total.weight");
  R_PreserveObject(RHUGIN_TM_TOTAL_WEIGHT);

  RHUGIN_EQUILIBRIUM_SUM = mkChar("sum");
  R_PreserveObject(RHUGIN_EQUILIBRIUM_SUM);
  RHUGIN_EQUILIBRIUM_MAX = mkChar("max");
  R_PreserveObject(RHUGIN_EQUILIBRIUM_MAX);

  RHUGIN_MODE_NORMAL = mkChar("normal");
  R_PreserveObject(RHUGIN_MODE_NORMAL);
  RHUGIN_MODE_FAST_RETRACTION = mkChar("fast");
  R_PreserveObject(RHUGIN_MODE_FAST_RETRACTION);

  RHUGIN_CONSTRAINT_NONE = mkChar("none");
  R_PreserveObject(RHUGIN_CONSTRAINT_NONE);
  RHUGIN_CONSTRAINT_EDGE_REQUIRED = mkChar("edge_required");
  R_PreserveObject(RHUGIN_CONSTRAINT_EDGE_REQUIRED);
  RHUGIN_CONSTRAINT_EDGE_FORBIDDEN = mkChar("edge_forbidden");
  R_PreserveObject(RHUGIN_CONSTRAINT_EDGE_FORBIDDEN);
  RHUGIN_CONSTRAINT_FORWARD_EDGE_REQUIRED = mkChar("forward_edge_required");
  R_PreserveObject(RHUGIN_CONSTRAINT_FORWARD_EDGE_REQUIRED);
  RHUGIN_CONSTRAINT_BACKWARD_EDGE_REQUIRED = mkChar("backward_edge_required");
  R_PreserveObject(RHUGIN_CONSTRAINT_BACKWARD_EDGE_REQUIRED);
  RHUGIN_CONSTRAINT_FORWARD_EDGE_FORBIDDEN = mkChar("forward_edge_forbidden");
  R_PreserveObject(RHUGIN_CONSTRAINT_FORWARD_EDGE_FORBIDDEN);
  RHUGIN_CONSTRAINT_BACKWARD_EDGE_FORBIDDEN = mkChar("backward_edge_forbiddden");
  R_PreserveObject(RHUGIN_CONSTRAINT_BACKWARD_EDGE_FORBIDDEN);
}


