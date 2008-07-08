generate.nodes <- function(domain, data)
{
  RHugin.check.args(domain, character(0), character(0), "generate.nodes")
  data <- data[sapply(data, is.factor)]
  for(var in names(data))
    status <- add.node(domain, var, states = levels(data[[var]]))
  invisible(NULL)
}


