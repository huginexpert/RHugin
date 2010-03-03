learn.cpt <- function(domain, tol = 1e-4, maxit = 0)
{
  RHugin.check.args(domain, character(0), character(0), "learn.cpt")

  .Call("RHugin_domain_set_log_likelihood_tolerance", domain, tol,
         PACKAGE = "RHugin")
  .Call("RHugin_domain_set_max_number_of_em_iterations", domain, maxit,
         PACKAGE = "RHugin")
  .Call("RHugin_domain_learn_tables", domain, PACKAGE = "RHugin")

  invisible()
}


