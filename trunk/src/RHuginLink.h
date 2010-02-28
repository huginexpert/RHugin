/*********************************************************************
  * The Hugin API
*********************************************************************/

/* Section 1.6 Errors */

DLLEXPORT SEXP RHugin_error_code();


/* Section 1.6.1 Handling errors */

DLLEXPORT SEXP RHugin_error_name(SEXP Scode);
DLLEXPORT SEXP RHugin_error_description(SEXP Scode);


/* Section 1.7 Taking advantage of multiple processors */

DLLEXPORT SEXP RHugin_domain_set_concurrency_level(SEXP Sdomain, SEXP Slevel);
DLLEXPORT SEXP RHugin_domain_get_concurrency_level(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_set_grain_size(SEXP Sdomain, SEXP Ssize);
DLLEXPORT SEXP RHugin_domain_get_grain_size(SEXP Sdomain);


/* Section 2.2 Domains: Creation and deletion */

DLLEXPORT SEXP RHugin_new_domain();
DLLEXPORT SEXP RHugin_domain_delete(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_clone(SEXP Sdomain);


/* Section 2.3 Nodes: Creation and deletion */

DLLEXPORT SEXP RHugin_domain_new_node(SEXP Sdomain, SEXP Scategory, SEXP Skind);
// SEXP RHugin_node_get_domain(SEXP Snode);
DLLEXPORT SEXP RHugin_node_get_category(SEXP Snode);
DLLEXPORT SEXP RHugin_node_get_kind(SEXP Snode);
DLLEXPORT SEXP RHugin_node_delete(SEXP Snode);
DLLEXPORT SEXP RHugin_node_clone(SEXP Snode);


/* Section 2.4 The links of the network */

DLLEXPORT SEXP RHugin_node_add_parent(SEXP Schild, SEXP Sparent);
DLLEXPORT SEXP RHugin_node_remove_parent(SEXP Snode, SEXP Sparent);
DLLEXPORT SEXP RHugin_node_switch_parent(SEXP Snode, SEXP Sold_parent, SEXP Snew_parent);
DLLEXPORT SEXP RHugin_node_reverse_edge(SEXP Snode1, SEXP Snode2);
DLLEXPORT SEXP RHugin_node_get_parents(SEXP Snodes);
DLLEXPORT SEXP RHugin_node_get_children(SEXP Snodes);


/* Section 2.5 The number of states of a node */

DLLEXPORT SEXP RHugin_node_set_number_of_states(SEXP Snode, SEXP Sstates);
DLLEXPORT SEXP RHugin_node_get_number_of_states(SEXP Snode);


/* Section 2.6 The conditional probability and the utility table */

DLLEXPORT SEXP RHugin_node_get_table(SEXP Snode);
DLLEXPORT SEXP RHugin_node_touch_table(SEXP Snode);
DLLEXPORT SEXP RHugin_node_set_alpha(SEXP Snode, SEXP Salpha, SEXP Si);
DLLEXPORT SEXP RHugin_node_set_beta(SEXP Snode, SEXP Sbeta, SEXP Sparent, SEXP Si);
DLLEXPORT SEXP RHugin_node_set_gamma(SEXP Snode, SEXP Sgamma, SEXP Si);
DLLEXPORT SEXP RHugin_node_get_alpha(SEXP Snode, SEXP Si);
DLLEXPORT SEXP RHugin_node_get_beta(SEXP Snode, SEXP Sparent, SEXP Si);
DLLEXPORT SEXP RHugin_node_get_gamma(SEXP Snode, SEXP Si);


/* Section 2.7 The name of a node */

DLLEXPORT SEXP RHugin_node_set_name(SEXP Snode, SEXP Sname);
DLLEXPORT SEXP RHugin_node_get_name(SEXP Snode);
DLLEXPORT SEXP RHugin_domain_get_node_by_name(SEXP Sdomain, SEXP Sname);


/* Section 2.8 Iterating through the nodes of a domain */

DLLEXPORT SEXP RHugin_domain_get_first_node(SEXP Sdomain);
DLLEXPORT SEXP RHugin_node_get_next(SEXP Snode);


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

DLLEXPORT SEXP RHugin_domain_save_as_kb(SEXP Sdomain, SEXP Sfile_name, SEXP Spassword);
DLLEXPORT SEXP RHugin_kb_load_domain(SEXP Sfile_name, SEXP Spassword);

/* Chapter 3: Object-Oriented Belief Networks and Influence Diagrams */


/* Section 4.2 The nodes and contents of a table */

DLLEXPORT SEXP RHugin_table_get_nodes(SEXP Stable);
DLLEXPORT SEXP RHugin_table_get_data(SEXP Stable);
DLLEXPORT SEXP RHugin_table_set_data(SEXP Stable, SEXP Sdata);
DLLEXPORT SEXP RHugin_table_get_mean(SEXP Stable, SEXP Si, SEXP Snode);
DLLEXPORT SEXP RHugin_table_get_covariance(SEXP Stable, SEXP Si, SEXP Snode1, SEXP Snode2);
DLLEXPORT SEXP RHugin_table_get_variance(SEXP Stable, SEXP Si, SEXP Snode);


/* Section 4.2 Deleting tables */

DLLEXPORT SEXP RHugin_table_delete(SEXP Stable);


/* Section 4.4 The size of a table */

DLLEXPORT SEXP RHugin_table_get_size(SEXP Stable);
DLLEXPORT SEXP RHugin_table_get_cg_size(SEXP Stable);

/* Section 4.5 Rearranging the contents of a table */

DLLEXPORT SEXP RHugin_table_reorder_nodes(SEXP Stable, SEXP Sorder);


/* Section 5.1 Subtyping of discrete nodes */

DLLEXPORT SEXP RHugin_node_set_subtype(SEXP Snode, SEXP Ssubtype);
DLLEXPORT SEXP RHugin_node_get_subtype(SEXP Snode);


/* Section 5.2 Expressions */

// Removed by Kjell Konis 16.10.2009


/* Section 5.3 Syntax for expression */

DLLEXPORT SEXP RHugin_string_parse_expression(SEXP Sstring, SEXP Smodel);
DLLEXPORT SEXP RHugin_expression_to_string(SEXP Sexpression);


/* Section 5.4 Creating and maintaining models */

DLLEXPORT SEXP RHugin_node_new_model(SEXP Snode, SEXP Smodel_nodes);
DLLEXPORT SEXP RHugin_node_get_model(SEXP Snodes);
DLLEXPORT SEXP RHugin_model_delete(SEXP Smodels);
DLLEXPORT SEXP RHugin_model_get_nodes(SEXP Smodel);
DLLEXPORT SEXP RHugin_model_get_size(SEXP Smodels);
DLLEXPORT SEXP RHugin_model_set_expression(SEXP Smodel, SEXP Sindex, SEXP Sexpression);
DLLEXPORT SEXP RHugin_model_get_expression(SEXP Smodel, SEXP Sindex);


/* Section 5.5 State labels */

DLLEXPORT SEXP RHugin_node_set_state_label(SEXP Snode, SEXP Ss, SEXP Slabel);
DLLEXPORT SEXP RHugin_node_get_state_label(SEXP Snode, SEXP Ss);
DLLEXPORT SEXP RHugin_node_get_state_index_from_label(SEXP Snode, SEXP Slabel);


/* Section 5.6 State values */

DLLEXPORT SEXP RHugin_node_set_state_value(SEXP Snode, SEXP Ss, SEXP Svalue);
DLLEXPORT SEXP RHugin_node_get_state_value(SEXP Snode, SEXP Ss);
DLLEXPORT SEXP RHugin_node_get_state_index_from_value(SEXP Snode, SEXP Svalue);


/* Section 5.8 Generating tables */

DLLEXPORT SEXP RHugin_node_generate_table(SEXP Snode);
DLLEXPORT SEXP RHugin_domain_generate_tables(SEXP Sdomain);


/* Section 5.9 How the computations are done */

DLLEXPORT SEXP RHugin_model_set_number_of_samples_per_interval(SEXP Smodel, SEXP Scount);
DLLEXPORT SEXP RHugin_model_get_number_of_samples_per_interval(SEXP Smodel);


/* Section 6.2 Compilation */

DLLEXPORT SEXP RHugin_domain_compile(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_is_compiled(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_set_max_number_of_separators(SEXP Sdomain, SEXP Scount);
DLLEXPORT SEXP RHugin_domain_get_max_number_of_separators(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_triangulate(SEXP Sdomain, SEXP Smethod);
DLLEXPORT SEXP RHugin_domain_triangulate_with_order(SEXP Sdomain, SEXP Sorder);
DLLEXPORT SEXP RHugin_domain_is_triangulated(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_get_elimination_order(SEXP Sdomain);
// SEXP RHugin_domain_parse_nodes(SEXP Sdomain, SEXP Sfile_name, SEXP Serror_fun, SEXP Sdata);
// SEXP RHugin_class_parse_nodes(SEXP Sclass, SEXP Sfile_name, SEXP Serror_fun, SEXP Sdata);


/* Section 6.4 Getting a compilation log */

// SEXP RHugin_domain_set_log_file(SEXP Sdomain, SEXP Slog_file);


/* Section 6.5 Uncompilation */

DLLEXPORT SEXP RHugin_domain_uncompile(SEXP Sdomain);


/* Section 6.5 Compression */

DLLEXPORT SEXP RHugin_domain_compress(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_is_compressed(SEXP Sdomain);


/* Section 6.7 Approxiamtion */

DLLEXPORT SEXP RHugin_domain_approximate(SEXP Sdomain, SEXP Sepsilon);
DLLEXPORT SEXP RHugin_domain_get_approximation_constant(SEXP Sdomain);


/* Section 7.2 Junction trees */

DLLEXPORT SEXP RHugin_domain_get_first_junction_tree(SEXP domain);
DLLEXPORT SEXP RHugin_jt_get_next(SEXP Sjt);
DLLEXPORT SEXP RHugin_clique_get_junction_tree(SEXP Sclique);
DLLEXPORT SEXP RHugin_node_get_junction_tree(SEXP Snode);
DLLEXPORT SEXP RHugin_jt_get_cliques(SEXP Sjt);
DLLEXPORT SEXP RHugin_jt_get_root(SEXP Sjt);


/* Section 7.3 Cliques */

DLLEXPORT SEXP RHugin_clique_get_members(SEXP Sclique);
DLLEXPORT SEXP RHugin_clique_get_neighbors(SEXP Sclique);


/* Section 8.2 Entering evidence */

DLLEXPORT SEXP RHugin_node_select_state(SEXP Snode, SEXP Sstate);
DLLEXPORT SEXP RHugin_node_enter_finding(SEXP Snode, SEXP Sstate, SEXP Svalue);
DLLEXPORT SEXP RHugin_node_enter_value(SEXP Snode, SEXP Svalue);


/* Section 8.3 Retracting evidence */

DLLEXPORT SEXP RHugin_node_retract_findings(SEXP Snode);
DLLEXPORT SEXP RHugin_domain_retract_findings(SEXP Sdomain);


/* Section 8.4 Determining independence properties */

DLLEXPORT SEXP RHugin_domain_get_d_connected_nodes(SEXP Sdomain, SEXP Ssource, SEXP Shard, SEXP Ssoft);
DLLEXPORT SEXP RHugin_domain_get_d_separated_nodes(SEXP Sdomain, SEXP Ssource, SEXP Shard, SEXP Ssoft);


/* Section 8.5 Retreiving beliefs */

DLLEXPORT SEXP RHugin_node_get_belief(SEXP Snode, SEXP Sstate);
DLLEXPORT SEXP RHugin_node_get_mean(SEXP Snode);
DLLEXPORT SEXP RHugin_node_get_variance(SEXP Snode);
DLLEXPORT SEXP RHugin_domain_get_marginal(SEXP Sdomain, SEXP Snodes);
DLLEXPORT SEXP RHugin_node_get_distribution(SEXP Snode);


/* Section 8.6 Retrieving expected utilities */

DLLEXPORT SEXP RHugin_node_get_expected_utility(SEXP Snode, SEXP Sstate);


/* Section 8.7 Examining Evidence */

DLLEXPORT SEXP RHugin_node_get_entered_finding(SEXP Snode, SEXP Sstate);
DLLEXPORT SEXP RHugin_node_get_propagated_finding(SEXP Snode, SEXP Sstate);
DLLEXPORT SEXP RHugin_node_get_entered_value(SEXP Snode);
DLLEXPORT SEXP RHugin_node_get_propagated_value(SEXP Snode);
DLLEXPORT SEXP RHugin_node_evidence_is_entered(SEXP Snode);
DLLEXPORT SEXP RHugin_node_likelihood_is_entered(SEXP Snode);
DLLEXPORT SEXP RHugin_node_evidence_is_propagated(SEXP Snode);
DLLEXPORT SEXP RHugin_node_likelihood_is_propagated(SEXP Snode);


/* Section 8.8 Case files */

DLLEXPORT SEXP RHugin_domain_save_case(SEXP Sdomain, SEXP Sfile_name);
// SEXP RHugin_domain_parse_case(SEXP Sdomain, SEXP Sfile_name, SEXP Serror_handler, SEXP Sdata);


/* Section 9.2 Propagation */

DLLEXPORT SEXP RHugin_domain_propagate(SEXP Sdomain, SEXP Sequilibrium, SEXP Sevidence_mode);
DLLEXPORT SEXP RHugin_jt_propagate(SEXP Sjt, SEXP Sequilibrium, SEXP Sevidence_mode);


/* Section 9.3 Conflict of evidence */

DLLEXPORT SEXP RHugin_domain_get_conflict(SEXP Sdomain);
DLLEXPORT SEXP RHugin_jt_get_conflict(SEXP Sjt);
DLLEXPORT SEXP RHugin_domain_reset_inference_engine(SEXP Sdomain);


/* Secttion 9.4 The normalization constant */

DLLEXPORT SEXP RHugin_domain_get_normalization_constant(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_get_log_normalization_constant(SEXP Sdomain);


/* Section 9.5 Initializing the domain */

DLLEXPORT SEXP RHugin_domain_save_to_memory(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_initialize(SEXP Sdomain);


/* Section 9.6 Querying the state of the inference engine */

DLLEXPORT SEXP RHugin_domain_equilibrium_is(SEXP Sdomain, SEXP Sequilibrium);
DLLEXPORT SEXP RHugin_jt_equilibrium_is(SEXP Sjt, SEXP Sequilibrium);
DLLEXPORT SEXP RHugin_domain_evidence_mode_is(SEXP Sdomain, SEXP Smode);
DLLEXPORT SEXP RHugin_jt_evidence_mode_is(SEXP Sjt, SEXP Smode);
DLLEXPORT SEXP RHugin_domain_evidence_is_propagated(SEXP Sdomain);
DLLEXPORT SEXP RHugin_jt_evidence_is_propagated(SEXP Sjt);
DLLEXPORT SEXP RHugin_domain_likelihood_is_propagated(SEXP Sdomain);
DLLEXPORT SEXP RHugin_jt_likelihood_is_propagated(SEXP Sjt);
DLLEXPORT SEXP RHugin_domain_cg_evidence_is_propagated(SEXP Sdomain);
DLLEXPORT SEXP RHugin_jt_cg_evidence_is_propagated(SEXP Sjt);
DLLEXPORT SEXP RHugin_domain_evidence_to_propagate(SEXP Sdomain);
DLLEXPORT SEXP RHugin_jt_evidence_to_propagate(SEXP Sjt);
DLLEXPORT SEXP RHugin_node_evidence_to_propagate(SEXP Snode);
DLLEXPORT SEXP RHugin_domain_tables_to_propagate(SEXP Sdomain);
DLLEXPORT SEXP RHugin_jt_tables_to_propagate(SEXP Sjt);


/* Section 9.7 Simulation */

DLLEXPORT SEXP RHugin_domain_simulate(SEXP Sdomain);
DLLEXPORT SEXP RHugin_node_get_sampled_state(SEXP Snode);
DLLEXPORT SEXP RHugin_node_get_sampled_value(SEXP Snode);
DLLEXPORT SEXP RHugin_domain_seed_random(SEXP Sdomain, SEXP Sseed);
DLLEXPORT SEXP RHugin_domain_get_uniform_deviate(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_get_normal_deviate(SEXP Sdomain, SEXP Smean, SEXP Svariance);


/* Section 9.8 Value of information analysis */

DLLEXPORT SEXP RHugin_node_get_entropy(SEXP Snode);
DLLEXPORT SEXP RHugin_node_get_mutual_information(SEXP Snode, SEXP Sother);


/* Section 9.9 Sensitivity analyis */

DLLEXPORT SEXP RHugin_node_compute_sensitivity_data(SEXP Snode, SEXP Sstate);
DLLEXPORT SEXP RHugin_node_get_sensitivity_constants(SEXP Snode, SEXP Sindex);
DLLEXPORT SEXP RHugin_domain_get_sensitivity_set(SEXP Sdomain);


/* Section 10.1 Experience counts and fading factors */

DLLEXPORT SEXP RHugin_node_get_experience_table(SEXP Snode);
DLLEXPORT SEXP RHugin_node_has_experience_table(SEXP Snode);
DLLEXPORT SEXP RHugin_node_get_fading_table(SEXP Snode);
DLLEXPORT SEXP RHugin_node_has_fading_table(SEXP Snode);


/* Section 10.2 Updating tables */

DLLEXPORT SEXP RHugin_domain_adapt(SEXP Sdomain);


/* Section 11.1 Data */

DLLEXPORT SEXP RHugin_domain_set_number_of_cases(SEXP Sdomain, SEXP Scount);
DLLEXPORT SEXP RHugin_domain_new_case(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_get_number_of_cases(SEXP Sdomain);
DLLEXPORT SEXP RHugin_node_set_case_state(SEXP Snode, SEXP Scase_index, SEXP Sstate);
DLLEXPORT SEXP RHugin_node_get_case_state(SEXP Snode, SEXP Scase_index);
DLLEXPORT SEXP RHugin_node_set_case_value(SEXP Snode, SEXP Scase_index, SEXP Svalue);
DLLEXPORT SEXP RHugin_node_get_case_value(SEXP Snode, SEXP Scase_index);
DLLEXPORT SEXP RHugin_node_unset_case(SEXP Snode, SEXP Scase_index);
DLLEXPORT SEXP RHugin_node_case_is_set(SEXP Snode, SEXP Scase_index);
DLLEXPORT SEXP RHugin_domain_set_case_count(SEXP Sdomain, SEXP Scase_index, SEXP Scase_count);
DLLEXPORT SEXP RHugin_domain_get_case_count(SEXP Sdomain, SEXP Scase_index);
DLLEXPORT SEXP RHugin_domain_enter_case(SEXP Sdomain, SEXP Scase_index);


/* Section 11.2 Scoring of graphical models */

DLLEXPORT SEXP RHugin_domain_get_log_likelihood(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_get_AIC(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_get_BIC(SEXP Sdomain);


/* Section 11.3 Data files */

DLLEXPORT SEXP RHugin_domain_parse_cases(SEXP Sdomain, SEXP Sfile_name);
DLLEXPORT SEXP RHugin_domain_save_cases(SEXP Sdomain, SEXP Sfile_name, SEXP Snodes, SEXP Scases,
                                        SEXP Sinclude_case_counts, SEXP Sseparator, SEXP Smissing_data);
 

/* Section 11.4 Learning network structure */

DLLEXPORT SEXP RHugin_domain_learn_structure(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_set_significance_level(SEXP Sdomain, SEXP Sprobability);
DLLEXPORT SEXP RHugin_domain_get_significance_level(SEXP Sdomain);


/* Section 11.5 Domain knowledge */

DLLEXPORT SEXP RHugin_node_set_edge_constraint(SEXP Sa, SEXP Sb, SEXP Sconstraint);
DLLEXPORT SEXP RHugin_node_get_edge_constraint(SEXP Sa, SEXP Sb);


/* Section 11.6 Learning conditional probability tables */

DLLEXPORT SEXP RHugin_domain_learn_tables(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_set_log_likelihood_tolerance(SEXP Sdomain, SEXP Stolerance);
DLLEXPORT SEXP RHugin_domain_get_log_likelihood_tolerance(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_set_max_number_of_em_iterations(SEXP Sdomain, SEXP Scount);
DLLEXPORT SEXP RHugin_domain_get_max_number_of_em_iterations(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_learn_class_tables(SEXP Sdomain);


/* Section 12.8 parsing NET files */

DLLEXPORT SEXP RHugin_net_parse_domain(SEXP Sfile_name);
DLLEXPORT SEXP RHugin_domain_save_as_net(SEXP Sdomain, SEXP Sfile_name);


/* Section 13.2 the position of a node */

DLLEXPORT SEXP RHugin_node_set_position(SEXP Snode, SEXP Sposition);
DLLEXPORT SEXP RHugin_node_get_position(SEXP Snode);


/* Section 13.3 the size of a node */

DLLEXPORT SEXP RHugin_domain_set_node_size(SEXP Sdomain, SEXP Ssize);
DLLEXPORT SEXP RHugin_domain_get_node_size(SEXP Sdomain);


