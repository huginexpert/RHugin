/*
 *
 * Header file for Hugin API, version 9.1.
 *
 * Copyright (C) 1989-2021, Hugin Expert A/S. All Rights Reserved.
 *
 *
 * This file can be used with both ISO (ANSI) C and C++ compilers.
 * C++ compilers should define the __cplusplus preprocessor symbol.
 *
 */
# ifndef __hugin_h
# define __hugin_h
# ifdef __cplusplus
extern"C"{
# endif
# include <stdio.h> 
# include <stddef.h> 
typedef ptrdiff_t h_count_t,h_index_t;
typedef int h_boolean_t;
typedef struct _h_domain_structure*h_domain_t;
typedef struct _h_jt_structure*h_junction_tree_t;
typedef struct _h_node_structure*h_node_t;
typedef struct _h_clique_structure*h_clique_t;
typedef struct _h_table_structure*h_table_t;
typedef struct _h_attribute_structure*h_attribute_t;
typedef struct _h_model_structure*h_model_t;
typedef struct _h_expr_structure*h_expression_t;
# include <float.h> 
# ifdef H_QUADRUPLE
typedef long double h_number_t,h_double_t;
# define h_infinity LDBL_MAX
# else
# ifdef H_DOUBLE
typedef double h_number_t;
# else
typedef float h_number_t;
# endif
typedef double h_double_t;
# define h_infinity DBL_MAX
# endif
# ifdef __cplusplus
typedef const char*h_string_t;
# else
typedef char*h_string_t;
# endif
typedef enum
{
h_error_none= 0,
h_error_usage,
h_error_io,
h_error_no_memory,
h_error_cg_limids_not_supported,
h_error_twice,
h_error_invalid_name,
h_error_cyclic_network,
h_error_cyclic_functional_dependency,h_error_functional_dependency,
h_error_size_too_large,
h_error_fast_retraction,
h_error_rounding,
h_error_bad_kb_password,
h_error_bad_kb_version,h_error_bad_kb_type,h_error_bad_kb_format,
h_error_not_compiled,
h_error_invalid_probability_potential,
h_error_chain_graph,
h_error_enumeration,
h_error_no_equilibrium,
h_error_low_density,
h_error_zero_variance,
h_error_inconsistency_or_underflow,
h_error_overflow,
h_error_cg_evidence_incorporated,
h_error_normalization,
h_error_compressed,
h_error_table_too_large,
h_error_invalid_evidence,
h_error_case_state_too_large,
h_error_no_value,
h_error_parse,
h_error_invalid_expression,
h_error_syntax,
h_error_division_by_zero,h_error_inappropriate_arguments,
h_error_computation_failed,h_error_insufficient_state_range,
h_error_invalid_state_values,
h_error_cyclic_instance_hierarchy,
h_error_illegal_binding,
h_error_locale,
h_error_invalid_license,
h_error_expired_license,
h_error_demo,
h_error_error
}h_error_t,h_status_t;
typedef enum
{h_category_error= -1,
h_category_function= 5,
h_category_instance= 6,
h_category_chance= 7,
h_category_decision,
h_category_utility
}h_node_category_t;
typedef enum
{h_kind_error= -2,h_unused= -1,
h_kind_other= -1,h_kind_discrete= 0,h_kind_continuous= 1
}h_node_kind_t;
typedef int h_coordinate_t;
typedef
enum{h_endian_host= 0,h_endian_big= 1,h_endian_little= 2}
h_endian_t;
typedef enum
{h_tm_clique_size= 15,h_tm_clique_weight,
h_tm_fill_in_size,h_tm_fill_in_weight,h_tm_total_weight,
h_tm_best_greedy
}h_triangulation_method_t;
typedef enum
{h_equilibrium_none= 10,
h_equilibrium_sum,
h_equilibrium_max
}h_equilibrium_t;
typedef enum{h_mode_normal= 20,h_mode_fast_retraction}h_evidence_mode_t;
typedef enum
{h_constraint_none= 100,
h_constraint_edge_required,
h_constraint_forward_edge_required,
h_constraint_backward_edge_required,
h_constraint_edge_forbidden,
h_constraint_forward_edge_forbidden,
h_constraint_backward_edge_forbidden,
h_constraint_error
}h_edge_constraint_t;
typedef size_t h_location_t;
typedef void(*h_old_error_handler_t)(int,h_string_t);
typedef void(*h_error_handler_t)(h_location_t,h_string_t,void*);
typedef struct _h_data_set*h_data_set_t;
typedef enum
{h_subtype_label= 30,h_subtype_boolean,h_subtype_number,
h_subtype_interval,h_subtype_error
}h_node_subtype_t;
typedef enum
{h_operator_Normal= 60,h_operator_LogNormal,
h_operator_Beta,h_operator_Gamma,
h_operator_Exponential,h_operator_Weibull,
h_operator_Uniform,h_operator_Triangular,h_operator_PERT,
h_operator_Binomial,h_operator_Poisson,
h_operator_NegativeBinomial,h_operator_Geometric,h_operator_Distribution,
h_operator_NoisyOR,
h_operator_truncate,
h_operator_aggregate,
h_operator_probability,
h_operator_variance,
h_operator_min,h_operator_max,
h_operator_log,h_operator_log2,h_operator_log10,h_operator_exp,
h_operator_sin,h_operator_cos,h_operator_tan,
h_operator_sinh,h_operator_cosh,h_operator_tanh,
h_operator_sqrt,
h_operator_abs,h_operator_floor,h_operator_ceil,h_operator_mod,
h_operator_if,h_operator_and,h_operator_or,h_operator_not,
h_operator_add,h_operator_subtract,h_operator_multiply,
h_operator_divide,h_operator_power,h_operator_negate,
h_operator_state_index,
h_operator_equals,h_operator_less_than,h_operator_greater_than,
h_operator_not_equals,h_operator_less_than_or_equals,
h_operator_greater_than_or_equals,
h_operator_number,h_operator_label,h_operator_node,h_operator_boolean,
h_operator_error
}h_operator_t;
typedef struct _h_class_structure*h_class_t;
typedef struct _h_cc_structure*h_class_collection_t;
typedef void(*h_get_class_t)(h_string_t,h_class_collection_t,void*);
# ifndef _H_DEF
# define _H_DEF(function, arguments) extern function arguments
# endif
_H_DEF(h_error_t h_error_code,(void));
_H_DEF(h_string_t h_error_name,(h_error_t));
_H_DEF(h_string_t h_error_description,(h_error_t));
_H_DEF(h_domain_t h_new_domain,(void));
_H_DEF(h_status_t h_domain_delete,(h_domain_t));
_H_DEF(h_status_t h_domain_uncompile,(h_domain_t));
_H_DEF(h_status_t h_domain_set_node_size,(h_domain_t,size_t,size_t));
_H_DEF(h_status_t h_domain_get_node_size,(h_domain_t,size_t*,size_t*));
_H_DEF(h_string_t h_domain_get_file_name,(h_domain_t));
_H_DEF(h_string_t h_domain_get_filename,(h_domain_t));
_H_DEF(h_status_t h_domain_set_log_file,(h_domain_t,FILE*));
_H_DEF(h_node_t h_domain_new_node,
(h_domain_t,h_node_category_t,h_node_kind_t));
_H_DEF(h_domain_t h_node_get_domain,(h_node_t));
_H_DEF(h_domain_t h_node_get_home_domain,(h_node_t));
_H_DEF(h_node_category_t h_node_get_category,(h_node_t));
_H_DEF(h_node_kind_t h_node_get_kind,(h_node_t));
_H_DEF(h_status_t h_node_set_category,(h_node_t,h_node_category_t));
_H_DEF(h_node_t h_node_clone,(h_node_t));
_H_DEF(h_status_t h_node_delete,(h_node_t));
_H_DEF(h_node_t h_domain_get_node_by_name,(h_domain_t,h_string_t));
_H_DEF(h_status_t h_node_set_name,(h_node_t,h_string_t));
_H_DEF(h_string_t h_node_get_name,(h_node_t));
_H_DEF(h_count_t h_node_get_number_of_states,(h_node_t));
_H_DEF(h_status_t h_node_set_number_of_states,(h_node_t,size_t));
_H_DEF(h_string_t h_node_get_state_label,(h_node_t,size_t));
_H_DEF(h_status_t h_node_set_state_label,(h_node_t,size_t,h_string_t));
_H_DEF(h_index_t h_node_get_state_index_from_label,(h_node_t,h_string_t));
_H_DEF(h_status_t h_node_reorder_states,(h_node_t,h_string_t const*));
_H_DEF(h_node_t*h_node_get_parents,(h_node_t));
_H_DEF(h_node_t*h_node_get_children,(h_node_t));
_H_DEF(h_status_t h_node_add_parent,(h_node_t,h_node_t));
_H_DEF(h_status_t h_node_remove_parent,(h_node_t,h_node_t));
_H_DEF(h_status_t h_node_remove_discrete_parent,
(h_node_t,h_node_t,size_t));
_H_DEF(h_status_t h_node_switch_parent,(h_node_t,h_node_t,h_node_t));
_H_DEF(h_node_t*h_node_get_descendants,(h_node_t));
_H_DEF(h_node_t*h_node_get_ancestors,(h_node_t));
_H_DEF(h_status_t h_node_reverse_edge,(h_node_t,h_node_t));
_H_DEF(h_node_t h_domain_get_first_node,(h_domain_t));
_H_DEF(h_node_t h_node_get_next,(h_node_t));
_H_DEF(h_string_t h_node_get_label,(h_node_t));
_H_DEF(h_status_t h_node_set_label,(h_node_t,h_string_t));
_H_DEF(h_status_t h_node_get_position,
(h_node_t,h_coordinate_t*,h_coordinate_t*));
_H_DEF(h_status_t h_node_set_position,
(h_node_t,h_coordinate_t,h_coordinate_t));
_H_DEF(h_table_t h_node_get_table,(h_node_t));
_H_DEF(h_status_t h_table_reorder_nodes,(h_table_t,h_node_t const*));
_H_DEF(h_status_t h_node_set_alpha,(h_node_t,h_double_t,size_t));
_H_DEF(h_status_t h_node_set_beta,(h_node_t,h_double_t,h_node_t,size_t));
_H_DEF(h_status_t h_node_set_gamma,(h_node_t,h_double_t,size_t));
_H_DEF(h_double_t h_node_get_alpha,(h_node_t,size_t));
_H_DEF(h_double_t h_node_get_beta,(h_node_t,h_node_t,size_t));
_H_DEF(h_double_t h_node_get_gamma,(h_node_t,size_t));
_H_DEF(h_clique_t h_domain_get_first_clique,(h_domain_t));
_H_DEF(h_clique_t h_clique_get_next,(h_clique_t));
_H_DEF(h_count_t h_domain_get_number_of_cliques,(h_domain_t));
_H_DEF(h_junction_tree_t h_clique_get_junction_tree,(h_clique_t));
_H_DEF(h_node_t*h_clique_get_members,(h_clique_t));
_H_DEF(h_count_t h_clique_get_number_of_neighbors,(h_clique_t));
_H_DEF(h_count_t h_clique_get_number_of_members,(h_clique_t));
_H_DEF(h_clique_t*h_clique_get_neighbors,(h_clique_t));
_H_DEF(h_table_t h_clique_get_probability_table,(h_clique_t));
_H_DEF(h_table_t h_clique_get_utility_table,(h_clique_t));
_H_DEF(h_clique_t h_jt_get_root,(h_junction_tree_t));
_H_DEF(h_junction_tree_t h_domain_get_first_junction_tree,(h_domain_t));
_H_DEF(h_junction_tree_t h_jt_get_next,(h_junction_tree_t));
_H_DEF(h_clique_t*h_jt_get_cliques,(h_junction_tree_t));
_H_DEF(size_t h_jt_get_total_size,(h_junction_tree_t));
_H_DEF(size_t h_jt_get_total_cg_size,(h_junction_tree_t));
_H_DEF(h_node_t*h_table_get_nodes,(h_table_t));
_H_DEF(h_number_t*h_table_get_data,(h_table_t));
_H_DEF(size_t h_table_get_size,(h_table_t));
_H_DEF(size_t h_table_get_cg_size,(h_table_t));
_H_DEF(h_double_t h_table_get_mean,(h_table_t,size_t,h_node_t));
_H_DEF(h_double_t h_table_get_covariance,
(h_table_t,size_t,h_node_t,h_node_t));
_H_DEF(h_double_t h_table_get_variance,(h_table_t,size_t,h_node_t));
_H_DEF(h_status_t h_table_delete,(h_table_t));
_H_DEF(size_t h_table_get_index_from_configuration,
(h_table_t,const size_t*));
_H_DEF(h_status_t h_table_get_configuration_from_index,
(h_table_t,size_t*,size_t));
_H_DEF(h_status_t h_domain_set_grain_size,(h_domain_t,size_t));
_H_DEF(h_count_t h_domain_get_grain_size,(h_domain_t));
_H_DEF(h_status_t h_domain_set_concurrency_level,(h_domain_t,size_t));
_H_DEF(h_count_t h_domain_get_concurrency_level,(h_domain_t));
_H_DEF(h_status_t h_domain_save,(h_domain_t,h_string_t,h_endian_t));
_H_DEF(h_status_t h_domain_save_as_kb,(h_domain_t,h_string_t,h_string_t));
_H_DEF(h_status_t h_cc_save_as_kb,
(h_class_collection_t,h_string_t,h_string_t));
_H_DEF(h_domain_t h_kb_load_domain,(h_string_t,h_string_t));
_H_DEF(h_domain_t h_load_domain,(h_string_t));
_H_DEF(h_class_collection_t h_kb_load_class_collection,
(h_string_t,h_string_t));
_H_DEF(h_node_t*h_domain_get_d_connected_nodes,
(h_domain_t,h_node_t const*,h_node_t const*,h_node_t const*));
_H_DEF(h_node_t*h_domain_get_d_separated_nodes,
(h_domain_t,h_node_t const*,h_node_t const*,h_node_t const*));
_H_DEF(h_node_t*h_domain_get_sensitivity_set_by_output,
(h_domain_t,size_t));
_H_DEF(h_node_t*h_domain_get_sensitivity_set,(h_domain_t));
_H_DEF(h_status_t h_node_compute_sensitivity_data,(h_node_t,size_t));
_H_DEF(h_status_t h_node_get_sensitivity_constants,
(h_node_t,size_t,h_number_t*,h_number_t*,h_number_t*,
h_number_t*));
_H_DEF(h_status_t h_node_get_sensitivity_constants_by_output,
(h_node_t,size_t,size_t,h_number_t*,h_number_t*,h_number_t*,
h_number_t*));
_H_DEF(h_status_t h_domain_compute_sensitivity_data,
(h_domain_t,h_node_t const*,size_t const*));
_H_DEF(h_boolean_t h_domain_is_compiled,(h_domain_t));
_H_DEF(h_status_t h_domain_compile,(h_domain_t));
_H_DEF(h_junction_tree_t h_node_get_junction_tree,(h_node_t));
_H_DEF(h_boolean_t h_domain_is_triangulated,(h_domain_t));
_H_DEF(h_status_t h_domain_set_initial_triangulation,
(h_domain_t,h_node_t const*));
_H_DEF(h_status_t h_domain_triangulate_with_order,
(h_domain_t,h_node_t const*));
_H_DEF(h_status_t h_domain_triangulate,
(h_domain_t,h_triangulation_method_t));
_H_DEF(h_status_t h_domain_set_ijt_nodes,(h_domain_t,h_node_t const*));
_H_DEF(h_node_t*h_node_get_moral_neighbors,(h_node_t));
_H_DEF(h_status_t h_domain_set_max_number_of_separators,
(h_domain_t,size_t));
_H_DEF(h_count_t h_domain_get_max_number_of_separators,(h_domain_t));
_H_DEF(h_status_t h_domain_set_max_separator_size,(h_domain_t,size_t));
_H_DEF(h_count_t h_domain_get_max_separator_size,(h_domain_t));
_H_DEF(size_t h_domain_get_jt_cost,(h_domain_t));
_H_DEF(h_node_t*h_domain_get_elimination_order,(h_domain_t));
_H_DEF(h_boolean_t h_node_evidence_to_propagate,(h_node_t));
_H_DEF(h_boolean_t h_node_evidence_is_entered,(h_node_t));
_H_DEF(h_boolean_t h_node_likelihood_is_entered,(h_node_t));
_H_DEF(h_boolean_t h_node_evidence_is_propagated,(h_node_t));
_H_DEF(h_boolean_t h_node_likelihood_is_propagated,(h_node_t));
_H_DEF(h_index_t h_node_get_selected_state,(h_node_t));
_H_DEF(h_boolean_t h_domain_evidence_to_propagate,(h_domain_t));
_H_DEF(h_boolean_t h_jt_evidence_to_propagate,(h_junction_tree_t));
_H_DEF(h_boolean_t h_domain_evidence_is_propagated,(h_domain_t));
_H_DEF(h_boolean_t h_jt_evidence_is_propagated,(h_junction_tree_t));
_H_DEF(h_boolean_t h_domain_likelihood_is_propagated,(h_domain_t));
_H_DEF(h_boolean_t h_jt_likelihood_is_propagated,(h_junction_tree_t));
_H_DEF(h_boolean_t h_domain_cg_evidence_is_propagated,(h_domain_t));
_H_DEF(h_boolean_t h_jt_cg_evidence_is_propagated,(h_junction_tree_t));
_H_DEF(h_status_t h_node_enter_finding,(h_node_t,size_t,h_number_t));
_H_DEF(h_status_t h_node_enter_value,(h_node_t,h_double_t));
_H_DEF(h_status_t h_node_select_state,(h_node_t,size_t));
_H_DEF(h_status_t h_node_retract_findings,(h_node_t));
_H_DEF(h_status_t h_domain_retract_findings,(h_domain_t));
_H_DEF(h_number_t h_node_get_entered_finding,(h_node_t,size_t));
_H_DEF(h_number_t h_node_get_propagated_finding,(h_node_t,size_t));
_H_DEF(h_double_t h_node_get_entered_value,(h_node_t));
_H_DEF(h_double_t h_node_get_propagated_value,(h_node_t));
_H_DEF(h_index_t h_node_get_propagated_state,(h_node_t));
_H_DEF(h_status_t h_node_touch_table,(h_node_t));
_H_DEF(h_boolean_t h_domain_tables_to_propagate,(h_domain_t));
_H_DEF(h_boolean_t h_jt_tables_to_propagate,(h_junction_tree_t));
_H_DEF(h_status_t h_domain_reset_inference_engine,(h_domain_t));
_H_DEF(h_number_t h_node_get_belief,(h_node_t,size_t));
_H_DEF(h_double_t h_node_get_mean,(h_node_t));
_H_DEF(h_double_t h_node_get_variance,(h_node_t));
_H_DEF(h_number_t h_node_get_expected_utility,(h_node_t,size_t));
_H_DEF(h_number_t h_node_get_variance_of_utility,(h_node_t));
_H_DEF(h_number_t h_node_get_min_utility,(h_node_t));
_H_DEF(h_number_t h_node_get_max_utility,(h_node_t));
_H_DEF(h_number_t h_domain_get_expected_utility,(h_domain_t));
_H_DEF(h_double_t h_node_get_quantile,(h_node_t,h_double_t));
_H_DEF(h_table_t h_node_get_distribution,(h_node_t));
_H_DEF(h_double_t h_table_compute_density,(h_table_t,h_double_t));
_H_DEF(h_double_t h_table_compute_probability_of_interval,
(h_table_t,h_double_t,h_double_t));
_H_DEF(h_boolean_t h_domain_equilibrium_is,(h_domain_t,h_equilibrium_t));
_H_DEF(h_boolean_t h_jt_equilibrium_is,(h_junction_tree_t,h_equilibrium_t));
_H_DEF(h_boolean_t h_domain_evidence_mode_is,
(h_domain_t,h_evidence_mode_t));
_H_DEF(h_boolean_t h_jt_evidence_mode_is,
(h_junction_tree_t,h_evidence_mode_t));
_H_DEF(h_double_t h_domain_get_normalization_constant,(h_domain_t));
_H_DEF(h_double_t h_domain_get_log_normalization_constant,(h_domain_t));
_H_DEF(h_status_t h_domain_propagate,
(h_domain_t,h_equilibrium_t,h_evidence_mode_t));
_H_DEF(h_status_t h_jt_propagate,
(h_junction_tree_t,h_equilibrium_t,h_evidence_mode_t));
_H_DEF(h_status_t h_clique_propagate,
(h_clique_t,h_equilibrium_t,h_evidence_mode_t));
_H_DEF(h_status_t h_domain_initialize,(h_domain_t));
_H_DEF(h_double_t h_clique_get_conflict,(h_clique_t));
_H_DEF(h_clique_t h_node_get_conflict_clique,(h_node_t));
_H_DEF(h_double_t h_domain_get_conflict,(h_domain_t));
_H_DEF(h_double_t h_jt_get_conflict,(h_junction_tree_t));
_H_DEF(h_table_t h_domain_get_marginal,(h_domain_t,h_node_t const*));
_H_DEF(h_double_t h_node_get_mutual_information,(h_node_t,h_node_t));
_H_DEF(h_double_t h_node_get_entropy,(h_node_t));
_H_DEF(h_status_t h_domain_reclaim_memory_tables,(h_domain_t));
_H_DEF(h_status_t h_domain_save_to_memory,(h_domain_t));
_H_DEF(h_boolean_t h_domain_is_compressed,(h_domain_t));
_H_DEF(h_double_t h_domain_compress,(h_domain_t));
_H_DEF(h_double_t h_domain_get_approximation_constant,(h_domain_t));
_H_DEF(h_double_t h_domain_approximate,(h_domain_t,h_double_t));
_H_DEF(h_status_t h_domain_update_policies,(h_domain_t));
_H_DEF(h_node_t*h_node_get_requisite_parents,(h_node_t));
_H_DEF(h_node_t*h_node_get_requisite_ancestors,(h_node_t));
_H_DEF(h_status_t h_domain_set_number_of_cases,(h_domain_t,size_t));
_H_DEF(h_index_t h_domain_new_case,(h_domain_t));
_H_DEF(h_count_t h_domain_get_number_of_cases,(h_domain_t));
_H_DEF(h_status_t h_domain_set_case_count,(h_domain_t,size_t,h_number_t));
_H_DEF(h_number_t h_domain_get_case_count,(h_domain_t,size_t));
_H_DEF(h_status_t h_node_set_case_state,(h_node_t,size_t,size_t));
_H_DEF(h_status_t h_node_set_case_value,(h_node_t,size_t,h_double_t));
_H_DEF(h_status_t h_node_unset_case,(h_node_t,size_t));
_H_DEF(h_boolean_t h_node_case_is_set,(h_node_t,size_t));
_H_DEF(h_index_t h_node_get_case_state,(h_node_t,size_t));
_H_DEF(h_double_t h_node_get_case_value,(h_node_t,size_t));
_H_DEF(h_status_t h_domain_enter_case,(h_domain_t,size_t));
_H_DEF(h_status_t h_node_set_edge_constraint,
(h_node_t,h_node_t,h_edge_constraint_t));
_H_DEF(h_edge_constraint_t h_node_get_edge_constraint,(h_node_t,h_node_t));
_H_DEF(h_status_t h_domain_learn_greedy_structure,(h_domain_t,int,size_t));
_H_DEF(h_status_t h_domain_learn_structure,(h_domain_t));
_H_DEF(h_status_t h_domain_set_significance_level,(h_domain_t,h_double_t));
_H_DEF(h_double_t h_domain_get_significance_level,(h_domain_t));
_H_DEF(h_status_t h_domain_learn_tree_structure,
(h_domain_t,h_node_t,h_node_t));
_H_DEF(h_status_t h_domain_learn_hnb_structure,(h_domain_t,h_node_t));
_H_DEF(h_status_t h_domain_learn_tables,(h_domain_t));
_H_DEF(h_status_t h_domain_set_log_likelihood_tolerance,
(h_domain_t,h_double_t));
_H_DEF(h_double_t h_domain_get_log_likelihood_tolerance,(h_domain_t));
_H_DEF(h_status_t h_domain_set_max_number_of_em_iterations,
(h_domain_t,size_t));
_H_DEF(h_count_t h_domain_get_max_number_of_em_iterations,(h_domain_t));
_H_DEF(h_status_t h_domain_learn_class_tables,(h_domain_t));
_H_DEF(h_double_t h_domain_get_log_likelihood,(h_domain_t));
_H_DEF(h_double_t h_domain_get_AIC,(h_domain_t));
_H_DEF(h_double_t h_domain_get_BIC,(h_domain_t));
_H_DEF(h_table_t h_node_get_experience_table,(h_node_t));
_H_DEF(h_boolean_t h_node_has_experience_table,(h_node_t));
_H_DEF(h_table_t h_node_get_fading_table,(h_node_t));
_H_DEF(h_boolean_t h_node_has_fading_table,(h_node_t));
_H_DEF(h_status_t h_domain_adapt,(h_domain_t));
_H_DEF(h_double_t h_domain_get_uniform_deviate,(h_domain_t));
_H_DEF(h_status_t h_domain_seed_random,(h_domain_t,unsigned int));
_H_DEF(h_double_t h_domain_get_normal_deviate,
(h_domain_t,h_double_t,h_double_t));
_H_DEF(h_index_t h_node_get_sampled_state,(h_node_t));
_H_DEF(h_index_t h_node_get_selection,(h_node_t));
_H_DEF(h_double_t h_node_get_sampled_value,(h_node_t));
_H_DEF(h_number_t h_node_get_sampled_utility,(h_node_t));
_H_DEF(h_status_t h_domain_simulate,(h_domain_t));
_H_DEF(h_double_t h_domain_get_probability_of_random_selection,(h_domain_t));
_H_DEF(h_count_t h_domain_get_number_of_map_configurations,(h_domain_t));
_H_DEF(size_t*h_domain_get_map_configuration,(h_domain_t,size_t));
_H_DEF(h_double_t h_domain_get_probability_of_map_configuration,
(h_domain_t,size_t));
_H_DEF(h_status_t h_domain_find_map_configurations,
(h_domain_t,h_node_t const*,h_double_t));
_H_DEF(h_status_t h_node_compute_explanation_data,
(h_node_t,size_t,h_node_t,size_t,size_t));
_H_DEF(h_count_t h_domain_get_number_of_explanations,(h_domain_t));
_H_DEF(h_node_t*h_domain_get_explanation,(h_domain_t,size_t));
_H_DEF(h_number_t h_domain_get_explanation_score,(h_domain_t,size_t));
_H_DEF(h_domain_t h_net_parse_domain,(h_string_t,h_error_handler_t,void*));
_H_DEF(h_domain_t h_net_parse,(FILE*,h_old_error_handler_t));
_H_DEF(h_domain_t h_net_parse_from_string,
(h_string_t,h_old_error_handler_t));
_H_DEF(h_node_t*h_domain_parse_nodes,
(h_domain_t,h_string_t,h_error_handler_t,void*));
_H_DEF(h_node_t*h_class_parse_nodes,
(h_class_t,h_string_t,h_error_handler_t,void*));
_H_DEF(h_status_t h_domain_write_net,(h_domain_t,FILE*));
_H_DEF(h_string_t h_domain_to_net_string,(h_domain_t));
_H_DEF(h_string_t h_class_to_net_string,(h_class_t));
_H_DEF(h_status_t h_domain_save_case,(h_domain_t,h_string_t));
_H_DEF(h_status_t h_domain_parse_case,
(h_domain_t,h_string_t,h_error_handler_t,void*));
_H_DEF(h_status_t h_domain_parse_cases,
(h_domain_t,h_string_t,h_error_handler_t,void*));
_H_DEF(h_status_t h_domain_save_cases,
(h_domain_t,h_string_t,h_node_t const*,h_index_t const*,
h_boolean_t,h_string_t,h_string_t));
_H_DEF(h_data_set_t h_new_data_set,(void));
_H_DEF(h_status_t h_ds_delete,(h_data_set_t));
_H_DEF(h_count_t h_ds_get_number_of_columns,(h_data_set_t));
_H_DEF(h_count_t h_ds_get_number_of_rows,(h_data_set_t));
_H_DEF(h_index_t h_ds_new_row,(h_data_set_t));
_H_DEF(h_index_t h_ds_new_column,(h_data_set_t,h_string_t));
_H_DEF(h_status_t h_ds_move_column,(h_data_set_t,size_t,size_t));
_H_DEF(h_status_t h_ds_move_row,(h_data_set_t,size_t,size_t));
_H_DEF(h_status_t h_ds_delete_row,(h_data_set_t,size_t));
_H_DEF(h_status_t h_ds_delete_column,(h_data_set_t,size_t));
_H_DEF(h_status_t h_ds_set_data_item,
(h_data_set_t,size_t,size_t,h_string_t));
_H_DEF(h_string_t h_ds_get_data_item,(h_data_set_t,size_t,size_t));
_H_DEF(h_count_t h_ds_count_data,(h_data_set_t,size_t,h_string_t));
_H_DEF(h_index_t h_ds_find_row,(h_data_set_t,size_t,size_t,h_string_t));
_H_DEF(h_boolean_t h_ds_column_data_are_numbers,(h_data_set_t,size_t));
_H_DEF(h_boolean_t h_ds_column_data_are_intervals,(h_data_set_t,size_t));
_H_DEF(h_boolean_t h_ds_column_is_empty,(h_data_set_t,size_t));
_H_DEF(h_string_t h_ds_get_column_name,(h_data_set_t,size_t));
_H_DEF(h_status_t h_ds_set_column_name,(h_data_set_t,size_t,h_string_t));
_H_DEF(h_string_t*h_ds_get_distinct_values,(h_data_set_t,size_t));
_H_DEF(h_double_t*h_ds_get_numbers,(h_data_set_t,size_t,h_double_t));
_H_DEF(h_double_t*h_ds_discretize_column,(h_data_set_t,size_t,size_t));
_H_DEF(h_status_t h_ds_apply_discretization,
(h_data_set_t,size_t,h_double_t const*,size_t));
_H_DEF(h_status_t h_ds_replace_values,
(h_data_set_t,size_t,h_string_t,h_string_t));
_H_DEF(h_status_t h_ds_sort_rows,(h_data_set_t,size_t));
_H_DEF(h_status_t h_ds_sort_rows_numerically,
(h_data_set_t,size_t,h_boolean_t));
_H_DEF(h_node_t h_domain_create_discrete_node,
(h_domain_t,h_data_set_t,size_t));
_H_DEF(h_status_t h_domain_add_cases,
(h_domain_t,h_data_set_t,size_t,size_t));
_H_DEF(h_data_set_t h_csv_parse_data_set,
(h_string_t,int,h_error_handler_t,void*));
_H_DEF(h_status_t h_ds_save,(h_data_set_t,h_string_t,int));
_H_DEF(h_string_t h_ds_to_csv_string,(h_data_set_t,int));
_H_DEF(h_double_t*h_create_intervals_from_data,
(h_double_t*,size_t*,size_t));
_H_DEF(h_status_t h_node_set_subtype,(h_node_t,h_node_subtype_t));
_H_DEF(h_node_subtype_t h_node_get_subtype,(h_node_t));
_H_DEF(h_status_t h_node_set_state_value,(h_node_t,size_t,h_double_t));
_H_DEF(h_double_t h_node_get_state_value,(h_node_t,size_t));
_H_DEF(h_index_t h_node_get_state_index_from_value,(h_node_t,h_double_t));
_H_DEF(h_expression_t h_number_make_expression,(h_double_t));
_H_DEF(h_expression_t h_boolean_make_expression,(h_boolean_t));
_H_DEF(h_expression_t h_label_make_expression,(h_string_t));
_H_DEF(h_expression_t h_node_make_expression,(h_node_t));
_H_DEF(h_expression_t h_make_composite_expression,
(h_operator_t,h_expression_t const*));
_H_DEF(h_boolean_t h_expression_is_composite,(h_expression_t));
_H_DEF(h_operator_t h_expression_get_operator,(h_expression_t));
_H_DEF(h_expression_t*h_expression_get_operands,(h_expression_t));
_H_DEF(h_node_t h_expression_get_node,(h_expression_t));
_H_DEF(h_double_t h_expression_get_number,(h_expression_t));
_H_DEF(h_string_t h_expression_get_label,(h_expression_t));
_H_DEF(h_boolean_t h_expression_get_boolean,(h_expression_t));
_H_DEF(h_expression_t h_expression_clone,(h_expression_t));
_H_DEF(h_status_t h_expression_delete,(h_expression_t));
_H_DEF(h_string_t h_expression_to_string,(h_expression_t));
_H_DEF(h_status_t h_model_set_number_of_samples_per_interval,
(h_model_t,size_t));
_H_DEF(h_count_t h_model_get_number_of_samples_per_interval,(h_model_t));
_H_DEF(h_model_t h_node_get_model,(h_node_t));
_H_DEF(h_node_t*h_model_get_nodes,(h_model_t));
_H_DEF(size_t h_model_get_size,(h_model_t));
_H_DEF(h_model_t h_node_new_model,(h_node_t,h_node_t const*));
_H_DEF(h_status_t h_model_delete,(h_model_t));
_H_DEF(h_status_t h_model_set_expression,
(h_model_t,size_t,h_expression_t));
_H_DEF(h_expression_t h_model_get_expression,(h_model_t,size_t));
_H_DEF(h_expression_t h_domain_string_to_expression,
(h_domain_t,h_string_t,h_error_handler_t,void*));
_H_DEF(h_expression_t h_string_to_expression,
(h_string_t,h_domain_t,h_old_error_handler_t));
_H_DEF(h_expression_t h_string_parse_expression,
(h_string_t,h_model_t,h_error_handler_t,void*));
_H_DEF(h_status_t h_node_generate_table,(h_node_t));
_H_DEF(h_status_t h_domain_generate_tables,(h_domain_t));
_H_DEF(h_double_t h_node_get_value,(h_node_t));
_H_DEF(h_class_collection_t h_class_get_class_collection,(h_class_t));
_H_DEF(h_class_collection_t h_new_class_collection,(void));
_H_DEF(h_class_t*h_cc_get_members,(h_class_collection_t));
_H_DEF(h_status_t h_cc_add_domain,(h_class_collection_t,h_domain_t));
_H_DEF(h_status_t h_cc_add_classes,
(h_class_collection_t,h_class_collection_t));
_H_DEF(h_class_t h_cc_new_class,(h_class_collection_t));
_H_DEF(h_status_t h_cc_delete,(h_class_collection_t));
_H_DEF(h_status_t h_class_delete,(h_class_t));
_H_DEF(h_status_t h_class_set_name,(h_class_t,h_string_t));
_H_DEF(h_string_t h_class_get_name,(h_class_t));
_H_DEF(h_class_t h_cc_get_class_by_name,(h_class_collection_t,h_string_t));
_H_DEF(h_node_t h_class_get_node_by_name,(h_class_t,h_string_t));
_H_DEF(h_node_t h_class_new_node,
(h_class_t,h_node_category_t,h_node_kind_t));
_H_DEF(h_class_t h_node_get_home_class,(h_node_t));
_H_DEF(h_node_t h_class_get_first_node,(h_class_t));
_H_DEF(h_status_t h_class_generate_tables,(h_class_t));
_H_DEF(h_status_t h_class_set_log_file,(h_class_t,FILE*));
_H_DEF(h_string_t h_class_get_file_name,(h_class_t));
_H_DEF(h_status_t h_class_set_node_size,(h_class_t,size_t,size_t));
_H_DEF(h_status_t h_class_get_node_size,(h_class_t,size_t*,size_t*));
_H_DEF(h_node_t*h_class_get_inputs,(h_class_t));
_H_DEF(h_node_t*h_class_get_outputs,(h_class_t));
_H_DEF(h_status_t h_node_add_to_inputs,(h_node_t));
_H_DEF(h_status_t h_node_add_to_outputs,(h_node_t));
_H_DEF(h_status_t h_node_remove_from_inputs,(h_node_t));
_H_DEF(h_status_t h_node_remove_from_outputs,(h_node_t));
_H_DEF(h_node_t*h_class_get_instances,(h_class_t));
_H_DEF(h_node_t h_class_new_instance,(h_class_t,h_class_t));
_H_DEF(h_class_t h_node_get_instance_class,(h_node_t));
_H_DEF(h_status_t h_node_substitute_class,(h_node_t,h_class_t));
_H_DEF(h_node_t h_node_get_output_master,(h_node_t));
_H_DEF(h_node_t h_node_get_master,(h_node_t));
_H_DEF(h_node_t h_node_get_instance,(h_node_t));
_H_DEF(h_node_t h_node_get_output,(h_node_t,h_node_t));
_H_DEF(h_status_t h_node_set_input,(h_node_t,h_node_t,h_node_t));
_H_DEF(h_status_t h_node_unset_input,(h_node_t,h_node_t));
_H_DEF(h_node_t h_node_get_input,(h_node_t,h_node_t));
_H_DEF(h_domain_t h_class_create_domain,(h_class_t));
_H_DEF(h_node_t*h_node_get_source,(h_node_t));
_H_DEF(h_domain_t h_domain_clone,(h_domain_t));
_H_DEF(h_status_t h_net_parse_classes,
(h_string_t,h_class_collection_t,h_get_class_t,h_error_handler_t,
void*));
_H_DEF(h_expression_t h_class_string_to_expression,
(h_class_t,h_string_t,h_error_handler_t,void*));
_H_DEF(h_status_t h_cc_save_as_net,(h_class_collection_t,h_string_t));
_H_DEF(h_string_t h_cc_to_net_string,(h_class_collection_t));
_H_DEF(h_status_t h_domain_save_as_net,(h_domain_t,h_string_t));
_H_DEF(h_status_t h_class_save_as_net,(h_class_t,h_string_t));
_H_DEF(h_node_t h_node_create_temporal_clone,(h_node_t));
_H_DEF(h_node_t h_node_get_temporal_clone,(h_node_t));
_H_DEF(h_node_t h_node_get_temporal_master,(h_node_t));
_H_DEF(h_domain_t h_class_create_dbn_domain,(h_class_t,size_t));
_H_DEF(h_status_t h_domain_triangulate_dbn,
(h_domain_t,h_triangulation_method_t));
_H_DEF(h_status_t h_domain_triangulate_dbn_for_bk,
(h_domain_t,h_triangulation_method_t));
_H_DEF(h_boolean_t h_domain_is_triangulated_for_bk,(h_domain_t));
_H_DEF(h_count_t h_domain_get_dbn_window_offset,(h_domain_t));
_H_DEF(h_status_t h_domain_move_dbn_window,(h_domain_t,size_t));
_H_DEF(h_status_t h_domain_initialize_dbn_window,(h_domain_t));
_H_DEF(h_status_t h_domain_compute_dbn_predictions,(h_domain_t,size_t));
_H_DEF(h_number_t h_node_get_predicted_belief,(h_node_t,size_t,size_t));
_H_DEF(h_double_t h_node_get_predicted_mean,(h_node_t,size_t));
_H_DEF(h_double_t h_node_get_predicted_variance,(h_node_t,size_t));
_H_DEF(h_double_t h_node_get_predicted_value,(h_node_t,size_t));
_H_DEF(h_status_t h_domain_adapt_class_tables_using_fractional_update,
(h_domain_t));
_H_DEF(h_status_t h_domain_adapt_class_tables_using_online_em,
(h_domain_t,h_double_t));
_H_DEF(h_status_t h_domain_learn_class_tables_using_online_em,
(h_domain_t,size_t,h_double_t));
_H_DEF(h_status_t h_domain_learn_class_tables_using_fractional_update,
(h_domain_t,size_t));
_H_DEF(h_status_t h_domain_set_user_data,(h_domain_t,void*));
_H_DEF(void*h_domain_get_user_data,(h_domain_t));
_H_DEF(h_status_t h_class_set_user_data,(h_class_t,void*));
_H_DEF(void*h_class_get_user_data,(h_class_t));
_H_DEF(h_status_t h_cc_set_user_data,(h_class_collection_t,void*));
_H_DEF(void*h_cc_get_user_data,(h_class_collection_t));
_H_DEF(h_status_t h_node_set_user_data,(h_node_t,void*));
_H_DEF(void*h_node_get_user_data,(h_node_t));
_H_DEF(h_status_t h_clique_set_user_data,(h_clique_t,void*));
_H_DEF(void*h_clique_get_user_data,(h_clique_t));
_H_DEF(h_status_t h_jt_set_user_data,(h_junction_tree_t,void*));
_H_DEF(void*h_jt_get_user_data,(h_junction_tree_t));
_H_DEF(h_status_t h_table_set_user_data,(h_table_t,void*));
_H_DEF(void*h_table_get_user_data,(h_table_t));
_H_DEF(h_status_t h_model_set_user_data,(h_model_t,void*));
_H_DEF(void*h_model_get_user_data,(h_model_t));
_H_DEF(h_status_t h_domain_set_attribute,
(h_domain_t,h_string_t,h_string_t));
_H_DEF(h_string_t h_domain_get_attribute,(h_domain_t,h_string_t));
_H_DEF(h_status_t h_node_set_attribute,(h_node_t,h_string_t,h_string_t));
_H_DEF(h_string_t h_node_get_attribute,(h_node_t,h_string_t));
_H_DEF(h_attribute_t h_domain_get_first_attribute,(h_domain_t));
_H_DEF(h_attribute_t h_node_get_first_attribute,(h_node_t));
_H_DEF(h_attribute_t h_attribute_get_next,(h_attribute_t));
_H_DEF(h_string_t h_attribute_get_key,(h_attribute_t));
_H_DEF(h_string_t h_attribute_get_value,(h_attribute_t));
_H_DEF(h_status_t h_class_set_attribute,
(h_class_t,h_string_t,h_string_t));
_H_DEF(h_string_t h_class_get_attribute,(h_class_t,h_string_t));
_H_DEF(h_attribute_t h_class_get_first_attribute,(h_class_t));
# undef _H_DEF
# ifdef __cplusplus
}
# endif
# endif 
