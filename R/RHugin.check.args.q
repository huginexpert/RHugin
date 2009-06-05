RHugin.check.args <- function(domain, required.nodes, conflicting.nodes,
                              fun.name)
{
  nodes <- get.nodes(domain)

  if(class(domain) != "RHuginDomain")
    stop("in function ", sQuote(fun.name), ": the first argument to ",
          sQuote(fun.name), " does not appear to be an RHugin domain",
          call. = FALSE)

  if(length(required.nodes)) {
    temp <- is.element(required.nodes, nodes)
    if(any(!temp))
      stop("in function ", sQuote(fun.name), ": the following nodes are not ", 
           "in the domain: ", dQuote(required.nodes[!temp]), call. = FALSE)
  }

  if(length(conflicting.nodes)) {
    temp <- is.element(conflicting.nodes, nodes)
    if(any(temp))
      stop("in function ", sQuote(fun.name), ": the following nodes are ",
           "already in the domain:", dQuote(conflicting.nodes[temp]),
            call. = FALSE)
  }
    
  invisible(NULL)
}


