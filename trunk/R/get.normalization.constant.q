get.normalization.constant <- function(domain, log = FALSE)
{
  RHugin.check.args(domain, character(0), character(0),
                   "get.normalization.constant")
  const <- ifelse(log,
                  .Call("RHugin_domain_get_log_normalization_constant",
                         domain$pointer, PACKAGE = "RHugin"),
                  .Call("RHugin_domain_get_normalization_constant",
                         domain$pointer, PACKAGE = "RHugin"))
  RHugin.handle.error()
  const
}


