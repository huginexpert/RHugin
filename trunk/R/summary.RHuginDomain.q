summary.RHuginDomain <- function(object, nodes = FALSE, ...)
{
  if(is.logical(nodes)) {
    if(nodes)
      nodes <- get.nodes(object)
    else
      nodes <- character(0)
  }

  else
    RHugin.check.args(object, nodes, character(0), "summary.RHuginDomain")


  compiled <- .Call("RHugin_domain_is_compiled", object, PACKAGE = "RHugin")

  equilibrium <- ifelse(.Call("RHugin_domain_equilibrium_is", object,
                              "max", PACKAGE = "RHugin"),
                        "max", "sum")

  evidence.normal <- .Call("RHugin_domain_evidence_mode_is", object,
                           "normal", PACKAGE = "RHugin")

  evidence.fast <- .Call("RHugin_domain_evidence_mode_is", object,
                         "fast", PACKAGE = "RHugin")

  evidence.mode <- c("normal", "fast")[c(evidence.normal, evidence.fast)]

  evidence.propagated <- .Call("RHugin_domain_evidence_is_propagated", object,
                                PACKAGE = "RHugin")

  L.evidence.propagated <- .Call("RHugin_domain_likelihood_is_propagated",
                                  object, PACKAGE = "RHugin")

  GC.evidence.propagated <- .Call("RHugin_domain_cg_evidence_is_propagated",
                                   object, PACKAGE = "RHugin")

  evidence.to.propagate <- .Call("RHugin_domain_evidence_to_propagate",
                                  object, PACKAGE = "RHugin")

  tables.to.propagate <- .Call("RHugin_domain_tables_to_propagate", object,
                                PACKAGE = "RHugin")

  domain.summary <- list(compiled = compiled,
                         equilibrium = equilibrium,
                         evidence.mode = evidence.mode,
                         evidence.propagated = evidence.propagated,
                         L.evidence.propagated = L.evidence.propagated,
                         GC.evidence.propagated = GC.evidence.propagated,
                         evidence.to.propagate = evidence.to.propagate,
                         tables.to.propagate = tables.to.propagate)

  node.summary <- list()

  for(node in nodes) {
    node.ptr <- .Call("RHugin_domain_get_node_by_name", object, node,
                       PACKAGE = "RHugin")
    RHugin.handle.error()

    category <- .Call("RHugin_node_get_category", node.ptr,
                       PACKAGE = "RHugin")
    RHugin.handle.error()

    if(category == "chance" || category == "decision") {
      kind <- .Call("RHugin_node_get_kind", node.ptr, PACKAGE = "RHugin")
      RHugin.handle.error()

      if(kind == "discrete") {
        subtype <- .Call("RHugin_node_get_subtype", node.ptr,
                               PACKAGE = "RHugin")
        RHugin.handle.error()
        states <- get.states(object, node)
      }

      else {
        subtype <- NULL
        states <- NULL
      }
    }

    else {
      kind <- NULL
      subtype <- NULL
      states <- NULL
    }

    evidence.is.entered <- .Call("RHugin_node_evidence_is_entered", node.ptr,
                                  PACKAGE = "RHugin")

    likelihood.is.entered <- .Call("RHugin_node_likelihood_is_entered",
                                    node.ptr, PACKAGE = "RHugin")

    evidence.is.propagated <- .Call("RHugin_node_evidence_is_propagated",
                                     node.ptr, PACKAGE = "RHugin")

    likelihood.is.propagated <- .Call("RHugin_node_likelihood_is_propagated",
                                       node.ptr, PACKAGE = "RHugin")

    experience.table <- .Call("RHugin_node_has_experience_table", node.ptr,
                               PACKAGE = "RHugin")

    fading.table <- .Call("RHugin_node_has_fading_table", node.ptr,
                           PACKAGE = "RHugin")

    node.summary[[node]] <- list(category = category, kind = kind,
                                 subtype = subtype, states = states,
                                 evidence.is.entered = evidence.is.entered,
                                 likelihood.is.entered = likelihood.is.entered,
                                 evidence.is.propagated = evidence.is.propagated,
                                 likelihood.is.propagated = likelihood.is.propagated,
                                 experience.table = experience.table,
                                 fading.table = fading.table)
  }

  ans <- list(node.names = get.nodes(object), edge.list = get.edges(object),
              domain = domain.summary, nodes = node.summary)
  oldClass(ans) <- "summary.RHuginDomain"
  ans
}


