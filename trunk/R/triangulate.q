triangulate <- function(domain, method = c("clique.size", "clique.weight",
                        "fill.in.size", "fill.in.weight", "total.weight"),
                        order, max.separators = 1e5)
{
  RHugin.check.args(domain, character(0), character(0), "triangulate")
  method = match.arg(method)

  status <- .Call("RHugin_domain_set_max_number_of_separators", domain,
                   as.integer(max.separators), PACKAGE = "RHugin")
  RHugin.handle.error(status)

  if(!missing(order)) {
  }

  else {
  }

  names(.Call("RHugin_domain_get_elimination_order", domain,
               PACKAGE = "RHugin"))
}