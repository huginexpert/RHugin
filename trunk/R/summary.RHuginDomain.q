summary.RHuginDomain <- function(object, domain = TRUE, nodes = FALSE, ...)
{
  RHugin.check.domain(object, "summary.RHuginDomain")

  if(is.logical(nodes)) {
    if(nodes)
      nodes <- get.nodes(object)
    else
      nodes <- character(0)
  }

  RHugin.check.args(object, nodes, character(0), "summary.RHuginDomain")

  compiled <- .Call("RHugin_domain_is_compiled", object, PACKAGE = "RHugin")
  domain.summary <- NULL
  
  if(domain) {
    triangulated <- .Call("RHugin_domain_is_triangulated", object,
                           PACKAGE = "RHugin")

    compressed <- .Call("RHugin_domain_is_compressed", object,
                         PACKAGE = "RHugin")

    evidence.normal <- .Call("RHugin_domain_evidence_mode_is", object,
                             "normal", PACKAGE = "RHugin")

    evidence.fast <- .Call("RHugin_domain_evidence_mode_is", object,
                           "fast", PACKAGE = "RHugin")

    evidence.mode <- c("normal", "fast")[c(evidence.normal, evidence.fast)]

    if(compiled) {
      evidence.propagated <- .Call("RHugin_domain_evidence_is_propagated",
                                    object, PACKAGE = "RHugin")

      equilibrium <- ifelse(.Call("RHugin_domain_equilibrium_is", object,
                                  "max", PACKAGE = "RHugin"),
                            "max", "sum")

      L.evidence.propagated <- .Call("RHugin_domain_likelihood_is_propagated",
                                      object, PACKAGE = "RHugin")

      GC.evidence.propagated <- .Call("RHugin_domain_cg_evidence_is_propagated",
                                       object, PACKAGE = "RHugin")

      evidence.to.propagate <- .Call("RHugin_domain_evidence_to_propagate",
                                      object, PACKAGE = "RHugin")

      tables.to.propagate <- .Call("RHugin_domain_tables_to_propagate", object,
                                    PACKAGE = "RHugin")
    }

    else {
      evidence.propagated <- NULL
      equilibrium <- NULL
      L.evidence.propagated <- NULL
      GC.evidence.propagated <- NULL
      evidence.to.propagate <- NULL
      tables.to.propagate <- NULL
    }

    domain.summary <- list(triangulated = triangulated,
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

    node.ptrs <- .Call("RHugin_domain_get_node_by_name", object, nodes,
                        PACKAGE = "RHugin")
    categories <- .Call("RHugin_node_get_category", node.ptrs,
                         PACKAGE = "RHugin")
    kinds <- .Call("RHugin_node_get_kind", node.ptrs, PACKAGE = "RHugin")
    subtypes <- .Call("RHugin_node_get_subtype", node.ptrs, PACKAGE = "RHugin")

    for(node in nodes) {
      category <- categories[node]
      kind <- kinds[node]
      kind <- if(is.na(kind)) NULL else kind
      subtype <- subtypes[node]
      subtype <- if(is.na(subtype)) NULL else subtype
      states <- NULL
      evidence.is.entered <- FALSE
      likelihood.is.entered <- FALSE
      evidence.is.propagated <- FALSE
      likelihood.is.propagated <- FALSE
      experience.table <- FALSE
      fading.table <- FALSE

      if(is.element(category, c("chance", "decision")) && kind == "discrete")
        states <- get.states(object, node)

      if(is.element(category, c("chance", "decision"))) {
        evidence.is.entered <- .Call("RHugin_node_evidence_is_entered",
                                      node.ptrs[node], PACKAGE = "RHugin")
        likelihood.is.entered <- .Call("RHugin_node_likelihood_is_entered",
                                        node.ptrs[node], PACKAGE = "RHugin")
      }

      if(compiled && is.element(category, c("chance", "decision"))) {
        evidence.is.propagated <- .Call("RHugin_node_evidence_is_propagated",
                                         node.ptrs[node], PACKAGE = "RHugin")
        likelihood.is.propagated <- .Call("RHugin_node_likelihood_is_propagated",
                                         node.ptrs[node], PACKAGE = "RHugin")
      }

      if(category == "chance")
        experience.table <- .Call("RHugin_node_has_experience_table",
                                   node.ptrs[node], PACKAGE = "RHugin")

      if(category == "chance" && kind == "discrete")
        fading.table <- .Call("RHugin_node_has_fading_table",
                               node.ptrs[node], PACKAGE = "RHugin")


      node.summary[[node]] <- list(category = category, kind = kind,
                                   subtype = subtype, states = states,
                                   evidence.is.entered = evidence.is.entered,
                                   likelihood.is.entered = likelihood.is.entered,
                                   evidence.is.propagated = evidence.is.propagated,
                                   likelihood.is.propagated = likelihood.is.propagated,
                                   experience.table = experience.table,
                                   fading.table = fading.table)
    }
  }

  ans <- list()
  ans[["domain"]] <- domain.summary
  ans[["nodes"]] <- node.summary
  oldClass(ans) <- "summary.RHuginDomain"
  ans
}


