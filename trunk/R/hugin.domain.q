hugin.domain <- function()
{
  domain <- list(pointer = .Call("RHugin_new_domain", PACKAGE = "RHugin"))
  oldClass(domain) <- "RHuginDomain"

  if(error.code() != 0) {
    domain <- NULL
    print(error.description(error.code())$description)
  }

  domain
}


