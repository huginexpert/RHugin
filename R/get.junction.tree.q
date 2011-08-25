get.junction.tree <- function(domain)
{
  RHugin.check.domain(domain, "get.junction.tree")

  if(!.Call(RHugin_domain_is_triangulated, domain))
    stop("the domain is not triangulated")

  junction.trees <- list()

  jt <- .Call(RHugin_domain_get_first_junction_tree, domain)

  while(!is.null(jt)) {
    junction.trees <- c(junction.trees, list(jt))
    jt <- .Call(RHugin_jt_get_next, jt)
  }

  for(i in 1:length(junction.trees)) {
	  clique.ptrs <- .Call(RHugin_jt_get_cliques, junction.trees[[i]])

	  cliques <- list()
	  neighbors <- list()

	  for(j in 1:length(clique.ptrs)) {
	    cliques[[j]] <- names(.Call(RHugin_clique_get_members, clique.ptrs[[j]]))
	    neighbor.ptrs <- .Call(RHugin_clique_get_neighbors, clique.ptrs[[j]])
      neighbors[[j]] <- match(neighbor.ptrs, clique.ptrs)
	  }

    root <- .Call(RHugin_jt_get_root, junction.trees[[i]])
    root <- match(list(root), clique.ptrs)

    junction.trees[[i]] <- list(cliques = cliques, root = root,
                                neighbors = neighbors)
  }

  junction.trees
}


