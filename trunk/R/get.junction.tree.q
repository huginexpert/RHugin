get.junction.tree <- function(domain)
{
  RHugin.check.args(domain, character(0), character(0), "get.junction.tree")

  if(!.Call("RHugin_domain_is_triangulated", domain, PACKAGE = "RHugin"))
    stop("the domain is not triangulated")

  junction.trees <- list()

  jt <- .Call("RHugin_domain_get_first_junction_tree", domain,
               PACKAGE = "RHugin")

  while(!is.null(jt)) {
    junction.trees <- c(junction.trees, list(jt))
    jt <- .Call("RHugin_jt_get_next", jt, PACKAGE = "RHugin")
  }

  for(i in 1:length(junction.trees)) {
	  clique.ptrs <- .Call("RHugin_jt_get_cliques", junction.trees[[i]],
                          PACKAGE = "RHugin")

	  cliques <- list()
	  neighbors <- list()

	  for(j in 1:length(clique.ptrs)) {
	    cliques[[j]] <- names(.Call("RHugin_clique_get_members",
                                        clique.ptrs[[j]], PACKAGE = "RHugin"))
	    neighbor.ptrs <- .Call("RHugin_clique_get_neighbors", clique.ptrs[[j]],
                              PACKAGE = "RHugin")
      neighbors[[j]] <- match(neighbor.ptrs, clique.ptrs)
	  }

    root <- .Call("RHugin_jt_get_root", junction.trees[[i]], PACKAGE = "RHugin")
    root <- match(list(root), clique.ptrs)

    junction.trees[[i]] <- list(root = root, cliques = cliques,
                                neighbors = neighbors)
  }

  junction.trees
}


