learn.cpt <- function(domain, tol = 1e-4, maxit = 0)
{
  RHugin.check.domain(domain, "learn.cpt")

  .Call(RHugin_domain_set_log_likelihood_tolerance, domain, tol)
  .Call(RHugin_domain_set_max_number_of_em_iterations, domain, maxit)
  .Call(RHugin_domain_learn_tables, domain)

  invisible()
}


