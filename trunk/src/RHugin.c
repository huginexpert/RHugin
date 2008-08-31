#include "RHugin.h"
#include "RHuginLink.h"

SEXP RHugin_domain_tag;
SEXP RHugin_node_tag;
SEXP RHugin_table_tag;
SEXP RHugin_expression_tag;
SEXP RHugin_model_tag;
SEXP RHugin_junction_tree_tag;
SEXP RHugin_clique_tag;


h_domain_t domainPointerFromSEXP(SEXP Sdomain)
{
  if(R_ExternalPtrAddr(Sdomain) == NULL)
    error("NULL value passed as domain");

  if(TYPEOF(Sdomain) != EXTPTRSXP || R_ExternalPtrTag(Sdomain) != RHugin_domain_tag)
    error("the domain argument does not appear to be a valid Hugin domain");

  return (h_domain_t) R_ExternalPtrAddr(Sdomain);
}


h_node_t nodePointerFromSEXP(SEXP Snode)
{
  if(R_ExternalPtrAddr(Snode) == NULL)
    error("NULL value passed as node");

  if(TYPEOF(Snode) != EXTPTRSXP || R_ExternalPtrTag(Snode) != RHugin_node_tag)
    error("the node argument does not appear to be a valid Hugin node");

  return (h_node_t) R_ExternalPtrAddr(Snode);
}


h_table_t tablePointerFromSEXP(SEXP Stable)
{
  if(R_ExternalPtrAddr(Stable) == NULL)
    error("NULL value passed as table");

  if(TYPEOF(Stable) != EXTPTRSXP || R_ExternalPtrTag(Stable) != RHugin_table_tag)
    error("the table argument does not appear to be a valid Hugin table");

  return (h_table_t) R_ExternalPtrAddr(Stable);
}


h_expression_t expressionPointerFromSEXP(SEXP Sexpression)
{
  if(R_ExternalPtrAddr(Sexpression) == NULL)
    error("NULL value passed as expression");

  if(TYPEOF(Sexpression) != EXTPTRSXP || R_ExternalPtrTag(Sexpression) != RHugin_expression_tag)
    error("the expression argument does not appear to be a valid Hugin expression");

  return (h_expression_t) R_ExternalPtrAddr(Sexpression);
}


h_model_t modelPointerFromSEXP(SEXP Smodel)
{
  if(R_ExternalPtrAddr(Smodel) == NULL)
    error("NULL value passed as model");

  if(TYPEOF(Smodel) != EXTPTRSXP || R_ExternalPtrTag(Smodel) != RHugin_model_tag)
    error("the model argument does not appear to be a valid Hugin model");

  return (h_model_t) R_ExternalPtrAddr(Smodel);
}


h_junction_tree_t jtPointerFromSEXP(SEXP Sjt)
{
  if(R_ExternalPtrAddr(Sjt) == NULL)
    error("NULL value passed as junction tree");

  if(TYPEOF(Sjt) != EXTPTRSXP || R_ExternalPtrTag(Sjt) != RHugin_junction_tree_tag)
    error("the junction tree argument does not appear to be a valid Hugin junction tree");

  return (h_junction_tree_t) R_ExternalPtrAddr(Sjt);
}


h_clique_t cliquePointerFromSEXP(SEXP Sclique)
{
  if(R_ExternalPtrAddr(Sclique) == NULL)
    error("NULL value passed as clique");

  if(TYPEOF(Sclique) != EXTPTRSXP || R_ExternalPtrTag(Sclique) != RHugin_clique_tag)
    error("the clique argument does not appear to be a valid Hugin clique");

  return (h_clique_t) R_ExternalPtrAddr(Sclique);
}


void R_init_RHugin(DllInfo *info)
{
  R_CallMethodDef dotCallMethods[] = {
    {"RHugin_error_code", (DL_FUNC) RHugin_error_code, 0},
    {"RHugin_error_name", (DL_FUNC) RHugin_error_name, 1},
    {"RHugin_error_description", (DL_FUNC) RHugin_error_description, 1},
    {"RHugin_domain_set_concurrency_level", (DL_FUNC) RHugin_domain_set_concurrency_level, 2},
    {"RHugin_domain_get_concurrency_level", (DL_FUNC) RHugin_domain_get_concurrency_level, 1},
    {"RHugin_domain_set_grain_size", (DL_FUNC) RHugin_domain_set_grain_size, 2},
    {"RHugin_domain_get_grain_size", (DL_FUNC) RHugin_domain_get_grain_size, 1},
    {"RHugin_new_domain", (DL_FUNC) RHugin_new_domain, 0},
    {"RHugin_domain_delete", (DL_FUNC) RHugin_domain_delete, 1},
    {"RHugin_domain_clone", (DL_FUNC) RHugin_domain_clone, 1},
    {"RHugin_domain_new_node", (DL_FUNC) RHugin_domain_new_node, 3},
    /*{"RHugin_node_get_domain", (DL_FUNC) RHugin_node_get_domain, 1},*/
    {"RHugin_node_get_category", (DL_FUNC) RHugin_node_get_category, 1},
    {"RHugin_node_get_kind", (DL_FUNC) RHugin_node_get_kind, 1},
    {"RHugin_node_delete", (DL_FUNC) RHugin_node_delete, 1},
    {"RHugin_node_clone", (DL_FUNC) RHugin_node_clone, 1},
    {"RHugin_node_add_parent", (DL_FUNC) RHugin_node_add_parent, 2},
    {"RHugin_node_remove_parent", (DL_FUNC) RHugin_node_remove_parent, 2},
    {"RHugin_node_switch_parent", (DL_FUNC) RHugin_node_switch_parent, 3},
    {"RHugin_node_reverse_edge", (DL_FUNC) RHugin_node_reverse_edge, 2},
    {"RHugin_node_get_parents", (DL_FUNC) RHugin_node_get_parents, 1},
    {"RHugin_node_get_children", (DL_FUNC) RHugin_node_get_children, 1},
    {"RHugin_node_set_number_of_states", (DL_FUNC) RHugin_node_set_number_of_states, 2},
    {"RHugin_node_get_number_of_states", (DL_FUNC) RHugin_node_get_number_of_states, 1},
    {"RHugin_node_get_table", (DL_FUNC) RHugin_node_get_table, 1},
    {"RHugin_node_touch_table", (DL_FUNC) RHugin_node_touch_table, 1},
    {"RHugin_node_set_alpha", (DL_FUNC) RHugin_node_set_alpha, 3},
    {"RHugin_node_set_beta", (DL_FUNC) RHugin_node_set_beta, 4},
    {"RHugin_node_set_gamma", (DL_FUNC) RHugin_node_set_gamma, 3},
    {"RHugin_node_get_alpha", (DL_FUNC) RHugin_node_get_alpha, 2},
    {"RHugin_node_get_beta", (DL_FUNC) RHugin_node_get_beta, 3},
    {"RHugin_node_get_gamma", (DL_FUNC) RHugin_node_get_gamma, 2},
    {"RHugin_node_set_name", (DL_FUNC) RHugin_node_set_name, 2},
    {"RHugin_node_get_name", (DL_FUNC) RHugin_node_get_name, 1},
    {"RHugin_domain_get_node_by_name", (DL_FUNC) RHugin_domain_get_node_by_name, 2},
    {"RHugin_domain_get_first_node", (DL_FUNC) RHugin_domain_get_first_node, 1},
    {"RHugin_node_get_next", (DL_FUNC) RHugin_node_get_next, 1},
    {"RHugin_domain_save_as_kb", (DL_FUNC) RHugin_domain_save_as_kb, 3},
    {"RHugin_kb_load_domain", (DL_FUNC) RHugin_kb_load_domain, 2},
    {"RHugin_table_get_nodes", (DL_FUNC) RHugin_table_get_nodes, 1},
    {"RHugin_table_get_data", (DL_FUNC) RHugin_table_get_data, 1},
    {"RHugin_table_set_data", (DL_FUNC) RHugin_table_set_data, 2},
    {"RHugin_table_get_mean", (DL_FUNC) RHugin_table_get_mean, 3},
    {"RHugin_table_get_covariance", (DL_FUNC) RHugin_table_get_covariance, 4},
    {"RHugin_table_get_variance", (DL_FUNC) RHugin_table_get_variance, 3},
    {"RHugin_table_delete", (DL_FUNC) RHugin_table_delete, 1},
    {"RHugin_table_get_size", (DL_FUNC) RHugin_table_get_size, 1},
    {"RHugin_table_reorder_nodes", (DL_FUNC) RHugin_table_reorder_nodes, 2},
    {"RHugin_node_set_subtype", (DL_FUNC) RHugin_node_set_subtype, 2},
    {"RHugin_node_get_subtype", (DL_FUNC) RHugin_node_get_subtype, 1},
    {"RHugin_node_make_expression", (DL_FUNC) RHugin_node_make_expression, 1},
    {"RHugin_label_make_expression", (DL_FUNC) RHugin_label_make_expression, 1},
    {"RHugin_boolean_make_expression", (DL_FUNC) RHugin_boolean_make_expression, 1},
    {"RHugin_number_make_expression", (DL_FUNC) RHugin_number_make_expression, 1},
    {"RHugin_make_composite_expression", (DL_FUNC) RHugin_make_composite_expression, 2},
    {"RHugin_expression_is_composite", (DL_FUNC) RHugin_expression_is_composite, 1},
    {"RHugin_expression_get_operator", (DL_FUNC) RHugin_expression_get_operator, 1},
    {"RHugin_expression_get_operands", (DL_FUNC) RHugin_expression_get_operands, 1},
    {"RHugin_expression_get_node", (DL_FUNC) RHugin_expression_get_node, 1},
    {"RHugin_expression_get_number", (DL_FUNC) RHugin_expression_get_number, 1},
    {"RHugin_expression_get_label", (DL_FUNC) RHugin_expression_get_label, 1},
    {"RHugin_expression_clone", (DL_FUNC) RHugin_expression_clone, 1},
    {"RHugin_expression_delete", (DL_FUNC) RHugin_expression_delete, 1},
    /*{"RHugin_string_parse_expression", (DL_FUNC) RHugin_string_parse_expression, 4},*/
    /*{"RHugin_expression_to_string", (DL_FUNC) RHugin_expression_to_string, 1},*/
    {"RHugin_node_new_model", (DL_FUNC) RHugin_node_new_model, 2},
    {"RHugin_node_get_model", (DL_FUNC) RHugin_node_get_model, 1},
    {"RHugin_model_delete", (DL_FUNC) RHugin_model_delete, 1},
    {"RHugin_model_get_nodes", (DL_FUNC) RHugin_model_get_nodes, 1},
    {"RHugin_model_get_size", (DL_FUNC) RHugin_model_get_size, 1},
    {"RHugin_model_set_expression", (DL_FUNC) RHugin_model_set_expression, 3},
    {"RHugin_model_get_expression", (DL_FUNC) RHugin_model_get_expression, 2},
    {"RHugin_node_set_state_label", (DL_FUNC) RHugin_node_set_state_label, 3},
    {"RHugin_node_get_state_label", (DL_FUNC) RHugin_node_get_state_label, 2},
    {"RHugin_node_get_state_index_from_label", (DL_FUNC) RHugin_node_get_state_index_from_label, 2},
    {"RHugin_node_set_state_value", (DL_FUNC) RHugin_node_set_state_value, 3},
    {"RHugin_node_get_state_value", (DL_FUNC) RHugin_node_get_state_value, 2},
    {"RHugin_node_get_state_index_from_value", (DL_FUNC) RHugin_node_get_state_index_from_value, 2},
    {"RHugin_node_generate_table", (DL_FUNC) RHugin_node_generate_table, 1},
    {"RHugin_domain_generate_tables", (DL_FUNC) RHugin_domain_generate_tables, 1},
    /*{"RHugin_class_generate_tables", (DL_FUNC) RHugin_class_generate_tables, 1},*/
    /*{"RHugin_class_set_log_file", (DL_FUNC) RHugin_class_set_log_file, 2},*/
    {"RHugin_model_set_number_of_samples_per_interval", (DL_FUNC) RHugin_model_set_number_of_samples_per_interval, 2},
    {"RHugin_model_get_number_of_samples_per_interval", (DL_FUNC) RHugin_model_get_number_of_samples_per_interval, 1},
    {"RHugin_domain_compile", (DL_FUNC) RHugin_domain_compile, 1},
    {"RHugin_domain_is_compiled", (DL_FUNC) RHugin_domain_is_compiled, 1},
    {"RHugin_domain_set_max_number_of_separators", (DL_FUNC) RHugin_domain_set_max_number_of_separators, 2},
    {"RHugin_domain_get_max_number_of_separators", (DL_FUNC) RHugin_domain_get_max_number_of_separators, 1},
    {"RHugin_domain_triangulate", (DL_FUNC) RHugin_domain_triangulate, 2},
    {"RHugin_domain_triangulate_with_order", (DL_FUNC) RHugin_domain_triangulate_with_order, 2},
    {"RHugin_domain_get_elimination_order", (DL_FUNC) RHugin_domain_get_elimination_order, 1},
    /*{"RHugin_domain_parse_nodes", (DL_FUNC) RHugin_domain_parse_nodes, 4},*/
    /*{"RHugin_class_parse_nodes", (DL_FUNC) RHugin_class_parse_nodes, 4},*/
    /*{"RHugin_domain_set_log_file", (DL_FUNC) RHugin_domain_set_log_file, 2},*/
    {"RHugin_domain_uncompile", (DL_FUNC) RHugin_domain_uncompile, 1},
    {"RHugin_domain_compress", (DL_FUNC) RHugin_domain_compress, 1},
    {"RHugin_domain_is_compressed", (DL_FUNC) RHugin_domain_is_compressed, 1},
    {"RHugin_domain_approximate", (DL_FUNC) RHugin_domain_approximate, 2},
    {"RHugin_domain_get_approximation_constant", (DL_FUNC) RHugin_domain_get_approximation_constant, 1},
    {"RHugin_domain_get_first_junction_tree", (DL_FUNC) RHugin_domain_get_first_junction_tree, 1},
    {"RHugin_jt_get_next", (DL_FUNC) RHugin_jt_get_next, 1},
    {"RHugin_clique_get_junction_tree", (DL_FUNC) RHugin_clique_get_junction_tree, 1},
    {"RHugin_node_get_junction_tree", (DL_FUNC) RHugin_node_get_junction_tree, 1},
    {"RHugin_jt_get_cliques", (DL_FUNC) RHugin_jt_get_cliques, 1},
    {"RHugin_jt_get_root", (DL_FUNC) RHugin_jt_get_root, 1},
    {"RHugin_clique_get_members", (DL_FUNC) RHugin_clique_get_members, 1},
    {"RHugin_clique_get_neighbors", (DL_FUNC) RHugin_clique_get_neighbors, 1},
    {"RHugin_node_select_state", (DL_FUNC) RHugin_node_select_state, 2},
    {"RHugin_node_enter_finding", (DL_FUNC) RHugin_node_enter_finding, 3},
    {"RHugin_node_enter_value", (DL_FUNC) RHugin_node_enter_value, 2},
    {"RHugin_node_retract_findings", (DL_FUNC) RHugin_node_retract_findings, 1},
    {"RHugin_domain_retract_findings", (DL_FUNC) RHugin_domain_retract_findings, 1},
    {"RHugin_domain_get_d_connected_nodes", (DL_FUNC) RHugin_domain_get_d_connected_nodes, 4},
    {"RHugin_domain_get_d_separated_nodes", (DL_FUNC) RHugin_domain_get_d_separated_nodes, 4},
    {"RHugin_node_get_belief", (DL_FUNC) RHugin_node_get_belief, 2},
    {"RHugin_node_get_mean", (DL_FUNC) RHugin_node_get_mean, 1},
    {"RHugin_node_get_variance", (DL_FUNC) RHugin_node_get_variance, 1},
    {"RHugin_domain_get_marginal", (DL_FUNC) RHugin_domain_get_marginal, 2},
    {"RHugin_node_get_distribution", (DL_FUNC) RHugin_node_get_distribution, 1},
    {"RHugin_node_get_expected_utility", (DL_FUNC) RHugin_node_get_expected_utility, 2},
    {"RHugin_node_get_entered_finding", (DL_FUNC) RHugin_node_get_entered_finding, 2},
    {"RHugin_node_get_propagated_finding", (DL_FUNC) RHugin_node_get_propagated_finding, 2},
    {"RHugin_node_get_entered_value", (DL_FUNC) RHugin_node_get_entered_value, 1},
    {"RHugin_node_get_propagated_value", (DL_FUNC) RHugin_node_get_propagated_value, 1},
    {"RHugin_node_evidence_is_entered", (DL_FUNC) RHugin_node_evidence_is_entered, 1},
    {"RHugin_node_likelihood_is_entered", (DL_FUNC) RHugin_node_likelihood_is_entered, 1},
    {"RHugin_node_evidence_is_propagated", (DL_FUNC) RHugin_node_evidence_is_propagated, 1},
    {"RHugin_node_likelihood_is_propagated", (DL_FUNC) RHugin_node_likelihood_is_propagated, 1},
    {"RHugin_domain_save_case", (DL_FUNC) RHugin_domain_save_case, 2},
    /*{"RHugin_domain_parse_case", (DL_FUNC) RHugin_domain_parse_case, 4},*/
    {"RHugin_domain_propagate", (DL_FUNC) RHugin_domain_propagate, 3},
    {"RHugin_jt_propagate", (DL_FUNC) RHugin_jt_propagate, 3},
    {"RHugin_domain_get_conflict", (DL_FUNC) RHugin_domain_get_conflict, 1},
    {"RHugin_jt_get_conflict", (DL_FUNC) RHugin_jt_get_conflict, 1},
    {"RHugin_domain_reset_inference_engine", (DL_FUNC) RHugin_domain_reset_inference_engine, 1},
    {"RHugin_domain_get_normalization_constant", (DL_FUNC) RHugin_domain_get_normalization_constant, 1},
    {"RHugin_domain_get_log_normalization_constant", (DL_FUNC) RHugin_domain_get_log_normalization_constant, 1},
    {"RHugin_domain_save_to_memory", (DL_FUNC) RHugin_domain_save_to_memory, 1},
    {"RHugin_domain_initialize", (DL_FUNC) RHugin_domain_initialize, 1},
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
    {"RHugin_domain_simulate", (DL_FUNC) RHugin_domain_simulate, 1},
    {"RHugin_node_get_sampled_state", (DL_FUNC) RHugin_node_get_sampled_state, 1},
    {"RHugin_node_get_sampled_value", (DL_FUNC) RHugin_node_get_sampled_value, 1},
    {"RHugin_domain_seed_random", (DL_FUNC) RHugin_domain_seed_random, 2},
    {"RHugin_domain_get_uniform_deviate", (DL_FUNC) RHugin_domain_get_uniform_deviate, 1},
    {"RHugin_domain_get_normal_deviate", (DL_FUNC) RHugin_domain_get_normal_deviate, 3},
    {"RHugin_node_get_entropy", (DL_FUNC) RHugin_node_get_entropy, 1},
    {"RHugin_node_get_mutual_information", (DL_FUNC) RHugin_node_get_mutual_information, 2},
    {"RHugin_node_get_experience_table", (DL_FUNC) RHugin_node_get_experience_table, 1},
    {"RHugin_node_has_experience_table", (DL_FUNC) RHugin_node_has_experience_table, 1},
    {"RHugin_node_get_fading_table", (DL_FUNC) RHugin_node_get_fading_table, 1},
    {"RHugin_node_has_fading_table", (DL_FUNC) RHugin_node_has_fading_table, 1},
    {"RHugin_domain_adapt", (DL_FUNC) RHugin_domain_adapt, 1},
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
    {"RHugin_domain_get_log_likelihood", (DL_FUNC) RHugin_domain_get_log_likelihood, 1},
    {"RHugin_domain_get_AIC", (DL_FUNC) RHugin_domain_get_AIC, 1},
    {"RHugin_domain_get_BIC", (DL_FUNC) RHugin_domain_get_BIC, 1},
    /*{"RHugin_domain_parse_cases", (DL_FUNC) RHugin_domain_parse_cases, 4},*/
    /*{"RHugin_domain_save_cases", (DL_FUNC) RHugin_domain_save_cases, 7},*/
    {"RHugin_domain_learn_structure", (DL_FUNC) RHugin_domain_learn_structure, 1},
    {"RHugin_domain_set_significance_level", (DL_FUNC) RHugin_domain_set_significance_level, 2},
    {"RHugin_domain_get_significance_level", (DL_FUNC) RHugin_domain_get_significance_level, 1},
    {"RHugin_node_set_edge_constraint", (DL_FUNC) RHugin_node_set_edge_constraint, 3},
    {"RHugin_node_get_edge_constraint", (DL_FUNC) RHugin_node_get_edge_constraint, 2},
    {"RHugin_domain_learn_tables", (DL_FUNC) RHugin_domain_learn_tables, 1},
    {"RHugin_domain_set_log_likelihood_tolerance", (DL_FUNC) RHugin_domain_set_log_likelihood_tolerance, 2},
    {"RHugin_domain_get_log_likelihood_tolerance", (DL_FUNC) RHugin_domain_get_log_likelihood_tolerance, 1},
    {"RHugin_domain_set_max_number_of_em_iterations", (DL_FUNC) RHugin_domain_set_max_number_of_em_iterations, 2},
    {"RHugin_domain_get_max_number_of_em_iterations", (DL_FUNC) RHugin_domain_get_max_number_of_em_iterations, 1},
    {"RHugin_domain_learn_class_tables", (DL_FUNC) RHugin_domain_learn_class_tables, 1},
    {"RHugin_node_set_position", (DL_FUNC) RHugin_node_set_position, 2},
    {"RHugin_node_get_position", (DL_FUNC) RHugin_node_get_position, 1},
    {NULL, NULL, 0}};

  /* ToDo: add these to the precious list for 2.8.0 */
  RHugin_domain_tag = install("RHUGIN_DOMAIN_TAG");
  RHugin_node_tag = install("RHUGIN_NODE_TAG");
  RHugin_table_tag = install("RHUGIN_TABLE_TAG");
  RHugin_expression_tag = install("RHUGIN_EXPRESSION_TAG");
  RHugin_model_tag = install("RHUGIN_MODEL_TAG");
  RHugin_junction_tree_tag = install("RHUGIN_JUNCTION_TREE_TAG");
  RHugin_clique_tag = install("RHUGIN_CLIQUE_TAG");

  R_registerRoutines(info, NULL, dotCallMethods, NULL, NULL);
}


