/*******************************************************************************
 * The Hugin API 
 ******************************************************************************/

/* 1.6 Errors */

DLLEXPORT SEXP RHugin_error_code(void);


/* 1.6.1 Handling errors */

DLLEXPORT SEXP RHugin_error_name(SEXP Scode);
DLLEXPORT SEXP RHugin_error_description(SEXP Scode);


/* 1.7 Taking advantage of multiple processors */

DLLEXPORT SEXP RHugin_domain_set_concurrency_level(SEXP Sdomain, SEXP Slevel);
DLLEXPORT SEXP RHugin_domain_get_concurrency_level(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_set_grain_size(SEXP Sdomain, SEXP Ssize);
DLLEXPORT SEXP RHugin_domain_get_grain_size(SEXP Sdomain);


/* 2.2 Domains: Creation and deletion */

DLLEXPORT SEXP RHugin_new_domain(void);
DLLEXPORT SEXP RHugin_domain_delete(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_clone(SEXP Sdomain);


/* 2.3 Nodes: Creation and deletion */

DLLEXPORT SEXP RHugin_domain_new_node(SEXP Sdomain, SEXP Scategory, SEXP Skind);
// SEXP RHugin_node_get_domain(SEXP Snode);
DLLEXPORT SEXP RHugin_node_get_category(SEXP Snodes);
DLLEXPORT SEXP RHugin_node_get_kind(SEXP Snodes);
// SEXP RHugin_node_set_category(SEXP Snode);
DLLEXPORT SEXP RHugin_node_delete(SEXP Snodes);
DLLEXPORT SEXP RHugin_node_clone(SEXP Snode);


/* 2.4 The links of the network */

DLLEXPORT SEXP RHugin_node_add_parent(SEXP Schild, SEXP Sparents);
DLLEXPORT SEXP RHugin_node_remove_parent(SEXP Snode, SEXP Sparent);
DLLEXPORT SEXP RHugin_node_switch_parent(SEXP Snode, SEXP Sold_parent, SEXP Snew_parent);
DLLEXPORT SEXP RHugin_node_reverse_edge(SEXP Snode1, SEXP Snode2);
DLLEXPORT SEXP RHugin_node_get_parents(SEXP Snodes);
DLLEXPORT SEXP RHugin_node_get_children(SEXP Snodes);


/* 2.4.1 The requisite parents and ancestors of decision nodes */

DLLEXPORT SEXP RHugin_node_get_requisite_parents(SEXP Snodes);
DLLEXPORT SEXP RHugin_node_get_requisite_ancestors(SEXP Snodes);


/* 2.5 The number of states of a node */

DLLEXPORT SEXP RHugin_node_set_number_of_states(SEXP Snode, SEXP Sstates);
DLLEXPORT SEXP RHugin_node_get_number_of_states(SEXP Snode);


/* 2.6 The conditional probability and the utility table */

DLLEXPORT SEXP RHugin_node_get_table(SEXP Snode);
DLLEXPORT SEXP RHugin_node_touch_table(SEXP Snode);
DLLEXPORT SEXP RHugin_node_set_alpha(SEXP Snode, SEXP Salpha, SEXP Si);
DLLEXPORT SEXP RHugin_node_set_beta(SEXP Snode, SEXP Sbeta, SEXP Sparent, SEXP Si);
DLLEXPORT SEXP RHugin_node_set_gamma(SEXP Snode, SEXP Sgamma, SEXP Si);
DLLEXPORT SEXP RHugin_node_get_alpha(SEXP Snode, SEXP Si);
DLLEXPORT SEXP RHugin_node_get_beta(SEXP Snode, SEXP Sparent, SEXP Si);
DLLEXPORT SEXP RHugin_node_get_gamma(SEXP Snode, SEXP Si);


/* 2.7 The name of a node */

DLLEXPORT SEXP RHugin_node_set_name(SEXP Snode, SEXP Sname);
DLLEXPORT SEXP RHugin_node_get_name(SEXP Snode);
DLLEXPORT SEXP RHugin_domain_get_node_by_name(SEXP Sdomain, SEXP Snames);


/* 2.8 Iterating through the nodes of a domain */

DLLEXPORT SEXP RHugin_domain_get_first_node(SEXP Sdomain);
DLLEXPORT SEXP RHugin_node_get_next(SEXP Snode);


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

DLLEXPORT SEXP RHugin_domain_save_as_kb(SEXP Sdomain, SEXP Sfile_name, SEXP Spassword);
DLLEXPORT SEXP RHugin_kb_load_domain(SEXP Sfile_name, SEXP Spassword);
// DLLEXPORT SEXP RHugin_domain_get_file_name(SEXP Sdomain);

/* 3.2 Creating classes and class collections */
DLLEXPORT SEXP RHugin_new_class_collection();
DLLEXPORT SEXP RHugin_cc_new_class(SEXP Sclass_collection);
DLLEXPORT SEXP RHugin_cc_get_members(SEXP Sclass_collection);
DLLEXPORT SEXP RHugin_class_get_class_collection(SEXP Sclass);

/* 3.3 Deleting classes and class collections */
DLLEXPORT SEXP RHugin_cc_delete(SEXP Sclass_collection);
DLLEXPORT SEXP RHugin_class_delete(SEXP Sclass);

/* 3.4 Naming classes */
DLLEXPORT SEXP RHugin_class_set_name(SEXP Sclass, SEXP Sname);
DLLEXPORT SEXP RHugin_class_get_name(SEXP Sclass);
DLLEXPORT SEXP RHugin_cc_get_class_by_name(SEXP Sclass_collection, SEXP Sname);

/* 3.5 Creating basic nodes */
DLLEXPORT SEXP RHugin_class_new_node(SEXP Sclass, SEXP Scategory, SEXP Skind);
DLLEXPORT SEXP RHugin_node_get_home_class(SEXP Snode);

/* 3.6 Naming nodes */
DLLEXPORT SEXP RHugin_class_get_node_by_name(SEXP Sclass, SEXP Sname);

/* 3.7 The interface of a class */
DLLEXPORT SEXP RHugin_node_add_to_input(SEXP Snode);
DLLEXPORT SEXP RHugin_class_get_inputs(SEXP Sclass);
DLLEXPORT SEXP RHugin_node_remove_from_inputs(SEXP Snode);
DLLEXPORT SEXP RHugin_node_add_to_outputs(SEXP Snode);
DLLEXPORT SEXP RHugin_class_get_outputs(SEXP Sclass);
DLLEXPORT SEXP RHugin_node_remove_from_outputs(SEXP Snode);

/* 3.8 Creating instances of classes */
DLLEXPORT SEXP RHugin_class_new_instance(SEXP Sclass1, SEXP Sclass2);
DLLEXPORT SEXP RHugin_node_get_instance_class(SEXP Snode);
DLLEXPORT SEXP RHugin_class_get_instance(SEXP Snode);
DLLEXPORT SEXP RHugin_node_get_master(SEXP Snode);
DLLEXPORT SEXP RHugin_node_get_instance(SEXP Snode);
DLLEXPORT SEXP RHugin_node_get_output(SEXP Snode1, SEXP Snode2);
DLLEXPORT SEXP RHugin_node_substitute_class(SEXP Snode, SEXP Sclass);

/* 3.9 Putting the pieces together */
DLLEXPORT SEXP RHugin_node_set_input(SEXP Snode1, SEXP Snode2, SEXP Snode3);
DLLEXPORT SEXP RHugin_node_get_input(SEXP Snode1, SEXP Snode2);
DLLEXPORT SEXP RHugin_node_unset_input(SEXP Snode1, SEXP Snode2);

/* 3.10 Creating a runtime domain */
DLLEXPORT SEXP RHugin_class_create_domain(SEXP Sclass);
DLLEXPORT SEXP RHugin_node_get_source(SEXP Snode);

/* 3.11 Node iterator */
DLLEXPORT SEXP RHugin_class_get_first_node(SEXP Sclass);

/* 3.12 User data */
/*DLLEXPORT SEXP RHugin_class_set_user_data(SEXP Sclass, SEXP Sdata);
DLLEXPORT SEXP RHugin_class_get_user_data(SEXP Sclass);
DLLEXPORT SEXP RHugin_class_set_attribute(SEXP Sclass, SEXP Skey, SEXP Svalue);
DLLEXPORT SEXP RHugin_class_get_attribute(SEXP Sclass, SEXP Skey);
DLLEXPORT SEXP RHugin_class_get_first_attribute(SEXP Sclass);*/

/* 3.13 Saving class collections as HKB files */
DLLEXPORT SEXP RHugin_cc_save_as_kb(SEXP Sclass_collection, SEXP Sfile_name, SEXP Spassword);
DLLEXPORT SEXP RHugin_kb_load_class_collection(SEXP Sfile_name, SEXP Spassword);
DLLEXPORT SEXP RHugin_class_get_file_name(SEXP Sclass);

/* 4.1 Temporal clones */
DLLEXPORT SEXP RHugin_node_create_temporal_clone(SEXP Snode);
DLLEXPORT SEXP RHugin_node_get_temporal_clone(SEXP Snode);
DLLEXPORT SEXP RHugin_node_get_temporal_master(SEXP Snode);

/* 4.2 DBN runtime domains */
DLLEXPORT SEXP RHugin_class_create_dbn_domain(SEXP Sclass, SEXP Snumber_of_slices);

/* 4.3 Inference in DBNs */
DLLEXPORT SEXP RHugin_domain_triangulate_dbn(SEXP Sdomain, SEXP Striangulation_method);
DLLEXPORT SEXP RHugin_domain_move_dbn_window(SEXP Sdomain, SEXP Ssize);
DLLEXPORT SEXP RHugin_domain_get_dbn_window_offset(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_initialize_dbn_window(SEXP Sdomain);

/* 4.4 Prediction */
DLLEXPORT SEXP RHugin_domain_compute_dbn_predictions(SEXP Sdomain, SEXP Snumber_of_time_instants);
DLLEXPORT SEXP RHugin_node_get_predicted_belief(SEXP Snode, SEXP Ss, SEXP Stime);
DLLEXPORT SEXP RHugin_node_get_predicted_mean(SEXP Snode, SEXP Stime);
DLLEXPORT SEXP RHugin_node_get_predicted_variance(SEXP Snode, SEXP Stime);
DLLEXPORT SEXP RHugin_node_get_predicted_value(SEXP Snode, SEXP Stime);

/* 4.5 The Boyen-Koller approximation algorithm */
DLLEXPORT SEXP RHugin_domain_triangulate_dbn_for_bk(SEXP Sdomain, SEXP Striangulation_method);
DLLEXPORT SEXP RHugin_domain_is_triangulated_for_bk(SEXP Sdomain);


/* 5.1 What is a table? */

// SEXP RHugin_table_get_index_from_configuration(SEXP Stable, SEXP Sconfiguration);
// SEXP RHugin_table_get_configuration_from_index(SEXP Stable, SEXP Sconfiguration, SEXP Sindex);


/* 5.2 The nodes and the contents of a table */

DLLEXPORT SEXP RHugin_table_get_nodes(SEXP Stable);
DLLEXPORT SEXP RHugin_table_get_data(SEXP Stable);
DLLEXPORT SEXP RHugin_table_set_data(SEXP Stable, SEXP Sdata);
DLLEXPORT SEXP RHugin_table_get_mean(SEXP Stable, SEXP Si, SEXP Snode);
DLLEXPORT SEXP RHugin_table_get_covariance(SEXP Stable, SEXP Si, SEXP Snode1, SEXP Snode2);
DLLEXPORT SEXP RHugin_table_get_variance(SEXP Stable, SEXP Si, SEXP Snode);


/* 5.3 Deleting tables */

DLLEXPORT SEXP RHugin_table_delete(SEXP Stable);


/* 5.4 The size of a table */

DLLEXPORT SEXP RHugin_table_get_size(SEXP Stable);
DLLEXPORT SEXP RHugin_table_get_cg_size(SEXP Stable);


/* 5.5 Rearranging the contents of a table */

DLLEXPORT SEXP RHugin_table_reorder_nodes(SEXP Stable, SEXP Sorder);


/* 6.1 Subtyping of discrete nodes */

DLLEXPORT SEXP RHugin_node_set_subtype(SEXP Snode, SEXP Ssubtype);
DLLEXPORT SEXP RHugin_node_get_subtype(SEXP Snodes);


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

DLLEXPORT SEXP RHugin_node_new_model(SEXP Snode, SEXP Smodel_nodes);
DLLEXPORT SEXP RHugin_node_get_model(SEXP Snodes);
DLLEXPORT SEXP RHugin_model_delete(SEXP Smodels);
DLLEXPORT SEXP RHugin_model_get_nodes(SEXP Smodel);
DLLEXPORT SEXP RHugin_model_get_size(SEXP Smodels);
DLLEXPORT SEXP RHugin_model_set_expression(SEXP Smodel, SEXP Sexpressions);
DLLEXPORT SEXP RHugin_model_get_expression(SEXP Smodel);


/* 6.5 State labels */

DLLEXPORT SEXP RHugin_node_set_state_label(SEXP Snode, SEXP Ss, SEXP Slabels);
DLLEXPORT SEXP RHugin_node_get_state_label(SEXP Snode, SEXP Ss);
DLLEXPORT SEXP RHugin_node_get_state_index_from_label(SEXP Snode, SEXP Slabels);


/* 6.6 State values */

DLLEXPORT SEXP RHugin_node_set_state_value(SEXP Snode, SEXP Ss, SEXP Svalues);
DLLEXPORT SEXP RHugin_node_get_state_value(SEXP Snode, SEXP Ss);
DLLEXPORT SEXP RHugin_node_get_state_index_from_value(SEXP Snode, SEXP Svalues);


/* 6.8 Generating tables */

DLLEXPORT SEXP RHugin_node_generate_table(SEXP Snode);
DLLEXPORT SEXP RHugin_domain_generate_tables(SEXP Sdomain);
// SEXP RHugin_class_generate_tables(SEXP Sclass);
// SEXP RHugin_class_set_log_file(SEXP Sclass, SEXP Slog_file);


/* 6.9 How the computations are done */

DLLEXPORT SEXP RHugin_model_set_number_of_samples_per_interval(SEXP Smodel, SEXP Scount);
DLLEXPORT SEXP RHugin_model_get_number_of_samples_per_interval(SEXP Smodel);


/* 7.2 Compilation */

DLLEXPORT SEXP RHugin_domain_compile(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_is_compiled(SEXP Sdomain);


/* 7.3 Triangulation */

DLLEXPORT SEXP RHugin_domain_set_initial_triangulation(SEXP Sdomain, SEXP Sorder);
DLLEXPORT SEXP RHugin_domain_set_max_number_of_separators(SEXP Sdomain, SEXP Scount);
DLLEXPORT SEXP RHugin_domain_get_max_number_of_separators(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_set_max_separator_size(SEXP Sdomain, SEXP Ssize);
DLLEXPORT SEXP RHugin_domain_get_max_separator_size(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_triangulate(SEXP Sdomain, SEXP Smethod);
DLLEXPORT SEXP RHugin_domain_triangulate_with_order(SEXP Sdomain, SEXP Sorder);
DLLEXPORT SEXP RHugin_domain_is_triangulated(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_get_elimination_order(SEXP Sdomain);
// SEXP RHugin_domain_parse_nodes(SEXP Sdomain, SEXP Sfile_name, SEXP Serror_fun, SEXP Sdata);
// SEXP RHugin_class_parse_nodes(SEXP Sclass, SEXP Sfile_name, SEXP Serror_fun, SEXP Sdata);


/* 7.4 Getting a compilation log */

DLLEXPORT SEXP RHugin_domain_set_log_file(SEXP Sdomain, SEXP Sfile_name);


/* 7.5 Uncompilation */

DLLEXPORT SEXP RHugin_domain_uncompile(SEXP Sdomain);


/* 7.6 Compression */

DLLEXPORT SEXP RHugin_domain_compress(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_is_compressed(SEXP Sdomain);


/* 7.7 Approximation */

DLLEXPORT SEXP RHugin_domain_approximate(SEXP Sdomain, SEXP Sepsilon);
DLLEXPORT SEXP RHugin_domain_get_approximation_constant(SEXP Sdomain);


/* 8.2 Junction trees */

DLLEXPORT SEXP RHugin_domain_get_first_junction_tree(SEXP Sdomain);
DLLEXPORT SEXP RHugin_jt_get_next(SEXP Sjt);
DLLEXPORT SEXP RHugin_clique_get_junction_tree(SEXP Sclique);
DLLEXPORT SEXP RHugin_node_get_junction_tree(SEXP Snode);
DLLEXPORT SEXP RHugin_jt_get_cliques(SEXP Sjt);
DLLEXPORT SEXP RHugin_jt_get_root(SEXP Sjt);
DLLEXPORT SEXP RHugin_jt_get_total_size(SEXP Sjt);
DLLEXPORT SEXP RHugin_jt_get_total_cg_size(SEXP Sjt);


/* 8.3 Cliques */

DLLEXPORT SEXP RHugin_clique_get_members(SEXP Scliques);
DLLEXPORT SEXP RHugin_clique_get_neighbors(SEXP Sclique);


/* 9.2 Entering evidence */

DLLEXPORT SEXP RHugin_node_select_state(SEXP Snode, SEXP Sstate);
DLLEXPORT SEXP RHugin_node_enter_finding(SEXP Snode, SEXP Sstates, SEXP Svalues);
DLLEXPORT SEXP RHugin_node_enter_value(SEXP Snode, SEXP Svalue);


/* 9.3 Retracting evidence */

DLLEXPORT SEXP RHugin_node_retract_findings(SEXP Snodes);
DLLEXPORT SEXP RHugin_domain_retract_findings(SEXP Sdomain);


/* 9.4 Determining independence properties */

DLLEXPORT SEXP RHugin_domain_get_d_connected_nodes(SEXP Sdomain, SEXP Ssource, SEXP Shard, SEXP Ssoft);
DLLEXPORT SEXP RHugin_domain_get_d_separated_nodes(SEXP Sdomain, SEXP Ssource, SEXP Shard, SEXP Ssoft);


/* 9.5 Retreiving beliefs */

DLLEXPORT SEXP RHugin_node_get_belief(SEXP Snode, SEXP Sstates);
DLLEXPORT SEXP RHugin_node_get_mean(SEXP Snode);
DLLEXPORT SEXP RHugin_node_get_variance(SEXP Snode);
DLLEXPORT SEXP RHugin_domain_get_marginal(SEXP Sdomain, SEXP Snodes);
DLLEXPORT SEXP RHugin_node_get_distribution(SEXP Snode);


/* 9.6 Retrieving expected utilities */

DLLEXPORT SEXP RHugin_node_get_expected_utility(SEXP Snode, SEXP Sstates);
DLLEXPORT SEXP RHugin_domain_get_expected_utility(SEXP Sdomain);


/* 9.7 Computing function values */

DLLEXPORT SEXP RHugin_node_get_value(SEXP Snode);


/* 9.8 Examining Evidence */

DLLEXPORT SEXP RHugin_node_get_entered_finding(SEXP Snode, SEXP Sstates);
DLLEXPORT SEXP RHugin_node_get_propagated_finding(SEXP Snode, SEXP Sstates);
DLLEXPORT SEXP RHugin_node_get_entered_value(SEXP Snode);
DLLEXPORT SEXP RHugin_node_get_propagated_value(SEXP Snode);
DLLEXPORT SEXP RHugin_node_evidence_is_entered(SEXP Snode);
DLLEXPORT SEXP RHugin_node_likelihood_is_entered(SEXP Snode);
DLLEXPORT SEXP RHugin_node_evidence_is_propagated(SEXP Snode);
DLLEXPORT SEXP RHugin_node_likelihood_is_propagated(SEXP Snode);


/* 9.9 Case files */

DLLEXPORT SEXP RHugin_domain_save_case(SEXP Sdomain, SEXP Sfile_name);
DLLEXPORT SEXP RHugin_domain_parse_case(SEXP Sdomain, SEXP Sfile_name);


/* 10.2 Propagation */

DLLEXPORT SEXP RHugin_domain_propagate(SEXP Sdomain, SEXP Sequilibrium, SEXP Smode);
DLLEXPORT SEXP RHugin_jt_propagate(SEXP Sjt, SEXP Sequilibrium, SEXP Smode);


/* 10.3 Inference in LIMIDs: Computing optimal policies */

DLLEXPORT SEXP RHugin_domain_update_policies(SEXP Sdomain);


/* 10.4 Conflict of evidence */

DLLEXPORT SEXP RHugin_domain_get_conflict(SEXP Sdomain);
DLLEXPORT SEXP RHugin_jt_get_conflict(SEXP Sjt);


/* 10.5 The normalization constant */

DLLEXPORT SEXP RHugin_domain_get_normalization_constant(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_get_log_normalization_constant(SEXP Sdomain);


/* 10.6 Initializing the inference engine */

DLLEXPORT SEXP RHugin_domain_save_to_memory(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_reset_inference_engine(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_initialize(SEXP Sdomain);


/* 10.7 Querying the state of the inference engine */

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


/* 10.8 Simulation */

DLLEXPORT SEXP RHugin_domain_simulate(SEXP Sdomain);
DLLEXPORT SEXP RHugin_node_get_sampled_state(SEXP Snode);
DLLEXPORT SEXP RHugin_node_get_sampled_value(SEXP Snode);
DLLEXPORT SEXP RHugin_node_get_sampled_utility(SEXP Snode);
DLLEXPORT SEXP RHugin_domain_seed_random(SEXP Sdomain, SEXP Sseed);
DLLEXPORT SEXP RHugin_domain_get_uniform_deviate(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_get_normal_deviate(SEXP Sdomain, SEXP Smean, SEXP Svariance);


/* 10.9 Value of information analysis */

DLLEXPORT SEXP RHugin_node_get_entropy(SEXP Snodes);
DLLEXPORT SEXP RHugin_node_get_mutual_information(SEXP Snodes, SEXP Sothers);


/* Section 10.10 Sensitivity analyis */

DLLEXPORT SEXP RHugin_node_compute_sensitivity_data(SEXP Snode, SEXP Sstate);
DLLEXPORT SEXP RHugin_node_get_sensitivity_constants(SEXP Snode, SEXP Sindex);
DLLEXPORT SEXP RHugin_domain_get_sensitivity_set(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_compute_sensitivity_data(SEXP Sdomain, SEXP Snodes, SEXP Sstates);
DLLEXPORT SEXP RHugin_node_get_sensitivity_constants_by_output(SEXP Snode, SEXP Sinput, SEXP Soutput);
DLLEXPORT SEXP RHugin_domain_get_sensitivity_set_by_output(SEXP Sdomain, SEXP Soutput);


/* 10.11 Most probable configurations */

DLLEXPORT SEXP RHugin_domain_find_map_configurations(SEXP Sdomain, SEXP Snodes, SEXP Spmin);
DLLEXPORT SEXP RHugin_domain_get_number_of_map_configurations(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_get_map_configuration(SEXP Sdomain, SEXP Sindex, SEXP Sn_nodes);
DLLEXPORT SEXP RHugin_domain_get_probability_of_map_configuration(SEXP Sdomain, SEXP Sindex);


/* 11.1 Experience counts and fading factors */

DLLEXPORT SEXP RHugin_node_get_experience_table(SEXP Snode);
DLLEXPORT SEXP RHugin_node_has_experience_table(SEXP Snode);
DLLEXPORT SEXP RHugin_node_get_fading_table(SEXP Snode);
DLLEXPORT SEXP RHugin_node_has_fading_table(SEXP Snode);


/* 11.2 Updating tables */

DLLEXPORT SEXP RHugin_domain_adapt(SEXP Sdomain);


/* 12.1 Data */

DLLEXPORT SEXP RHugin_domain_set_number_of_cases(SEXP Sdomain, SEXP Scount);
DLLEXPORT SEXP RHugin_domain_new_case(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_get_number_of_cases(SEXP Sdomain);
DLLEXPORT SEXP RHugin_node_set_case_state(SEXP Snode, SEXP Scase_indices, SEXP Sstates);
DLLEXPORT SEXP RHugin_node_get_case_state(SEXP Snode, SEXP Scase_indices);
DLLEXPORT SEXP RHugin_node_set_case_value(SEXP Snode, SEXP Scase_indices, SEXP Svalues);
DLLEXPORT SEXP RHugin_node_get_case_value(SEXP Snode, SEXP Scase_indices);
DLLEXPORT SEXP RHugin_node_unset_case(SEXP Snode, SEXP Scase_indices);
DLLEXPORT SEXP RHugin_node_case_is_set(SEXP Snode, SEXP Scase_indices);
DLLEXPORT SEXP RHugin_domain_set_case_count(SEXP Sdomain, SEXP Scase_indices, SEXP Scase_counts);
DLLEXPORT SEXP RHugin_domain_get_case_count(SEXP Sdomain, SEXP Scase_indices);
DLLEXPORT SEXP RHugin_domain_enter_case(SEXP Sdomain, SEXP Scase_index);


/* 12.2 Scoring of graphical models */

DLLEXPORT SEXP RHugin_domain_get_log_likelihood(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_get_AIC(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_get_BIC(SEXP Sdomain);


/* 12.3 Data files */

DLLEXPORT SEXP RHugin_domain_parse_cases(SEXP Sdomain, SEXP Sfile_name);
DLLEXPORT SEXP RHugin_domain_save_cases(SEXP Sdomain, SEXP Sfile_name, SEXP Snodes,
                                        SEXP Scases, SEXP Sinclude_case_counts,
                                        SEXP Sseparator, SEXP Smissing_data);


/* 12.4 Learning network structure */

DLLEXPORT SEXP RHugin_domain_learn_structure(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_set_significance_level(SEXP Sdomain, SEXP Sprobability);
DLLEXPORT SEXP RHugin_domain_get_significance_level(SEXP Sdomain);


/* 12.5 Domain knowledge */

DLLEXPORT SEXP RHugin_node_set_edge_constraint(SEXP Sa, SEXP Sb, SEXP Sconstraint);
DLLEXPORT SEXP RHugin_node_get_edge_constraint(SEXP Sa, SEXP Sb);


/* 12.6 Learning conditional probability tables */

DLLEXPORT SEXP RHugin_domain_learn_tables(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_set_log_likelihood_tolerance(SEXP Sdomain, SEXP Stolerance);
DLLEXPORT SEXP RHugin_domain_get_log_likelihood_tolerance(SEXP Sdomain);
DLLEXPORT SEXP RHugin_domain_set_max_number_of_em_iterations(SEXP Sdomain, SEXP Scount);
DLLEXPORT SEXP RHugin_domain_get_max_number_of_em_iterations(SEXP Sdomain);
// SEXP RHugin_domain_learn_class_tables(SEXP Sdomain);


/* 13.8 parsing NET files */

DLLEXPORT SEXP RHugin_net_parse_domain(SEXP Sfile_name);
DLLEXPORT SEXP RHugin_net_parse_classes(SEXP Sfile_name);
DLLEXPORT SEXP RHugin_domain_save_as_net(SEXP Sdomain, SEXP Sfile_name);


/* 13.9 Saving class collections, classes, and domains as NET files */

// SEXP RHugin_cc_save_as_net(SEXP Scc, SEXP Sfile_name);
// SEXP RHugin_class_save_as_net(SEXP Sclass, SEXP Sfile_name);
// SEXP RHugin_domain_save_as_net(SEXP Sdomain, SEXP Sfile_name);
// SEXP RHugin_class_get_file_name(SEXP Sclass);
// SEXP RHugin_domain_get_file_name(SEXP Sdomain);


/* 14.1 The label of a node */

DLLEXPORT SEXP RHugin_node_set_label(SEXP Snode, SEXP Slabel);
DLLEXPORT SEXP RHugin_node_get_label(SEXP Snode);


/*  14.2 The position of a node */

DLLEXPORT SEXP RHugin_node_set_position(SEXP Snode, SEXP Sposition);
DLLEXPORT SEXP RHugin_node_get_position(SEXP Snode);


/* 14.3 The size of a node */

DLLEXPORT SEXP RHugin_domain_set_node_size(SEXP Sdomain, SEXP Ssize);
DLLEXPORT SEXP RHugin_domain_get_node_size(SEXP Sdomain);
// SEXP RHugin_class_set_node_size(SEXP Sclass, SEXP Ssize);
// SEXP RHugin_class_get_node_size(SEXP Sclass);


