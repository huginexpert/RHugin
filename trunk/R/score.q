score <- function(domain, measure = c("log-likelihood", "AIC", "BIC"))
{
  RHugin.check.args(domain, character(0), character(0), "score")
  measure <- match.arg(measure, choices = c("log-likelihood", "AIC", "BIC"),
                       several.ok = TRUE)

  ans <- numeric(length(measure))
  names(ans) <- measure

  if(is.element("log-likelihood", measure))
    ans["log-likelihood"] <- .Call("RHugin_domain_get_log_likelihood", domain,
                                    PACKAGE = "RHugin")

  if(is.element("AIC", measure))
    ans["AIC"] <- .Call("RHugin_domain_get_AIC", domain, PACKAGE = "RHugin")

  if(is.element("BIC", measure))
    ans["BIC"] <- .Call("RHugin_domain_get_BIC", domain, PACKAGE = "RHugin")

  ans
}


