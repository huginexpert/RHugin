get.normalization.constant <- function(domain, log = FALSE)
{
  ifelse(log,
    .Call(RHugin_domain_get_log_normalization_constant, domain),
    .Call(RHugin_domain_get_normalization_constant, domain))
}


