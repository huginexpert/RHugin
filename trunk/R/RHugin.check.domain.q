RHugin.check.domain <- function(domain, fun.name)
{
  if(class(domain) != "RHuginDomain")
    stop(fun.name, ": the ", sQuote("domain"), " argument is not an RHugin domain",
         call. = FALSE)

  if(is.null(.Call("RHugin_R_Nilify_externalptr", domain, PACKAGE = "RHugin")))
    stop(fun.name, ": the ", sQuote("domain"), " argument does not contain a valid Hugin domain",
         call. = FALSE)

  invisible()
}


