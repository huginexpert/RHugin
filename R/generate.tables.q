generate.tables <- function(domain, data, nodes = NULL)
{
  if(is.null(nodes))
    nodes <- get.nodes(domain)

  RHugin.check.args(domain, nodes, character(0), "generate.tables")

  missing.data <- nodes[!is.element(nodes, names(data))]
  if(length(missing.data))
    stop("no data provided for node(s):", dQuote(missing.data))

  if(!is.numeric(data[[length(data)]]))
    data <- cbind(data, Freq = 1)

  for(node in nodes) {
    table.nodes <- get.table.nodes(domain, node)
    status <- set.table(domain, node, condense.data.frame(data, table.nodes))
  }

  invisible(NULL)
}


