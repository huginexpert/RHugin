summary.RHuginDomain <- function(object, domain = TRUE, nodes = FALSE,
                                 jt = FALSE, print.cliques = FALSE, ...)
{
  if(is.logical(nodes)) {
    if(nodes)
      nodes <- get.nodes(object)
    else
      nodes <- character(0)
  }

  compiled <- .Call(RHugin_domain_is_compiled, object)
  domain.summary <- NULL
  
  if(domain) {
    logfile <- .Call(RHugin_domain_get_logfile, object)
    triangulated <- .Call(RHugin_domain_is_triangulated, object)
    compressed <- .Call(RHugin_domain_is_compressed, object)
    evidence.normal <- .Call(RHugin_domain_evidence_mode_is, object, "normal")
    evidence.fast <- .Call(RHugin_domain_evidence_mode_is, object, "fast")
    evidence.mode <- c("normal", "fast")[c(evidence.normal, evidence.fast)]

    if(compiled) {
      evidence.propagated <- .Call(RHugin_domain_evidence_is_propagated, object)
      equilibrium <- ifelse(.Call(RHugin_domain_equilibrium_is, object, "max"), "max", "sum")
      L.evidence.propagated <- .Call(RHugin_domain_likelihood_is_propagated, object)
      GC.evidence.propagated <- .Call(RHugin_domain_cg_evidence_is_propagated, object)
      evidence.to.propagate <- .Call(RHugin_domain_evidence_to_propagate, object)
      tables.to.propagate <- .Call(RHugin_domain_tables_to_propagate, object)
    }

    else {
      evidence.propagated <- NULL
      equilibrium <- NULL
      L.evidence.propagated <- NULL
      GC.evidence.propagated <- NULL
      evidence.to.propagate <- NULL
      tables.to.propagate <- NULL
    }

    domain.summary <- list(logfile = logfile,
                           triangulated = triangulated,
                           compiled = compiled,
                           compressed = compressed,
                           evidence.propagated = evidence.propagated,
                           equilibrium = equilibrium,
                           evidence.mode = evidence.mode,
                           L.evidence.propagated = L.evidence.propagated,
                           GC.evidence.propagated = GC.evidence.propagated,
                           evidence.to.propagate = evidence.to.propagate,
                           tables.to.propagate = tables.to.propagate)
  }


  node.summary <- NULL

  if(length(nodes)) {
    node.summary <- list()

    node.ptrs <- nodePointersFromNames(object, nodes)
    categories <- .Call(RHugin_node_get_category, node.ptrs)
    kinds <- .Call(RHugin_node_get_kind, node.ptrs)
    subtypes <- .Call(RHugin_node_get_subtype, node.ptrs)

    for(node in nodes) {
      category <- categories[node]
      kind <- kinds[node]
      subtype <- subtypes[node]
      subtype <- if(subtype == "error") NULL else subtype
      states <- NULL
      model <- FALSE
      model.size <- NULL
      size <- NULL
      cgsize <- NULL
      evidence.is.entered <- FALSE
      likelihood.is.entered <- FALSE
      evidence.is.propagated <- FALSE
      likelihood.is.propagated <- FALSE
      experience.table <- FALSE
      fading.table <- FALSE

      if(is.element(category, c("chance", "decision")) && kind == "discrete")
        states <- get.states(object, node)

      table.ptr <- .Call(RHugin_node_get_table, node.ptrs[node])
      size <- .Call(RHugin_table_get_size, table.ptr)
      cgsize <- .Call(RHugin_table_get_cg_size, table.ptr)

      if(kind %in% c("discrete", "utility", "function")) {
        model.ptr <- .Call(RHugin_node_get_model, node.ptrs[node])
        if(!is.null(model.ptr[[node]])) {
          model <- TRUE
          model.size <- .Call(RHugin_model_get_size, model.ptr)
        }
      }

      if(is.element(category, c("chance", "decision"))) {
        evidence.is.entered <- .Call(RHugin_node_evidence_is_entered, node.ptrs[node])
        likelihood.is.entered <- .Call(RHugin_node_likelihood_is_entered, node.ptrs[node])
      }

      if(compiled && is.element(category, c("chance", "decision"))) {
        evidence.is.propagated <- .Call(RHugin_node_evidence_is_propagated, node.ptrs[node])
        likelihood.is.propagated <- .Call(RHugin_node_likelihood_is_propagated, node.ptrs[node])
      }

      if(category == "chance")
        experience.table <- .Call(RHugin_node_has_experience_table, node.ptrs[node])

      if(category == "chance" && kind == "discrete")
        fading.table <- .Call(RHugin_node_has_fading_table, node.ptrs[node])

      node.summary[[node]] <- list(category = category,
                                   kind = kind,
                                   subtype = subtype,
                                   states = states,
                                   model = model,
                                   model.size = model.size,
                                   size = size,
                                   cgsize = cgsize,
                                   evidence.is.entered = evidence.is.entered,
                                   likelihood.is.entered = likelihood.is.entered,
                                   evidence.is.propagated = evidence.is.propagated,
                                   likelihood.is.propagated = likelihood.is.propagated,
                                   experience.table = experience.table,
                                   fading.table = fading.table)
    }
  }

  jt.summary <- NULL

  if(jt && .Call(RHugin_domain_is_triangulated, object)) {

    jt.summary <- list()
    jts <- list(.Call(RHugin_domain_get_first_junction_tree, object))

    while(!is.null(njt <- .Call(RHugin_jt_get_next, jts[[length(jts)]])))
      jts <- c(jts, njt)

    for(i in 1:length(jts)) {
      jt.summary[[i]] <- list()
      jt.summary[[i]]$size <- .Call(RHugin_jt_get_total_size, jts[i])
      jt.summary[[i]]$cgsize <- .Call(RHugin_jt_get_total_cg_size, jts[i])
      cliques <- .Call(RHugin_jt_get_cliques, jts[i])
      clique.members <- .Call(RHugin_clique_get_members, cliques)
      clique.nodes <- lapply(clique.members, names)
      names(clique.nodes) <- paste("clique", 1:length(clique.nodes))
      jt.summary[[i]]$cliques <- clique.nodes
    }

    if(print.cliques)
      attr(jt.summary, "print.cliques") <- TRUE
  }

  ans <- list()
  ans[["domain"]] <- domain.summary
  ans[["nodes"]] <- node.summary
  ans[["jt"]] <- jt.summary
  oldClass(ans) <- "summary.RHuginDomain"
  ans
}


