score <- function(domain, measure = c("log-likelihood", "AIC", "BIC"))
{
  measure <- match.arg(measure, choices = c("log-likelihood", "AIC", "BIC"),
                       several.ok = TRUE)

  ans <- numeric(length(measure))
  names(ans) <- measure

  if(is.element("log-likelihood", measure))
    ans["log-likelihood"] <- .Call(RHugin_domain_get_log_likelihood, domain)

  if(is.element("AIC", measure))
    ans["AIC"] <- .Call(RHugin_domain_get_AIC, domain)

  if(is.element("BIC", measure))
    ans["BIC"] <- .Call(RHugin_domain_get_BIC, domain)

  ans
}


