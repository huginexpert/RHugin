hugin.domain <- function(graph, data)
{
  domain <- .Call("RHugin_new_domain", PACKAGE = "RHugin")
  oldClass(domain) <- "RHuginDomain"

  if(!missing(graph) && !missing(data)) {
    if(!is.data.frame(data))
      stop("the ", sQuote("data"), " argument is not a data frame")
    if(!isDirected(graph))
      stop("the ", sQuote("graph"), " argument is not a directed graph")

    node.names <- nodes(graph)
    data.names <- names(data)
    data.names <- intersect(data.names, node.names)
    empty.nodes <- setdiff(node.names, data.names)

    edge.list <- edges(graph)

    for(node in data.names) {
      switch(class(data[[node]])[1],
        "integer" = add.node(domain, name = node,
                             states = as.numeric(sort(unique(data[[node]])))),

        "numeric" = add.node(domain, name = node,
                             states = as.numeric(sort(unique(data[[node]])))),

        "logical" = add.node(domain, name = node, states = c(FALSE, TRUE)),

        {
          x <- as.factor(data[[node]])
          add.node(domain, name = node, states = levels(x))
        }
      )
    }

    for(node in empty.nodes)
      add.node(domain, name = node)

    for(parent in node.names)
      for(child in edge.list[[parent]])
        add.edge(domain, child, parent)

    if(length(empty.nodes) == 0)
      for(node in node.names)
        set.table(domain, node, data = data)
  }

  else if(!missing(graph)) {
    if(!isDirected(graph))
      stop("the ", sQuote("graph"), " argument is not a directed graph")

    node.names <- nodes(graph)
    edge.list <- edges(graph)

    for(node in node.names)
      add.node(domain, name = node)

    for(parent in node.names)
      for(child in edge.list[[parent]])
        add.edge(domain, child, parent)
  }

  else if(!missing(data)) {
    if(!is.data.frame(data))
      stop("the ", sQuote("data"), " argument is not a data frame")

    node.names <- names(data)
    if(length(Freq <- which("Freq" == node.names)))
      node.names <- node.names[-Freq]

    for(node in node.names) {
      switch(class(data[[node]])[1],
        "integer" = add.node(domain, name = node,
                             states = as.numeric(sort(unique(data[[node]])))),

        "numeric" = add.node(domain, name = node,
                             states = as.numeric(sort(unique(data[[node]])))),

        "logical" = add.node(domain, name = node, states = c(FALSE, TRUE)),

        {
          x <- as.factor(data[[node]])
          add.node(domain, name = node, states = levels(x))
        }
      )
    }
  }

  domain
}


 